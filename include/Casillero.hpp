#ifndef AYP2_TP3_SOLUCION_CASILLERO_HPP
#define AYP2_TP3_SOLUCION_CASILLERO_HPP

#include <utility>
#include <cstddef>

/* Clase decoradora. Define los tipos de datos que usa std::pair.
 * Como hereda de std::pair, puede usar todos los métodos de la clase. */
class Casillero : public std::pair<size_t, size_t> {
public:
    Casillero();

    Casillero(size_t i, size_t j);

    Casillero(int i, int j);

    Casillero(std::pair<int, int> indices);
};

#endif