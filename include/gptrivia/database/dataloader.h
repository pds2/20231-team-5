/**
 * @file dataloader.h
 * @brief Declaração da classe DataLoader.
 */

#ifndef DATALOADER_H
#define DATALOADER_H

#include <map>
using std::map;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "../database/quizcard.h"

/**
 * @brief Exceção lançada quando não é possível abrir o arquivo.
 */
class FileDoesNotOpen : public std::exception{
  public:
    const char* what() const throw() {
      return "Não foi possível abrir o arquivo!";
    }
};

/**
 * @brief Exceção lançada quando a resposta não é encontrada.
 */
class AnswerNotFound : public std::exception{
  public:
    const char* what() const throw() {
      return "Resposta não encontrada!";
    }
};

/**
 * @brief Classe responsável por carregar os dados de um arquivo.
 */
class DataLoader{

  public:
    /**
     * @brief Construtor da classe DataLoader.
     * @param filename O nome do arquivo a ser carregado.
     * @throw FileDoesNotOpen Se não for possível abrir o arquivo.
     */
    DataLoader(const string filename);

    /**
     * @brief Obtém o mapa de cartões.
     * @return O mapa de cartões.
     */
    map<string, vector<QuizCard>> getCardsMap();

  private:
    map<string, vector<QuizCard>> cardsMap;

    /**
     * @brief Verifica se a linha representa um tema.
     * @param line A linha do arquivo.
     * @return true se a linha representa um tema, false caso contrário.
     */
    bool isThemeLine(const string line) const;

    /**
     * @brief Verifica se a linha representa um cartão.
     * @param line A linha do arquivo.
     * @return true se a linha representa um cartão, false caso contrário.
     */
    bool isCardLine(const string line) const;

    /**
     * @brief Extrai o tema de uma linha.
     * @param line A linha do arquivo.
     * @return O tema extraído da linha.
     */
    string extractTheme(const string line);

    /**
     * @brief Extrai um cartão de uma linha.
     * @param line A linha do arquivo.
     * @return O cartão extraído da linha.
     * @throw AnswerNotFound Se a resposta não for encontrada.
     */
    QuizCard extractCard(const string line);

};

#endif