#ifndef GPERFIL_H
#define GPERFIL_H

#include "service/rodada.h"
#include "../common/services/player_service.h"
#include "../common/services/scoreboard_service.h"
#include "../../include/gperfil/service/viewperfil.h"
#include "../../include/common/game.h"

/**
 * @brief Classe Gperfil que representa o jogo GPerfil.
 */
class Gperfil : public Game
{
private:
    const int PONT_RODADA = 22;
    const int QNT_RODADA = 5;

    PlayerService playerService;
    ViewPerfil _viewPerfil;
    int numRound{0};
    bool continuar = true;


public:
    /**
     * @brief Construtor padrão da classe Gperfil.
     */
    Gperfil();

    /**
     * @brief Função para iniciar o jogo GPerfil.
     */
    void playGame() override;
    void resetData();

    /**
     * @brief Processa a vez de um jogador.
     *
     * @param scoreboardService O serviço de placar do jogo.
     * @param header O cabeçalho da rodada atual.
     * @param currentRound A rodada atual.
     * @param tema O tema atual.
     * @param objeto O objeto atual.
     */
    void processPlayerTurn(ScoreboardService &scoreboardService, const std::string header, Rodada &currentRound, std::string tema, std::string objeto);

    /**
     * @brief Função para jogar o modo multiplayer do jogo GPerfil.
     */
    void multiPlayer();

    /**
     * @brief Realiza uma rodada do jogo GPerfil.
     *
     * @param currentRound A rodada atual.
     * @param scoreboardService O serviço de placar do jogo.
     * @param tema O tema atual.
     * @param objeto O objeto atual.
     */
    void round(Rodada &currentRound, ScoreboardService &scoreboardService, std::string tema, std::string objeto);

    /**
     * @brief Atualiza a pontuação do jogador e verifica o fim da rodada.
     *
     * @param x A rodada atual.
     * @param currentPlayer O jogador atual.
     * @param scoreboardService O serviço de placar do jogo.
     * @param respostaUsuario A resposta do jogador.
     * @param respostaCorreta Indica se a resposta do jogador está correta.
     */
    void updateScore(Rodada &x, Player &currentPlayer, ScoreboardService &scoreboardService, std::string respostaUsuario, bool respostaCorreta);

    /**
     * @brief Obtém o cabeçalho da rodada atual.
     *
     * @return O cabeçalho da rodada atual.
     */
    std::string getHeader();
};

#endif // GPERFIL_H