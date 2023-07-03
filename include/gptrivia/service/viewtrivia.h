#ifndef VIEWTRIVIA_H
#define VIEWTRIVIA_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "../../common/view.h"
#include "../database/quizcard.h"

class ExitGame : public std::exception {
public:
  const char* what() const throw() {
    return "O jogador saiu do jogo.";
  }
};

class InvalidNumber : public exception {
  public:
    const char* what() const throw() {
        return "Número inválido!";
    }
};

enum GameType{
  SinglePlayer, 
  MultiPlayer
};

class ViewTrivia : public View{

  public:
    ViewTrivia(PlayerService* player_service);
    ~ViewTrivia() = default;
    GameType displayMenu();

    string displayQuestion(const QuizCard& userCard, std::vector<string>& content, const string header);
    void displayFeedback(const string feedback, std::vector<string>& content, const string header);
    char getUserChoice(const vector<string>& content, const string header);
    string getUserAnswer(const vector<string>& content, const string header);

  private:
    bool displaySinglePlayer(GameType& gameType);
    bool displayMultiPlayer(GameType& gameType);
    bool displayRules();

    void addToNextLine(vector<string>& content, const string newContent);
    void addToCurrentLine(vector<string>& content, const string newContent);
    void addEmptyLines(vector<string>& content, unsigned int numberOfLines);

    unsigned int getNumberOfPlayers();
    string getUsername(vector<string>& content);
    vector<string> getUsernamesList(vector<string>& content, int numPlayers);

};

#endif