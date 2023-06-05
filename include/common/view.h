#ifndef VIEW
#define VIEW

#include <string>
#include <vector>
#include "services/scoreboard_service.h"
#include "services/player_service.h"

using namespace std;

class InvalidScoreboardServiceException : public exception {
    public:
        const char* what() const throw() {
            return "Scoreboard service inválido!";
        }
};

class InvalidPlayerServiceException : public exception {
    public:
        const char* what() const throw() {
            return "Player service inválido!";
        }
};

class InvalidLineException : public exception {
    public:
        const char* what() const throw() {
            return "Linha inválida!";
        }
};

class View {
    private:
        // Atributos
        unsigned int line_nb;
        unsigned int column_nb;
        vector<string> lines;

        string header;
        ScoreboardService* scoreboard_service;
        PlayerService* player_service;

        // Metodos

        string clean(string str);
        vector<string> formatScoreboard();
        
    public:
        View(ScoreboardService* scoreboard_service, PlayerService* player_service, string header);
        ~View();

        string getInput();
        void setLine(unsigned int line, string content);
        void display();
};

#endif