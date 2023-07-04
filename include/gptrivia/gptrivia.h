#ifndef GPTRIVIA_H
#define GPTRIVIA_H

#include <string>
using std::string;

#include "../../include/common/services/ai_service.h"
#include "database/dataloader.h"
#include "service/cardservice.h"
#include "service/viewtrivia.h"

class GPTrivia{
  public:
    GPTrivia();
    void playGame();
  
  private:
    static const unsigned int numberOfRounds = 10;
    unsigned int numRound;
    string filename;

    DataLoader dataLoader;
    AIService chatGPT;
    CardService cardService;
    PlayerService playerService;
    ViewTrivia viewTrivia;

    void multiPlayer();
    void singlePlayer();
    void round(ScoreboardService& scoreboardService);
    void processPlayerTurn(ScoreboardService& scoreboardService,const string header);
    void updateScore(ScoreboardService& scoreboardService,const bool isCorrectAnswer);
    void resetData();
    string getHeader();

};

#endif