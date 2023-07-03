#ifndef CARDSERVICE_H
#define CARDSERVICE_H

#include <map>
using std::map;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "../../../include/common/services/ai_service.h"
#include "../database/quizcard.h"

class NoCardsAvailable : public std::exception {
  public:
    const char* what() const throw() {
      return "Não há cartões disponíveis!";
    }
};

class CardService{

  public:
    CardService(AIService* chatGPT, map<string,vector<QuizCard>> cardsMap);
    QuizCard generateCard();
    bool evaluateAnswer(const QuizCard& quizCard, const string userAnswer);
    string getFeedback(const QuizCard& quizCard, const bool isCorrectAnswer);

  private:
    AIService* chatGPT; 
    map<string,vector<QuizCard>> cardsMap; 

    string getRandomTheme() const;
    unsigned int getRandomIndex(const string theme) const;
    void removeCardFromCardsMap(const string theme, const unsigned int index);
    void removeThemeFromCardsMap(const string theme);

};

#endif