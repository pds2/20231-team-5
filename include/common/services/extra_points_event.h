#ifndef EXTRA_POINTS_EVENT
#define EXTRA_POINTS_EVENT

#include "../database/event.h"

#include <iostream>
#include <string>

/**
 * @brief Classe que representa um evento ExtraPointsEvent, que concede pontos extras ao jogador atual.
 * 
 * Esse evento adiciona pontos extras ao jogador atual do jogo quando executado.
 * A classe herda da classe base Event.
 */
class ExtraPointsEvent : public Event
{
private:
    string name;        ///< Nome do evento.
    string description; ///< Descrição do evento.

public:
    /**
     * @brief Construtor da classe ExtraPointsEvent.
     * 
     * Define o nome e a descrição do evento.
     */
    ExtraPointsEvent();

    /**
     * @brief Retorna o nome do evento.
     * @return string nome do evento.
     */
    string getName() override;

    /**
     * @brief Retorna a descrição do evento.
     * @return string a descrição do evento.
     */
    string getDescription() override;
    /**
     * @brief Executa o evento ExtraPointsEvent, concedendo pontos extras ao jogador atual.
     * 
     * Obtém o jogador atual por meio do serviço de jogadores e adiciona pontos extras ao placar
     * do jogador usando o serviço de placar.
     * 
     * @param player_service Serviço de gerenciamento de jogadores.
     * @param scoreboard_service Serviço de gerenciamento do placar.
     */
    void run(unsigned int score, PlayerService* player_service, ScoreboardService* scoreboard_service) override;
};

#endif