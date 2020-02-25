#pragma once
#include "Singleton.h"
class Login : public Singleton <Login>
{
private:
	std::vector<std::string> loginInfo;
	std::vector<std::string> alreadyNickName;
public:
	void			initLoginInfo();
	bool			checkAlreadyId(std::string id);
	std::string		findAndLoingInfoApply(std::string id, std::string pw);
	void			logoutDisconnectId(std::string id);
};

