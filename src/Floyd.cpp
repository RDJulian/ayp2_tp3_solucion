#include "Floyd.hpp"

void Floyd::inicializar_matrices() {
    matriz_caminos = Matriz(cantidad_vertices);
    for (size_t i = 0; i < cantidad_vertices; i++) {
        for (size_t j = 0; j < cantidad_vertices; j++) {
            matriz_caminos.elemento(i, j) = (int) j;
        }
    }

    matriz_costos = matriz_adyacencia;
}

std::vector<size_t> Floyd::obtener_camino(size_t origen, size_t destino) {
    std::vector<size_t> camino;
    size_t vertice = origen;
    camino.push_back(vertice);
    while (vertice != destino) {
        vertice = size_t(matriz_caminos.elemento(vertice, destino));
        camino.push_back(vertice);
    }
    return camino;
}

std::vector<size_t>
Floyd::calcular_camino_minimo(Matriz adyacencia, size_t vertices, size_t origen, size_t destino, bool hay_cambios) {
    if (hay_cambios) {
        matriz_adyacencia = adyacencia;
        cantidad_vertices = vertices;
        inicializar_matrices();
        for (size_t k = 0; k < vertices; k++) {
            for (size_t i = 0; i < vertices; i++) {
                for (size_t j = 0; j < vertices; j++) {
                    if (matriz_costos.elemento(i, j) > (matriz_costos.elemento(i, k) + matriz_costos.elemento(k, j))) {
                        matriz_costos.elemento(i, j) = matriz_costos.elemento(i, k) + matriz_costos.elemento(k, j);
                        matriz_caminos.elemento(i, j) = matriz_caminos.elemento(i, k);
                    }
                }
            }
        }
    }
    return obtener_camino(origen, destino);
}