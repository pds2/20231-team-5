#ifndef DATAIMPORTER_H
#define DATAIMPORTER_H

#include <vector>
#include <map>
#include <string>

/**
 * @brief Exceção lançada quando não é possível abrir o arquivo.
 */
class FileDoesNotOpen : public std::exception
{
public:
    const char* what() const throw()
    {
        return "Não foi possível abrir o arquivo!";
    }
};

/**
 * @brief Classe responsável por importar e armazenar dados de diferentes temas.
 */
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

    // /**
    //  * @brief Carrega os dados de um arquivo e armazena em um vetor.
    //  * @param nomeArquivo O nome do arquivo a ser carregado.
    //  * @param dados O vetor para armazenar os dados do arquivo.
    //  * @throw FileDoesNotOpen Se o arquivo não puder ser aberto.
    //  */
    // void carregar_arquivos(const std::string& nomeArquivo, std::vector<std::string>& dados);

public:
    /**
     * @brief Construtor padrão da classe DataImporter.
     */
    DataImporter();

    /**
     * @brief Retorna os dados relacionados a um tema específico.
     * @param tema O tema desejado.
     * @return Um vetor contendo os dados relacionados ao tema.
     */
    std::vector<std::string> get_relacao(std::string tema);

    /**
     * @brief Adiciona os arquivos de dados aos vetores correspondentes.
     */
    void adicionar_arquivo_a_vetor();

    /**
     * @brief Adiciona os temas e seus respectivos vetores de dados ao mapa de relacionamento.
     */
    void adicionar_tema_a_map();

    /**
     * @brief Carrega os dados de um arquivo e armazena em um vetor.
     * @param nomeArquivo O nome do arquivo a ser carregado.
     * @param dados O vetor para armazenar os dados do arquivo.
     * @throw FileDoesNotOpen Se o arquivo não puder ser aberto.
     */
    void carregar_arquivos(const std::string& nomeArquivo, std::vector<std::string>& dados);
};

#endif
