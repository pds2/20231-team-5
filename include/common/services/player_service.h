#ifndef PLAYER_SERVICE
#define PLAYER_SERVICE

#include <string>
#include <vector>
#include "../database/player.h"

using namespace std;

/**
 * @brief Classe de exceção lançada quando não há jogadores cadastrados.
 * 
 */
class NoPlayersException : public exception {
    public:
        virtual const char* what() const throw() {
            return "Não há jogadores cadastrados!";
        }
};

/**
 * @brief Classe responsável por gerenciar os jogadores do jogo.
 * 
 */
class PlayerService{
    private:
        vector<Player> players;
        unsigned int current_player_id;

    public:
        /**
         * @brief Construtor da classe PlayerService.
         * 
         */
        PlayerService();

        /**
         * @brief Adiciona um novo jogador ao vetor de jogadores.
         * 
         * @param name Nome do jogador a ser adicionado.
         */
        void addPlayer(string name);

        /**
         * @brief Retorna o jogador com o id especificado.
         * 
         * @param id Id do jogador a ser retornado.
         * @return Player& Referência para o jogador com o id especificado.
         */
        Player& getPlayer(unsigned int id);

        /**
         * @brief Retorna o jogador atual.
         * 
         * @return Player& Referência para o jogador atual.
         */
        Player& getCurrentPlayer();

        /**
         * @brief Muda o jogador atual para o próximo jogador na lista de jogadores.
         * Por padrão o jogador atual será o próximo da lista. Caso o jogador atual seja o último da lista, 
         * o primeiro jogador da lista será o novo jogador atual.
         * Essa classe pode ser sobrescrita para implementar um comportamento diferente do padrão.
         */
        virtual void changeCurrentPlayer();
};

#endif