/**
 * @file game.h
 * @brief Declaração da classe Game.
 */

#ifndef GAME_H
#define GAME_H

#include "services/scoreboard_service.h"

/**
 * @brief Classe abstrata que representa um jogo.
 */
class Game{

  public:
    /**
     * @brief Executa o jogo.
     */
    virtual void playGame() = 0;

};

#endif
