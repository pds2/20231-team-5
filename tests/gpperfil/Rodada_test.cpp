#include "../../include/gperfil/service/rodada.h"
#include "../../include/third_party/doctest/doctest.h"
#include <sstream>
#include <fstream>

TEST_CASE("Verificar pontuação inicial da rodada")
{
    Rodada rodada(10);
    CHECK_EQ(rodada.get_pontuacao_da_rodada(), 10);
}

TEST_CASE("Diminuir pontuação da rodada")
{
    Rodada rodada(10);
    rodada.decrease_pontuacao_rodada();
    CHECK_EQ(rodada.get_pontuacao_da_rodada(), 8);
}

TEST_CASE("Calcular similaridade entre resposta do usuário e objeto")
{
    Rodada rodada(10);
    double similaridade = rodada.calcularSimilaridade("banana", "maçã");
    CHECK(similaridade > 0.0);
    CHECK(similaridade <= 1.0);
}

TEST_CASE("Verificar resposta correta do usuário")
{
    Rodada rodada(10);
    bool correta = rodada.verificar_resposta_correta("banana", "maçã");
    CHECK_FALSE(correta);

    correta = rodada.verificar_resposta_correta("maçã", "maçã");
    CHECK(correta);
}