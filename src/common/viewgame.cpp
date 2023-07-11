#include "../../include/common/viewgame.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>

ViewGame::ViewGame(string gameName) : gameName(gameName) {}

void ViewGame::displayMenu(){
  vector<string> content{}; // Cria um vetor vazio de strings para armazenar o conteúdo

  addEmptyLines(content, 1);
  addToNextLine(content, "Bem vindo ao " + gameName + ". Digite a opcao desejada!");
  addEmptyLines(content, 6);
  addToNextLine(content, "Iniciar ---------------------- I");
  addEmptyLines(content, 1);
  addToNextLine(content, "Regras ----------------------- R");
  addEmptyLines(content, 1);
  addToNextLine(content, "Sair ------------------------- X");

  bool loopAgain{true}; // Controla o loop do menu
  while (loopAgain) {
    char userChoice = getUserChoice(content, gameName); // Obtém a escolha do usuário

    switch (userChoice)
    {
    case 'i':
      loopAgain = displayConfig(); // Configura o jogo
      break;
    case 'r':
      loopAgain = displayRules(); // Exibe as regras do jogo
      break;
    case 'x':
      throw ExitGame(); // Lança uma exceção para sair do jogo
    }
  }
}

bool ViewGame::displayConfig(){ 
  vector<string> content=vector<string>(); // Cria um vetor vazio de strings para armazenar o conteúdo

  unsigned int numPlayers = getNumberOfPlayers(); // Obtém o número de jogadores
  vector<string> usernamesList = getUsernamesList(content, numPlayers); // Obtém a lista de usernames dos jogadores

  addEmptyLines(content, 1); 
  addToNextLine(content, "Continuar -------------------- C"); 
  addEmptyLines(content, 1); 
  addToNextLine(content, "Voltar ----------------------- V"); 

  while (true) { 
    char userChoice = getUserChoice(content, gameName); // Obtém a escolha do usuário

    switch (userChoice)
    {
      case 'c':
        for(std::string x:usernamesList) player_service -> addPlayer(x); // Adiciona os jogadores ao serviço de jogadores
        return false; // Retorna false para indicar que o usuário escolheu continuar
      case 'v':
        return true; // Retorna true para indicar que o usuário escolheu voltar
    }
  }
}

void ViewGame::displayRanking(ScoreboardService& scoreboardService){
  vector<string> content = vector<string>(); // Cria um vetor vazio de strings para armazenar o conteúdo

  buildRanking(scoreboardService, content); // Constrói o ranking
  removeScoreboardService(); // Remove o serviço de pontuação

  addEmptyLines(content, 2); 
  addToNextLine(content, "GPjogos ---------------------- J"); 
  addEmptyLines(content, 1); 
  addToNextLine(content, "Sair ------------------------- X");
  
  bool loopAgain{true};
  while (loopAgain) {
    char userChoice = getUserChoice(content, "RESULTADOS"); // Obtém a escolha do usuário

    switch (userChoice)
    {
    case 'j':
      loopAgain = false; // Retorna false para indicar que o usuário escolheu voltar
      break;
    case 'x':
      throw ExitGame(); // Lança uma exceção para sair do jogo
    }
  }
}

void ViewGame::buildRanking(ScoreboardService& scoreboardService, vector<string>& content){
  vector<unsigned int> idRanking = scoreboardService.getRanking(); // Obtém um vetor com os ID's ordenados por suas pontuações

  addToNextLine(content, "Ranking: ");
  int i = 1;
  for(unsigned int id : idRanking){
    // Obtém o jogador e sua pontuação
    Player& player = player_service->getPlayer(id);
    string playerName = player.getName();
    unsigned int playerScore = scoreboardService.getScore(id);

    // Formata a string do jogador no ranking
    std::ostringstream oss;
    oss << std::setw(3) << std::setfill(' ') << playerScore;
    std::string stringScore = oss.str();

    string stringPlayer = std::to_string(i) + ". Pontuacao: " + stringScore;
    for(int i = 0; i <= 10; i++) stringPlayer += ' ';
    stringPlayer += playerName;
    i++;

    addEmptyLines(content, 1);
    addToNextLine(content, stringPlayer);
  }

  // Obtém o ganhador 
  Player& winner = player_service->getPlayer(idRanking[0]);
  string winnerName = winner.getName();

  addEmptyLines(content, 1);
  addToNextLine(content, "Ganhador: ");
  addToCurrentLine(content, winnerName);
}

string ViewGame::getUserAnswer(const vector<string>& content, const string header, const string message){ 
  setHeader(header);
  setContent(content);

  string userAnswer{};
  while (true) {
    userAnswer = display(message); // Exibe a mensagem e obtém a resposta do usuário
    if (!userAnswer.empty()) break; // Verifica se a resposta possui algum caractere
  }

  return userAnswer;
}

char ViewGame::getUserChoice(const vector<string>& content, const string header){
  setHeader(header);
  setContent(content);

  string userChoice{};
  while (true) {
    userChoice = display("Sua escolha: "); // Exibe a mensagem e obtém a entrada do usuário
    if (userChoice.size()==1) break; // Verifica se foi inserido apenas um caractere
  }

  return userChoice[0];
}

void ViewGame::getUserEnter(const vector<string>& content, const string header){
  setHeader(header);
  setContent(content);

  while (true) {
    string userEnter = display("Pressione -ENTER- para continuar..."); // Exibe a mensagem e aguarda a entrada do usuário
    if (userEnter.empty()) break; // Se o usuário pressionar apenas ENTER, sai do loop
  }
}

vector<string> ViewGame::getUsernamesList(vector<string>& content, int numPlayers) {
  addEmptyLines(content, 1);
  addToNextLine(content, "Adicione os usernames dos jogadores.");
  addEmptyLines(content, 2);

  vector<string> usernamesList{}; // Armazena os usernames de jogadores
  usernamesList.reserve(numPlayers);

  // Loop para obter o username de cada jogador
  for (int i = 1; i <= numPlayers; i++) {
    addToNextLine(content, to_string(i) + "º jogador: ");

    string username = getUserAnswer(content, gameName, "Sua resposta: "); // Obtém a resposta do usuário
    while (true) {
      try {
        if (username.length() > 15) throw InvalidNameException(); // Lança uma exceção se o username exceder o limite de caracteres

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        if(username.length() != converter.from_bytes(username).length()){
          // Lança uma exceção se o username possuir caracteres especiais
          throw InvalidNameException();
        }

        break;
      } catch (const InvalidNameException& e) {
        username = getUserAnswer(content, gameName, "Username invalido. Digite novamente: "); // Continua solicitando um username válido.
      }
    }

    addToCurrentLine(content, username);
    addEmptyLines(content, 1);

    usernamesList.push_back(move(username)); // Adciona o username na lista de usuários de jogadores
  }

  return usernamesList;
}

unsigned int ViewGame::getNumberOfPlayers(){ 
  vector<string> content{};

  addEmptyLines(content, 1);
  addToNextLine(content, "Digite o numero de jogadores (maximo 4): ");

  unsigned int numPlayers{0};
  string numString = getUserAnswer(content, gameName, "Sua resposta: "); // Obtém a entrada do usuário
  while (true) {
    try {
      numPlayers = std::stoi(numString); // Tenta converter a entrada para um número inteiro
      if(!(numPlayers > 1 && numPlayers <= 4)) throw InvalidNumber(); // Lança uma exceção se o número estiver fora do intervalo válido
      break;
    } catch (const std::exception &e) {
      numString = getUserAnswer(content, gameName, "Numero invalido. Digite novamente: "); // Continua solicitando um número válido caso ocorra alguma exceção
    }
  }

  return numPlayers; 
}

void ViewGame::addToNextLine(vector<string>& content, const string newContent){
  content.push_back(newContent);
}

void ViewGame::addToCurrentLine(vector<string>& content, const string newContent){
  unsigned int index = content.size()-1;
  content[index] += newContent;
}

void ViewGame::addEmptyLines(vector<string>& content, unsigned int numberOfLines){
  while (numberOfLines>0) {
    content.push_back("");
    numberOfLines--;
  }
}