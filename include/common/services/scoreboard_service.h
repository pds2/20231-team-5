/**
 * @file scoreboard_service.h
 * @brief Este arquivo contém a declaração da classe ScoreboardService, que é responsável por gerenciar o placar de jogadores em um jogo.
 */

#ifndef SCOREBOARD_SERVICE
#define SCOREBOARD_SERVICE

#include <map>
#include <vector>
#include "../database/player.h"

using namespace std;

/**
 * @brief Exceção lançada quando um jogador não existe no placar.
 */
class PlayerDoesNotExistException : public exception {
    public:
        virtual const char* what() const throw() {
            return "Jogador não existe";
        }
};

/**
 * @brief A classe ScoreboardService é responsável por gerenciar o placar de jogadores em um jogo.
 */
class ScoreboardService {
    private:
        map<unsigned int, double> scoreboard; // <player_id, score>

        static bool compareInts(int a, int b);

    public:
        /**
         * @brief Constrói um novo objeto ScoreboardService.
         * @param players Um vetor de objetos Player a serem adicionados ao placar.
         */
        ScoreboardService(vector<Player*> players);

        /**
         * @brief Altera a pontuação de um jogador no placar.
         * @param player_id O ID do jogador cuja pontuação será alterada.
         * @param delta_score A quantidade pela qual a pontuação será alterada.
         * @throws PlayerDoesNotExistException se o jogador não existir no placar.
         */
        void changeScore(unsigned int player_id, double delta_score);

        /**
         * @brief Obtém a pontuação de um jogador no placar.
         * @param player_id O ID do jogador cuja pontuação será recuperada.
         * @throws PlayerDoesNotExistException se o jogador não existir no placar.
         * @return A pontuação do jogador.
         */
        double getScore(unsigned int player_id);
        
        /**
         * @brief Obtém o ranking de jogadores no placar.
         * @return Um vetor de IDs de jogadores, ordenados por suas pontuações em ordem decrescente.
         */
        vector<unsigned int> getRanking();

        /**
         * @brief Obtém o ID do jogador com a maior pontuação no placar.
         * @return O ID do jogador com a maior pontuação.
         */
        unsigned int getWinner();
};
#endif