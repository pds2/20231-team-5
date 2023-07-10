/**
 * @file viewmanager.h
 * @brief Declaração da classe ViewManager.
 */

#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "../common/viewgame.h"

/**
 * @brief Enumeração que representa os jogos disponíveis.
 */
enum EnumChoice {
  Trivia, 
  Perfil
};

/**
 * @brief Classe responsável pela visualização que gerencia os jogos.
 */
class ViewManager : public ViewGame{
  
  public:
    /**
     * @brief Construtor da classe ViewManager.
     */
    ViewManager();

    /**
     * @brief Exibe o menu inicial para o usuário e retorna a escolha do jogo.
     * @return A escolha do jogo como um valor da enumeração EnumChoice.
     */
    EnumChoice displayStart();

    bool displayRules() override;

};

#endif
