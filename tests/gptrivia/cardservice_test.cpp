#include "../../include/gptrivia/service/cardservice.h"
#include "../../include/third_party/doctest/doctest.h"

TEST_CASE("Test constructor"){
  map<string,vector<QuizCard>> cardsMap{};
  AIService chatGPT=AIService("");
  CHECK_NOTHROW(CardService(&chatGPT,cardsMap));
}

TEST_CASE("Test NoCardAvailable"){
  map<string,vector<QuizCard>> cardsMap{};
  AIService chatGPT=AIService("");
  CardService cardService=CardService(&chatGPT,cardsMap);
  CHECK_THROWS_AS(cardService.generateCard(),NoCardsAvailable);
}