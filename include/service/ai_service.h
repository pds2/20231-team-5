#ifndef AI_SERVICE
#define AI_SERVICE

#include <string>
#include "../database/question.h"
#include "../database/player.h"

using namespace std;

class AIService {
    private:
        Player current_player;

    string promptGPT(string prompt);

    public:
        AIService();

        void definePlayer(Player player);
        string generateQuestion(Difficulty difficulty);
        bool evaluateAnswer(string answer);
};
#endif