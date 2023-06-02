#include "../include/common/services/scoreboard_service.h"
#include <algorithm>

ScoreboardService::ScoreboardService(vector<Player*> players) {
    for (Player* player : players) {
        scoreboard[player->getId()] = 0.0;
    }
}

void ScoreboardService::changeScore(unsigned int player_id, double delta_score) {
    if (this->scoreboard.find(player_id) == scoreboard.end()) {
        throw PlayerDoesNotExistException();
    }

    scoreboard[player_id] += delta_score;
}

double ScoreboardService::getScore(unsigned int player_id) {
    if (this->scoreboard.find(player_id) == scoreboard.end()) {
        throw PlayerDoesNotExistException();
    }

    return scoreboard[player_id];
}

bool ScoreboardService::compareInts(int a, int b) {
    return a > b;
}

vector<unsigned int> ScoreboardService::getRanking() {
    vector<double> scores = vector<double>(scoreboard.size());
    for (pair<unsigned int, double> player_score : scoreboard) {
        double score = player_score.second;
        scores.push_back(score);
    }
    sort(scores.begin(), scores.end(), compareInts); // Ordena em ordem decrescente

    vector<unsigned int> ranking = vector<unsigned int>(scoreboard.size());
    for (double score : scores) {
        for (pair<unsigned int, double> player_score : scoreboard) {
            if (player_score.second == score) {
                ranking.push_back(player_score.first);
            }
        }
    }
    
    return ranking;
}

unsigned int ScoreboardService::getWinner() {
    vector<unsigned int> ranking = this->getRanking();
    unsigned int winner_id = ranking[0];
    return scoreboard[winner_id];
}