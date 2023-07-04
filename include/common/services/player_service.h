/**
 * @file player_service.h
 * @brief Este arquivo contém a declaração da classe PlayerService, que é responsável por gerenciar os jogadores do jogo.
 */

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
 * @brief Classe de exceção lançada quando o id especificado não corresponde a nenhum jogador.
 * 
 */
class InvalidPlayerException : public exception {
    public:
        virtual const char* what() const throw() {
            return "Jogador inválido!";
        }
};

/**
 * @brief Classe de exceção lançada quando o número máximo de jogadores é atingido.
 * 
 */
class PlayerOverloadException : public exception {
    public:
        virtual const char* what() const throw() {
            return "Número máximo de jogadores atingido!";
        }
};

/**
 * @brief Classe responsável por gerenciar os jogadores do jogo.
 */
class PlayerService{
    private:
        vector<Player> players;
        unsigned int current_player_id;

    public:
        /**
         * @brief Construtor da classe PlayerService.
         */
        PlayerService();

        /**
         * @brief Adiciona um novo jogador ao vetor de jogadores.
         * @param name Nome do jogador a ser adicionado.
         */
        void addPlayer(string name);

        /**
         * @brief Remove o jogador com o id especificado.
         * @param id Id do jogador a ser removido.
         * @throws NoPlayersException Exceção lançada quando não há jogadores cadastrados.
         * @throws InvalidPlayerException Exceção lançada quando o id especificado não corresponde a nenhum jogador.
         */
        void removePlayer(unsigned int id);

        /**
         * @brief Retorna o jogador com o id especificado.
         * @param id Id do jogador a ser retornado.
         * @throws InvalidPlayerException Exceção lançada quando o id especificado não corresponde a nenhum jogador.
         * @return Player& Referência para o jogador com o id especificado.
         */
        Player& getPlayer(unsigned int id);

        /**
         * @brief Retorna o vetor de jogadores.
         * @return vector<Player*> Vetor de jogadores.
         */
        vector<Player*> getPlayers();

        /**
         * @brief Retorna o jogador atual.
         * @throws NoPlayersException Exceção lançada quando não há jogadores cadastrados.
         * @return Player& Referência para o jogador atual.
         */
        Player& getCurrentPlayer();

        /**
         * @brief Muda o jogador atual para o próximo jogador na lista de jogadores.
         * Por padrão o jogador atual será o próximo da lista. Caso o jogador atual seja o último da lista, 
         * o primeiro jogador da lista será o novo jogador atual.
         * Essa classe pode ser sobrescrita para implementar um comportamento diferente do padrão.
         * @throws NoPlayersException Exceção lançada quando não há jogadores cadastrados.
         */
        virtual void changeCurrentPlayer();
        
        /**
         * @brief Retorna o número máximo de jogadores.
         * @return unsigned int Número máximo de jogadores.
         */
        unsigned int getMaxPlayerNb();
};

#endif
