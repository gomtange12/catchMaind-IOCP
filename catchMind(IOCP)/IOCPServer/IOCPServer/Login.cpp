#include "pch.h"
#include "Login.h"


void Login::initLoginInfo()
{
	std::string line;
	std::ifstream in("info\\LOGIN_INFO.txt");
	while (getline(in, line)) {
		loginInfo.push_back(line);
	}
	in.close();
}
bool Login::checkAlreadyId(std::string id) {
	for (auto iter : alreadyNickName) {
		if (iter == id)
			return true;
	}
	return false;
}
std::string Login::findAndLoingInfoApply(std::string id, std::string pw)
{
	std::string nickName={"#Unknown"};

	for (auto iter = loginInfo.begin(); iter != loginInfo.end(); ++iter) {
		if ((*iter) == id) {
			if ((*++iter) == pw) {
				nickName.clear();
				++iter;
				nickName = (*iter);
				if (checkAlreadyId(nickName))
					return "#Unknown";
				alreadyNickName.push_back(nickName);
				return nickName;
			}
		}
	}
	return nickName;
}
void Login::logoutDisconnectId(std::string id) {
	for (auto iter = alreadyNickName.begin(); iter != alreadyNickName.end(); ) {
		if ((*iter) == id) {
			iter = alreadyNickName.erase(iter);
		}
		else
			++iter;
	}
}
