#ifndef AYP2_TP3_SOLUCION_CASILLERO_HPP
#define AYP2_TP3_SOLUCION_CASILLERO_HPP

#include <utility>
#include <cstddef>

// TODO: Documentar
class Casillero : public std::pair<size_t, size_t> {
public:
    Casillero();

    Casillero(size_t i, size_t j);

    Casillero(int i, int j);

    Casillero(std::pair<int, int> indices);

    std::pair<int, int> a_int();
};

#endif