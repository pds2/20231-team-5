#include "../include/common/services/scoreboard_service.h"
#include <algorithm>
#include <iostream>

using namespace std;

ScoreboardService::ScoreboardService(vector<Player*> players) {
    for (Player* player : players) {
        if(player == nullptr){
            throw PlayerDoesNotExistException();
        }
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
    vector<double> scores = vector<double>();
    for (pair<unsigned int, double> player_score : scoreboard) {
        double score = player_score.second;
        scores.push_back(score);
    }
    sort(scores.begin(), scores.end(), compareInts); // Ordena em ordem decrescente

    vector<unsigned int> ranking = vector<unsigned int>();
    for (double score : scores) {
        for (pair<unsigned int, double> player_score : scoreboard) {
            unsigned int player_id = player_score.first;
            
            auto it = std::find(ranking.begin(), ranking.end(), player_id);
            if (it != ranking.end()) { // Jogador ja existe em ranking
                continue; 
            }

            if (player_score.second == score) {
                ranking.push_back(player_id);
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