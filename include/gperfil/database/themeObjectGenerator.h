#ifndef THEME_OBJECT_GENERATOR_H
#define THEME_OBJECT_GENERATOR_H
#include <string>
#include "dataImporter.h"

class ThemeObjectGenerator
{

private:
    std::string _tema;

    std::string _objeto;

    void definir_tema();

public:
    ThemeObjectGenerator();

    void sortear_objeto();

    std::string get_objeto();

    std::string get_tema();
};

#endif