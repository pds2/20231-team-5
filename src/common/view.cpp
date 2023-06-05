#include "../include/common/view.h"
#include <string>
#include <regex>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std;

#include <algorithm>

View::View(ScoreboardService* scoreboard_service, PlayerService* player_service, string header, unsigned int line_nb) : 
    scoreboard_service(scoreboard_service), player_service(player_service) {

    if (scoreboard_service == nullptr) {
        throw InvalidArgumentException();
    }

    if (player_service == nullptr) {
        throw InvalidArgumentException();
    }

    unsigned int max_content_line_nb = 5;
    this->available_line_nb = line_nb - player_service->getMaxPlayerNb() - max_content_line_nb;

    if (line_nb < player_service->getMaxPlayerNb() + 5 + this->available_line_nb) { // 5 = 2 de separador + 1 de header + 2 de scoreboard
        throw InvalidArgumentException();
    }

    this->content = vector<string>();
    this-> line_nb = line_nb;
    this->column_nb = 80;
    this->header = " " + header + " ";
}

View::~View() {
    // this->player_service->~PlayerService();
    // this->scoreboard_service->~ScoreboardService();
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

vector<pair<string, unsigned int>> View::formatScoreboard() {
    vector<pair<string, unsigned int>> formatted_scoreboard = vector<pair<string, unsigned int>>();

    vector<Player*> players = this->player_service->getPlayers();
    string current_player_name = this->player_service->getCurrentPlayer().getName();
    for(Player* player : players) {
        string player_name = player->getName();
        double player_score = this->scoreboard_service->getScore(player->getId());

        if (player_name == current_player_name) {
            player_name = "-> " + player_name;
        }

        formatted_scoreboard.push_back(make_pair(player_name, ceil(player_score)));
    }

    return formatted_scoreboard;
}

string View::wrapInBox(string content){
    string wrapped_content = "| " + content;
    int stop_column = this->column_nb - wrapped_content.length();
    for(int i=0; i< stop_column; i++){
        wrapped_content += " ";
    }
    wrapped_content += " |";
    return wrapped_content;
}

string View::createTopSeparator(){
    string first_separator = "+";

    double stop_column_d = (this->column_nb - this->header.length()) / 2.0;
    int stop_column = ceil(stop_column_d);
    for(int i=0; i< stop_column; i++){
        first_separator += "=";
    }

    first_separator += this->header;

    stop_column = this->column_nb - first_separator.length() + 1;
    for(int i=0; i< stop_column; i++){
        first_separator += "=";
    }
    first_separator += "+";

    return first_separator;
}

void View::displayScoreboard(){
    string scoreboard_separator = "| ┌";
    for(int i=0; i< 34; i++){
        scoreboard_separator += "─";
    }

    scoreboard_separator += "┐";
    for (int i=0; i< 42; i++){
        scoreboard_separator += " ";
    }
    scoreboard_separator += " |";
    

    cout << setw(this->column_nb) << scoreboard_separator << endl;

    string remaining_space = "";
    for(int i=0; i< 42; i++){
        remaining_space += " ";
    }

    remaining_space += " |";

    vector<pair<string, unsigned int>> formatted_scoreboard = this->formatScoreboard();
    for (pair<string, unsigned int> name_score : formatted_scoreboard) {
        string name = name_score.first;
        string score = to_string(name_score.second);

        cout << left << "| │  " << left << setw(18) << name << right << setw(12) << "... " + score + " pts" << right << "  │" << remaining_space << endl;
    }

    scoreboard_separator = "| └";
    for(int i=0; i< 34; i++){
        scoreboard_separator += "─";
    }
    scoreboard_separator += "┘";
    for (int i=0; i< 42; i++){
        scoreboard_separator += " ";
    }
    scoreboard_separator += " |";

    cout << setw(this->column_nb) << scoreboard_separator << endl;
    cout << this->wrapInBox("") << endl;
}

string View::createBottomSeparator(){
    string second_separator = "+";
    for(int i=0; i< this->column_nb; i++){
        second_separator += "=";
    }
    second_separator += "+";

    return second_separator;
}

void View::setContent(string content) {
    this->content = vector<string>();

    if(content.length() <= this->column_nb - 4) { // 4 = 2 de padding + 2 de borda
        this->content.push_back(content);
        return;
    }
    // separa em multiplas linhas
    string line = "";
    int counter = -1;
    for (char c : content) {
        counter++;
        line += c;
        if (counter == this->column_nb - 4) {
            this->content.push_back(line);
            line = "";
            counter = 0;
        }
    }
}

void View::display() {
    system("clear");
    cout << this->createTopSeparator() << endl;
    cout << this->wrapInBox("") << endl;

    this->displayScoreboard();

    for (string line : this->content) {
        cout << left << setw(this->column_nb) << this->wrapInBox(line) << endl;
    }
    cout << this->wrapInBox("") << endl;

    // cout << this-> createBottomSeparator() << endl;
    cout << "|> ";
    string input = this->getInput();
}