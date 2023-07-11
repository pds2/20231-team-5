#include "../../include/gperfil/database/dataImporter.h"
#include "../../include/third_party/doctest/doctest.h"
#include <sstream>
#include <fstream>
#include <vector>





TEST_CASE("Carregar arquivos")
{
    DataImporter dataImporter;
    dataImporter.adicionar_arquivo_a_vetor();
    dataImporter.adicionar_tema_a_map();

    SUBCASE("Verificar tamanho dos vetores")
    {
        CHECK(dataImporter.get_relacao("Filme").size() == 84);
        CHECK(dataImporter.get_relacao("Alimento").size() == 77);
        CHECK(dataImporter.get_relacao("Cidade").size() == 59);
        CHECK(dataImporter.get_relacao("Musica").size() == 99);
        CHECK(dataImporter.get_relacao("Pais").size() == 50);
        CHECK(dataImporter.get_relacao("Personalidade Historica").size() == 44);
        CHECK(dataImporter.get_relacao("Personalidade Atual").size() == 92);
        CHECK(dataImporter.get_relacao("Livro").size() == 58);
    }
}

TEST_CASE("Arquivo não encontrado")
{
    DataImporter dataImporter;
    std::vector<std::string> vetor;
    CHECK_THROWS_AS(dataImporter.carregar_arquivos("essearquivonaoexiste.txt", vetor), FileDoesNotOpen);
}