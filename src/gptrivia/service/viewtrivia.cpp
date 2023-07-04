#include <cctype>

#include "../../../include/gptrivia/service/viewtrivia.h"

ViewTrivia::ViewTrivia(PlayerService* player_service) : View(player_service) {} 

GameType ViewTrivia::displayMenu(const string header){
  vector<string> content{}; // Cria um vetor vazio de strings para armazenar o conteúdo

  addEmptyLines(content,1);
  addToNextLine(content,"Bem vindo ao "+header+". Digite a opção desejada!"); 
  addEmptyLines(content,5);
  addToNextLine(content,"SINGLEPLAYER ----------------- S");
  addEmptyLines(content,1);
  addToNextLine(content,"MULTIPLAYER ------------------ M");
  addEmptyLines(content,1);
  addToNextLine(content,"REGRAS ----------------------- R");
  addEmptyLines(content,1);
  addToNextLine(content,"SAIR ------------------------- X");

  bool loopAgain{true}; // Controla o loop do menu
  GameType gameType{}; // Armazena o tipo de jogo selecionado

  while(loopAgain){
    char userChoice=getUserChoice(content,header); // Obtém a escolha do usuário

    switch (userChoice)
    {
    case 'S':
      loopAgain=displaySinglePlayer(gameType); // Exibe o menu para o jogo singleplayer
      break;
    case 'M':
      loopAgain=displayMultiPlayer(gameType); // Exibe o menu para o jogo multiplayer
      break;
    case 'R':
      loopAgain=displayRules(); // Exibe as regras do jogo
      break;
    case 'X':
      throw ExitGame(); // Lança uma exceção para sair do jogo
    }
  }

  return gameType;
}

bool ViewTrivia::displayRules(){ 
  vector<string> content=vector<string>(); // Cria um vetor vazio de strings para armazenar o conteúdo

  addToNextLine(content,"1 - Fusce finibus tristique dui. Nullam est ligula, vestibulum iniaculis et, rutrum nec tortor. Lorem ipsum dolor sit amet, consectetur."); 
  addEmptyLines(content,1); 
  addToNextLine(content,"2 - Fusce finibus tristique dui. Nullam est ligula, vestibulum iniaculis et, rutrum nec tortor. Lorem ipsum dolor sit amet, consectetur."); 
  addEmptyLines(content,1); 
  addToNextLine(content,"3 - Fusce finibus tristique dui. Nullam est ligula, vestibulum iniaculis et, rutrum nec tortor. Lorem ipsum dolor sit amet, consectetur."); 
  addEmptyLines(content,2); 
  addToNextLine(content,"VOLTAR ----------------------- V"); 

  while(true){ 
    char userChoice=getUserChoice(content,"REGRAS"); // Obtém a escolha do usuário

    if(userChoice=='V') return true; // Retorna true se o usuário escolher voltar
  }
}

bool ViewTrivia::displaySinglePlayer(GameType& roundType){ 
  vector<string> content=vector<string>(); // Cria um vetor vazio de strings para armazenar o conteúdo

  string username=getUsername(content); // Obtém o nome de usuário do jogador

  addEmptyLines(content,1); 
  addToNextLine(content,"INICIAR ---------------------- I"); 
  addEmptyLines(content,1); 
  addToNextLine(content,"VOLTAR ----------------------- V");

  while(true){
    char userChoice=getUserChoice(content, "SINGLEPLAYER"); // Obtém a escolha do usuário

    switch (userChoice)
    {
    case 'I':
      player_service->addPlayer(username); // Adiciona o jogador ao serviço de jogadores
      roundType=SinglePlayer; // Define o tipo de jogo como singleplayer
      return false; // Retorna false para indicar que o jogo deve começar
      break;
    case 'V':
      return true; // Retorna true para indicar que o usuário escolheu voltar
    }
  }
}

bool ViewTrivia::displayMultiPlayer(GameType& roundType){ 
  vector<string> content=vector<string>(); // Cria um vetor vazio de strings para armazenar o conteúdo

  unsigned int numPlayers=getNumberOfPlayers(); // Obtém o número de jogadores
  vector<string> usernamesList=getUsernamesList(content,numPlayers); // Obtém a lista de usernames dos jogadores

  addEmptyLines(content,1); 
  addToNextLine(content,"INICIAR ---------------------- I"); 
  addEmptyLines(content,1); 
  addToNextLine(content,"VOLTAR ----------------------- V"); 

  while(true){ 
    char userChoice=getUserChoice(content,"MULTIPLAYER"); // Obtém a escolha do usuário

    switch(userChoice)
    {
      case 'I':
        for(std::string x:usernamesList) player_service->addPlayer(x); // Adiciona os jogadores ao serviço de jogadores
        roundType=MultiPlayer; // Define o tipo de jogo como multiplayer
        return false; // Retorna false para indicar que o jogo deve começar
      case 'V':
        return true; // Retorna true para indicar que o usuário escolheu voltar
    }
  }
}

string ViewTrivia::displayQuestion(const QuizCard& userCard, std::vector<string>& content, const string header){ 
  addToNextLine(content,userCard.getQuestion()); 
  addEmptyLines(content,2);

  std::string userAnswer{};
  while(true){
    userAnswer=getUserAnswer(content, header); // Obtém a resposta do usuário

    // Verifica se a resposta contém o caractere '\' e continua solicitando uma resposta se conter
    if(userAnswer.find('\\') == std::string::npos) break;
  }

  // Adiciona a resposta do usuário ao conteúdo
  addToNextLine(content,"SUA RESPOSTA: ");
  addToCurrentLine(content,userAnswer);
  addEmptyLines(content,1);
  // Adiciona uma linha separadora ao conteúdo
  addToNextLine(content,"--------------------------------------");
  addToCurrentLine(content,"-------------------------------------");
  addEmptyLines(content,1);

  return userAnswer; 
}

void ViewTrivia::displayFeedback(const string feedback, std::vector<string>& content, const string header){
  addToNextLine(content,feedback);
  addEmptyLines(content,2);

  getUserEnter(content, header);
}

void ViewTrivia::getUserEnter(const vector<string>& content, const string header){
  setHeader(header);
  setContent(content);

  while(true){
    string userEnter=display("--ENTER--"); // Exibe a mensagem "--ENTER--" e aguarda a entrada do usuário
    if(userEnter.empty()) break; // Se o usuário pressionar apenas Enter, sai do loop
  }
}

char ViewTrivia::getUserChoice(const vector<string>& content, const string header){
  setHeader(header); 
  setContent(content);

  string userChoice{};
  while(true){
    userChoice=display("Sua escolha: "); // Exibe a mensagem "Sua escolha: " e obtém a entrada do usuário
    if(userChoice.size()==1) break; // Verifica se foi inserido apenas um caractere
  }

  return toupper(userChoice[0]); // Converte o caractere para maiúsculo e retorna
}

string ViewTrivia::getUserAnswer(const vector<string>& content, const string header){ 
  setHeader(header); 
  setContent(content);

  string userAnswer{};
  while(true){
    userAnswer=display("Sua resposta: "); // Exibe a mensagem "Sua resposta: " e obtém a resposta do usuário
    if(!userAnswer.empty()) break; // Verifica se a resposta não está vazia
  }

  return userAnswer;
}

unsigned int ViewTrivia::getNumberOfPlayers(){ 
  vector<string> content{};

  addEmptyLines(content,1);
  addToNextLine(content,"Digite o número de jogadores: (máximo 4):");

  unsigned int numPlayers{};
  while(true){
    try{
      string numString=getUserAnswer(content,"MULTIPLAYER"); // Obtém a entrada do usuário
      numPlayers=std::stoi(numString); // Tenta converter a entrada para um número inteiro
      if(numPlayers>4||numPlayers<=1) throw InvalidNumber(); // Lança uma exceção se o número estiver fora do intervalo válido
      break;
    }catch(const std::exception& e){
      // Continua solicitando um número válido caso ocorra uma exceção
    }
  }

  return numPlayers; 
}

string ViewTrivia::getUsername(vector<string>& content) {
  addEmptyLines(content, 1);
  addToNextLine(content, "Username (máximo 15 caracteres): ");

  string username{};
  while (true) {
    try {
      username = getUserAnswer(content, "SINGLEPLAYER"); // Obtém a resposta do usuário
      if (username.size() > 15) throw InvalidNameException(); // Lança uma exceção se o nome de usuário exceder o limite de caracteres
      break;
    } catch (const std::exception& e) {
      // Continua solicitando um nome de usuário válido caso ocorra uma exceção
    }
  }

  addToCurrentLine(content, username);
  addEmptyLines(content, 1);

  return username;
}

vector<string> ViewTrivia::getUsernamesList(vector<string>& content, int numPlayers) {
  addEmptyLines(content, 1);
  addToNextLine(content, "Adicione os usernames dos jogadores (máximo 15 caracteres).");
  addEmptyLines(content, 2);

  vector<string> usernamesList{}; // Armazena os nomes de usuários de jogadores
  usernamesList.reserve(numPlayers);

  // Loop para obter o nome de usuário de cada jogador
  for (int i = 1; i <= numPlayers; i++) {
    string numString = to_string(i);
    addToNextLine(content, numString + "º jogador: ");

    string username{};
    while (true) {
      try {
        username = getUserAnswer(content, "MULTIPLAYER"); // Obtém a resposta do usuário
        if (username.size() > 15) throw InvalidNameException(); // Lança uma exceção se o nome de usuário exceder o limite de caracteres
        break;
      } catch (const std::exception& e) {
        // Continua solicitando um nome de usuário válido caso ocorra uma exceção
      }
    }

    addToCurrentLine(content, username);
    addEmptyLines(content, 1);

    usernamesList.push_back(move(username)); // Adciona o nome de usuário na lista de usuários de jogadores
  }

  return usernamesList;
}

void ViewTrivia::addEmptyLines(vector<string>& content, unsigned int numberOfLines){
  while(numberOfLines>0){
    content.push_back("");
    numberOfLines--;
  }
}

void ViewTrivia::addToNextLine(vector<string>& content, const string newContent){
  content.push_back(newContent);
}

void ViewTrivia::addToCurrentLine(vector<string>& content, const string newContent){
  unsigned int index=content.size()-1;
  content[index]+=newContent;
}