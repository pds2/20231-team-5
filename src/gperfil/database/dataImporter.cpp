#include "../../../include/gperfil/database/dataImporter.h"
#include <iostream>
#include <fstream>

DataImporter::DataImporter()
{
    // Construtor padrão da classe DataImporter
}

void DataImporter::carregar_arquivos(const std::string& nomeArquivo, std::vector<std::string>& dados)
{
    // Carrega os dados de um arquivo e armazena em um vetor
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    if (!arquivo)
    {
        throw FileDoesNotOpen();
    }

    while (std::getline(arquivo, linha))
    {
        dados.push_back(linha);
    }

    arquivo.close();
}

void DataImporter::adicionar_arquivo_a_vetor()
{
    // Adiciona os arquivos de dados aos vetores correspondentes
    carregar_arquivos("files/gperfil/filmes.txt", _Filme);
    carregar_arquivos("files/gperfil/alimentos.txt", _Alimento);
    carregar_arquivos("files/gperfil/cidades.txt", _Cidade);
    carregar_arquivos("files/gperfil/musica.txt", _Musica);
    carregar_arquivos("files/gperfil/paises.txt", _Pais);
    carregar_arquivos("files/gperfil/personalidades_atuais.txt", _Personalidade_Atual);
    carregar_arquivos("files/gperfil/personalidades_historicas.txt", _Personalidade_Historica);
    carregar_arquivos("files/gperfil/livros.txt", _Livro);
}

void DataImporter::adicionar_tema_a_map()
{
    // Adiciona os temas e seus respectivos vetores de dados ao mapa de relacionamento
    _relacao["Filme"] = _Filme;
    _relacao["Alimento"] = _Alimento;
    _relacao["Cidade"] = _Cidade;
    _relacao["Musica"] = _Musica;
    _relacao["Pais"] = _Pais;
    _relacao["Personalidade Historica"] = _Personalidade_Historica;
    _relacao["Personalidade Atual"] = _Personalidade_Atual;
    _relacao["Livro"] = _Livro;
}

std::vector<std::string> DataImporter::get_relacao(std::string tema)
{
    // Retorna os dados relacionados a um tema específico
    return _relacao[tema];
}
