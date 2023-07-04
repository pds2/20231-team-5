#include "../include/gptrivia/gptrivia.h"

#include <iostream>
#include <chrono>
#include <thread>

const unsigned int GPTrivia::numberOfRounds;

GPTrivia::GPTrivia() : filename("triviacards.txt"), dataLoader(filename), chatGPT(""), cardService(&chatGPT,dataLoader.getCardsMap()), viewTrivia(&playerService) {}

void GPTrivia::playGame(){
  try{
    //apresenta o menu e obtém o modo de jogo
    GameType gameType=viewTrivia.displayMenu("GPTrivia");

    //inicia o jogo com base na escolha do jogador
    if(gameType==MultiPlayer) multiPlayer();
    if(gameType==SinglePlayer) singlePlayer();
  }catch(const ExitGame &e){

    //implementar fechamento do jogo
    cout<<"FIM DE JOGO"<<endl;
  }
}

void GPTrivia::singlePlayer(){
  //implementar singleplayer
}

void GPTrivia::multiPlayer(){
  ScoreboardService scoreboardService=ScoreboardService(playerService.getPlayers());
  viewTrivia.setScoreboardService(&scoreboardService);

  for(int i=1;i<=numberOfRounds;i++){
    numRound=i;
    round(scoreboardService);
  }
  //implementar ranking após acabar todas as rodadas
}

void GPTrivia::round(ScoreboardService& scoreboardService){
  //obtém header da rodada
  string header=getHeader();

  //itera sobre cada jogador
  int numberOfPlayers=playerService.getPlayers().size();
  for(int i=0; i<numberOfPlayers; i++){
    processPlayerTurn(scoreboardService,header);
    playerService.changeCurrentPlayer();
  }
}

void GPTrivia::processPlayerTurn(ScoreboardService& scoreboardService, const string header){
  std::vector<string> content=std::vector<string>();

  //gera card
  QuizCard userCard=cardService.generateCard();

  //apresenta pergunta e obtém resposta
  string userAnswer=viewTrivia.displayQuestion(userCard, content, header);

  //avalia resposta
  bool isCorrectAnswer=cardService.evaluateAnswer(userCard, userAnswer);

  while(true){
    try{
      //gera feedback
      string feedback=cardService.getFeedback(userCard,isCorrectAnswer);

      //apresenta correção
      viewTrivia.displayFeedback(feedback,content,header);

      break;
    }catch(const std::exception& e){
      for(int i=0; i<3; i++) content.pop_back();
    }
  }

  //altera pontuação
  updateScore(scoreboardService,isCorrectAnswer);
}

void GPTrivia::updateScore(ScoreboardService& scoreboardService, const bool isCorrectAnswer){
  Player& currentPlayer=playerService.getCurrentPlayer();
  if(isCorrectAnswer) scoreboardService.changeScore(currentPlayer.getId(), 10);
}

string GPTrivia::getHeader(){
  std::string numString=std::to_string(numRound);
  std::string header="GPTrivia - RODADA "+numString;

  return header;
}

void GPTrivia::resetData(){
  cardService=CardService(&chatGPT, dataLoader.getCardsMap());
  playerService=PlayerService();
  viewTrivia=ViewTrivia(&playerService);
}