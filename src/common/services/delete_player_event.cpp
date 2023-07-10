#include "../../../include/common/services/delete_player_event.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

DeletePlayerEvent::DeletePlayerEvent() : Event(EventType::RANDOM)
{}

string DeletePlayerEvent::getName()
{
        return "DeletePlayerEvent";
}

string DeletePlayerEvent::getDescription()
{
        return "Evento que exclui um player do jogo.";
}

bool DeletePlayerEvent::canRun()
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
 * @brief Executa o evento DeletePlayerEvent, que remove o jogador atual do jogo.
 * 
 * Obtém o jogador atual por meio do serviço de jogadores e, em seguida, remove o jogador do jogo
 * usando o serviço de jogadores.
 */
void DeletePlayerEvent::run(unsigned int score, PlayerService* player_service, ScoreboardService* scoreboard_service)
{
	Player& currentPlayer = player_service->getCurrentPlayer();
        
        player_service->removePlayer(currentPlayer.getId());
}


