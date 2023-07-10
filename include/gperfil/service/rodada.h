#ifndef RODADA_H
#define RODADA_H

#include <string>
#include "../../common/services/ai_service.h"
#include <regex>

/**
 * @brief Classe que representa uma rodada do jogo
 */
class Rodada
{
private:
    AIService aiService;        /**< Serviço de IA para realizar interações de chat */
    int _pontuacao_da_rodada;   /**< Pontuação da rodada */

public:
    /**
     * @brief Construtor da classe Rodada
     * @param pontuacao_da_rodada Pontuação inicial da rodada
     */
    Rodada(int pontuacao_da_rodada);

    /**
     * @brief Faz uma pergunta ao usuário e retorna a resposta fornecida
     * @param pergunta Pergunta a ser feita ao usuário
     * @param tema Tema relacionado à pergunta
     * @param objeto Objeto sobre o qual a pergunta é feita
     * @return Resposta do usuário à pergunta
     */
    std::string fazer_pergunta(std::string pergunta, std::string tema, std::string objeto);

    /**
     * @brief Calcula a similaridade entre a resposta do usuário e um objeto
     * @param resposta_usuario Resposta do usuário
     * @param objeto Objeto a ser comparado
     * @return Valor de similaridade entre 0.0 e 1.0
     */
    double calcularSimilaridade(const std::string &resposta_usuario, std::string objeto);

    /**
     * @brief Verifica se a resposta do usuário está correta com base em um objeto
     * @param resposta_usuario Resposta do usuário
     * @param objeto Objeto a ser comparado
     * @return True se a resposta estiver correta, False caso contrário
     */
    bool verificar_resposta_correta(const std::string &resposta_usuario, std::string objeto);

    /**
     * @brief Obtém a pontuação da rodada
     * @return Pontuação da rodada
     */
    int get_pontuacao_da_rodada();

    /**
     * @brief Diminui a pontuação da rodada em 2 pontos
     */
    void decrease_pontuacao_rodada();

    /**
     * @brief Verifica se a rodada chegou ao fim
     * @param resposta Resposta do usuário
     * @param objeto Objeto a ser comparado
     * @return True se a rodada chegou ao fim, False caso contrário
     */
    bool verificar_fim_rodada(std::string resposta, std::string objeto);

    /**
     * @brief Verifica se a pontuação da rodada é negativa ou zero
     * @return True se a pontuação da rodada for negativa ou zero, False caso contrário
     */
    bool verificar_pont_rod_neg_or_zero();
};

#endif // RODADA_H
