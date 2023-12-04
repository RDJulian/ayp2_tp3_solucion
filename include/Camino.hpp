#ifndef AYP2_TP3_SOLUCION_CAMINO_HPP
#define AYP2_TP3_SOLUCION_CAMINO_HPP

#include <utility>
#include <vector>
#include <cstddef>

/* Clase decoradora. Define los tipos de datos que usa el template std::pair.
 * Como hereda de std::pair, puede usar todos los métodos de la clase. */
class Camino : public std::pair<std::vector<size_t>, int> {
public:
    Camino();

    Camino(std::vector<size_t> first, int second);
};

#endif