#ifndef RODADA_H
#define RODADA_H

#include <string>
#include "../../common/services/ai_service.h"
#include <regex>

class Rodada
{
private:
    AIService aiService;
    int _pontuacao_da_rodada;

public:
    Rodada(int pontuacao_da_rodada);

    std::string fazer_pergunta(std::string pergunta, std::string tema, std::string objeto);

    double calcularSimilaridade(const std::string &resposta_usuario, std::string objeto);

    bool verificar_resposta_correta(const std::string &resposta_usuario, std::string objeto);

    int get_pontuacao_da_rodada();

    void decrease_pontuacao_rodada();

    bool verificar_fim_rodada(std::string resposta, std::string objeto);

    bool verificar_pont_rod_neg_or_zero();
};

#endif // RODADA_H