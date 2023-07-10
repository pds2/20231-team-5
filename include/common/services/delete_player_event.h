#ifndef DELETE_PLAYER_EVENT
#define DELETE_PLAYER_EVENT

#include "../database/event.h"

#include <iostream>
#include <string>

/**
 * @brief Classe que representa um evento específico do jogo, onde o jogador atual é deletado.
 */
class DeletePlayerEvent : public Event
{
	private:
		string name; /**< Nome específico do evento DeletePlayerEvent */
        string description; /**< Descrição específica do evento DeletePlayerEvent */
	public:
		/**
		 * @brief Construtor da classe DeletePlayerEvent.
		 * Inicializa os atributos name e description com valores adequados para o evento DeletePlayerEvent.
		 */
		DeletePlayerEvent();
		
		/**
     	 * @brief Retorna o nome do evento.
     	 * @return string nome do evento.
     	 */
		string getName() override;

		/**
     	 * @brief Retorna o nome do evento.
     	 * @return string nome do evento.
    	 */
		string getDescription() override;

		/**
		 * @brief Verifica se o evento DeletePlayerEvent pode ser executado.
		 * @return true se o evento pode ser executado.
		 * @return false se o evento não pode ser executado.
		 */
		bool canRun() override;
		
		/**
		 * @brief Executa o evento DeletePlayerEvent.
		 * @param player_service serviço de gerenciamento de jogadores.
		 * @param scoreboard_service serviço de gerenciamento do placar.
		 */
		void run(unsigned int score, PlayerService* player_service, ScoreboardService* scoreboard_service) override;
};
		

#endif 
