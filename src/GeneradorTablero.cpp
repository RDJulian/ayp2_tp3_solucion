#include "GeneradorTablero.hpp"

Tablero GeneradorTablero::generar_tablero(size_t altura) {
    if (altura % 2 == 0) {
        return Tablero(DIMENSIONES, CASILLERO_INICIO, CASILLERO_DESTINO, LAYOUT_1);
    } else {
        return Tablero(DIMENSIONES, CASILLERO_INICIO, CASILLERO_DESTINO, LAYOUT_2);
    }
}