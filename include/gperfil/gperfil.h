
#ifndef GPERFIL_H
#define GPERFIL_H

#include "service/rodada.h"
#include "../common/services/player_service.h"
#include "../common/services/scoreboard_service.h"
#include "../../include/gperfil/service/viewperfil.h"

const int PONT_RODADA = 20;
const int QNT_RODADA = 2;

class Gperfil
{

private:
    PlayerService _playerservice;

    ViewPerfil _view;

    void vez_do_jogador(Rodada &x, ScoreboardService &scoreboardService,std::string tema, std::string objeto);

    void resposta_do_jogador(Rodada &x, Player &currentPlayer, ScoreboardService &scoreboardService, std::string objeto);

    bool continuar = true;

public:
    void Rodada_p(ScoreboardService &scoreboardService);

    void Gperfil_jogo();

    void iniciarview();

    Gperfil();
};

#endif