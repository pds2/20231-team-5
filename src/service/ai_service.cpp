#include "../include/openai/openai.hpp"
#include <iostream>
#include "../include/service/ai_service.h"

AIService::AIService() {}

void AIService::definePlayer(Player player) {
    this->current_player = player;
}

string AIService::promptGPT(string prompt) {
    
}

string AIService::generateQuestion(Difficulty difficulty) {
    
}

bool AIService::evaluateAnswer(string answer) {
    
}
