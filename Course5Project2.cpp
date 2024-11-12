#include <iostream>

using namespace std;

enum enLevel { Easy = 1, Mid = 2, Hard = 3, MixedLevel = 4 };
enum enOpType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixedOp = 5 };

struct stQuestion
{
	enLevel QuestionLevel;
	enOpType QuestionOpType;
	short Number1 = 0;
	short Number2 = 0;
	short CorrectAnswer = 0;
	short UserAnswer = 0;
	bool IsCorrect = false;
};

struct stQuizz
{
	stQuestion QuestionsList[100];
	enLevel QuizzLevel;
	enOpType QuizzOpType;
	short NumberOfQuestions = 0;
	short NumberOfCorrectAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool IsPass = false;
};

int RandomNumber(int From, int To)
{

	int RandomNum = rand() % (To - From + 1) + From;

	return RandomNum;
}

void ClearScreen()
{
	system("cls");
	system("color 0F");
}

short ReadnumberOfQuestions()
{

	short NumberOfQuestions = 0;

	do
	{
		cout << "How mamy questions do you want to answer?\n";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;
}

enLevel ReadQuizzLevel()
{
	short QuizzLevel = 0;

	do
	{
		cout << "Choice quizz level [1]Easy [2]Mid [3]Hard [4]Mix\n";
		cin >> QuizzLevel;

	} while (QuizzLevel < 1 || QuizzLevel > 4);

	return (enLevel)QuizzLevel;
}

enOpType ReadQuizzOpType()
{
	short QuizzOpType = 0;

	do
	{
		cout << "Choce operation type : [1]Add [2]Sub [3]Mult [4]Div [5]Mix \n";
		cin >> QuizzOpType;
	} while (QuizzOpType < 1 || QuizzOpType > 5);
	return (enOpType)QuizzOpType;
}

short SimpleCalculater(short Number1, short Number2, enOpType OpType)
{

	switch (OpType)
	{
	case Add:
		return Number1 + Number2;
		break;

	case Sub:
		return Number1 - Number2;
		break;

	case Mult:
		return Number1 * Number2;
		break;

	case Div:
		return Number1 / Number2;
		break;
	}

}

stQuestion GenerateQuestion(enLevel QuizzLevel, enOpType QuizzOpType)
{

	stQuestion Question;

	if (QuizzLevel == enLevel::MixedLevel)
	{
		QuizzLevel = (enLevel)RandomNumber(1, 3);
	}

	if (QuizzOpType == enOpType::MixedOp)
	{
		QuizzOpType = (enOpType)RandomNumber(1, 4);
	}

	Question.QuestionOpType = QuizzOpType;

	switch (QuizzLevel)
	{
	case Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.QuestionOpType);
		Question.QuestionLevel = QuizzLevel;
		return Question;
		break;

	case Mid:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.QuestionOpType);
		Question.QuestionLevel = QuizzLevel;
		return Question;
		break;

	case Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.QuestionOpType);
		Question.QuestionLevel = QuizzLevel;
		return Question;
		break;
	}

	return Question;

}

void GenerateQuestions(stQuizz& Quizz)
{

	for (short Questions = 0; Questions <= Quizz.NumberOfQuestions - 1; Questions++)
	{
		Quizz.QuestionsList[Questions] = GenerateQuestion(Quizz.QuizzLevel, Quizz.QuizzOpType);
	}

}

string GetOpTypeAsText(enOpType OpType)
{
	switch (OpType)
	{
	case Add:
		return "+";
		break;

	case Sub:
		return "-";
		break;

	case Mult:
		return "X";
		break;

	case Div:
		return "/";
		break;

	case MixedOp:
		return "Mix";
		break;

	default:
		return "+";
		break;
	}
}

void PrintQuestin(stQuizz Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question Number [" << QuestionNumber + 1 << " / " << Quizz.NumberOfQuestions << "]\n";
	cout << Quizz.QuestionsList[QuestionNumber].Number1 << "\n";
	cout << "\n";
	cout << "\t";
	cout << GetOpTypeAsText(Quizz.QuestionsList[QuestionNumber].QuestionOpType) << "\n";
	cout << Quizz.QuestionsList[QuestionNumber].Number2 << "\n";
	cout << "----------\n";
}

short ReadUserAnswer()
{
	short UserAnswer = 0;
	cin >> UserAnswer;
	return UserAnswer;
}

void ChangeScreenColor(bool Pass)
{
	if (Pass)
	{
		system("Color 2F");
	}
	else
	{
		system("Color 4F");
		cout << "\a";
	}
}

void CorrectUesrAnswer(stQuizz& Quizz, short QuestionNumber)
{

	if (Quizz.QuestionsList[QuestionNumber].CorrectAnswer != Quizz.QuestionsList[QuestionNumber].UserAnswer)
	{
		Quizz.NumberOfWrongAnswers++;
		Quizz.QuestionsList[QuestionNumber].IsCorrect = false;
		cout << "Wrong answer :-(\n";
		cout << "Correct answer is : ";
		cout << Quizz.QuestionsList[QuestionNumber].CorrectAnswer;
	}
	else
	{
		Quizz.NumberOfCorrectAnswers++;
		Quizz.QuestionsList[QuestionNumber].IsCorrect = true;
		cout << "RightAnswer :-)\n";
	}

	cout << "\n";

	ChangeScreenColor(Quizz.QuestionsList[QuestionNumber].IsCorrect);
}

void AskUesrAndCorrectAnswer(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber <= Quizz.NumberOfQuestions - 1; QuestionNumber++)
	{
		PrintQuestin(Quizz, QuestionNumber);

		Quizz.QuestionsList[QuestionNumber].UserAnswer = ReadUserAnswer();

		CorrectUesrAnswer(Quizz, QuestionNumber);
	}

	Quizz.IsPass = (Quizz.NumberOfCorrectAnswers >= Quizz.NumberOfWrongAnswers);

}

string CheckIsPass(bool IsPass)
{
	if (IsPass)
	{
		return "Pass :-)";
	}
	else
	{
		return "Fail :-(";
	}
}

string GetLevelAsText(enLevel Level)
{
	switch (Level)
	{
	case Easy:
		return "Easy";
		break;

	case Mid:
		return "Mid";
		break;

	case Hard:
		return "Hard";
		break;

	case MixedLevel:
		return "Mix";
		break;
	}
}

void PrintFinalResult(stQuizz& Quizz)
{
	cout << "\n--------------------\n";
	cout << CheckIsPass(Quizz.IsPass);
	cout << "\n--------------------\n";
	cout << "Number of questions         : " << Quizz.NumberOfQuestions << "\n";
	cout << "Number of currect answers   : " << Quizz.NumberOfCorrectAnswers << "\n";
	cout << "Number of wrong answers     : " << Quizz.NumberOfWrongAnswers << "\n";
	cout << "Quizz Level                 : " << GetLevelAsText(Quizz.QuizzLevel) << "\n";
	cout << "Quizz operation type        : " << GetOpTypeAsText(Quizz.QuizzOpType) << "\n";
	ChangeScreenColor(Quizz.IsPass);
}

void PlayMathGame()
{

	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadnumberOfQuestions();
	Quizz.QuizzLevel = ReadQuizzLevel();
	Quizz.QuizzOpType = ReadQuizzOpType();

	GenerateQuestions(Quizz);
	AskUesrAndCorrectAnswer(Quizz);

	PrintFinalResult(Quizz);

}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{

		ClearScreen();
		PlayMathGame();

		cout << "\nDo you want to play again [Y] [N] ?\n";

		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}