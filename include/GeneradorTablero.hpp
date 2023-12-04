#ifndef AYP2_TP3_SOLUCION_GENERADORTABLERO_HPP
#define AYP2_TP3_SOLUCION_GENERADORTABLERO_HPP

#include "Tablero.hpp"

const std::pair<size_t, size_t> DIMENSIONES = {9, 9};
const Casillero CASILLERO_INICIO = {8, 0};
const Casillero CASILLERO_DESTINO = {0, 8};

const std::vector<Casillero> LAYOUT_1 = {
        {0, 1},
        {1, 1},
        {2, 1},
        {4, 1},
        {5, 1},
        {6, 1},
        {0, 3},
        {2, 3},
        {3, 3},
        {4, 3},
        {6, 3},
        {7, 3},
        {8, 3},
        {0, 5},
        {1, 5},
        {2, 5},
        {3, 5},
        {5, 5},
        {6, 5},
        {7, 5},
        {0, 7},
        {1, 7},
        {3, 7},
        {4, 7},
        {5, 7},
        {6, 7},
        {7, 7}
};

const std::vector<Casillero> LAYOUT_2 = {
        {1, 1},
        {1, 2},
        {1, 3},
        {1, 4},
        {1, 5},
        {1, 7},
        {2, 7},
        {4, 7},
        {5, 7},
        {3, 0},
        {3, 1},
        {3, 3},
        {3, 4},
        {3, 5},
        {5, 1},
        {5, 2},
        {5, 3},
        {5, 5},
        {6, 5},
        {7, 5},
        {7, 3},
        {8, 3},
        {7, 7},
        {7, 8},
        {7, 1},
};

class GeneradorTablero {
public:
    // Pre: -
    // Post: Genera un tablero en base a la altura del árbol de placas especificado.
    static Tablero generar_tablero(size_t altura);
};

#endif