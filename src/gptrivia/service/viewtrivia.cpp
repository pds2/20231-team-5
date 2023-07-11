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

bool ViewTrivia::displayRules(){ 
  vector<string> content=vector<string>(); // Cria um vetor vazio de strings para armazenar o conteúdo

  addToNextLine(content,"1 - As perguntas serao geradas aleatoriamente de uma ampla variedade de categorias. Prepare-se para testar seus conhecimentos em diferentes areas!"); 
  addEmptyLines(content,1); 
  addToNextLine(content,"2 - A pontuacao eh baseada na rapidez e precisao das respostas. Quanto mais rapido voce responder corretamente, mais pontos voce ganhara."); 
  addEmptyLines(content,1); 
  addToNextLine(content,"3 - Cada jogador tera a chance de responder a uma pergunta por rodada. Prepare-se, pois em uma rodada pode ocorrer eventos, que ira te remover do jogo ou adicionar pontos extras caso acerte a resposta. Qual voce prefere?");
  addEmptyLines(content,1); 
  addToNextLine(content,"4 - No final do jogo, a pontuacao de cada jogador sera somada para determinar o vencedor. O jogador com a pontuacao mais alta eh o vencedor do GPTrivia!");
  addEmptyLines(content,2); 
  addToNextLine(content,"Voltar ----------------------- V"); 

  while(true){ 
    char userChoice = getUserChoice(content, "REGRAS"); // Obtém a escolha do usuário

    if(userChoice=='v') return true; // Retorna true se o usuário escolher voltar
  }
}