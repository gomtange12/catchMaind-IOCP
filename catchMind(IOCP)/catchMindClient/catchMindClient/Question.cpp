#include "stdafx.h"
#include "Question.h"


void Question::renderQuestion(HDC hdc)
{
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, 469, 142, question.c_str(), (int)question.length());
}
