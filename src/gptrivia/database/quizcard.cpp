#include "../../../include/gptrivia/database/quizcard.h"

QuizCard::QuizCard(const string question, const string answer) : question(question), answer(answer){}

string QuizCard::getAnswer() const{
  return answer;
}

string QuizCard::getQuestion() const{
  return question;
}