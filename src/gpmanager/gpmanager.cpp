#include "../../include/gpmanager/gpmanager.h"
#include "../../include/gptrivia/gptrivia.h"
#include "../../include/gperfil/gperfil.h"

GPManager::GPManager() : viewManager() {
  // Insere os jogos disponíveis no mapa de jogos
  games.insert(std::make_pair<EnumChoice, Game*>(Trivia, new GPTrivia()));
  games.insert(std::make_pair<EnumChoice, Game*>(Perfil, new GPerfil()));
}

GPManager::~GPManager() {
  // Libera a memória dos jogos
  for(auto& game : games) {
    delete game.second;
  }
}

void GPManager::startManager(){
  try {
    while (true) {
      // Exibe o menu inicial e obtém a escolha do usuário
      EnumChoice enumChoice = viewManager.displayStart();
      
      // Inicia o jogo correspondente à escolha do usuário
      games.at(enumChoice)->playGame();
    }
  } catch (const ExitGame &e) {
    // Tratamento da exceção quando o jogador sai do jogo
    cout << "\nEncerrando..." << endl;
  }
}
