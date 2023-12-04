#include "Simulador.hpp"
#include "GeneradorTablero.hpp"
#include "ConversorTablero.hpp"
#include "Visual.hpp"
#include <iostream>

Simulador::Simulador() {
    arma_actual = nullptr;
    puntaje_total = 0;
    nivel = 1;
    arbol_placas.generar_placa_aleatoria();
    inventario_armas.generar_arma_aleatoria();
    tablero = GeneradorTablero::generar_tablero(arbol_placas.altura());
    std::vector<Camino> caminos = tablero.obtener_caminos();
    camino_optimo = obtener_camino_optimo(caminos);
}

Camino Simulador::obtener_camino_optimo(std::vector<Camino>& caminos) {
    size_t cantidad_armas = inventario_armas.tamanio() + (arma_actual ? 1 : 0);
    Camino camino_1, camino_2;
    size_t estrategia;
    if (cantidad_armas >= tablero.obtener_cantidad_pyramids()) {
        estrategia = CON_ARMA;
    } else if (cantidad_armas == 1 && tablero.obtener_cantidad_pyramids() == CANTIDAD_MAXIMA_PYRAMIDS) {
        estrategia = CASO_BORDE;
    } else {
        estrategia = SIN_ARMA;
    }
    if (estrategia == SIN_ARMA) {
        return caminos[estrategia];
    } else {
        camino_1 = caminos[estrategia];
        camino_2 = caminos[SIN_ARMA];
        if (camino_1.second < camino_2.second) {
            return camino_1;
        } else {
            return camino_2;
        }
    }
}

void Simulador::avanzar_nivel() {
    nivel++;
    if (partida_en_curso()) {
        arbol_placas.generar_placa_aleatoria();
        inventario_armas.generar_arma_aleatoria();
        tablero = GeneradorTablero::generar_tablero(arbol_placas.altura());
        std::vector<Camino> caminos = tablero.obtener_caminos();
        camino_optimo = obtener_camino_optimo(caminos);
    }
}

void Simulador::romper_armas() {
    Casillero casillero;
    size_t i = 0;
    while (i < camino_optimo.first.size() && arma_actual) {
        casillero = tablero.obtener_casillero(camino_optimo.first[i] % (tablero.columnas() * tablero.filas()));
        if (tablero.elemento(casillero) == PYRAMID) {
            std::cout << "Se rompió el arma actual: " << arma_actual << std::endl;
            delete arma_actual;
            arma_actual = nullptr;
            equipar_arma_debil();
        }
        i++;
    }
}

bool Simulador::partida_en_curso() {
    return nivel <= NIVEL_FINAL && camino_optimo.second < INFINITO;
}

void Simulador::equipar_arma_debil() {
    if (partida_en_curso() && !arma_actual && inventario_armas.consultar_arma(false)) {
        arma_actual = inventario_armas.obtener_arma(false);
        std::cout << "James equipó el arma: " << arma_actual << std::endl;
    }
}

void Simulador::mover_camino_optimo() {
    if (partida_en_curso()) {
        romper_armas();
        puntaje_total += camino_optimo.second;
        avanzar_nivel();
    }
}

void Simulador::mostrar_informacion() {
    std::cout << "Nivel: " << nivel << std::endl;
    Matriz visualizacion = tablero.obtener_visualizacion(camino_optimo.first);
    Visual::imprimir_tablero(visualizacion);
    if (arma_actual) {
        std::cout << "Arma actual: " << arma_actual;
    } else {
        std::cout << "James no tiene equipada un arma." << std::endl;
    }
    std::cout << "Cantidad de armas: " << inventario_armas.tamanio() + (arma_actual ? 1 : 0) << std::endl;
    std::cout << "Puntaje del mejor camino para este nivel: " << camino_optimo.second << std::endl;
    std::cout << "Puntaje total actual: " << puntaje_total << std::endl;
    std::cout << std::endl;
}

void Simulador::mostrar_resultado() {
    if (partida_en_curso()) {
        std::cout << "La partida sigue en curso..." << std::endl;
    } else if (nivel > NIVEL_FINAL) {
        std::cout << "¡James logró salir! Puntaje final: " << puntaje_total << std::endl;
    } else {
        Matriz visualizacion = tablero.obtener_visualizacion(camino_optimo.first);
        Visual::imprimir_tablero(visualizacion);
        std::cout << "Se perdió la partida." << std::endl;
        std::cout << "Máximo nivel alcanzado: " << nivel << std::endl;
    }
    std::cout << std::endl;
}

Simulador::~Simulador() {
    delete arma_actual;
}