#include "../include/gptrivia/gptrivia.h"

#include <iostream>

const unsigned int GPTrivia::numberOfRounds;

GPTrivia::GPTrivia() : dataLoader(), chatGPT(""), cardService(&chatGPT, dataLoader.getCardsMap()), viewTrivia(&playerService) {}

void GPTrivia::playGame(){
  try {
    while (true) {
      // Apresenta o menu e obtém o modo de jogo
      GameType gameType = viewTrivia.displayMenu();

      // Inicia o jogo com base na escolha do jogador
      if (gameType == SinglePlayer) singlePlayer();
      if (gameType == MultiPlayer) multiPlayer();

      // Reinicia os dados do jogo
      resetData();
    }
  } catch (const ExitGame &e) {
    //IMPLEMENTAR FECHAMENTO
    cout<<"FIM DE JOGO"<<endl;
  }
}

void GPTrivia::singlePlayer(){
  //IMPLEMENTAR SINGLEPLAYER
}

void GPTrivia::multiPlayer(){
  // Configura o placar do jogo
  ScoreboardService scoreboardService = ScoreboardService(playerService.getPlayers());
  viewTrivia.setScoreboardService(&scoreboardService);

  // Executa todas as rodadas
  for (unsigned int i = 1; i <= numberOfRounds; i++) {
    numRound = i;
    round(scoreboardService);
  }

  // Apresenta o ranking após acabar todas as rodadas
  viewTrivia.displayRanking(scoreboardService);
}

void GPTrivia::round(ScoreboardService& scoreboardService){
  // Obtém o header da rodada
  string header = getHeader();

  // Obtém a quantidade de jogadores
  unsigned int numberOfPlayers = playerService.getPlayers().size();

  // Itera sobre todos os jogador
  for (unsigned int i = 0; i < numberOfPlayers; i++) {
    playerTurn(scoreboardService, header);
    playerService.changeCurrentPlayer();
  }
}

void GPTrivia::playerTurn(ScoreboardService& scoreboardService, const string header){
  std::vector<string> content=std::vector<string>();

  // Gera um card
  QuizCard userCard = cardService.generateCard();

  // Apresenta a pergunta e obtém a resposta e o tempo de resposta
  std::pair<string, unsigned int> answerTime = viewTrivia.displayQuestion(userCard, content, header);
  string userAnswer = answerTime.first;
  unsigned int userTime = answerTime.second;

  // Avalia a resposta
  bool isCorrectAnswer = cardService.evaluateAnswer(userCard, userAnswer);

  while (true) {
    try {
      // Gera um feedback
      string feedback = cardService.getFeedback(userCard, isCorrectAnswer);

      // Apresenta a correção
      viewTrivia.displayFeedback(feedback, content, header);

      break;
    } catch (const std::exception& e){
        // Remove a string feedback problemática
        for (int i = 0; i < 3; i++) content.pop_back();
    }
  }

  // Altera a pontuação
  updateScore(answerTime, scoreboardService, isCorrectAnswer);
}

void GPTrivia::updateScore(const unsigned int answerTime, ScoreboardService& scoreboardService, const bool isCorrectAnswer){
  Player& currentPlayer = playerService.getCurrentPlayer();
  unsigned int score{0};

  if (isCorrectAnswer) {
    if (answerTime <= 5) score = 10;
    else if (answerTime <= 10) score = 8;
    else score = 6;
    //PROCESSAR EVENTO
    scoreboardService.changeScore(currentPlayer.getId(), score);
  }
}

void GPTrivia::resetData(){
  cardService = CardService(&chatGPT, dataLoader.getCardsMap());
  playerService = PlayerService();
  viewTrivia = ViewTrivia(&playerService);
}

string GPTrivia::getHeader(){
  std::string numString = std::to_string(numRound);
  std::string header = "GPTrivia - RODADA " + numString;

  return header;
}