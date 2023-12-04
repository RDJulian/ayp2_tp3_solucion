#ifndef AYP2_TP3_SOLUCION_CAMINO_HPP
#define AYP2_TP3_SOLUCION_CAMINO_HPP

#include <utility>
#include <vector>
#include <cstddef>

// TODO: Documentar.
class Camino : public std::pair<std::vector<size_t>, int> {
public:
    Camino();

    Camino(std::vector<size_t> first, int second);
};

#endif