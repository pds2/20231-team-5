#include <cctype> 

#include "../../../include/gptrivia/service/viewtrivia.h"

ViewTrivia::ViewTrivia(PlayerService* player_service) : View(player_service) {}

GameType ViewTrivia::displayMenu(){
  vector<string> content{};
  
  addEmptyLines(content,1);
  addToNextLine(content,"Bem vindo ao GPTrivia. Digite a opção desejada!");
  addEmptyLines(content,5);
  addToNextLine(content,"SINGLEPLAYER ----------------- S");
  addEmptyLines(content,1);
  addToNextLine(content,"MULTIPLAYER ------------------ M");
  addEmptyLines(content,1);
  addToNextLine(content,"REGRAS ----------------------- R");
  addEmptyLines(content,1);
  addToNextLine(content,"SAIR ------------------------- X");

  bool loopAgain{true};
  GameType gameType{};

  while(loopAgain){
    char userChoice=getUserChoice(content,"GPTrivia");

    switch (userChoice)
    {
    case 'S':
      loopAgain=displaySinglePlayer(gameType);
      break;
    case 'M':
      loopAgain=displayMultiPlayer(gameType);
      break;
    case 'R':
      loopAgain=displayRules();
      break;
    case 'X':
      throw ExitGame();
    }
  }

  return gameType;
}

bool ViewTrivia::displayRules(){
  vector<string> content=vector<string>();

  addToNextLine(content,"1 - Fusce finibus tristique dui. Nullam est ligula, vestibulum iniaculis et, rutrum nec tortor. Lorem ipsum dolor sit amet, consectetur.");
  addEmptyLines(content,1);
  addToNextLine(content,"2 - Fusce finibus tristique dui. Nullam est ligula, vestibulum iniaculis et, rutrum nec tortor. Lorem ipsum dolor sit amet, consectetur.");
  addEmptyLines(content,1); 
  addToNextLine(content,"3 - Fusce finibus tristique dui. Nullam est ligula, vestibulum iniaculis et, rutrum nec tortor. Lorem ipsum dolor sit amet, consectetur.");
  addEmptyLines(content,2);
  addToNextLine(content,"VOLTAR ----------------------- V");

  while(true){
    char userChoice=getUserChoice(content,"REGRAS");

    if(userChoice=='V') return true;
  }
}

bool ViewTrivia::displaySinglePlayer(GameType& roundType){
  vector<string> content=vector<string>();

  string username=getUsername(content);

  addEmptyLines(content,1);
  addToNextLine(content,"INICIAR ---------------------- I");
  addEmptyLines(content,1);
  addToNextLine(content,"VOLTAR ----------------------- V");

  while(true){
    char userChoice=getUserChoice(content, "SINGLEPLAYER");

    switch (userChoice)
    {
    case 'I':
      player_service->addPlayer(username);
      roundType=SinglePlayer;
      return false;
      break;
    case 'V':
      return true;
    }
  }
}

bool ViewTrivia::displayMultiPlayer(GameType& roundType){
  vector<string> content=vector<string>();

  unsigned int numPlayers=getNumberOfPlayers();
  vector<string> usernamesList=getUsernamesList(content,numPlayers);

  addEmptyLines(content,1);
  addToNextLine(content,"INICIAR ---------------------- I");
  addEmptyLines(content,1);
  addToNextLine(content,"VOLTAR ----------------------- V");

  while(true){
    char userChoice=getUserChoice(content,"MULTIPLAYER");

    switch(userChoice)
    {
      case 'I':
        for(std::string x:usernamesList) player_service->addPlayer(x);
        roundType=MultiPlayer;
        return false;
      case 'V':
        return true;
    }
  }
}

string ViewTrivia::displayQuestion(const QuizCard& userCard, std::vector<string>& content, const string header){
  addToNextLine(content,userCard.getQuestion());
  addEmptyLines(content,2);

  std::string userAnswer{};
  while(true){
    userAnswer=getUserAnswer(content, header);
    if(userAnswer.find('\\') == std::string::npos) break;
  }

  // adiciona resposta do usuário
  addToNextLine(content,"SUA RESPOSTA: ");
  addToCurrentLine(content,userAnswer);
  addEmptyLines(content,1);
  content.push_back("---------------------------------------------------------------------------"); //OLHAR
  addEmptyLines(content,1);

  return userAnswer;
}

void ViewTrivia::displayFeedback(const string feedback, std::vector<string>& content, const string header){
  addToNextLine(content,feedback);
  addEmptyLines(content,2);

  while(true){
    setHeader(header);
    setContent(content);
    string userEnter=display("ENTER");

    if(userEnter.empty()) break;
  }
}

//AUXILIARES

char ViewTrivia::getUserChoice(const vector<string>& content, const string header){
  setHeader(header);
  setContent(content);

  string userChoice{};
  while(true){
    userChoice=display("Sua escolha: ");
    if(userChoice.size()==1) break;
  }

  return toupper(userChoice[0]);
}

string ViewTrivia::getUserAnswer(const vector<string>& content, const string header){
  setHeader(header);
  setContent(content);

  string userAnswer{};
  while(true){
    userAnswer=display("Sua resposta: ");
    if(userAnswer.size()>0) break;
  }

  return userAnswer;
}

unsigned int ViewTrivia::getNumberOfPlayers(){
  vector<string> content{};
  int numPlayers{0};

  addToNextLine(content,"Quantidade de jogadores (máximo 4):");
  bool loopAgain{};
  do{
    string numString=getUserAnswer(content,"MULTIPLAYER");
    try{
      numPlayers=stoi(numString);
      if(numPlayers>4||numPlayers<=1) throw InvalidNumber();

      loopAgain=false;
    }catch(const std::exception& e){
      loopAgain=true;
    }
  }while(loopAgain);
    
  return numPlayers;
}

vector<string> ViewTrivia::getUsernamesList(vector<string>& content, int numPlayers){
  vector<string> usernamesList{};

  for(int i=1; i<=numPlayers; i++){
    string numString=to_string(i);
    addToNextLine(content,"Username "+numString+"º jogador: ");

    string username=getUserAnswer(content,"MULTIPLAYER");
    addToCurrentLine(content,username);
    addEmptyLines(content,1);

    usernamesList.push_back(username);
  }

  return usernamesList;
}

string ViewTrivia::getUsername(vector<string>& content){
  addToNextLine(content,"Username: ");
  string username=getUserAnswer(content,"SINGLEPLAYER");
  addToCurrentLine(content,username);
  addEmptyLines(content,1);

  return username;
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