#pragma once
#include "Singleton.h"
class Question : public Singleton<Question>
{
private:
	std::vector<std::string> question;
public:
	void			initQuestion();
	std::string		selectRandomQuestion();
};

