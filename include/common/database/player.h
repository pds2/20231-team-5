/**
 * @file player.h
 * @brief Este arquivo contém a declaração da classe Player.
 */

#ifndef PLAYER
#define PLAYER

#include <string>

using namespace std;

/**
 * @brief A classe Player representa um jogador no jogo.
 */
class Player{
    private:
        unsigned int id;
        string name;

    public :
        /**
         * @brief Constrói um novo objeto Player.
         * @param id O ID do jogador.
         * @param name O nome do jogador.
         */
        Player(unsigned int id, string name);

        /**
         * @brief Obtém o ID do jogador.
         * @return O ID do jogador.
         */
        unsigned int getId();

        /**
         * @brief Obtém o nome do jogador.
         * @return O nome do jogador.
         */
        string getName();
};

#endif