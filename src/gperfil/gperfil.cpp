#include "../../include/gperfil/gperfil.h"
#include "../../include/gperfil/database/themeObjectGenerator.h"
#include "../../include/gperfil/service/viewperfil.h"

Gperfil::Gperfil()
{
    // Construtor padrão da classe Gperfil
}

void Gperfil::playGame()
{
    _viewPerfil.setPlayerService(&playerService);
    _viewPerfil.displayMenu();
    multiPlayer();
}

void Gperfil::multiPlayer()
{
    ScoreboardService scoreboardService = ScoreboardService(playerService.getPlayers());
    _viewPerfil.setScoreboardService(&scoreboardService);

    for (int i = 1; i <= 1; i++)
    {
        numRound = i;
        Rodada currentRound(PONT_RODADA);
        ThemeObjectGenerator objeto_E_tema = ThemeObjectGenerator();
        objeto_E_tema.sortear_objeto();
        std::string tema = objeto_E_tema.get_tema();
        std::string objeto = objeto_E_tema.get_objeto();
        continuar = true;
        round(currentRound, scoreboardService, tema, objeto);
    }
    _viewPerfil.displayRanking(scoreboardService);
}

void Gperfil::round(Rodada &currentRound, ScoreboardService &scoreboardService, std::string tema, std::string objeto)
{
    std::string header = getHeader();

    while (continuar)
    {
        processPlayerTurn(scoreboardService, header, currentRound, tema, objeto);
    }
}

void Gperfil::processPlayerTurn(ScoreboardService &scoreboardService, const std::string header, Rodada &currentRound, std::string tema, std::string objeto)
{
    Player &currentPlayer = playerService.getCurrentPlayer();
    std::vector<std::string> content;

    std::string pergunta = _viewPerfil.displaypergunta(content, getHeader(), tema);
    std::string resposta_chatGPT = currentRound.fazer_pergunta(pergunta, tema, objeto);
    content.clear();
    std::string respostaUsuario = _viewPerfil.displayresposta(content, getHeader(), tema, resposta_chatGPT);
    bool respostaCorreta = currentRound.verificar_resposta_correta(respostaUsuario, objeto);
    updateScore(currentRound, currentPlayer, scoreboardService, respostaUsuario, respostaCorreta);
}

void Gperfil::updateScore(Rodada &x, Player &currentPlayer, ScoreboardService &scoreboardService, std::string respostaUsuario, bool respostaCorreta)
{
    if (respostaCorreta)
    {
        unsigned int currentPlayerId = currentPlayer.getId();
        scoreboardService.changeScore(currentPlayerId, x.get_pontuacao_da_rodada());
        bool acabou = false;
        _viewPerfil.display_resp_correct(respostaUsuario, "correta", acabou);
        playerService.changeCurrentPlayer();
        continuar = false;
    }
    else if (x.verificar_pont_rod_neg_or_zero())
    {
        bool acabou = true;
        _viewPerfil.display_resp_correct(respostaUsuario, "errada", acabou);
        continuar = false;
    }
    else{
        bool acabou = false;
        _viewPerfil.display_resp_correct(respostaUsuario, "errada", acabou);
        playerService.changeCurrentPlayer();
        continuar = true;
    }
}

std::string Gperfil::getHeader()
{
    std::string numString = std::to_string(numRound);
    std::string header = "GPerfil - RODADA " + numString;

    return header;
}
