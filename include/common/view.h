/**
 * @file view.h
 * @brief Arquivo responsável por definir a classe View que serve como base para a interface de um jogo.
*/
#ifndef VIEW
#define VIEW

#include <string>
#include <vector>
#include <map>
#include "services/scoreboard_service.h"
#include "services/player_service.h"

using namespace std;

/**
 * @brief Exceção lançada quando um argumento do view é inválido.
*/
class InvalidArgumentException : public exception {
    public:
        const char* what() const throw() {
            return "Argumento do view inválido!";
        }
};

/**
 * @brief Exceção lançada quando o estado do view é inválido.
*/
class InvalidStateException : public exception {
    public:
        const char* what() const throw() {
            return "Estado do view inválido!";
        }
};

/**
 * @brief Classe responsável por exibir a interface do jogo e receber e tratar o input do usuário. 
*/
class View {
    private:
        // Atributos
        unsigned available_line_nb;
        unsigned int line_nb;
        unsigned int column_nb;
        vector<string> content;

        string header;
        ScoreboardService* scoreboard_service;
        PlayerService* player_service;

        string user_message;

        // Metodos
        void initContent();
        string clean(string str);   

        vector<string> splitString(string str);
        void completeWithEmptyLines();

        string createTopSeparator();
        string createBottomSeparator();
        string wrapInBox(string content);

        vector<pair<string, unsigned int>> formatScoreboard();
        void displayScoreboard();
        
    public:
        /**
         * @brief Classe responsável por gerenciar a exibição de informações na tela e na recepção 
         * e tratamento do input do usuário.
         * @param player_service Serviço de jogador do qual as informações dos jogadores serão retiradas.
         * @param header Cabeçalho customizável a ser exibido na tela, pode ser o nome do jogo.
         * @throw InvalidArgumentException Caso o serviço de jogador seja nulo.
         * @throw InvalidStateException Caso o número de linhas disponíveis seja menor que 0.
         */
        View(PlayerService* player_service, string header);

        /**
         * @brief Destrutor da classe View.
         */
        ~View();

        /**
         * @brief Recebe uma entrada do usuário e a trata.
         * @return string 
         */
        string getInput();

        /**
         * @brief Define o conteúdo customizável a ser exibido na tela, ele será separado em diferentes linhas
         * para caber dentro da interface. Caso ele seja maior que o número de linhas disponíveis, ele será cortado
         * com ... no final.
         * @param content 
         */
        void setContent(string content);

        /**
         * @brief Define o conteúdo customizável a ser exibido na tela. Cada string do vetor será exibida em 
         * uma linha, caso a string não caiba na linha, ela será separada em multiplas linhas.
         * @param content
         * @throw InvalidStateException Caso o content ultrapasse o número de linhas disponíveis.
         */
        void setContent(vector<string> content);

        /**
         * @brief Define o cabeçalho customizável a ser exibido na tela, pode ser o nome do jogo.
         * @param header
         */
        void setHeader(string header);

        /**
         * @brief Define o serviço de placar a ser utilizado pelo view.
         * @param scoreboard_service
         * @throw InvalidArgumentException Caso o serviço de placar seja nulo.
         * @throw InvalidStateException Caso o placar já tenha sido definido.
         */
        void setScoreboardService(ScoreboardService* scoreboard_service);

        /**
        * @brief Retorna o conteúdo customizável a ser exibido na tela.
        * @return vector<string>
        */
        vector<string> getContent();

        /**
         * @brief Exibe a interface do jogo na tela, com o nome do jogo, conteúdo customizável e o placar.
         * @returns string Input do usuário.
         */
        string display();

        /**
         * @brief Exibe a interface do jogo na tela, com o nome do jogo, conteúdo customizável e o placar.
         * @param user_message Mensagem a ser exibida na tela para o usuário no campo de input.
         * @returns string Input do usuário.
         */
        string display(string user_message);
};

#endif