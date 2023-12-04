#include "Camino.hpp"

Camino::Camino() : std::pair<std::vector<size_t>, int>({}, 0) {}

Camino::Camino(std::vector<size_t> first, int second) : std::pair<std::vector<size_t>, int>(first, second) {}