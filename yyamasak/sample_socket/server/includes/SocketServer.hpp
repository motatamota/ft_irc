#ifndef __SOCKETSERVER_HPP__
#define __SOCKETSERVER_HPP__

#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <cstdio>
#include <cerrno>
#include <sstream>
#include <utility>

#include "Parser.hpp"
#include "RefCounted.h"
#include "IntrusivePtr.h"

#define BUFFER_SIZE 512
#define MAX_CLIENTS 10

class Parser;

struct ClientInfo
{
	std::string nick;
	std::string user;
	bool hasNick;
	bool hasUser;
	bool registered;
	bool isLoggedIn;
};

class SocketServer
{
private:
	int server_fd_;
	int port_;
	std::string password_;
	std::vector<struct pollfd> poll_fds_;
	std::map<int, std::string> message_buffer_;
	IntrusivePtr<Parser>	parser;
	void setNonBlocking(int fd);
	bool initServer();
	void handleNewConnection();
	std::string receiveMessage(int fd);
	void registerClient(int client_fd);
	void handleClientMessage(size_t index);
	void closeClient(size_t index);

public:
	SocketServer(int port, const std::string &password);
	~SocketServer();
	void start();
	void cleanUp();
};
#endif