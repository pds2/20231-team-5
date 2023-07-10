#include "../../include/gptrivia/database/quizcard.h"
#include "../../include/third_party/doctest/doctest.h"

TEST_CASE("QuizCard - Teste de construtor e getters") {
    // Preparação
    std::string question = "Qual é a capital do Brasil?";
    std::string answer = "Brasília";

    // Execução
    QuizCard card(question, answer);

    // Verificação
    CHECK(card.getQuestion() == question);
    CHECK(card.getAnswer() == answer);
}