// #ifndef VIEWTRIVIA_H
// #define VIEWTRIVIA_H

// #include <string>
// using std::string;

// #include <vector>
// using std::vector;

// #include "../../common/view.h"

// /**
//  * @brief Exceção lançada quando o jogador sai do jogo.
//  */
// class ExitGame : public std::exception {
//   public:
//     const char* what() const throw() {
//       return "O jogador saiu do jogo.";
//   }
// };

// /**
//  * @brief Exceção lançada quando um número inválido é fornecido.
//  */
// class InvalidNumber : public exception {
//   public:
//     const char* what() const throw() {
//       return "Número inválido!";
//     }
// };

// /**
//  * @brief Enumeração que representa o tipo de jogo.
//  */
// enum GameType {
//   SinglePlayer, 
//   MultiPlayer
// };

// /**
//  * @brief Classe responsável pela interface de visualização do jogo.
//  */
// class ViewPerfil : public View {

//   public:
//     /**
//      * @brief Construtor da classe ViewTrivia.
//      * @param player_service Um ponteiro para o serviço de jogador.
//      */
//     ViewPerfil(PlayerService* player_service);

//     /**
//      * @brief Exibe o menu e retorna o tipo de jogo escolhido pelo jogador.
//      * @return O tipo de jogo selecionado (SinglePlayer ou MultiPlayer).
//      */
//     void displayMenu();

//     /**
//      * @brief Exibe uma pergunta e retorna a resposta do jogador.
//      * @param userCard O cartão para exibir a pergunta.
//      * @param content Um vetor de strings contendo o conteúdo da interface.
//      * @param header O cabeçalho a ser exibido acima do conteúdo.
//      * @return A resposta do jogador.
//      */
//     // string displayQuestion(const QuizCard& userCard, std::vector<string>& content, const string header);

//     // /**
//     //  * @brief Exibe o feedback para a resposta do jogador.
//     //  * @param feedback O feedback a ser exibido.
//     //  * @param content Um vetor de strings contendo o conteúdo da interface.
//     //  * @param header O cabeçalho a ser exibido acima do conteúdo.
//     //  */
//     // void displayFeedback(const string feedback, std::vector<string>& content, const string header);

//     // /**
//     //  * @brief Obtém a escolha do jogador.
//     //  * @param content Um vetor de strings contendo o conteúdo da interface.
//     //  * @param header O cabeçalho a ser exibido acima do conteúdo.
//     //  * @return A escolha do jogador.
//     //  */
//     char getUserChoice(const vector<string>& content, const string header);

//     /**
//      * @brief Obtém a resposta do jogador exibida na interface.
//      * @param content Um vetor de strings contendo o conteúdo da interface.
//      * @param header O cabeçalho a ser exibido acima do conteúdo.
//      * @return A resposta do jogador.
//      */
//     string getUserAnswer(const vector<string>& content, const string header);

//   private:
//     /**
//      * @brief Exibe as opções para o modo de jogo single player.
//      * @param gameType O tipo de jogo a ser preenchido de acordo com a escolha do jogador.
//      */
//     // bool displaySinglePlayer(GameType& gameType);

//     // /**
//     //  * @brief Exibe as opções para o modo de jogo multiplayer.
//     //  * @param gameType O tipo de jogo a ser preenchido de acordo com a escolha do jogador.
//     //  */
//     bool displayMultiPlayer();

//     /**
//      * @brief Exibe as regras do jogo na interface.
//      */
//     bool displayRules();

//     /**
//      * @brief Adiciona uma nova linha de conteúdo ao vetor de strings.
//      * @param content O vetor de strings onde adicionar o conteúdo.
//      * @param newContent O conteúdo a ser adicionado.
//      */
//     void addToNextLine(vector<string>& content, const string newContent);

//     /**
//      * @brief Adiciona conteúdo à linha atual do vetor de strings.
//      * @param content O vetor de strings onde adicionar o conteúdo.
//      * @param newContent O conteúdo a ser adicionado.
//      */
//     void addToCurrentLine(vector<string>& content, const string newContent);

//     /**
//      * @brief Adiciona um número especificado de linhas vazias ao vetor de strings.
//      * @param content O vetor de strings onde adicionar as linhas vazias.
//      * @param numberOfLines O número de linhas vazias a serem adicionadas.
//      */
//     void addEmptyLines(vector<string>& content, unsigned int numberOfLines);

//     /**
//      * @brief Obtém o número de jogadores a partir da entrada do usuário.
//      * @return O número de jogadores.
//      */
//     unsigned int getNumberOfPlayers();

//     // /**
//     //  * @brief Obtém o nome de usuário do jogador a partir da entrada do usuário.
//     //  * @param content O vetor de strings onde adicionar o conteúdo.
//     //  * @return O nome de usuário do jogador.
//     //  */
//     // string getUsername(vector<string>& content);

//     /**
//      * @brief Obtém uma lista de nomes de jogadores a partir da entrada do usuário.
//      * @param content O vetor de strings onde adicionar o conteúdo.
//      * @param numPlayers O número de jogadores.
//      * @return Uma lista de nomes de usuários de jogadores.
//      */
//     vector<string> getUsernamesList(vector<string>& content, int numPlayers);

// };

// #endif







// /**
//  * @file viewtrivia.h
//  * @brief Declaração da classe ViewTrivia.
//  */

// #ifndef VIEWTRIVIA_H
// #define VIEWTRIVIA_H

// #include <string>
// using std::string;

// #include <vector>
// using std::vector;

// #include "../../common/view.h"

// /**
//  * @brief Exceção lançada quando o jogador sai do jogo.
//  */
// class ExitGame : public std::exception
// {
// public:
//   const char *what() const throw()
//   {
//     return "O jogador saiu do jogo.";
//   }
// };

// /**
//  * @brief Exceção lançada quando um número inválido é fornecido.
//  */
// class InvalidNumber : public exception
// {
// public:
//   const char *what() const throw()
//   {
//     return "Número inválido!";
//   }
// };

// /**
//  * @brief Enumeração que representa o tipo de jogo.
//  */
// enum GameType
// {
//   SinglePlayer,
//   MultiPlayer
// };

// /**
//  * @brief Classe responsável pela interface de visualização do jogo.
//  */
// class ViewPerfil : public ViewGame
// {

// public:
//   void display_resp_correct(std::string respostaUsuario, std::string corretude, bool acabou);
//   string displayresposta(std::vector<string> &content, const string header, std::string tema, std::string resposta_chat);
//   string displaypergunta(std::vector<string> &content, const string header, std::string tema);
//   /**
//    * @brief Construtor da classe ViewTrivia.
//    * @param player_service Um ponteiro para o serviço de jogador.
//    */
//   ViewPerfil(PlayerService *player_service);

//   /**
//    * @brief Exibe o menu e retorna o tipo de jogo escolhido pelo jogador.
//    * @param header O cabeçalho a ser exibido acima do conteúdo.
//    * @return O tipo de jogo selecionado (SinglePlayer ou MultiPlayer).
//    */
//   GameType displayMenu(const string header);

//   // /**
//   //  * @brief Exibe uma pergunta e retorna a resposta do jogador.
//   //  * @param userCard O cartão para exibir a pergunta.
//   //  * @param content Um vetor de strings contendo o conteúdo da interface.
//   //  * @param header O cabeçalho a ser exibido acima do conteúdo.
//   //  * @return A resposta do jogador.
//   //  */
//   // string displayQuestion(const QuizCard& userCard, std::vector<string>& content, const string header);

//   /**
//    * @brief Exibe o feedback para a resposta do jogador.
//    * @param feedback O feedback a ser exibido.
//    * @param content Um vetor de strings contendo o conteúdo da interface.
//    * @param header O cabeçalho a ser exibido acima do conteúdo.
//    */
//   void displayFeedback(const string feedback, std::vector<string> &content, const string header);

//   /**
//    * @brief Obtém a escolha do jogador.
//    * @param content Um vetor de strings contendo o conteúdo da interface.
//    * @param header O cabeçalho a ser exibido acima do conteúdo.
//    * @return A escolha do jogador.
//    */
//   char getUserChoice(const vector<string> &content, const string header);

//   /**
//    * @brief Obtém a resposta do jogador exibida na interface.
//    * @param content Um vetor de strings contendo o conteúdo da interface.
//    * @param header O cabeçalho a ser exibido acima do conteúdo.
//    * @return A resposta do jogador.
//    */
//   string getUserAnswer(const vector<string> &content, const string header);

//   /**
//    * @brief Solicita ao usuário que pressione Enter para continuar a execução.
//    * @param content Um vetor de strings contendo o conteúdo da interface.
//    * @param header O cabeçalho a ser exibido acima do conteúdo.
//    */
//   void getUserEnter(const vector<string> &content, const string header);

//   /**
//    * @brief Adiciona uma nova linha de conteúdo ao vetor de strings.
//    * @param content O vetor de strings onde adicionar o conteúdo.
//    * @param newContent O conteúdo a ser adicionado.
//    */
//   void addToNextLine(vector<string> &content, const string newContent);

// private:
//   /**
//    * @brief Exibe as opções para o modo de jogo single player.
//    * @param gameType O tipo de jogo a ser preenchido de acordo com a escolha do jogador.
//    */
//   bool displaySinglePlayer(GameType &gameType);

//   /**
//    * @brief Exibe as opções para o modo de jogo multiplayer.
//    * @param gameType O tipo de jogo a ser preenchido de acordo com a escolha do jogador.
//    */
//   bool displayMultiPlayer(GameType &gameType);

//   /**
//    * @brief Exibe as regras do jogo na interface.
//    */
//   bool displayRules();

//   // /**
//   //  * @brief Adiciona uma nova linha de conteúdo ao vetor de strings.
//   //  * @param content O vetor de strings onde adicionar o conteúdo.
//   //  * @param newContent O conteúdo a ser adicionado.
//   //  */
//   // void addToNextLine(vector<string>& content, const string newContent);

//   /**
//    * @brief Adiciona conteúdo à linha atual do vetor de strings.
//    * @param content O vetor de strings onde adicionar o conteúdo.
//    * @param newContent O conteúdo a ser adicionado.
//    */
//   void addToCurrentLine(vector<string> &content, const string newContent);

//   /**
//    * @brief Adiciona um número especificado de linhas vazias ao vetor de strings.
//    * @param content O vetor de strings onde adicionar as linhas vazias.
//    * @param numberOfLines O número de linhas vazias a serem adicionadas.
//    */
//   void addEmptyLines(vector<string> &content, unsigned int numberOfLines);

//   /**
//    * @brief Obtém o número de jogadores a partir da entrada do usuário.
//    * @return O número de jogadores.
//    */
//   unsigned int getNumberOfPlayers();

//   /**
//    * @brief Obtém o nome de usuário do jogador a partir da entrada do usuário.
//    * @param content O vetor de strings onde adicionar o conteúdo.
//    * @return O nome de usuário do jogador.
//    */
//   string getUsername(vector<string> &content);

//   /**
//    * @brief Obtém uma lista de nomes de jogadores a partir da entrada do usuário.
//    * @param content O vetor de strings onde adicionar o conteúdo.
//    * @param numPlayers O número de jogadores.
//    * @return Uma lista de nomes de usuários de jogadores.
//    */
//   vector<string> getUsernamesList(vector<string> &content, int numPlayers);
// };

// #endif





/**
 * @file viewperfil.h
 * @brief Declaração da classe ViewPerfil.
 */

#ifndef VIEWPERFIL_H
#define VIEWPERFIL_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "../../../include/common/viewgame.h"

/**
 * @brief Classe responsável pela visualização do jogo de Trivia.
 */
class ViewPerfil : public ViewGame{

  private:
    bool displayRules() override;

  public:
    /**
     * @brief Construtor da classe ViewTrivia.
     */
    ViewPerfil();

    void display_resp_correct(std::string respostaUsuario, std::string corretude, bool acabou);
    string displayresposta(std::vector<string> &content, const string header, std::string tema, std::string resposta_chat);
    string displaypergunta(std::vector<string> &content, const string header, std::string tema);

    
};

#endif