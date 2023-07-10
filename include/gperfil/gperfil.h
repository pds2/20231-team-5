#ifndef GPERFIL_H
#define GPERFIL_H

#include "service/rodada.h"
#include "../common/services/player_service.h"
#include "../common/services/scoreboard_service.h"
#include "../../include/gperfil/service/viewperfil.h"
#include "../../include/common/game.h"


const int PONT_RODADA = 10;
const int QNT_RODADA = 2;

class Gperfil : public Game
{

const int PONT_RODADA = 22;
const int QNT_RODADA = 2;

private:
    PlayerService playerService;

    ViewPerfil _viewPerfil;

    int numRound{0};

    bool continuar = true;

public:

    Gperfil();
    
    void playGame() override;
    void processPlayerTurn(ScoreboardService &scoreboardService, const string header, Rodada &currentRound, std::string tema, std::string objeto);
    void multiPlayer();
    void round(Rodada &currentRound, ScoreboardService &scoreboardService, std::string tema, std::string objeto);
    void updateScore(Rodada &x, Player &currentPlayer, ScoreboardService &scoreboardService, std::string respostaUsuario, bool respostaCorreta);
    string getHeader();

};

#endif
