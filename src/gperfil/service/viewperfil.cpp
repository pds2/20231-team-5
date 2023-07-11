#include <cctype>
#include "../../../include/gperfil/service/viewperfil.h"

ViewPerfil::ViewPerfil() : ViewGame("GPerfil") {}

std::string ViewPerfil::displaypergunta(std::vector<std::string>& content, const std::string header, std::string tema)
{
  addToNextLine(content, "TEMA : " + tema);
  addEmptyLines(content, 2);
  addToNextLine(content, "Faça sua pergunta para tentar advinhar o objeto: ");
  addEmptyLines(content, 2);

  std::string userAnswer{};
  while (true)
  {
    userAnswer = getUserAnswer(content, header, "Faça sua pergunta: "); // Obtém a resposta do usuário

    // Verifica se a resposta contém o caractere '\' e continua solicitando uma resposta se conter
    if (userAnswer.find('\\') == std::string::npos)
      break;
  }

  // Adiciona a resposta do usuário ao conteúdo
  addToNextLine(content, "SUA Pergunta: ");
  addToCurrentLine(content, userAnswer);
  addEmptyLines(content, 1);
  // Adiciona uma linha separadora ao conteúdo
  addToNextLine(content, "--------------------------------------");
  addToCurrentLine(content, "-------------------------------------");
  addEmptyLines(content, 1);

  return userAnswer;
}

std::string ViewPerfil::displayresposta(std::vector<std::string>& content, const std::string header, std::string tema, std::string resposta_chat)
{
  addToNextLine(content, "Resposta do chatGPT: " + resposta_chat);
  addEmptyLines(content, 2);
  addToNextLine(content, "Tente advinhar o objeto: ");
  addEmptyLines(content, 2);

  std::string userAnswer{};
  while (true)
  {
    userAnswer = getUserAnswer(content, header, "Tente advinhar: "); // Obtém a resposta do usuário

    // Verifica se a resposta contém o caractere '\' e continua solicitando uma resposta se conter
    if (userAnswer.find('\\') == std::string::npos)
      break;
  }

  // Adiciona a resposta do usuário ao conteúdo
  addToNextLine(content, "SUA RESPOSTA: ");
  addToCurrentLine(content, userAnswer);
  addEmptyLines(content, 1);
  // Adiciona uma linha separadora ao conteúdo
  addToNextLine(content, "--------------------------------------");
  addToCurrentLine(content, "-------------------------------------");
  addEmptyLines(content, 1);

  return userAnswer;
}

void ViewPerfil::display_resp_correct(std::string respostaUsuario, std::string corretude, bool acabou)
{
  std::vector<std::string> content_two = std::vector<std::string>();
  addToNextLine(content_two, "Sua resposta foi: " + respostaUsuario);
  addEmptyLines(content_two, 1);
  addEmptyLines(content_two, 1);
  addToNextLine(content_two, "Sua resposta está " + corretude + " !!!!");
  if (acabou)
  {
    addToNextLine(content_two, "A rodada acabou \n Ninguem pontuou");
  }
  getUserEnter(content_two, "Gperfil");
}

bool ViewPerfil::displayRules()
{ 
  // RESUMIR E RETIRAR ACENTOS
  std::vector<std::string> content = std::vector<std::string>(); // Cria um vetor vazio de strings para armazenar o conteúdo

  addToNextLine(content, "1 - O jogo consiste em adivinhar um objeto sorteado, fazendo perguntas ao ChatGPT, com pontuaçao maior para menos perguntas feitas antes de acertar."); 
  addEmptyLines(content, 1); 
  addToNextLine(content, "2 - Antes do jogo, um tema eh sorteado para fornecer contexto sobre o tipo de objeto sorteado e auxiliar nas perguntas dos jogadores."); 
  addEmptyLines(content, 1); 
  addToNextLine(content, "3 - Os jogadores fazem perguntas ao ChatGPT em formato sim ou nao para obter pistas e adivinhar o objeto sorteado. ");
  addEmptyLines(content, 1); 
  addToNextLine(content, "4 - A pontuaçao depende do numero de perguntas feitas para acertar o objeto, sendo maior para menos perguntas realizadas.");
  addEmptyLines(content, 2); 
  addToNextLine(content, "Voltar ----------------------- V"); 

  while (true)
  { 
    char userChoice = getUserChoice(content, "REGRAS"); // Obtém a escolha do usuário

    if (userChoice == 'v' || userChoice == 'V') 
      return true; // Retorna true se o usuário escolher voltar
  }
}
