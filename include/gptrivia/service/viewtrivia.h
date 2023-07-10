/**
 * @file viewtrivia.h
 * @brief Declaração da classe ViewTrivia.
 */

#ifndef VIEWTRIVIA_H
#define VIEWTRIVIA_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "../../../include/common/viewgame.h"
#include "../database/quizcard.h"

/**
 * @brief Classe responsável pela visualização do jogo de Trivia.
 */
class ViewTrivia : public ViewGame{

  private:
    bool displayRules() override;

  public:
    /**
     * @brief Construtor da classe ViewTrivia.
     */
    ViewTrivia();

    /**
     * @brief Exibe uma pergunta para o jogador e retorna a resposta juntamente com o tempo de resposta.
     * @param userCard O cartão de perguntas a ser exibido.
     * @param content Um vetor de strings contendo o conteúdo da interface.
     * @param header O cabeçalho a ser exibido acima do conteúdo.
     * @return Um par contendo a resposta do jogador (string) e o tempo de resposta (unsigned int).
     */
    std::pair<string, unsigned int> displayQuestion(const QuizCard& userCard, std::vector<string>& content, const string header);

    /**
     * @brief Exibe o feedback para a resposta do jogador.
     * @param feedback O feedback a ser exibido.
     * @param content Um vetor de strings contendo o conteúdo da interface.
     * @param header O cabeçalho a ser exibido acima do conteúdo.
     */
    void displayFeedback(const string feedback, std::vector<string>& content, const string header);
};

#endif
