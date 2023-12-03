#include "ConversorTablero.hpp"
#include <cmath>

void
ConversorTablero::conectar_vertices(std::pair<int, int> i1, std::pair<int, int> i2, Grafo& grafo, Tablero& tablero) {
    size_t vertice_1 = tablero.calcular_indice(i1);
    size_t vertice_2 = tablero.calcular_indice(i2);
    grafo.cambiar_arista(vertice_1, vertice_2, PESO);
    grafo.cambiar_arista(vertice_2, vertice_1, PESO);
}

void
ConversorTablero::multiplicar_costos(std::pair<int, int> i1, std::pair<int, int> i2, Grafo& grafo, Tablero& tablero) {
    size_t vertice_1 = tablero.calcular_indice(i1);
    size_t vertice_2 = tablero.calcular_indice(i2);
    grafo.cambiar_arista(vertice_2, vertice_1, PESO * PENALIZACION);
}

void ConversorTablero::afectar_adyacentes([[maybe_unused]] std::pair<int, int> i1, std::pair<int, int> i2, Grafo& grafo,
                                          Tablero& tablero) {
    if (tablero.elemento(i2) != PARED && tablero.elemento(i2) != PYRAMID) {
        verificar_adyacentes(i2, grafo, tablero, multiplicar_costos);
    }
}

// Feote pero funciona. Extremadamente específico a la consigna (solo 2 Pyramids). Agregar uno mas rompe.
void ConversorTablero::redirigir_grafo_pyramid_1(std::pair<int, int> i1, std::pair<int, int> i2, Grafo& grafo,
                                                 Tablero& tablero) {
    size_t vertice_1 = tablero.calcular_indice(i1);
    size_t vertice_2 = tablero.calcular_indice(i2);
    grafo.cambiar_arista(vertice_2, vertice_1 + (size_t) pow((double) tablero.columnas(), 2), PESO);
}

// Feote pero funciona. Extremadamente específico a la consigna (solo 2 Pyramids). Agregar uno mas rompe.
void ConversorTablero::redirigir_grafo_pyramid_2(std::pair<int, int> i1, std::pair<int, int> i2, Grafo& grafo,
                                                 Tablero& tablero) {
    size_t vertice_1 = tablero.calcular_indice(i1);
    size_t vertice_2 = tablero.calcular_indice(i2);
    grafo.cambiar_arista(vertice_2, vertice_1 + 2 * (size_t) pow((double) tablero.columnas(), 2), PESO);
}

// TRUCAZO: Hace algo en los casilleros adyacentes (desde el punto de vista matricial del problema) sobre el grafo.
void ConversorTablero::verificar_adyacentes(std::pair<int, int> i1, Grafo& grafo, Tablero& tablero,
                                            void accion(std::pair<int, int>, std::pair<int, int>, Grafo&, Tablero&)) {
    if (tablero.indice_valido(i1.first + 1, i1.second)) {
        accion(i1, {i1.first + 1, i1.second}, grafo, tablero);
    }
    if (tablero.indice_valido(i1.first - 1, i1.second)) {
        accion(i1, {i1.first - 1, i1.second}, grafo, tablero);
    }
    if (tablero.indice_valido(i1.first, i1.second + 1)) {
        accion(i1, {i1.first, i1.second + 1}, grafo, tablero);
    }
    if (tablero.indice_valido(i1.first, i1.second - 1)) {
        accion(i1, {i1.first, i1.second - 1}, grafo, tablero);
    }
}

Grafo ConversorTablero::generar_grafo_base(Tablero& tablero) {
    Grafo grafo(tablero.columnas() * tablero.filas());
    for (int i = 0; i < (int) tablero.filas(); i++) {
        for (int j = 0; j < (int) tablero.columnas(); j++) {
            verificar_adyacentes({i, j}, grafo, tablero, conectar_vertices);
        }
    }
    return grafo;
}

std::vector<Grafo> ConversorTablero::generar_grafos(Tablero& tablero) {
    std::vector<Grafo> grafos;
    std::vector<std::pair<int, int>> pyramids;
    std::pair<int, int> destino;

    // Grafo sin Pyramids
    Grafo grafo = generar_grafo_base(tablero);
    size_t vertice;
    for (int i = 0; i < (int) tablero.filas(); i++) {
        for (int j = 0; j < (int) tablero.columnas(); j++) {
            if (tablero.elemento(i, j) == PARED) {
                vertice = tablero.calcular_indice(i, j);
                grafo.aislar_vertice(vertice);
            } else if (tablero.elemento(i, j) == DESTINO) {
                destino = {i, j};
            }
        }
    }
    grafos.push_back(grafo);

    // Grafo con Pyramids
    Grafo grafo_pyramids = grafo;
    for (int i = 0; i < (int) tablero.filas(); i++) {
        for (int j = 0; j < (int) tablero.columnas(); j++) {
            if (tablero.elemento(i, j) == PYRAMID) {
                verificar_adyacentes({i, j}, grafo_pyramids, tablero, afectar_adyacentes);
                vertice = tablero.calcular_indice(i, j);
                grafo_pyramids.aislar_vertice(vertice);
                pyramids.emplace_back(i, j);
            }
        }
    }
    grafos.push_back(grafo_pyramids);

    // Grafo para el caso especial de una sola arma y dos Pyramids.
    // La forma de pensar el grafo es MUY SIMILAR al del ejemplo práctico de DD2.
    // Este grafo es, sin embargo, MUY DEPENDIENTE de la consigna (son solo 2 Pyramids).
    // Agregar uno más rompe a pedazitos esta solución.
    if (pyramids.size() == 2) {
        Grafo grafo_caso_especial = grafo;
        Grafo grafo_pyramid_1 = grafo;
        Grafo grafo_pyramid_2 = grafo;

        // Genero un grafo sin uno de los Pyramids.
        verificar_adyacentes(pyramids[0], grafo_pyramid_1, tablero, afectar_adyacentes);
        vertice = tablero.calcular_indice(pyramids[0]);
        grafo_pyramid_1.aislar_vertice(vertice);
        grafo_caso_especial.aislar_vertice(vertice);

        // Idem para el otro.
        verificar_adyacentes(pyramids[1], grafo_pyramid_2, tablero, afectar_adyacentes);
        vertice = tablero.calcular_indice(pyramids[1]);
        grafo_pyramid_2.aislar_vertice(vertice);
        grafo_caso_especial.aislar_vertice(vertice);

        // Uno los tres grafos, "pegando" las matrices de adyacencia, si se quiere.
        grafo_caso_especial.juntar_grafos(grafo_pyramid_1);
        grafo_caso_especial.juntar_grafos(grafo_pyramid_2);

        // Conecto los vértices adyacentes a un Pyramid para que pase a uno de los "subgrafos".
        verificar_adyacentes(pyramids[0], grafo_caso_especial, tablero, redirigir_grafo_pyramid_2);
        verificar_adyacentes(pyramids[1], grafo_caso_especial, tablero, redirigir_grafo_pyramid_1);

        // Conecto el destino de los "subgrafos" al destino original.
        vertice = tablero.calcular_indice(destino);
        grafo_caso_especial.cambiar_arista(vertice + (size_t) pow((double) tablero.columnas(), 2), vertice, 0);
        grafo_caso_especial.cambiar_arista(vertice + 2 * (size_t) pow((double) tablero.columnas(), 2), vertice, 0);

        grafos.push_back(grafo_caso_especial);
    }
    return grafos;
}