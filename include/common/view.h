#ifndef VIEW
#define VIEW

#include <string>
#include <vector>
#include <map>
#include "services/scoreboard_service.h"
#include "services/player_service.h"

using namespace std;

class InvalidArgumentException : public exception {
    public:
        const char* what() const throw() {
            return "Argumento inválido!";
        }
};

class View {
    private:
        // Atributos
        unsigned available_line_nb;
        unsigned int line_nb;
        unsigned int column_nb;
        vector<string> content;

        string header;
        ScoreboardService* scoreboard_service;
        PlayerService* player_service;

        // Metodos
        string clean(string str);

        string createTopSeparator();
        string createBottomSeparator();
        string wrapInBox(string content);

        vector<pair<string, unsigned int>> formatScoreboard();
        void displayScoreboard();
        
    public:
        View(ScoreboardService* scoreboard_service, PlayerService* player_service, string header, unsigned int line_nb);
        ~View();

        string getInput();
        void setContent(string content);
        void display();
};

#endif