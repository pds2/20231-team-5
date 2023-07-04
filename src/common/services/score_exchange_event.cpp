#include "../../../include/common/services/score_exchange_event.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

ScoreExchangeEvent::ScoreExchangeEvent() : Event(EventType::RANDOM)
{
        this->name = "ScoreExchangeEvent";
        this->description = "Evento que troca a pontuação entre players.";
}

bool ScoreExchangeEvent::canRun()
{
    if (getType() != EventType::RANDOM)
    {
        throw EventTypeMismatchException();
    }

    if (isActive() == false)
    {
        return false;
    }

    std::srand(std::time(nullptr));

    int numCount = 100;

	for (int i = 0; i < numCount; ++i)
	{
    	int random_number = std::rand() % 100;  // Gera um número entre 0 e 99

    	if (random_number == 0)  // 1% de chance (0 representa 1 em 100)
        {
            return true;
        }
	}

    return false;
}

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
void ScoreExchangeEvent::run(PlayerService* player_service, ScoreboardService* scoreboard_service)
{
    Player& current_player = player_service->getCurrentPlayer();  ///< Obtém o jogador atual.
    int score_current_player = scoreboard_service->getScore(current_player.getId());  ///< Obtém os pontos do jogador atual.

    int last_player = scoreboard_service->getRanking().back();  ///< Obtém o último colocado no placar.
    int score_last_player = scoreboard_service->getScore(last_player);  ///< Obtém os pontos do último colocado.

    // Troca os pontos entre os jogadores
    scoreboard_service->changeScore(current_player.getId(), score_last_player);
    scoreboard_service->changeScore(last_player, score_current_player);
}
