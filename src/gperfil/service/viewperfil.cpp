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
  std::vector<std::string> content = std::vector<std::string>(); // Cria um vetor vazio de strings para armazenar o conteúdo

  addToNextLine(content, "Objetivo: O objetivo do jogo é adivinhar o objeto sorteado fazendo perguntas ao ChatGPT. Quanto menos perguntas forem feitas, maior será a pontuação do jogador em caso de acerto."); 
  addEmptyLines(content, 1); 
  addToNextLine(content, "Tema: Antes de começar o jogo, um tema será sorteado e informado aos jogadores. Esse tema servirá como uma pista geral sobre o tipo de objeto que foi sorteado, fornecendo um contexto para as perguntas."); 
  addEmptyLines(content, 1); 
  addToNextLine(content, "Perguntas: Os jogadores podem fazer perguntas ao ChatGPT para obter pistas e tentar adivinhar o objeto sorteado. As perguntas devem ser feitas de forma que a resposta seja um sim ou não, para ajudar a eliminar possibilidades e direcionar a busca. Os jogadores podem fazer perguntas alternadamente ou em rodadas definidas.");
  addEmptyLines(content, 1); 
  addToNextLine(content, "Pontuação: A pontuação será calculada com base no número de perguntas feitas para adivinhar o objeto correto. Quanto menos perguntas forem necessárias para acertar, maior será a pontuação obtida pelo jogador.");
  addEmptyLines(content, 2); 
  addToNextLine(content, "Voltar ----------------------- V"); 

  while (true)
  { 
    char userChoice = getUserChoice(content, "REGRAS"); // Obtém a escolha do usuário

    if (userChoice == 'v' || userChoice == 'V') 
      return true; // Retorna true se o usuário escolher voltar
  }
}
