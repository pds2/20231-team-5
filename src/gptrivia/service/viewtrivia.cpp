#include <chrono>

#include "../../../include/gptrivia/service/viewtrivia.h"

ViewTrivia::ViewTrivia() : ViewGame("GPTrivia") {}

std::pair<string, unsigned int> ViewTrivia::displayQuestion(const QuizCard& userCard, vector<string>& content, const string header){
  // Adiciona a pergunta ao conteúdo
  addToNextLine(content, userCard.getQuestion()); 
  addEmptyLines(content, 2);

  auto start = std::chrono::steady_clock::now();
  string userAnswer = getUserAnswer(content, header, "Sua resposta: "); // Obtém a resposta do usuário
  auto end = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  unsigned int answerTime = static_cast<unsigned int>(duration); // Obtém o tempo de resposta

  // Adiciona a resposta do usuário ao conteúdo
  addToNextLine(content, "SUA RESPOSTA: ");
  addToCurrentLine(content, userAnswer);
  addEmptyLines(content, 1);

  // Adiciona uma linha separadora ao conteúdo
  string separatorLine{};
  for(int i = 0; i <= 75; i++) separatorLine += '-';
  addToNextLine(content, separatorLine);
  addEmptyLines(content, 1);

  return {userAnswer, answerTime};
}

void ViewTrivia::displayFeedback(const string feedback, vector<string>& content, const string header){
  // Adiciona o feedback ao conteúdo
  addToNextLine(content, feedback);
  addEmptyLines(content, 2);

  // Apresenta o contéudo
  getUserEnter(content, header);
}

bool ViewTrivia::displayRules(){}