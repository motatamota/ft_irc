#include "MessageTranslator.h"

MessageTranslator::MessageTranslator()
{
	func_["UNKNOWN"] = &Unknown;
	func_["PASS"] = &Pass;
	func_["NICK"] = &Nick;
	func_["USER"] = &User;
}

MessageTranslator::MessageTranslator(const MessageTranslator& other)
{

}

MessageTranslator& MessageTranslator::operator=(const MessageTranslator& other)
{

}

MessageTranslator::~MessageTranslator()
{

}

std::vector<std::string> MessageTranslator::Translate(std::string str)
{
	std::vector<std::string>	box;
	std::stringstream			ss(str);
	std::string					tmp;

	while (ss >> tmp)
		box.push_back(tmp);
	return (box);
}

void	MessageTranslator::Execute(std::string message, int user_fd)
{
	std::vector<std::string> box;

	box = Translate(message);
	if (func_.find(box[0]) == func_.end())
	{
		(this->*(func_["UNKNOWN"]))(box, user_fd);
		return ;
	}
	(this->*(func_[box[0]]))(box, user_fd);
}

ChannelResult	MessageTranslator::MessageTranslator::Unknown(std::vector<std::string>, int)
{
	return (ChannelResult(1, ""));
}

ChannelResult	MessageTranslator::MessageTranslator::Pass(std::vector<std::string> av, int player_fd)
{
	if (av.size() == 1)
		return (ChannelResult(ERR_NEEDMOREPARAMS, ""));
	return (ChannelResult(1, ""));
}

ChannelResult	MessageTranslator::MessageTranslator::Nick(std::vector<std::string> av, int player_fd)
{
	return (ChannelResult(1, ""));
}

ChannelResult	MessageTranslator::MessageTranslator::User(std::vector<std::string> av, int player_fd)
{
	return (ChannelResult(1, ""));
}
ChannelResult	MessageTranslator::Server(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Oper(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Quit(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Squit(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Join(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Part(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Mode(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Topic(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Names(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::List(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Invite(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Kick(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Version(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Stats(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Links(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Time(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Connect(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Trace(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Admin(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Info(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Privmsg(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Notice(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Who(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Whois(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Whowas(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Kill(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Ping(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Pong(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Error(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Away(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Rehash(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Restart(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Summon(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Users(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Wallops(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
ChannelResult	MessageTranslator::Userhost(std::vector<std::string> av, int player_fd) {
	return ChannelResult();
}
