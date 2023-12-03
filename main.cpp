#include "ArbolPlacas.hpp"
#include "InventarioArmas.hpp"
#include "GeneradorTablero.hpp"
#include "ConversorTablero.hpp"
#include "Visual.hpp"
#include <iostream>
#include <cmath>

const size_t CON_ARMAS = 0;
const size_t SIN_ARMAS = 1;
const size_t CON_UNA_SOLA_ARMA = 2;

// La solución es acotada en el sentido de que no se codea la interacción con el usuario.
// El simulador "se juega solo". La dificultad del TP no pasa por recibir y validar inputs del usuario,
// por lo que se omite en la posible solución. Lo implementado es, en mi opinión, bastante representativo
// de por donde iba la mano. Posiblemente, la parte mas dificil de entender es la clase "ConversorTablero".
// El codigo empezo siendo bastante modular, hasta que implementé el grafo del caso borde y se desmoronó.
// La idea general, es que se parte de una posible representación matricial del problema y me aprovecho de eso
// para generar todos los grafos, asociando cada indice bidimensional i, j con uno unidimensional de la forma
// i * col + j. En un 3x3, el (0,0) es 0, (0,1) es 1, (2,2) es 8, etc...
// De ahi, es facil de entender (creo), que el (0,0) conecta con el (0,1) y (1,0) pero no con el (0,-1) ni (-1,0)...
// Finalmente, teniendo las dimensiones del tablero (matriz), es facil volver de indice unidimensional al bidimensional.
// El unico método que falta implementar y que merece un comentario es el de "mover a James en un casillero".
// Lo unico que puede ocurrir, en ese caso, potencialmente, es que al mover a James, se ahuyenta a un Pyramid Head.
// La forma en que pensé resolverlo es eliminar ese Pyramid Head al mover a James, luego volver a calcular los grafos.
// Se equipan armas debiles siempre que sea posible porque se calcula el mejor camino posible, ya sea con un arma
// equipada o no.

int main() {
    // Atributos. Probablemente.
    ArbolPlacas arbol_placas;
    InventarioArmas inventario_armas;
    Arma* arma_actual = nullptr;
    bool partida_perdida = false;
    size_t nivel = 1;
    int puntaje_total = 0;
    size_t grafo_a_usar;
    size_t cantidad_armas;
    inventario_armas.guardar_arma(new Arma("Glock", 10));
    while (nivel <= 5 && !partida_perdida) {
        Tablero tablero = GeneradorTablero::generar_tablero(arbol_placas.altura());
        std::vector<Grafo> grafos = ConversorTablero::generar_grafos(tablero);
        // Equipo por default.
        if (!arma_actual && inventario_armas.consultar_arma(false)) {
            arma_actual = inventario_armas.obtener_arma(false);
            std::cout << "James equipó el arma: " << arma_actual;
        }
        // Reviso qué grafo deberia usar, dadas las condiciones. Si son 3 grafos es porque hay 2 Pyramids.
        // Esto es, de nuevo, extremadamente específico a la consigna, y agregar un Pyramid rompe.
        cantidad_armas = inventario_armas.tamanio() + (arma_actual ? 1 : 0);
        if (cantidad_armas >= 2 || (cantidad_armas >= 1 && grafos.size() < 3)) {
            grafo_a_usar = CON_ARMAS;
        } else if (cantidad_armas == 1 && grafos.size() == 3) {
            grafo_a_usar = CON_UNA_SOLA_ARMA;
        } else {
            grafo_a_usar = SIN_ARMAS;
        }
        // Busco el mejor camino posible.
        std::pair<std::vector<size_t>, int> camino, camino_1, camino_2;
        if (grafo_a_usar == SIN_ARMAS) {
            grafos[grafo_a_usar].usar_dijkstra();
            camino = grafos[grafo_a_usar].obtener_camino_minimo(tablero.calcular_indice(COORDENADA_INICIO),
                                                                tablero.calcular_indice(COORDENADA_DESTINO));
        } else {
            grafos[grafo_a_usar].usar_dijkstra();
            camino_1 = grafos[grafo_a_usar].obtener_camino_minimo(tablero.calcular_indice(COORDENADA_INICIO),
                                                                  tablero.calcular_indice(COORDENADA_DESTINO));
            grafos[SIN_ARMAS].usar_dijkstra();
            camino_2 = grafos[SIN_ARMAS].obtener_camino_minimo(tablero.calcular_indice(COORDENADA_INICIO),
                                                               tablero.calcular_indice(COORDENADA_DESTINO));
            if (camino_2.second <= camino_1.second) {
                camino = camino_2;
            } else {
                camino = camino_1;
            }
        }
        // A partir de aca es visual.
        Matriz visualizacion = tablero.obtener_visualizacion(camino.first);
        Visual::imprimir_tablero(visualizacion);
        if (camino.second >= INFINITO) {
            partida_perdida = true;
            std::cout << "Se perdió la partida." << std::endl;
            std::cout << "Máximo nivel alcanzado: " << nivel << std::endl;
        } else {
            size_t i = 0;
            while (i < camino.first.size() && arma_actual) {
                if (tablero.elemento(
                        tablero.obtener_indices(camino.first[i] % (size_t) pow((double) tablero.columnas(), 2))) ==
                    PYRAMID) {
                    std::cout << "Se rompió el arma actual: " << arma_actual;
                    delete arma_actual;
                    if (inventario_armas.consultar_arma(false)) {
                        arma_actual = inventario_armas.obtener_arma(false);
                        std::cout << "James equipó el arma: " << arma_actual;
                    } else {
                        arma_actual = nullptr;
                    }
                }
                i++;
            }
            puntaje_total += camino.second;
            if (arma_actual) {
                std::cout << "Arma actual: " << arma_actual;
            } else {
                std::cout << "James no tiene equipada un arma." << std::endl;
            }
            std::cout << "Cantidad de armas: " << inventario_armas.tamanio() << std::endl;
            std::cout << "Puntaje actual: " << puntaje_total << std::endl;
            std::cout << std::endl;
            arbol_placas.generar_placa_aleatoria();
            inventario_armas.generar_arma_aleatoria();
            nivel++;
        }
    }
    if (!partida_perdida) {
        std::cout << "¡James logró salir! Puntaje final: " << puntaje_total << std::endl;
    }
    delete arma_actual;
    return 0;
}