#include "Grafo.hpp"
#include "Floyd.hpp"
#include "Dijkstra.hpp"
#include <iostream>

Grafo::Grafo() {
    matriz_adyacencia = Matriz(0);
    algoritmo_camino_minimo = nullptr;
    vertices = 0;
    hay_cambios = true;
}

Grafo::Grafo(size_t cantidad_vertices) {
    matriz_adyacencia = Matriz(cantidad_vertices, INFINITO);
    vertices = cantidad_vertices;
    algoritmo_camino_minimo = nullptr;
    hay_cambios = true;
    for (size_t i = 0; i < vertices; i++) {
        matriz_adyacencia.elemento((int) i, (int) i) = 0;
    }
}

void Grafo::agrandar_matriz_adyacencia() {
    matriz_adyacencia.expandir();
    vertices++;
    for (size_t i = 0; i < vertices - 1; i++) {
        eliminar_arista(vertices - 1, i);
        eliminar_arista(i, vertices - 1);
    }
}

int Grafo::obtener_peso_camino(std::vector<size_t> camino) {
    int peso = 0;
    if (camino.size() > 1) {
        for (size_t i = 0; i < camino.size() - 1; i++) {
            peso += matriz_adyacencia.elemento((int) camino[i], (int) camino[i + 1]);
        }
    }
    return peso;
}

void Grafo::agregar_vertice() {
    agrandar_matriz_adyacencia();
    hay_cambios = true;
}

void Grafo::cambiar_arista(size_t origen, size_t destino, int peso) {
    if (origen < vertices && destino < vertices) {
        matriz_adyacencia.elemento((int) origen, (int) destino) = peso;
        hay_cambios = true;
    } else {
        std::cout << "ERROR: Los vértices no son válidos. No se cambió el camino." << std::endl;
    }
}

void Grafo::eliminar_arista(size_t origen, size_t destino) {
    cambiar_arista(origen, destino, INFINITO);
}

void Grafo::aislar_vertice(size_t vertice) {
    if (vertice < vertices) {
        for (size_t i = 0; i < vertices; i++) {
            if (i != vertice) {
                eliminar_arista(i, vertice);
                eliminar_arista(vertice, i);
            }
        }
        hay_cambios = true;
    } else {
        std::cout << "ERROR: El vértice no es válido. No se aisló." << std::endl;
    }
}

void Grafo::usar_floyd() {
    delete algoritmo_camino_minimo;
    algoritmo_camino_minimo = new Floyd();
    hay_cambios = true;
}

void Grafo::usar_dijkstra() {
    delete algoritmo_camino_minimo;
    algoritmo_camino_minimo = new Dijkstra();
    hay_cambios = true;
}

std::pair<std::vector<size_t>, int> Grafo::obtener_camino_minimo(size_t origen, size_t destino) {
    std::pair<std::vector<size_t>, int> camino;
    if (algoritmo_camino_minimo) {
        if (origen < vertices && destino < vertices) {
            camino.first = algoritmo_camino_minimo->calcular_camino_minimo(matriz_adyacencia, vertices, origen,
                                                                           destino, hay_cambios);
            camino.second = obtener_peso_camino(camino.first);
            hay_cambios = false;
        } else {
            std::cout << "ERROR: Los vértices no son válidos." << std::endl;
        }
    } else {
        std::cout << "ERROR: No se indicó el algoritmo a usar." << std::endl;
    }
    return camino;
}

// Metodo que "pega" las matrices de adyacencia.
void Grafo::juntar_grafos(Grafo& grafo) {
    Matriz nueva_matriz = Matriz(vertices + grafo.vertices, INFINITO);
    for (int i = 0; i < (int) (vertices + grafo.vertices); i++) {
        for (int j = 0; j < (int) (vertices + grafo.vertices); j++) {
            if (i < (int) vertices && j < (int) vertices) {
                nueva_matriz.elemento(i, j) = matriz_adyacencia.elemento(i, j);
            } else if (i >= (int) vertices && j >= (int) vertices) {
                nueva_matriz.elemento(i, j) =
                        grafo.matriz_adyacencia.elemento(i - (int) vertices, j - (int) vertices);
            }
        }
    }
    matriz_adyacencia = nueva_matriz;
    vertices = vertices + grafo.vertices;
    algoritmo_camino_minimo = nullptr;
    hay_cambios = true;
}

Grafo::Grafo(const Grafo& grafo1) {
    matriz_adyacencia = grafo1.matriz_adyacencia;
    vertices = grafo1.vertices;
    hay_cambios = grafo1.hay_cambios;
    algoritmo_camino_minimo = nullptr;
}

Grafo& Grafo::operator=(const Grafo& grafo1) {
    if (this != &grafo1) {
        delete algoritmo_camino_minimo;
        algoritmo_camino_minimo = nullptr;
        matriz_adyacencia = grafo1.matriz_adyacencia;
        vertices = grafo1.vertices;
        hay_cambios = grafo1.hay_cambios;
    }
    return *this;
}

Grafo::~Grafo() {
    delete algoritmo_camino_minimo;
}