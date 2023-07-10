#ifndef THEME_OBJECT_GENERATOR_H
#define THEME_OBJECT_GENERATOR_H

#include <string>
#include "dataImporter.h"

/**
 * @brief Classe responsável por gerar objetos de temas aleatórios.
 */
class ThemeObjectGenerator
{

private:
    std::string _tema;   /**< O tema aleatório */
    std::string _objeto; /**< O objeto aleatório */

    /**
     * @brief Define um tema aleatório para gerar o objeto.
     */
    void definir_tema();

public:
    /**
     * @brief Construtor padrão da classe ThemeObjectGenerator.
     */
    ThemeObjectGenerator();

    /**
     * @brief Sorteia um objeto aleatório com base no tema definido.
     */
    void sortear_objeto();

    /**
     * @brief Obtém o objeto sorteado.
     * @return O objeto sorteado.
     */
    std::string get_objeto();

    /**
     * @brief Obtém o tema sorteado.
     * @return O tema sorteado.
     */
    std::string get_tema();
};

#endif
