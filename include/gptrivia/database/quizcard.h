#ifndef QUIZCARD_H
#define QUIZCARD_H

#include <string>
using std::string;

class QuizCard{

  public:
    QuizCard() = default;
    QuizCard(const string question, const string answer);
    ~QuizCard() = default;
    string getAnswer() const;
    string getQuestion() const;

  private:
    string question;
    string answer;

};

#endif