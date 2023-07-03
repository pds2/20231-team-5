/**
 * @file cardservice.h
 * @brief Declaração da classe CardService.
 */

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

/**
 * @brief Exceção lançada quando não há cartões disponíveis.
 */
class NoCardsAvailable : public std::exception {
  public:
    const char* what() const throw() {
      return "Não há cartões disponíveis!";
    }
};

/**
 * @brief Classe responsável por gerenciar os serviços relacionados aos cartões.
 */
class CardService{

  public:
    /**
     * @brief Construtor da classe CardService.
     * @param chatGPT Ponteiro para o serviço de AI.
     * @param cardsMap Mapa contendo os cartões organizados por tema.
     */
    CardService(AIService* chatGPT, map<string,vector<QuizCard>> cardsMap);

    /**
     * @brief Destrutor padrão da classe CardService.
     */
    ~CardService() = default;

    /**
     * @brief Gera um cartão aleatório.
     * @return O cartão gerado.
     * @throw NoCardsAvailable Se não houver cartões disponíveis.
     */
    QuizCard generateCard();

    /**
     * @brief Avalia a resposta do usuário para um cartão.
     * @param quizCard O cartão a ser avaliado.
     * @param userAnswer A resposta fornecida pelo usuário.
     * @return true se a resposta estiver correta, false caso contrário.
     */
    bool evaluateAnswer(const QuizCard& quizCard, const string userAnswer);

    /**
     * @brief Obtém o feedback com base na resposta do usuário para um cartão.
     * @param quizCard O cartão.
     * @param isCorrectAnswer Indica se a resposta do usuário está correta.
     * @return O feedback correspondente à resposta do usuário.
     */
    string getFeedback(const QuizCard& quizCard, const bool isCorrectAnswer);

  private:
    AIService* chatGPT; 
    map<string,vector<QuizCard>> cardsMap; 

    /**
     * @brief Obtém um tema aleatório.
     * @return O tema aleatório selecionado.
     */
    string getRandomTheme() const;

    /**
     * @brief Obtém um índice aleatório dentro do vetor de cartões de um tema específico.
     * @param theme O tema dos cartões.
     * @return O índice aleatório selecionado.
     */
    unsigned int getRandomIndex(const string theme) const;

    /**
     * @brief Remove um cartão do mapa de cartões com base no tema e índice fornecidos.
     * @param theme O tema do cartão.
     * @param index O índice do cartão no vetor.
     */
    void removeCardFromCardsMap(const string theme, const unsigned int index);

    /**
     * @brief Remove um tema do mapa de cartões.
     * @param theme O tema a ser removido.
     */
    void removeThemeFromCardsMap(const string theme);

};

#endif