/**
 * @file event_service.h
 * @brief Classe que representa um serviço de eventos. O serviço de eventos é
 * responsável por gerenciar os eventos do jogo e como eles são executados.
*/

#ifndef EVENT_SERVICE
#define EVENT_SERVICE

#include "../database/event.h"

using namespace std;

/**
 * @brief Exceção lançada quando um evento não existe.
*/
class EventDoesNotExistException : public exception {
    public:
        virtual const char* what() const throw() {
            return "Evento não existe";
        }
};

/**
 * @brief Classe que representa um serviço de eventos. O serviço de eventos é
 * responsável por gerenciar os eventos do jogo e como eles são executados.
*/
class EventService{
    private:
        vector<Event*> events;
        Event* currentEvent;

    public:
        /**
         * @brief Construtor da classe EventService.
         * @param events Vetor de ponteiros para eventos a serem adicionados ao serviço.
        */
        EventService();

        /**
         * @brief Destrutor da classe EventService.
        */
        ~EventService();
        
        /**
        * @brief Adiciona um evento ao serviço de eventos.
        * 
        * @param event Um ponteiro para o evento a ser adicionado.
        */
        void addEvent(Event* event);


        /**
         * @brief Retorna um evento cadastrado no serviço pelo nome.
         * @param event_name Nome do evento a ser retornado.
         * @return Ponteiro para o evento.
         * @throws EventDoesNotExistException se o evento não existir.
        */
        Event* getEvent(string event_name);

        /**
         * @brief Tenta executar todos os eventos cadastrados no serviço. As regras
         * de execução e quando cada evento deve ser executado são definidos dentro
         * de cada evento.
         * @param player_service Serviço de jogadores.
         * @param scoreboard_service Serviço de placar.
         * @throws EventDoesNotExistException se o evento não existir.
        */
        //void run(PlayerService* player_service, ScoreboardService* scoreboard_service);


        /**
         * @brief Tenta executar todos os eventos cadastrados no serviço. As regras
         * de execução e quando cada evento deve ser executado são definidos dentro
         * de cada evento.
         * @param player_service Serviço de jogadores.
         * @param scoreboard_service Serviço de placar.
         * @throws EventDoesNotExistException se o evento não existir.
        */
        void runCurrentEvent(unsigned int, PlayerService* player_service, ScoreboardService* scoreboard_service);

        /**
         * @brief Encontra o próximo evento que pode ser executado.
         * Esta função percorre todos os eventos registrados no serviço e verifica se algum deles pode ser executado.
         * Se encontrar um evento que possa ser executado, atribui esse evento à variável currentEvent e retorna true.
         * Caso contrário, retorna false.
         *
         * @return true se um evento executável foi encontrado, false caso contrário.
        */
        bool getRunnableEvent();
};

#endif
