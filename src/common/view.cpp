#include "../include/common/view.h"
#include <string>
#include <regex>
#include <iostream>
#include <cstdlib>

using namespace std;

#include <algorithm>

View::View(ScoreboardService* scoreboard_service, PlayerService* player_service, string header) : 
    scoreboard_service(scoreboard_service), player_service(player_service) {

    if (scoreboard_service == nullptr) {
        throw InvalidScoreboardServiceException();
    }

    if (player_service == nullptr) {
        throw InvalidPlayerServiceException();
    }

    this->lines = vector<string>();
    this-> line_nb = 20;
    this->column_nb = 80;
    this->header = header;

    for(int i = 0; i < this->line_nb; i++) {
        this->lines.push_back("");
    }
}

View::~View() {
    this->player_service->~PlayerService();
    this->scoreboard_service->~ScoreboardService();
}

string View::clean(string str) {
    size_t start = str.find_first_not_of(" ");
    if (start != string::npos) {
        str = str.substr(start);
    } else {
        str = "";
    }

    size_t end = str.find_last_not_of(" ");
    if (end != string::npos) {
        str = str.substr(0, end + 1);
    } else {
        str = "";
    }

    str = regex_replace(str, regex("\n"), "");
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return tolower(c); });

    return str;
}

string View::getInput() {
    string message;
    cin >> message;
    message = this->clean(message);
    return message;
}

void View::setLine(unsigned int line, string content) {
    if (line >= this->line_nb) {
        throw InvalidLineException();
    }

    this->lines[line] = content;
}

vector<string> View::formatScoreboard() {
    vector<string> formatted_scoreboard = vector<string>();

    vector<unsigned int> ranking = this->scoreboard_service->getRanking();
    string current_player_name = this->player_service->getCurrentPlayer().getName();
    for(unsigned int player_id: ranking){
        Player& player = this->player_service->getPlayer(player_id);
        
        string player_name = player.getName();
        string player_score = to_string(this->scoreboard_service->getScore(player_id));
        if (player_name == current_player_name) {
            player_name = "-> " + player_name;
        }

        formatted_scoreboard.push_back(player_name + " - " + player_score);
    }

    return formatted_scoreboard;
}

void View::display() {
    string first_separator = "";
    string second_separator = "";

    int stop_column = this->column_nb - this->header.length();
    for(int i=0; i< stop_column; i++){
        first_separator += "=";
    }

    for(int i=0; i< this->column_nb; i++){
        second_separator += "=";
    }
    
    system("clear");
    cout << first_separator + this-> header << endl;
    cout << "" << endl;

    vector<string> formatted_scoreboard = this->formatScoreboard();
    for (string& line : formatted_scoreboard) {
        cout << line << endl;
    }

    for(string& line : this->lines) {
        cout << line << endl;
    }
    cout << second_separator << endl;
}