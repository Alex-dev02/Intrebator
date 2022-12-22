#include "../../include/Utils/InsertFromFileIntoQuestions.hpp"

std::vector<Question*> InsertFromFileIntoQuestionsNum(){
	std::vector<Question*> questionsArray;
	NumericQuestion numQuestion;
	std::ifstream file1("multiple answer questions.txt");
	std::string line;
	int lineNb = 0;

	while(std::getline(file1, line)){
		if(lineNb % 3 == 0){
			numQuestion.SetQuestion(line);
		}
		else if(lineNb % 3 == 1){
			numQuestion.SetAnswer(std::stoi(line));
			questionsArray.emplace_back(numQuestion);
		}
		lineNb++;
	}

	file1.close();
	return questionsArray;
}

std::vector<Question*> InsertFromFileIntoQuestionsMultip(){
	std::vector<Question*> questionsArray;


	return questionsArray;
}
