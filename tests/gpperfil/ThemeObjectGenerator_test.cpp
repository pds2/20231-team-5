#include "../../include/gperfil/database/themeObjectGenerator.h"
#include "../../include/third_party/doctest/doctest.h"
#include <sstream>
#include <fstream>

TEST_CASE("Sortear objeto aleatório")
{
    ThemeObjectGenerator generator;

    SUBCASE("Verificar objeto e tema")
    {
        generator.sortear_objeto();
        std::string tema = generator.get_tema();
        std::string objeto = generator.get_objeto();

        CHECK(!tema.empty());
        CHECK(!objeto.empty());
    }
}

TEST_CASE("Sortear múltiplos objetos")
{
    ThemeObjectGenerator generator;

    SUBCASE("Verificar objetos diferentes")
    {
        std::string tema1, tema2, objeto1, objeto2;

        generator.sortear_objeto();
        tema1 = generator.get_tema();
        objeto1 = generator.get_objeto();

        generator.sortear_objeto();
        tema2 = generator.get_tema();
        objeto2 = generator.get_objeto();

        CHECK(tema1 != tema2);
        CHECK(objeto1 != objeto2);
    }
}