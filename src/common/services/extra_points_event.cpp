#include "../../../include/common/services/extra_points_event.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

ExtraPointsEvent::ExtraPointsEvent() : Event(EventType::RANDOM)
{}

string ExtraPointsEvent::getName()
{
    return "ExtraPointEvent";
}

string ExtraPointsEvent::getDescription()
{
    return "Evento que aumenta a pontuação do jogador atual.";
}

/**
 * @brief Executa o evento ExtraPointsEvent, concedendo pontos extras ao jogador atual.
 * 
 * Este método é responsável por adicionar pontos extras ao placar do jogador atual.
 * Ele obtém o jogador atual por meio do serviço de jogadores e aumenta o seu placar
 * adicionando uma quantidade fixa de pontos.
 * 
 * @param player_service Serviço de gerenciamento de jogadores.
 * @param scoreboard_service Serviço de gerenciamento do placar.
 */
void ExtraPointsEvent::run(unsigned int score, PlayerService* player_service, ScoreboardService* scoreboard_service)
{
    Player& player = player_service->getCurrentPlayer();  ///< Obtém o jogador atual.

    int new_score = score * 2;  ///< Calcula o novo placar.

    scoreboard_service->changeScore(player.getId(), new_score);  ///< Atualiza o placar do jogador.
}
