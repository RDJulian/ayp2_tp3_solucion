#include "Casillero.hpp"

Casillero::Casillero(size_t i, size_t j) : std::pair<size_t, size_t>(i, j) {}

Casillero::Casillero() : Casillero(0, 0) {}

Casillero::Casillero(int i, int j) : Casillero((size_t) i, (size_t) j) {}

Casillero::Casillero(std::pair<int, int> indices) : Casillero(indices.first, indices.second) {}

std::pair<int, int> Casillero::a_int() {
    return {(int) first, (int) second};
}