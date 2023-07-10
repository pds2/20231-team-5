/**
 * @file viewgame.h
 * @brief Declaração da classe ViewGame.
 */

#ifndef VIEWGAME_H
#define VIEWGAME_H

#include "view.h"

/**
 * @brief Exceção lançada quando o jogador sai do jogo.
 */
class ExitGame : public std::exception {
  public:
    const char* what() const throw() {
      return "Jogador saiu do jogo.";
  }
};

/**
 * @brief Exceção lançada quando um número inválido é fornecido.
 */
class InvalidNumber : public exception {
  public:
    const char* what() const throw() {
      return "Número inválido!";
    }
};

/**
 * @brief Classe base para a visualização de um jogo.
 */
class ViewGame : public View{
  
  public: 
    /**
     * @brief Construtor da classe ViewGame.
     * @param gameName O nome do jogo.
     */
    ViewGame(string gameName);
    
    /**
     * @brief Exibe o menu do jogo.
     */
    void displayMenu();

    /**
     * @brief Exibe o ranking do jogo com base nos dados do ScoreboardService.
     * @param scoreboardService O serviço de pontuação que contém os dados do ranking.
     */
    void displayRanking(ScoreboardService& scoreboardService);
  
  protected:
    string gameName;

    /**
     * @brief Exibe as opções de configuração do jogo.
     */
    bool displayConfig();

    /**
     * @brief Exibe as regras na interface.
     */
    virtual bool displayRules() = 0;

    /**
     * @brief Obtém a resposta do jogador exibida na interface.
     * @param content Um vetor de strings contendo o conteúdo da interface.
     * @param header O cabeçalho a ser exibido acima do conteúdo.
     * @param message A mensagem a ser exibida na tela para o usuário no campo de input.
     * @return A resposta do jogador.
     */
    string getUserAnswer(const vector<string>& content, const string header, const string message);

    /**
     * @brief Obtém a escolha do jogador.
     * @param content Um vetor de strings contendo o conteúdo da interface.
     * @param header O cabeçalho a ser exibido acima do conteúdo.
     * @return A escolha do jogador (maiúsculo).
     */
    char getUserChoice(const vector<string>& content, const string header);

    /**
     * @brief Solicita ao usuário que pressione Enter para continuar a execução.
     * @param content Um vetor de strings contendo o conteúdo da interface.
     * @param header O cabeçalho a ser exibido acima do conteúdo.
     */
    void getUserEnter(const vector<string>& content, const string header);

    /**
     * @brief Obtém uma lista de nomes de jogadores a partir da entrada do usuário.
     * @param content O vetor de strings onde adicionar o conteúdo.
     * @param numPlayers O número de jogadores.
     * @return Uma lista de nomes de usuários de jogadores.
     */
    vector<string> getUsernamesList(vector<string>& content, int numPlayers);

    /**
     * @brief Obtém o número de jogadores a partir da entrada do usuário.
     * @return O número de jogadores.
     */
    unsigned int getNumberOfPlayers();

    /**
     * @brief Adiciona uma nova linha de conteúdo ao vetor de strings.
     * @param content O vetor de strings onde adicionar o conteúdo.
     * @param newContent O conteúdo a ser adicionado.
     */
    void addToNextLine(vector<string>& content, const string newContent);

    /**
     * @brief Adiciona conteúdo à linha atual do vetor de strings.
     * @param content O vetor de strings onde adicionar o conteúdo.
     * @param newContent O conteúdo a ser adicionado.
     */
    void addToCurrentLine(vector<string>& content, const string newContent);

    /**
     * @brief Adiciona um número especificado de linhas vazias ao vetor de strings.
     * @param content O vetor de strings onde adicionar as linhas vazias.
     * @param numberOfLines O número de linhas vazias a serem adicionadas.
     */
    void addEmptyLines(vector<string>& content, unsigned int numberOfLines);

  private: 
    /**
     * @brief Constrói o ranking do jogo com base nos dados do ScoreboardService.
     * @param scoreboardService O serviço de pontuação que contém os dados do ranking.
     * @param content O vetor de strings onde o ranking será armazenado.
     */
    void buildRanking(ScoreboardService& scoreboardService, vector<string>& content);

};

#endif
