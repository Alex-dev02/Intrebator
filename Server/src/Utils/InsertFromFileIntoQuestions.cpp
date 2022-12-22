#include "../../include/Utils/InsertFromFileIntoQuestions.hpp"

std::vector<Question*> InsertFromFileIntoQuestionsNum(){
	std::vector<Question*> questionsArray;
	NumericQuestion numQuestion;
	std::ifstream file1("multiple_answer_questions.txt");
	if(not file1.is_open()){
		std::printf("the file hasnt been found..");
	}
	std::string line;
	int lineNb = 0;
	while(lineNb < 3){   // ignore introductory lines
		std::getline(file1, line);
		lineNb++;
	}

	while(std::getline(file1, line)){
		if(lineNb % 3 == 0){
			numQuestion.SetQuestion(line);
		}
		else if(lineNb % 3 == 1){
			numQuestion.SetAnswer(std::stoi(line));
			questionsArray.emplace_back(&numQuestion);
		}
		lineNb++;
	}

	file1.close();
	return questionsArray;
}

std::vector<Question*> InsertFromFileIntoQuestionsMultip(){
	std::vector<Question*> questionsArray;
	MultipleAnswerQuestion multipQuestion;
	std::ifstream file1("numeric_questions.txt");
	if(not file1.is_open()){
		std::printf("the file hasnt been found..");
	}
	std::string line;
	int lineNb = 0;
	while(lineNb < 6){    // ignore introductory lines
		std::getline(file1, line);
		lineNb++;
	}

	while(std::getline(file1, line)){
		if(lineNb % 6 == 0){
			multipQuestion.SetQuestion(line);
		}
		if(lineNb % 6 == 1){
			multipQuestion.SetFirstAnswer(line);
		}
		if(lineNb % 6 == 2){
			multipQuestion.SetSecondAnswer(line);
		}
		if(lineNb % 6 == 3){
			multipQuestion.SetThirdAnswer(line);
		}
		if(lineNb % 6 == 4){
			multipQuestion.SetCorrectAnswer(line);
			questionsArray.emplace_back(&multipQuestion);
		}
		lineNb++;
	}

	file1.close();
	return questionsArray;
}
