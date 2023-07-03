#ifndef DATALOADER_H
#define DATALOADER_H

#include <map>
using std::map;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "../database/quizcard.h"

class DataLoader{

  public:
    DataLoader(const string filename);
    ~DataLoader() = default;
    map<string, vector<QuizCard>> getCardsMap();

  private:
    string filename;
    map<string, vector<QuizCard>> cardsMap;

    bool isThemeLine(const string line) const;
    bool isCardLine(const string line) const;
    string extractTheme(const string line);
    QuizCard extractCard(const string line);

};

#endif