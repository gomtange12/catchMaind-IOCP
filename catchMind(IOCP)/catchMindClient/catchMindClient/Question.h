#pragma once
#include "Singleton.h"
class Question :public Singleton<Question>
{
private:
	string question;
public:
	void renderQuestion(HDC hdc);

	inline void changeQuestion(string ques) { question = ques; };
	inline void removeQuestion() { question.clear(); };
};

