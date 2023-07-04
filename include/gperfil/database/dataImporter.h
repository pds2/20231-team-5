#ifndef DATALOADER_H
#define DATALOADER_H
#include <vector>
#include <map>
#include <string>

/**
 * @brief Exceção lançada quando não é possível abrir o arquivo.
 */
class FileDoesNotOpen : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Não foi possível abrir o arquivo!";
    }
};

class DataImporter
{
private:
    std::vector<std::string> _Filme;                          /**< Dados carregados do arquivo de filmes */
    std::vector<std::string> _Alimento;                       /**< Dados carregados do arquivo de alimentos */
    std::vector<std::string> _Personalidade_Historica;        /**< Dados carregados do arquivo de personalidades históricas */
    std::vector<std::string> _Personalidade_Atual;            /**< Dados carregados do arquivo de personalidades atuais */
    std::vector<std::string> _Livro;                          /**< Dados carregados do arquivo de livros */
    std::vector<std::string> _Cidade;                         /**< Dados carregados do arquivo de cidades */
    std::vector<std::string> _Pais;                           /**< Dados carregados do arquivo de países */
    std::vector<std::string> _Musica;                         /**< Dados carregados do arquivo de músicas */
    std::map<std::string, std::vector<std::string>> _relacao; /**< Mapa relacionando tipos de objetos aos seus dados correspondentes */

    void carregar_arquivos(const std::string &nomeArquivo, std::vector<std::string> &dados);

public:
    DataImporter();

    std::vector<std::string> get_relacao(std::string tema);

    void adicionar_tema_a_map();

    void adicionar_arquivo_a_vetor();
};

#endif