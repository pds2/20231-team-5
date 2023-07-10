#include "../../../include/common/services/extra_points_event.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

ExtraPointsEvent::ExtraPointsEvent() : Event(EventType::RANDOM)
{
        this->name = "ExtraPointEvent";
        this->description = "Evento que aumenta a pontuação do jogador atual.";
}

ExtraPointsEvent::~ExtraPointsEvent(){}

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
void ExtraPointsEvent::run(PlayerService* player_service, ScoreboardService* scoreboard_service)
{
    const int EXTRA_POINTS = 10;  ///< Quantidade fixa de pontos extras a serem concedidos.

    Player& player = player_service->getCurrentPlayer();  ///< Obtém o jogador atual.

    int new_score = scoreboard_service->getScore(player.getId()) + EXTRA_POINTS;  ///< Calcula o novo placar.

    scoreboard_service->changeScore(player.getId(), new_score);  ///< Atualiza o placar do jogador.
}