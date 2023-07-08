#ifndef GPTRIVIA_H
#define GPTRIVIA_H

#include <string>
using std::string;

#include "../../include/common/services/ai_service.h"
#include "../../include/common/game.h"
#include "database/dataloader.h"
#include "service/cardservice.h"
#include "service/viewtrivia.h"

class GPTrivia : public Game{

  public:
    GPTrivia();
    void playGame() override;

  private:
    static const unsigned int numberOfRounds = 1; // COLOCAR 10
    unsigned int numRound;

    DataLoader dataLoader;
    AIService chatGPT;
    CardService cardService;
    PlayerService playerService;
    ViewTrivia viewTrivia;

    void singlePlayer() override;
    void multiPlayer() override;
    void round(ScoreboardService& scoreboardService) override;
    void processPlayerTurn(ScoreboardService& scoreboardService, const string header) override;
    void resetData() override;
    void updateScore(const unsigned int userTime, ScoreboardService& scoreboardService, const bool isCorrectAnswer);
    string getHeader();

};

#endif