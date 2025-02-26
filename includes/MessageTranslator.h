#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <utility>

#include "ErrorCode.h"

class MessageTranslator
{
private:
	std::string pass_;
	std::map<std::string, ChannelResult (MessageTranslator::*)(std::vector<std::string>, int)> func_;

	std::vector<std::string>	Translate(std::string str);
	ChannelResult				Unknown(std::vector<std::string> av, int player_fd);
	ChannelResult				Pass(std::vector<std::string> av, int player_fd);
	ChannelResult				Nick(std::vector<std::string> av, int player_fd);
	ChannelResult				User(std::vector<std::string> av, int player_fd);
	ChannelResult				Server(std::vector<std::string> av, int player_fd);
	ChannelResult				Oper(std::vector<std::string> av, int player_fd);
	ChannelResult				Quit(std::vector<std::string> av, int player_fd);
	ChannelResult				Squit(std::vector<std::string> av, int player_fd);
	ChannelResult				Join(std::vector<std::string> av, int player_fd);
	ChannelResult				Part(std::vector<std::string> av, int player_fd);
	ChannelResult				Mode(std::vector<std::string> av, int player_fd);
	ChannelResult				Topic(std::vector<std::string> av, int player_fd);
	ChannelResult				Names(std::vector<std::string> av, int player_fd);
	ChannelResult				List(std::vector<std::string> av, int player_fd);
	ChannelResult				Invite(std::vector<std::string> av, int player_fd);
	ChannelResult				Kick(std::vector<std::string> av, int player_fd);
	ChannelResult				Version(std::vector<std::string> av, int player_fd);
	ChannelResult				Stats(std::vector<std::string> av, int player_fd);
	ChannelResult				Links(std::vector<std::string> av, int player_fd);
	ChannelResult				Time(std::vector<std::string> av, int player_fd);
	ChannelResult				Connect(std::vector<std::string> av, int player_fd);
	ChannelResult				Trace(std::vector<std::string> av, int player_fd);
	ChannelResult				Admin(std::vector<std::string> av, int player_fd);
	ChannelResult				Info(std::vector<std::string> av, int player_fd);
	ChannelResult				Privmsg(std::vector<std::string> av, int player_fd);
	ChannelResult				Notice(std::vector<std::string> av, int player_fd);
	ChannelResult				Who(std::vector<std::string> av, int player_fd);
	ChannelResult				Whois(std::vector<std::string> av, int player_fd);
	ChannelResult				Whowas(std::vector<std::string> av, int player_fd);
	ChannelResult				Kill(std::vector<std::string> av, int player_fd);
	ChannelResult				Ping(std::vector<std::string> av, int player_fd);
	ChannelResult				Pong(std::vector<std::string> av, int player_fd);
	ChannelResult				Error(std::vector<std::string> av, int player_fd);
	ChannelResult				Away(std::vector<std::string> av, int player_fd);
	ChannelResult				Rehash(std::vector<std::string> av, int player_fd);
	ChannelResult				Restart(std::vector<std::string> av, int player_fd);
	ChannelResult				Summon(std::vector<std::string> av, int player_fd);
	ChannelResult				Users(std::vector<std::string> av, int player_fd);
	ChannelResult				Wallops(std::vector<std::string> av, int player_fd);
	ChannelResult				Userhost(std::vector<std::string> av, int player_fd);

public:
	MessageTranslator();
	MessageTranslator(const MessageTranslator& other);
	MessageTranslator& operator=(const MessageTranslator& other);
	~MessageTranslator();

	void	Execute(std::string message, int user_fd);
};
