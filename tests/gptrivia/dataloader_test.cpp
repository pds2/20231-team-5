#include "../../include/gptrivia/database/dataloader.h"
#include "../../include/third_party/doctest/doctest.h"
#include <sstream>
#include <fstream>

TEST_CASE("DataLoader - Teste de leitura de arquivo") {
    // Preparação
    std::stringstream input;
    input << "Tema: Esporte\n";
    input << "Pergunta: Quem venceu a Copa do Mundo de 2018? Resposta: França\n";
    input << "Tema: História\n";
    input << "Pergunta: Qual foi o ano do descobrimento do Brasil? Resposta: 1500\n";

    std::ifstream in_file;
    std::ofstream tempFile("temp.txt");
    tempFile << input.rdbuf(); // Salva o conteúdo do stringstream no arquivo temporário
    tempFile.close();

    // Execução
    DataLoader loader = DataLoader("temp.txt");

    // Verificação
    const auto& cardsMap = loader.getCardsMap();
    CHECK(cardsMap.size() == 2);

    CHECK(cardsMap.count("Esporte") == 1);
    CHECK(cardsMap.count("História") == 1);

    const auto& sportCards = cardsMap.at("Esporte");
    CHECK(sportCards.size() == 1);
    CHECK(sportCards[0].getQuestion() == "Quem venceu a Copa do Mundo de 2018? ");
    CHECK(sportCards[0].getAnswer() == "França");

    const auto& historyCards = cardsMap.at("História");
    CHECK(historyCards.size() == 1);
    CHECK(historyCards[0].getQuestion() == "Qual foi o ano do descobrimento do Brasil? ");
    CHECK(historyCards[0].getAnswer() == "1500");

    // exclui o arquivo temporário
    std::remove("temp.txt");
}

TEST_CASE("DataLoader - Teste de exceção ao abrir arquivo") {
    // Execução e Verificação
    CHECK_THROWS_AS(DataLoader loader(""), FileDoesNotOpen);
}

TEST_CASE("DataLoader - Teste de exceção ao extrair card sem resposta") {
    // Preparação
    std::stringstream input;
    input << "Tema: Esporte\n";
    input << "Pergunta: Quem venceu a Copa do Mundo de 2018?\n";
    // Resposta ausente

    std::ifstream in_file;
    std::ofstream tempFile("temp.txt");
    tempFile << input.rdbuf(); // Salva o conteúdo do stringstream no arquivo temporário
    tempFile.close();

    // Execução e Verificação
    CHECK_THROWS_AS(DataLoader("temp.txt"), AnswerNotFound);

    // exclui o arquivo temporário
    std::remove("temp.txt");
} 