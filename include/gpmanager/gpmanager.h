/**
 * @file gamemanager.h
 * @brief Declaração da classe GPManager.
 */

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <map>
using std::map;

#include "../../include/gpmanager/viewmanager.h"
#include "../common/game.h"

/**
 * @brief Classe responsável por gerenciar os jogos.
 */
class GPManager{

  public:
    /**
     * @brief Construtor da classe GPManager.
     */
    GPManager();

    /**
     * @brief Destrutor da classe GPManager.
     */
    ~GPManager();

    /**
     * @brief Inicia o gerenciador de jogos.
     */
    void startManager();
  
  private:
    map<EnumChoice, Game*> games;
    ViewManager viewManager;

};

#endif
