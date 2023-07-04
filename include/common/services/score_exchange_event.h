#ifndef SCORE_EXCHANGE_EVENT
#define SCORE_EXCHANGE_EVENT

#include "../database/event.h"

#include <iostream>
#include <string>

/**
 * @brief Classe que representa o evento ScoreExchangeEvent, responsável por trocar os pontos entre o jogador atual e o último colocado no placar.
 * 
 * A classe ScoreExchangeEvent herda da classe Event e implementa a funcionalidade de trocar os pontos entre o jogador atual e o último colocado no placar.
 * Ela possui métodos para verificar se o evento pode ser executado e para executar o evento em si.
 * 
 * A classe também possui atributos para armazenar o nome e a descrição do evento.
 */
class ScoreExchangeEvent : public Event
{
    private:
        string name;  ///< O nome do evento.
        string description;  ///< A descrição do evento.
    
    public:
        /**
         * @brief Construtor da classe ScoreExchangeEvent.
         */
        ScoreExchangeEvent();
        
        /**
         * @brief Verifica se o evento pode ser executado.
         * 
         * Este método verifica se o tipo do evento condiz com a regra de execução padrão.
         * Caso contrário, lança uma exceção EventTypeMismatchException.
         * 
         * @return true se o evento pode ser executado.
         * @return false se o evento não pode ser executado.
         * @throws EventTypeMismatchException se o tipo do evento não condiz com a regra de execução padrão.
         */
        bool canRun() override;

        /**
         * @brief Executa o evento ScoreExchangeEvent, trocando os pontos entre o jogador atual e o último colocado no placar.
         * 
         * Este método é responsável por trocar os pontos entre o jogador atual e o último colocado no placar.
         * Ele obtém o jogador atual por meio do serviço de jogadores e o último colocado no placar por meio do serviço de placar.
         * Em seguida, realiza a troca dos pontos entre os dois jogadores, atualizando seus respectivos placares.
         * 
         * @param player_service Serviço de gerenciamento de jogadores.
         * @param scoreboard_service Serviço de gerenciamento do placar.
         */
        void run(PlayerService* player_service, ScoreboardService* scoreboard_service) override;
};

#endif 