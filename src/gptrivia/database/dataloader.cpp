#include <fstream>

#include "../../../include/gptrivia/database/dataloader.h"

DataLoader::DataLoader(const string filename) : filename(filename){
  // Abre o arquivo
  string line{};

  std::ifstream in_file{filename};
  if(!in_file) throw FileDoesNotOpen(); // Lança exceção se não for possível abrir o arquivo

  // Copia os dados do arquivo para cardsMap
  string currentTheme{};
  QuizCard currentCard{};

  while(getline(in_file, line)){
    if(isThemeLine(line)){
      currentTheme = extractTheme(line); // Extrai o tema da linha
      if(cardsMap.find(currentTheme) == cardsMap.end()) cardsMap[currentTheme] = vector<QuizCard>(); // Cria um novo vetor de cartões se o tema ainda não existir no mapa
    }
    else if(isCardLine(line)){
      currentCard = extractCard(line); // Extrai o cartão da linha
      cardsMap[currentTheme].push_back(currentCard); // Adiciona o cartão ao vetor correspondente ao tema no mapa
    }
    else continue; // Ignora linhas que não são de tema ou cartão
  }

  // Fecha o arquivo
  in_file.close();
}

map<string, vector<QuizCard>> DataLoader::getCardsMap(){
  return cardsMap;
}

bool DataLoader::isThemeLine(const string line) const{
  size_t found = line.find("Tema: ");
  if(found == string::npos) return false;
  return true;
}

bool DataLoader::isCardLine(const string line) const{
  size_t found = line.find("Pergunta: ");
  if(found == string::npos) return false;
  return true;
}

string DataLoader::extractTheme(const string line){
  size_t themePosition = line.find("Tema: ");
  themePosition += 6;

  return line.substr(themePosition); // Retorna a substring após "Tema: "
}

QuizCard DataLoader::extractCard(const string line){
  size_t questionPosition = line.find("Pergunta: ");
  questionPosition += 10;
  size_t answerPosition = line.find("Resposta: ");
  if(answerPosition == string::npos) throw AnswerNotFound(); // Lança exceção se não encontrar "Resposta: "

  string question = line.substr(questionPosition, answerPosition - questionPosition); // Extrai a pergunta
  answerPosition += 10;
  string answer = line.substr(answerPosition); // Extrai a resposta
  
  return QuizCard(question, answer);
}
