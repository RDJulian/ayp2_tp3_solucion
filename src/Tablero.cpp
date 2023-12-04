#include "Tablero.hpp"
#include "Random.hpp"
#include "ConversorTablero.hpp"
#include <iostream>

Tablero::Tablero(std::pair<size_t, size_t> dimensiones, Casillero inicio, Casillero destino,
                 const std::vector<Casillero>& paredes) : Matriz(dimensiones.first, dimensiones.second, CAMINO) {
    for (Casillero pared: paredes) {
        elemento(pared) = PARED;
    }
    elemento(inicio) = INICIO;
    elemento(destino) = DESTINO;
    posicion_james = inicio;
    this->destino = destino;
    cantidad_pyramids = 0;
    generar_pyramids_aleatorios();
}

bool Tablero::puede_generar_pyramid_head(Casillero pyramid) {
    return elemento(pyramid) != INICIO &&
           elemento(pyramid) != DESTINO &&
           elemento(pyramid) != PARED &&
           elemento(pyramid) != PYRAMID;
}

// NOTA: Se podría iterar por el tablero, obtener los casilleros válidos, luego sacar uno al azar.
void Tablero::generar_pyramid_head() {
    bool valido = false;
    size_t i = 0;
    const size_t MAX_ITERACIONES = 100;
    while (!valido && i < MAX_ITERACIONES) {
        Casillero pyramid = {Random::number(0, (int) fila - 1),
                             Random::number(0, (int) columna - 1)};
        if (puede_generar_pyramid_head(pyramid)) {
            elemento(pyramid) = PYRAMID;
            valido = true;
        } else {
            i++;
        }
        if (i >= MAX_ITERACIONES) {
            std::cout << "WARNING: Se intentó insertar el Pyramid Head en " << i << " casilleros distintos, sin éxito."
                      << std::endl;
        }
    }
}

void Tablero::generar_pyramids_aleatorios() {
    int chance;
    for (size_t i = 0; i < CANTIDAD_MAXIMA_PYRAMIDS; i++) {
        chance = Random::number(0, 1);
        if (chance == 1) {
            generar_pyramid_head();
            cantidad_pyramids++;
        }
    }
}

bool Tablero::casillero_valido(int i, int j) {
    return i >= 0 && i < (int) fila && j >= 0 && j < (int) columna;
}

bool Tablero::casillero_valido(std::pair<int, int> indices) {
    return casillero_valido(indices.first, indices.second);
}

Casillero Tablero::obtener_casillero(size_t vertice) {
    return {vertice / columna, vertice % columna};
}

void Tablero::insertar_multiplicados(Casillero casillero, Matriz& visualizacion) {
    int i = (int) casillero.first;
    int j = (int) casillero.second;
    std::vector<std::pair<int, int>> posibles_adyacentes = {{i + 1, j},
                                                            {i - 1, j},
                                                            {i,     j + 1},
                                                            {i,     j - 1}};
    for (auto adyacente: posibles_adyacentes) {
        if (casillero_valido(adyacente) && visualizacion.elemento(adyacente) == CAMINO) {
            visualizacion.elemento(adyacente) = MULTIPLICADO;
        }
    }
}

size_t Tablero::obtener_vertice(Casillero casillero) {
    return calcular_indice(casillero.first, casillero.second);
}

std::vector<Camino> Tablero::obtener_caminos() {
    std::vector<Camino> caminos;
    std::vector<Grafo> grafos = ConversorTablero::generar_grafos(*this);
    for (Grafo grafo: grafos) {
        grafo.usar_dijkstra();
        size_t vertice_origen = obtener_vertice(posicion_james);
        size_t vertice_destino = obtener_vertice(destino);
        Camino camino = grafo.obtener_camino_minimo(vertice_origen, vertice_destino);
        caminos.push_back(camino);
    }
    return caminos;
}

size_t Tablero::obtener_cantidad_pyramids() {
    return cantidad_pyramids;
}

Matriz Tablero::obtener_visualizacion(std::vector<size_t>& camino) {
    Matriz visualizacion(fila, columna);
    for (size_t i = 0; i < fila; i++) {
        for (size_t j = 0; j < columna; j++) {
            visualizacion.elemento(i, j) = elemento(i, j);
        }
    }
    for (int i = 0; i < (int) fila; i++) {
        for (int j = 0; j < (int) columna; j++) {
            if (visualizacion.elemento(Casillero(i, j)) == PYRAMID) {
                insertar_multiplicados({i, j}, visualizacion);
            }
        }
    }
    for (size_t vertice: camino) {
        Casillero casillero = obtener_casillero(vertice % (columna * fila));
        if (visualizacion.elemento(casillero) == CAMINO || visualizacion.elemento(casillero) == MULTIPLICADO) {
            visualizacion.elemento(casillero) = CAMINO_OPTIMO;
        }
    }
    visualizacion.elemento(posicion_james) = JAMES;
    return visualizacion;
}