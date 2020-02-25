#include "pch.h"
#include "Question.h"
#include <random>
void Question::initQuestion()
{
	std::string line;
	std::ifstream in("info\\QUESTION_INFO.txt");
	while (getline(in, line)) {
		question.push_back(line);
	}
	in.close();
}

std::string Question::selectRandomQuestion()
{
	std::default_random_engine dre(GetTickCount());
	std::uniform_int_distribution<int> ui(0, (int)question.size());

	int randNum = ui(dre);
	return question[randNum];
}
