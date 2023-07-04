#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include <algorithm>

#include "../../../include/gperfil/service/rodada.h"


Rodada::Rodada(int pontuacao_da_rodada) : aiService(" ")
{
    _pontuacao_da_rodada = pontuacao_da_rodada;
}

bool contemCaracteresNaoEscapados(const std::string &str)
{
    // Procurar por caractere CR não escapado
    if (str.find('\r') != std::string::npos)
    {
        return true; // Caractere CR não escapado encontrado
    }
    return false; // Nenhum caractere não escapado encontrado
}

void Rodada::fazer_pergunta(std::string pergunta, std::string tema, std::string objeto)
{
    decrease_pontuacao_rodada();
    std::string tema_para_prompt = tema;
    std::string objeto_para_prompt = objeto;

    // Verificar objeto_para_prompt
    if (contemCaracteresNaoEscapados(objeto_para_prompt))
    {
        // Substituir caracteres não escapados por sequências de escape apropriadas
        std::replace(objeto_para_prompt.begin(), objeto_para_prompt.end(), '\r', '\n');
        // Outras substituições de caracteres não escapados podem ser adicionadas aqui, se necessário
    }
    if (contemCaracteresNaoEscapados(pergunta))
    {
        // Substituir caracteres não escapados por sequências de escape apropriadas
        std::replace(pergunta.begin(), pergunta.end(), '\r', '\n');
        // Outras substituições de caracteres não escapados podem ser adicionadas aqui, se necessário
    }

    aiService.restartChat();

    std::string x = "Olá, irei fazer um jogo o qual o usuario irá fazer uma pergunta sobre um elemento de um conjunto de " + tema_para_prompt + ",esse elemento é " + objeto_para_prompt +
                    ", e vc irá responder sem citar o nome do " + objeto_para_prompt + " atenção em hipotese alguma vc pode citar o nome " + objeto_para_prompt;
    aiService.chat(x);

    // std::string prompt = "olá, vamos jogar um jogo, eu irei digitar uma pergunta sobre: '" + objeto_para_prompt +
    //                      "', e vc irá responder sem citar '" + objeto_para_prompt + "'.";
    std::string prompt = "A pergunta é: " + pergunta;
    std::string resposta = aiService.chat(prompt);
    std::cout << resposta << std::endl;
}

double Rodada::calcularSimilaridade(const std::string &resposta_usuario, std::string objeto)
{
    std::string resposta_correta_lowercase = objeto;
    std::string resposta_usuario_lowercase = resposta_usuario;

    // Converter ambas as strings para letras minúsculas
    std::transform(resposta_correta_lowercase.begin(), resposta_correta_lowercase.end(), resposta_correta_lowercase.begin(), ::tolower);
    std::transform(resposta_usuario_lowercase.begin(), resposta_usuario_lowercase.end(), resposta_usuario_lowercase.begin(), ::tolower);

    // Remover espaços em branco
    resposta_correta_lowercase.erase(std::remove(resposta_correta_lowercase.begin(), resposta_correta_lowercase.end(), ' '), resposta_correta_lowercase.end());
    resposta_usuario_lowercase.erase(std::remove(resposta_usuario_lowercase.begin(), resposta_usuario_lowercase.end(), ' '), resposta_usuario_lowercase.end());

    int distancia = 0;

    // Calcular a distância de Levenshtein
    const int m = resposta_correta_lowercase.length();
    const int n = resposta_usuario_lowercase.length();
    int **dp = new int *[m + 1];

    for (int i = 0; i <= m; i++)
    {
        dp[i] = new int[n + 1];
        dp[i][0] = i;
    }

    for (int j = 0; j <= n; j++)
    {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + (resposta_correta_lowercase[i - 1] != resposta_usuario_lowercase[j - 1])});
        }
    }

    distancia = dp[m][n];

    // Liberar memória
    for (int i = 0; i <= m; i++)
    {
        delete[] dp[i];
    }
    delete[] dp;

    // Calcular a similaridade
    double similaridade = 1.0 - (static_cast<double>(distancia) / std::max(m, n));

    return similaridade;
}

bool Rodada::verificar_resposta_correta(const std::string &resposta_usuario, std::string objeto)
{
    double limite_similaridade = 0.6; // Defina um limite de similaridade desejado

    double similaridade = calcularSimilaridade(resposta_usuario, objeto);

    if (similaridade >= limite_similaridade)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Rodada::get_pontuacao_da_rodada()
{
    return _pontuacao_da_rodada;
}

void Rodada::decrease_pontuacao_rodada()
{
    _pontuacao_da_rodada -= 1;
}

bool Rodada::verificar_fim_rodada(std::string resposta, std::string objeto)
{
    if (verificar_resposta_correta(resposta, objeto))
    {
        return true;
    }

    else if (get_pontuacao_da_rodada() <= 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}
bool Rodada::verificar_pont_rod_neg_or_zero()
{
    if (get_pontuacao_da_rodada() <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}