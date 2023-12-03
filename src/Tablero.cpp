#include "Tablero.hpp"
#include "Random.hpp"
#include <cmath>

Tablero::Tablero(std::pair<size_t, size_t> dimensiones, std::pair<int, int> inicio, std::pair<int, int> destino,
                 const std::vector<std::pair<int, int>>& paredes) :
        Matriz(dimensiones.first, dimensiones.second, CAMINO) {
    for (auto pared: paredes) {
        elemento(pared) = PARED;
    }
    elemento(destino) = DESTINO;
    elemento(inicio) = INICIO;
    this->destino = destino;
    posicion_james = inicio;
    generar_pyramids_aleatorios();
}

bool Tablero::puede_generar_pyramid_head(std::pair<int, int> pyramid) {
    return elemento(pyramid) != INICIO &&
           elemento(pyramid) != DESTINO &&
           elemento(pyramid) != PARED &&
           elemento(pyramid) != PYRAMID;
}

void Tablero::generar_pyramid_head() {
    bool valido = false;
    while (!valido) {
        std::pair<int, int> pyramid = {Random::random(0, (int) fila - 1),
                                       Random::random(0, (int) columna - 1)};
        if (puede_generar_pyramid_head(pyramid)) {
            elemento(pyramid) = PYRAMID;
            valido = true;
        }
    }
}

void Tablero::generar_pyramids_aleatorios() {
    int chance;
    for (int i = 0; i < 2; i++) {
        chance = Random::random(0, 1);
        if (chance == 1) {
            generar_pyramid_head();
        }
    }
}

std::pair<int, int> Tablero::obtener_indices(size_t casillero) {
    int i = (int) (casillero / columna);
    int j = (int) (casillero % columna);
    return {i, j};
}


void Tablero::afectar_adyacente(int i, int j, Matriz& visualizacion) {
    if (visualizacion.indice_valido(i, j) && visualizacion.elemento(i, j) == CAMINO) {
        visualizacion.elemento(i, j) = MULTIPLICADO;
    }
}


void Tablero::quitar_pyramid_head(std::pair<int, int> indices) {
    if (elemento(indices) == PYRAMID) {
        elemento(indices) = CAMINO;
    }
}


Matriz Tablero::obtener_visualizacion(std::vector<size_t>& camino) {
    Matriz visualizacion(fila, columna);
    for (int i = 0; i < (int) fila; i++) {
        for (int j = 0; j < (int) columna; j++) {
            visualizacion.elemento(i, j) = elemento(i, j);
        }
    }
    for (int i = 0; i < (int) fila; i++) {
        for (int j = 0; j < (int) columna; j++) {
            if (visualizacion.elemento(i, j) == PYRAMID) {
                afectar_adyacente(i, j + 1, visualizacion);
                afectar_adyacente(i, j - 1, visualizacion);
                afectar_adyacente(i + 1, j, visualizacion);
                afectar_adyacente(i - 1, j, visualizacion);
            }
        }
    }
    for (size_t casillero: camino) {
        std::pair<int, int> indices = obtener_indices(casillero % (size_t) pow((double) columna, 2));
        if (visualizacion.elemento(indices) == CAMINO || visualizacion.elemento(indices) == MULTIPLICADO) {
            visualizacion.elemento(indices) = CAMINO_OPTIMO;
        }
    }
    visualizacion.elemento(posicion_james) = JAMES;
    return visualizacion;
}