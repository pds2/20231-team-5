/**
 * @file event.h
 * @brief Este arquivo contém a declaração da classe Event, que representa um evento genérico do jogo.
 */

#ifndef EVENT
#define EVENT

#include "../services/player_service.h"
#include "../services/scoreboard_service.h"

using namespace std;

/**
 * @brief Exceção lançada quando o tipo do evento não condiz com a regra de execução.
*/
class EventTypeMismatchException : public exception {
    public:
        virtual const char* what() const throw() {
            return "Tipo do evento não condiz com a regra de execução";
        }
};

// POSSUI DUAS DECLARAÇÕES DE MESMA EXCEÇÃO (VIEW.H)

// /**
//  * @brief Exceção lançada quando um argumento do evento é nulo.
// */
// class InvalidArgumentException : public exception {
//     public:
//         const char* what() const throw() {
//             return "Argumento do evento é nulo!";
//         }
// };

/**
 * @brief Enum que representa o tipo de evento. Eventos aleatórios aconcetecem de forma aleatória,
 * enquanto eventos globais acontecem seguindo uma regra que deve ser especificada.
 */
enum EventType{
    RANDOM,
    GLOBAL
};

/**
 * @brief Classe que representa um evento genérico do jogo.
 */
class Event{
    private:
        EventType type;
        bool active;

        string name = "Evento Genérico";
        string description = "Evento genérico do jogo.";
    
    public:
        /**
         * @brief Construtor da classe Event. Por padrão o evento é instanciado já ativo.
         * @param name Nome do evento.
         * @param description Descrição do evento.
         * @param type Tipo do evento.
        */
        Event(EventType type);
        virtual ~Event();
        
        /**
         * @brief Retorna o tipo do evento.
         * @return EventType tipo do evento.
         */
        EventType getType();

        /**
         * @brief Retorna se o evento está ativo.
         * @return true se o evento está ativo.
         * @return false se o evento não está ativo.
         */
        bool isActive();

        /**
         * @brief Ativa o evento.
        */
        void enable();

        /**
         * @brief Desativa o evento.
        */
        void disable();

        /**
         * @brief Retorna o nome do evento.
         * @return string nome do evento.
         */
        string getName();

        /**
         * @brief Retorna a descrição do evento.
         * @return string descrição do evento.
         */
        string getDescription();

        /**
         * @brief Retorna se o evento pode ser executado. A implementação padrão retorna 
         * true com 10% de chance. Esse método pode ser sobrescrito para implementar regras
         * específicas para eventos globais, ou para mudar a chance do evento aleatório acontecer.
         *
         * Caso queira usar a implementação padrão o evento DEVE ser aleatório.
         * 
         * Se o evento estiver desativado então essa função retorna false sempre.
         * 
         * @throws EventTypeMismatchException se o tipo do evento não condiz com a regra de execução padrão.
         * @return true se o evento pode ser rodado
         * @return false se o evento não pode ser rodado
         */
        virtual bool canRun();
        
        /**
         * @brief Executa o evento. Um evento pode ser qualquer acontecimento dentro do jogo, já que os 
         * serviços de jogadores e placar são passados como argumento.
         * @param player_service serviço de gerenciamento de jogadores.
         * @param scoreboard_service serviço de gerenciamento do placar.
         * @throws InvalidArgumentException se algum dos argumentos for nulo.
         */
        virtual void run(PlayerService* player_service, ScoreboardService* scoreboard_service) = 0;
};

#endif