#include "ConversorTablero.hpp"

// Métodos estáticos auxiliares para encapsular cada una de las diferentes transformaciones sobre los adyacentes.
void ConversorTablero::conectar_adyacentes(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero) {
    grafo.cambiar_arista(tablero.obtener_vertice(casillero), tablero.obtener_vertice(adyacente), PESO_BASE);
}

void ConversorTablero::multiplicar_costos(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero) {
    grafo.cambiar_arista(tablero.obtener_vertice(adyacente), tablero.obtener_vertice(casillero),
                         PESO_BASE * PENALIZACION);
}

void
ConversorTablero::multiplicar_adyacentes(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero) {
    if (tablero.elemento(adyacente) != PARED && tablero.elemento(adyacente) != PYRAMID) {
        ejecutar_adyacentes(adyacente, grafo, tablero, multiplicar_costos);
    }
}

void
ConversorTablero::redirigir_grafo_pyramid_1(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero) {
    size_t vertice_casillero = tablero.obtener_vertice(casillero);
    size_t vertice_adyacente = tablero.obtener_vertice(adyacente);
    size_t offset = tablero.columnas() * tablero.filas();
    grafo.cambiar_arista(vertice_adyacente, vertice_casillero + offset, PESO_BASE);
}

void
ConversorTablero::redirigir_grafo_pyramid_2(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero) {
    size_t vertice_casillero = tablero.obtener_vertice(casillero);
    size_t vertice_adyacente = tablero.obtener_vertice(adyacente);
    size_t offset = tablero.columnas() * tablero.filas();
    grafo.cambiar_arista(vertice_adyacente, vertice_casillero + 2 * offset, PESO_BASE);
}

// TRUCAZO: Hace algo en los casilleros adyacentes (desde el punto de vista matricial del problema) sobre el grafo.
void ConversorTablero::ejecutar_adyacentes(Casillero casillero, Grafo& grafo, Tablero& tablero,
                                           void accion(Casillero, Casillero, Grafo&, Tablero&)) {
    int i = (int) casillero.first;
    int j = (int) casillero.second;
    std::vector<std::pair<int, int>> posibles_adyacentes = {{i + 1, j},
                                                            {i - 1, j},
                                                            {i,     j + 1},
                                                            {i,     j - 1}};
    for (auto adyacente: posibles_adyacentes) {
        if (tablero.casillero_valido(adyacente)) {
            accion(casillero, adyacente, grafo, tablero);
        }
    }
}

Grafo ConversorTablero::generar_grafo_base(Tablero& tablero) {
    Grafo grafo(tablero.columnas() * tablero.filas());
    for (size_t i = 0; i < tablero.filas(); i++) {
        for (size_t j = 0; j < tablero.columnas(); j++) {
            ejecutar_adyacentes({i, j}, grafo, tablero, conectar_adyacentes);
        }
    }
    return grafo;
}

std::vector<Grafo> ConversorTablero::generar_grafos(Tablero& tablero) {
    std::vector<Grafo> grafos;
    std::vector<Casillero> pyramids;
    Casillero destino;

    // Grafo sin Pyramids
    Grafo grafo = generar_grafo_base(tablero);
    for (size_t i = 0; i < tablero.filas(); i++) {
        for (size_t j = 0; j < tablero.columnas(); j++) {
            if (tablero.elemento(i, j) == PARED) {
                grafo.aislar_vertice(tablero.obtener_vertice({i, j}));
            } else if (tablero.elemento(i, j) == DESTINO) {
                destino = {i, j};
            }
        }
    }
    grafos.push_back(grafo);

    // Grafo con Pyramids
    Grafo grafo_pyramids = grafo;
    for (size_t i = 0; i < tablero.filas(); i++) {
        for (size_t j = 0; j < tablero.columnas(); j++) {
            if (tablero.elemento(i, j) == PYRAMID) {
                ejecutar_adyacentes({i, j}, grafo_pyramids, tablero, multiplicar_adyacentes);
                grafo_pyramids.aislar_vertice(tablero.obtener_vertice({i, j}));
                pyramids.emplace_back(i, j);
            }
        }
    }
    grafos.push_back(grafo_pyramids);

    // Grafo para el caso especial de una sola arma y dos Pyramids.
    // La forma de pensar el grafo es MUY SIMILAR al del ejemplo práctico de DD2.
    // Este grafo es, sin embargo, MUY DEPENDIENTE de la consigna (son exactamente dos Pyramids).
    // Agregar uno más rompe a pedazitos esta solución.
    if (pyramids.size() == CANTIDAD_MAXIMA_PYRAMIDS) {
        Grafo grafo_caso_especial = grafo;
        Grafo grafo_pyramid_1 = grafo;
        Grafo grafo_pyramid_2 = grafo;
        size_t vertice;

        // Genero un grafo sin uno de los Pyramids.
        ejecutar_adyacentes(pyramids[0], grafo_pyramid_1, tablero, multiplicar_adyacentes);
        vertice = tablero.obtener_vertice(pyramids[0]);
        grafo_pyramid_1.aislar_vertice(vertice);
        grafo_caso_especial.aislar_vertice(vertice);

        // Idem para el otro Pyramid.
        ejecutar_adyacentes(pyramids[1], grafo_pyramid_2, tablero, multiplicar_adyacentes);
        vertice = tablero.obtener_vertice(pyramids[1]);
        grafo_pyramid_2.aislar_vertice(vertice);
        grafo_caso_especial.aislar_vertice(vertice);

        // Uno los tres grafos, "pegando" las matrices de adyacencia, si se quiere.
        grafo_caso_especial.juntar_grafos(grafo_pyramid_1);
        grafo_caso_especial.juntar_grafos(grafo_pyramid_2);

        // Conecto los vértices adyacentes a un Pyramid para que pase al otro "subgrafo".
        ejecutar_adyacentes(pyramids[0], grafo_caso_especial, tablero, redirigir_grafo_pyramid_2);
        ejecutar_adyacentes(pyramids[1], grafo_caso_especial, tablero, redirigir_grafo_pyramid_1);

        // Conecto el destino de los "subgrafos" al destino original.
        // El offset no es mas que la cantidad de vértices (81, en este problema).
        vertice = tablero.obtener_vertice(destino);
        size_t offset = tablero.columnas() * tablero.filas();
        grafo_caso_especial.cambiar_arista(vertice + offset, vertice, 0);
        grafo_caso_especial.cambiar_arista(vertice + 2 * offset, vertice, 0);

        grafos.push_back(grafo_caso_especial);
    }
    return grafos;
}