#include "../../../include/gperfil/database/themeObjectGenerator.h"

#include <random>

ThemeObjectGenerator::ThemeObjectGenerator()
{
}

void ThemeObjectGenerator::definir_tema()
{
    std::vector<std::string> temas;
    temas = {"Filme", "Alimento", "Personalidade Historica", "Personalidade Atual", "Musica", "Livro", "Cidade", "Pais"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, temas.size() - 1);
    int indice_aleatorio = dis(gen);
    _tema = temas[indice_aleatorio];
}

void ThemeObjectGenerator::sortear_objeto()
{
    definir_tema();
    DataImporter carregar;
    carregar.adicionar_arquivo_a_vetor();
    carregar.adicionar_tema_a_map();

    std::vector<std::string> sorteio_objeto;
    sorteio_objeto = carregar.get_relacao(_tema);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sorteio_objeto.size() - 1);
    int indice_aleatorio1 = dis(gen);
    _objeto = sorteio_objeto[indice_aleatorio1];
}

std::string ThemeObjectGenerator::get_objeto()
{
    return _objeto;
}

std::string ThemeObjectGenerator::get_tema()
{
    return _tema;
}
