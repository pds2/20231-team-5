#include "../../include/gptrivia/service/cardservice.h"
#include "../../include/third_party/doctest/doctest.h"


TEST_CASE("CardService - Teste do construtor") {
    // Preparação
    std::map<std::string, std::vector<QuizCard>> cardsMap;
    AIService chatGPT = AIService("");

    // Execução e Verificação
    CHECK_NOTHROW(CardService(&chatGPT, cardsMap));
}

TEST_CASE("CardService - Teste de exceção NoCardsAvailable") {
    // Preparação
    std::map<std::string, std::vector<QuizCard>> cardsMap;
    AIService chatGPT = AIService("");
    CardService cardService(&chatGPT, cardsMap);

    // Execução e Verificação
    CHECK_THROWS_AS(cardService.generateCard(), NoCardsAvailable);
}

TEST_CASE("CardService - Teste de geração de cartão aleatório") {
    // Preparação
    AIService chatGPT = AIService("");
    std::map<std::string, std::vector<QuizCard>> cardsMap;
    std::vector<QuizCard> themeCards1 = {
      QuizCard("Pergunta 1", "Resposta 1"),
      QuizCard("Pergunta 2", "Resposta 2")
    };
    std::vector<QuizCard> themeCards2 = {
      QuizCard("Pergunta 3", "Resposta 3"),
      QuizCard("Pergunta 4", "Resposta 4")
    };
    cardsMap["Tema 1"] = themeCards1;
    cardsMap["Tema 2"] = themeCards2;

    CardService cardService(&chatGPT, cardsMap);

    // Execução
    QuizCard randomCard = cardService.generateCard();

    // Verificação
    CHECK(cardsMap.size() == 2);
    CHECK(cardsMap["Tema 1"].size() == 2);
    CHECK(cardsMap["Tema 2"].size() == 2);
}

TEST_CASE("CardService - Teste de avaliação de resposta correta") {
    // Preparação
    AIService chatGPT = AIService("");
    std::map<std::string, std::vector<QuizCard>> cardsMap;
    CardService cardService(&chatGPT, cardsMap);
    QuizCard quizCard("Pergunta", "RespostaCorreta");

    // Execução e Verificação
    CHECK(cardService.evaluateAnswer(quizCard, "RespostaCorreta") == true);
}

TEST_CASE("CardService - Teste de avaliação de resposta incorreta") {
    // Preparação
    AIService chatGPT = AIService("");
    std::map<std::string, std::vector<QuizCard>> cardsMap;
    CardService cardService(&chatGPT, cardsMap);
    QuizCard quizCard("Pergunta", "RespostaCorreta");

    // Execução e Verificação
    CHECK(cardService.evaluateAnswer(quizCard, "RespostaErrada") == false);
}