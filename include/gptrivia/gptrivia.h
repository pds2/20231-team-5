/**
 * @file gptrivia.h
 * @brief Declaração da classe GPTrivia.
 */

#ifndef GPTRIVIA_H
#define GPTRIVIA_H

#include <string>
using std::string;

#include "../../include/common/services/ai_service.h"
#include "../../include/common/services/event_service.h"
#include "../../include/common/game.h"
#include "database/dataloader.h"
#include "service/cardservice.h"
#include "service/viewtrivia.h"

/**
 * @brief Classe que representa o jogo de trivia.
 */
class GPTrivia : public Game{

  public:
    /**
     * @brief Construtor da classe GPTrivia.
     */
    GPTrivia();

    /**
     * @brief Inicia o jogo.
     */
    void playGame() override;

  private:
    static const unsigned int numberOfRounds = 10;
    static const unsigned int defaultScore = 10;
    unsigned int numRound;

    DataLoader dataLoader;
    AIService chatGPT;
    CardService cardService;
    PlayerService playerService;
    ViewTrivia viewTrivia;
    EventService eventService;

    /**
     * @brief Executa as rodadas do jogo.
     */
    void runGameRounds();

    /**
     * @brief Executa uma rodada do jogo.
     * @param scoreboardService O serviço de pontuação.
     */
    void round(ScoreboardService& scoreboardService);

    /**
     * @brief Realiza a vez do jogador durante uma rodada.
     * @param scoreboardService O serviço de pontuação.
     * @param header O cabeçalho a ser exibido durante a vez do jogador.
     */
    void playerTurn(ScoreboardService& scoreboardService, const string header);

    /**
     * @brief Atualiza a pontuação do jogador com base no tempo de resposta e na correção da resposta.
     * @param userTime O tempo de resposta do jogador.
     * @param scoreboardService O serviço de pontuação.
     * @param isCorrectAnswer Flag indicando se a resposta do jogador está correta.
     */
    void updateScore(const unsigned int userTime, ScoreboardService& scoreboardService, const bool isCorrectAnswer);

    /**
     * @brief Reinicia os dados do jogo para uma nova partida.
     */
    void resetData();

    /**
     * @brief Obtém o cabeçalho para exibição durante uma rodada.
     * @return O cabeçalho.
     */
    string getHeader();

};

#endif
