#include "../includes/SocketServer.hpp"

void SocketServer::setNonBlocking(int fd) {
	fcntl(fd, F_SETFL, O_NONBLOCK);
}

bool SocketServer::initServer() {
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ == -1) {
        perror("socket");
        return false;
    }

    int opt = 1;
    setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_);

    if (bind(server_fd_, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        return false;
    }

    if (listen(server_fd_, MAX_CLIENTS) == -1) {
        perror("listen");
        return false;
    }

    setNonBlocking(server_fd_);

    struct pollfd pfd;
    pfd.fd = server_fd_;
    pfd.events = POLLIN;
    pfd.revents = 0;
    poll_fds_.push_back(pfd);

    std::cout << "Server listening on port " << port_ << "...\n";

    return true;
}


void SocketServer::handleNewConnection() {
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_fd = accept(server_fd_, (struct sockaddr *)&client_addr, &client_len);
	struct pollfd pfd;

	if (client_fd < 0) {
		perror("accept");
		return;
	}
	setNonBlocking(client_fd);
	pfd.fd = client_fd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	poll_fds_.push_back(pfd);
#ifdef DEBUG
	std::cout << "New client connected: " << inet_ntoa(client_addr.sin_addr)
			  << ":" << ntohs(client_addr.sin_port) << "\n";
#endif
}

std::string SocketServer::receiveMessage(int fd) {
    std::string message;
    int bytesRead;
    char buffer[BUFFER_SIZE + 1];

    while (true) {
        memset(buffer, 0, BUFFER_SIZE + 1);
        bytesRead = recv(fd, buffer, BUFFER_SIZE, 0);
        if (bytesRead < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                break;
            } else {
                perror("recv");
                break;
            }
        } else if (bytesRead == 0) {
            break;
        }
        buffer[bytesRead] = '\0';
        message.append(buffer);
        if (message.find('\n') != std::string::npos) {
            break;
        }
    }
#ifdef DEBUG
    std::cout << "Received: " << message;
#endif
    return message;
}

void SocketServer::handleClientMessage(size_t& index) {
    int client_fd = poll_fds_[index].fd;
    std::string message = receiveMessage(client_fd);

    if (message.empty()) {
        message_buffer_[client_fd].clear();
        closeClient(index);
        return;
    }
    message_buffer_[client_fd] += message;
    std::string &buffer = message_buffer_[client_fd];
    size_t pos;
    while ((pos = buffer.find('\n')) != std::string::npos) {
        std::string line = buffer.substr(0, pos);
        buffer.erase(0, pos + 1);
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1, 1);
        }
        translator_->Execute(line, client_fd);
    }
}

void SocketServer::closeClient(size_t& index)
{
	// std::cout << "Client disconnected: FD " << poll_fds_[index].fd << "\n";
	close(poll_fds_[index].fd);
    Everyone::GetInstance()->DeleteUser(poll_fds_[index].fd);
	// poll_fds_.erase(poll_fds_.begin() + index);
}

SocketServer::SocketServer(int port, const std::string &password) : port_(port), password_(password), server_fd_(-1), translator_(new MessageTranslator(password)){
    everyone_ = Everyone::GetInstance();
}

SocketServer::~SocketServer(){
    delete translator_;
	cleanUp();
}

void SocketServer::start() {
	if (!initServer()) {
		return;
	}
	while (true) {
        std::vector<int> indices_to_remove;
		int ret = poll(poll_fds_.data(), poll_fds_.size(), -1);
		if (ret < 0) {
			perror("poll");
			break;
		}
		for (size_t i = 0; i < poll_fds_.size(); i++) {
			if (poll_fds_[i].revents & POLLIN) {
				if (poll_fds_[i].fd == server_fd_) {
					handleNewConnection();
				} else {
					handleClientMessage(i);
                    if ((message_buffer_[poll_fds_[i].fd].size() == 0) && !(everyone_->IsCreated(poll_fds_[i].fd))) {
                        indices_to_remove.push_back(i);
                    }
				}
			}

		}
        for (std::vector<int>::reverse_iterator it = indices_to_remove.rbegin();
            it != indices_to_remove.rend(); ++it) {
#ifdef DEBUG
            std::cout << "Client disconnected: FD " << poll_fds_[*it].fd << "\n";
            close(poll_fds_[*it].fd);
#endif
            poll_fds_.erase(poll_fds_.begin() + *it);
        }
	}
}

void SocketServer::cleanUp() {
	for (size_t i = 0; i < poll_fds_.size(); i++) {
		close(poll_fds_[i].fd);
	}
	std::cout << "Server shutdown.\n";
}
