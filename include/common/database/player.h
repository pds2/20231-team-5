/**
 * @file player.h
 * @brief Este arquivo contém a declaração da classe Player.
 */

#ifndef PLAYER
#define PLAYER

#include <string>

using namespace std;

/**
 * @brief Exceção lançada quando o nome do jogador é inválido (com mais de 15 caracteres).
 */
class InvalidNameException : public exception {
    public:
        virtual const char* what() const throw() {
            return "Nome inválido";
        }
};

/**
 * @brief A classe Player representa um jogador no jogo.
 */
class Player{
    private:
        unsigned int id;
        string name;
        bool is_playing;

    public :
        /**
         * @brief Constrói um novo objeto Player. NÃO DEVE SER USADO DIRETAMENTE, caso queira
         * construir um novo jogador use o metodo addPlayer da classe PlayerService.
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

        /**
         * @brief Verifica se o jogador está jogando.
         * @return true se o jogador está jogando, false caso contrário.
         */
        bool isPlaying();

        /**
         * @brief Elimina o jogador do jogo.
         */
        void eliminate();
};

#endif