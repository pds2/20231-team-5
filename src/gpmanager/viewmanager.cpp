#include "../../include/gpmanager/viewmanager.h"

ViewManager::ViewManager() : ViewGame("GPjogos") {}

EnumChoice ViewManager::displayStart() {
  vector<string> content{}; // Cria um vetor vazio de strings para armazenar o conteúdo

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
      return Trivia; // Retorna a escolha do jogo "GPTrivia"
    case 'p':
      return Perfil; // Retorna a escolha do jogo "GPerfil"
    case 'r':
      loopAgain = displayRules(); // Exibe as regras 
      break;
    case 'x':
      throw ExitGame(); // Lança uma exceção para sair do jogo
    }
  }
}

bool ViewManager::displayRules(){ 
  vector<string> content=vector<string>(); // Cria um vetor vazio de strings para armazenar o conteúdo

  addToNextLine(content,"1 - Bem-vindo ao GPjogos! Voce pode escolher entre dois jogos emocionantes para se desafiar com seus amigos: GPTrivia e GPerfil."); 
  addEmptyLines(content,1); 
  addToNextLine(content,"2 - No GPTrivia, voce tera que responder perguntas de diferentes categorias. Teste seu conhecimento e veja quantas perguntas voce consegue acertar!"); 
  addEmptyLines(content,1); 
  addToNextLine(content,"3 - No GPerfil, você terá Você terá que desvendar um objeto sorteado fazendo perguntas ao ChatGPT para obter pistas. Mas atenção: quanto menos perguntas fizer, maior será a sua pontuação quando acertar! Desafie seus amigos neste emocionante desafio de adivinhação e prove que você tem o que eh preciso para ser o grande vencedor!");
  addEmptyLines(content,1); 
  addToNextLine(content,"4 - Ambos os jogos permitem de 2 a 4 jogadores. Reuna seus amigos e divirtam-se juntos!"); 
  addEmptyLines(content,2); 
  addToNextLine(content,"Voltar ----------------------- V"); 

  while(true){ 
    char userChoice = getUserChoice(content, "REGRAS"); // Obtém a escolha do usuário

    if(userChoice=='v') return true; // Retorna true se o usuário escolher voltar
  }
}