/**
 * @file view.h
 * @brief Declaração da classe View.
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
 * @brief Classe responsável por criar a interface de um jogo e receber o input do usuário. 
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
        string message;

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

        /**
         * @brief Recebe uma entrada do usuário.
         * @return string 
         */
        string getInput();

    protected:
        PlayerService* player_service;

        /**
         * @brief Define o conteúdo customizável a ser exibido na tela. Cada string do vetor será exibida em 
         * uma linha, caso a string não caiba na linha, ela será separada em multiplas linhas.
         * @param content
         * @throw InvalidStateException Caso o content ultrapasse o número de linhas disponíveis.
         */
        void setContent(vector<string> content);

        /**
         * @brief Define o cabeçalho customizável a ser exibido na tela.
         * @param header
         */
        void setHeader(string header);

        /**
         * @brief Exibe a interface do jogo na tela, com o nome do jogo, conteúdo customizável e o placar.
         * @param message Mensagem a ser exibida na tela para o usuário no campo de input.
         * @returns string Input do usuário.
         */
        string display(string message);
        
    public:
        /**
        * @brief Construtor da classe View.
        * @throw InvalidStateException Caso o número de linhas disponíveis seja menor que 0.
        */
        View();

        /**
        * @brief Destrutor virtual da classe View.
        */
        virtual ~View();

        /**
        * @brief Retorna o conteúdo customizável a ser exibido na tela.
        * @return vector<string>
        */
        vector<string> getContent();

        /**
         * @brief Define o serviço de jogador a ser utilizado pelo view.
         * @param player_service
         * @throw InvalidArgumentException Caso o serviço de jogador seja nulo.
         */
        void setPlayerService(PlayerService* player_service);

        /**
         * @brief Define o serviço de placar a ser utilizado pelo view.
         * @param scoreboard_service
         * @throw InvalidArgumentException Caso o serviço de placar seja nulo.
         * @throw InvalidStateException Caso o placar já tenha sido definido.
         */
        void setScoreboardService(ScoreboardService* scoreboard_service);

        /**
         * @brief Remove o serviço de placar utilizado pelo view.
         */
        void removeScoreboardService();

};

#endif