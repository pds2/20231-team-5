#include "../../include/gptrivia/gptrivia.h"

#include <iostream>

const unsigned int GPTrivia::numberOfRounds;

GPTrivia::GPTrivia() : dataLoader("files/gptrivia/triviacards.txt"), chatGPT(""), cardService(&chatGPT, dataLoader.getCardsMap()) {}

void GPTrivia::playGame(){
  // Configura o serviço de jogador
  viewTrivia.setPlayerService(&playerService);

  // Apresenta o menu
  viewTrivia.displayMenu();

  // Executa as rodadas
  runGameRounds();

  // Reinicia os dados do jogo
  resetData();
}

void GPTrivia::runGameRounds(){
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
  updateScore(userTime, scoreboardService, isCorrectAnswer);
}

void GPTrivia::updateScore(const unsigned int userTime, ScoreboardService& scoreboardService, const bool isCorrectAnswer){
  Player& currentPlayer = playerService.getCurrentPlayer();
  unsigned int score{0};

  if (userTime <= 5) score = 10;
  else if (userTime <= 10) score = 8;
  else score = 6;

  //if (ocorrer algum evento) ocorre o evento;
  // else {eu altero o placar manualmente}
  if (isCorrectAnswer) scoreboardService.changeScore(currentPlayer.getId(), score);
}

void GPTrivia::resetData(){
  cardService = CardService(&chatGPT, dataLoader.getCardsMap());
  playerService = PlayerService();
  viewTrivia = ViewTrivia();
}

string GPTrivia::getHeader(){
  std::string numString = std::to_string(numRound);
  std::string header = "GPTrivia - RODADA " + numString;

  return header;
}