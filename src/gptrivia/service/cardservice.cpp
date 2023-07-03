#include <random>
#include <regex>
#include <iterator>

#include "../../../include/gptrivia/service/cardservice.h"
#include "../../../include/gptrivia/database/dataloader.h"

CardService::CardService(AIService* chatGPT, map<string,vector<QuizCard>> cardsMap) : chatGPT(chatGPT), cardsMap(cardsMap) {}

QuizCard CardService::generateCard(){
  if(cardsMap.empty()) throw NoCardsAvailable(); // Lança exceção se o mapa de cartões estiver vazio

  // Obtém um tema e um índice aleatórios
  string randomTheme = getRandomTheme();
  unsigned int randomIndex = getRandomIndex(randomTheme);

  // Remove e retorna o cartão aleatório
  QuizCard randomCard = cardsMap.at(randomTheme).at(randomIndex);
  removeCardFromCardsMap(randomTheme, randomIndex);

  return randomCard;
}

bool CardService::evaluateAnswer(const QuizCard& quizCard, const string userAnswer){
  string chatPrompt = "Em nosso jogo de Quiz, a resposta '" + userAnswer + "' do jogador pode ser considerada correta, dado que a resposta correta para a pergunta é '" + quizCard.getAnswer() + "'? As respostas não precisam ser idênticas, apenas ter semelhanças (responda 1 se correta e 0 se incorreta).";
  string chatAnswer = chatGPT->singlePrompt(chatPrompt);

  // Define as expressões regulares para verificar se a resposta obtida contém "1" ou "0".
  std::regex truePattern("1");
  std::regex falsePattern("0");
  if(std::regex_search(chatAnswer, truePattern)) return true;
  if(std::regex_search(chatAnswer, falsePattern)) return false;
}

string CardService::getFeedback(const QuizCard& quizCard, const bool isCorrectAnswer){
  string feedback{};

  if(isCorrectAnswer){
    feedback = chatGPT->singlePrompt("O jogador do quiz acertou a resposta, dê um feedback positivo e engraçado para ele->");
  }else{
    feedback = chatGPT->singlePrompt("O jogador do quiz errou a resposta. Diga que ele errou, faça uma piada e apresente a seguinte resposta correta ao final: '" + quizCard.getAnswer() + "'. Não tente advinhar a resposta que ele deu!");
  }

  return feedback;
}

string CardService::getRandomTheme() const{
  // Obtém um iterador para uma posição aleatória
  std::random_device rd;
  std::mt19937 gen(rd());
  unsigned int min = 0;
  unsigned int max = cardsMap.size() - 1;
  std::uniform_int_distribution<unsigned int> dist(min, max);

  // Retorna um tema aleatório selecionado a partir do mapa de cartões
  auto it = std::begin(cardsMap);
  std::advance(it, dist(gen));
  string randomTheme = it->first;

  return randomTheme;
}

unsigned int CardService::getRandomIndex(const string theme) const{
  const vector<QuizCard>& cardsTheme = cardsMap.at(theme);
  unsigned int numCards = cardsTheme.size();

  // Obtém e retorna um índice aleatório do vetor de cartões correspondente ao tema
  std::random_device rd;
  std::mt19937 gen(rd());
  unsigned int min = 0;
  unsigned int max = numCards - 1;
  std::uniform_int_distribution<unsigned int> dist(min, max);
  unsigned int randomIndex = dist(gen);

  return randomIndex;
}

void CardService::removeCardFromCardsMap(const string theme, const unsigned int index){
  vector<QuizCard>& cardsTheme = cardsMap.at(theme);
  cardsTheme.erase(cardsTheme.begin() + index); // Remove o cartão do vetor usando o índice fornecido.
  
  if(cardsTheme.size() == 0) removeThemeFromCardsMap(theme); // Verifica se o vetor de cartões ficou vazio após a remoção e remove o tema correspondente do mapa de cartões, se necessário.
} 

void CardService::removeThemeFromCardsMap(const string theme){
  cardsMap.erase(theme);
}