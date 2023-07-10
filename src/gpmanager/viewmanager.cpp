#include "../../include/gpmanager/viewmanager.h"

ViewManager::ViewManager() : ViewGame("GPjogos") {}

EnumChoice ViewManager::displayStart() {
  vector<string> content{};

  addEmptyLines(content, 1);
  addToNextLine(content, "Selecione o jogo que deseja se aventurar!");
  addEmptyLines(content, 5);
  addToNextLine(content, "GPTrivia --------------------- G");
  addEmptyLines(content, 1);
  addToNextLine(content, "GPerfil ---------------------- P");
  addEmptyLines(content, 1);
  addToNextLine(content, "Regras ----------------------- R");
  addEmptyLines(content, 1);
  addToNextLine(content, "Sair ------------------------- X");

  bool loopAgain{true};
  while (loopAgain) {
    char userChoice = getUserChoice(content, gameName);

    switch (userChoice)
    {
    case 'g':
      return Trivia;
    case 'p':
      return Perfil;
    case 'r':
      loopAgain = displayRules();
    case 'x':
      throw ExitGame();
    }
  }
}

bool ViewManager::displayRules() {
  
}