#pragma once

#include "Everyone.h"
#include "RefCounted.h"
#include "IntrusivePtr.h"
#include "ErrorCode.h"

#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <climits>

#define LIMIT_MEMBER 10000
#define MOD_INVITE 1	//0d00001
#define MOD_TOPIC 2		//0d00010
#define MOD_KEYWORD 4	//0d00100
#define MOD_OPERATOR 8	//0d01000
#define MOD_LIMITED 16	//0d10000

class Everyone;

struct ChannelInfo
{
	int						channel_id;
	std::string				channel_name;
	std::string				password;
	std::string				topic;
	int						mode;
	std::set<std::string>	joined_plyer;
	std::set<std::string>	is_master;
	int						limit_member;
};

class Channel : public RefCounted
{
private:
	static IntrusivePtr<Channel>		instance_;
	std::map<std::string, ChannelInfo>	channels_;
	std::map<int, std::string>			channels_itos_;
	long								latest_channel_id_;

	Channel();
	Channel(const Channel &);
	Channel &operator=(const Channel &);

public:
	~Channel();

	static IntrusivePtr<Channel>	GetInstance();
	pair<int, std::string>			CreateChannel(const std::string& name, const std::string &player_str, int mode);
	pair<int, std::string>			DeleteChannel(const std::string& channel_str);
	pair<int, std::string>			GetChannelInfo(const std::string& channel_str, ChannelInfo &dest) const;
	pair<int, std::string>			InviteToChannel(const std::string &player_str, const std::string &focas_user_str, const std::string& channel_str);
	pair<int, std::string>			JoinedChannel(const std::string &player_str, const std::string& channel_str, int flag = 0);
	pair<int, std::string>			LeaveChannel(const std::string &player_str, const std::string& channel_str);
	pair<int, std::string>			KickChannel(const std::string &player_str, const std::string &focas_user_str, const std::string& channel_str);
	pair<int, std::string>			ChangeTopic(const std::string &player_str, const std::string& channel_str, const std::string &topic);
	pair<int, std::string>			AddMaster(const std::string &player_str, const std::string &focas_user_str, const std::string& channel_str);
	pair<int, std::string>			DeleteMaster(const std::string &player_str, const std::string &focas_user_str, const std::string& channel_str);
	pair<int, std::string>			ChangeMode(const std::string &player_str, int mode, bool valid, const std::string& channel_str);
	pair<int, std::string>			SendMessageToChannel(const std::string &player_str, const std::string& channel_str);

	bool							ExistChannel(const std::string& channel_str) const;
	bool							IsOperator(const std::string &player_str, const std::string& channel_str) const;
	bool							IsJoined(const std::string &player_str, const std::string& channel_str) const;
};

