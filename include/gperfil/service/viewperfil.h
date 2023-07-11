/**
 * @file viewperfil.h
 * @brief Declaração da classe ViewPerfil.
 */

#ifndef VIEWPERFIL_H
#define VIEWPERFIL_H

#include <string>
#include <vector>
#include "../../../include/common/viewgame.h"

/**
 * @brief Classe responsável pela visualização do perfil do jogo de Trivia.
 */
class ViewPerfil : public ViewGame {

private:
  bool displayRules() override;

public:
  /**
   * @brief Construtor da classe ViewPerfil.
   */
  ViewPerfil();

  /**
   * @brief Exibe a pergunta para tentar adivinhar o objeto.
   * @param content Vetor de strings contendo o conteúdo a ser exibido na tela.
   * @param header Cabeçalho a ser exibido na tela.
   * @param tema O tema relacionado à pergunta.
   * @return A pergunta feita pelo jogador.
   */
  std::string displaypergunta(std::vector<std::string>& content, const std::string header, std::string tema);

  /**
   * @brief Exibe a resposta do ChatGPT e solicita uma tentativa de adivinhar o objeto.
   * @param content Vetor de strings contendo o conteúdo a ser exibido na tela.
   * @param header Cabeçalho a ser exibido na tela.
   * @param tema O tema relacionado à resposta.
   * @param resposta_chat A resposta do ChatGPT.
   * @return A tentativa de adivinhar o objeto feita pelo jogador.
   */
  std::string displayresposta(std::vector<std::string>& content, const std::string header, std::string tema, std::string resposta_chat);

  /**
   * @brief Exibe a resposta dada pelo jogador e se está correta ou não.
   * @param respostaUsuario A resposta dada pelo jogador.
   * @param corretude Indicação se a resposta está correta ou não.
   * @param acabou Indicação se a rodada do jogo acabou.
   */
  void display_resp_correct(std::string respostaUsuario, std::string corretude, bool acabou);

  /**
   * @brief Exibe as regras do jogo.
   * @return `true` se o usuário escolher voltar.
   */
};

#endif
