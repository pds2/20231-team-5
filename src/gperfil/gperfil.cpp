#include "../../include/gperfil/gperfil.h"

GPerfil::GPerfil(){}

void GPerfil::playGame(){}

// #include "../../include/gperfil/gperfil.h"

// #include "../../include/gperfil/database/themeObjectGenerator.h"
// #include "../../include/gperfil/service/viewperfil.h"


// void Gperfil::Rodada_p(ScoreboardService &scoreboardService)
// {
//     for (int n_rodada = 1; n_rodada <= QNT_RODADA; n_rodada++)
//     {
//         Rodada currentRound(PONT_RODADA);
//         ThemeObjectGenerator objeto_E_tema=ThemeObjectGenerator();
//         objeto_E_tema.sortear_objeto();
//         std::string tema = objeto_E_tema.get_tema();
//         std::string objeto = objeto_E_tema.get_objeto();
//         continuar = true;
//         vez_do_jogador(currentRound, scoreboardService, tema, objeto);
//     }
// }

// Gperfil::Gperfil() : _view(&_playerservice)
// {
// }

// void Gperfil::vez_do_jogador(Rodada &x, ScoreboardService &scoreboardService, std::string tema, std::string objeto)
// {
//     while (continuar)
//     {
//         Player &currentPlayer = _playerservice.getCurrentPlayer();

//         std::cout << "Tema: " << tema << std::endl;
//         std::cout << "Objeto: " << objeto << std::endl;
//         std::cout << "Vez do jogador " << currentPlayer.getId() << ": " << currentPlayer.getName() << std::endl;
//         std::string pergunta{};
//         std::cout << "faça a pergunta:" << std::endl;
//         std::getline(std::cin, pergunta);
//         x.fazer_pergunta(pergunta, tema, objeto);
//         resposta_do_jogador(x, currentPlayer, scoreboardService, objeto);
//     }
// }
// void Gperfil::resposta_do_jogador(Rodada &x, Player &currentPlayer, ScoreboardService &scoreboardService, std::string objeto)
// {
//     std::cout << "Tente acertar:" << std::endl;
//     cin.ignore();
//     std::string respostaUsuario;
//     std::getline(std::cin, respostaUsuario);
//     bool respostaCorreta = x.verificar_resposta_correta(respostaUsuario, objeto);
//     if (respostaCorreta)
//     {
//         // Atribuindo a pontuação da rodada ao jogador
//         unsigned int currentPlayerId = currentPlayer.getId();
//         scoreboardService.changeScore(currentPlayerId, x.get_pontuacao_da_rodada());
//         std::cout << "Resposta correta! Jogador " << currentPlayerId << " ganhou " << x.get_pontuacao_da_rodada() << " pontos." << std::endl;
//         std::cout << "Pressione Enter para continuar...";
//         std::cin.ignore();
//         std::cin.get();
//         _playerservice.changeCurrentPlayer();
//         continuar = false;
//     }
//     else if (x.verificar_pont_rod_neg_or_zero())
//     {
//         std::cout << "A Rodada acabou!!!" << std::endl;
//         std::cout << "Ninguém pontuou" << std::endl;
//         continuar = false;
//     }
//     else
//     {
//         std::cout << "Resposta incorreta!" << std::endl;
//         x.decrease_pontuacao_rodada();
//         _playerservice.changeCurrentPlayer(); // Passa para o próximo jogador
//     }
// }

// void Gperfil::Gperfil_jogo()
// {  std::cout << "Aqui foi 1" << std::endl;
//     _view.displayMenu();
//     ScoreboardService placar = ScoreboardService(_playerservice.getPlayers());
//     _view.setScoreboardService(&placar);
//     Rodada_p(placar);
// }