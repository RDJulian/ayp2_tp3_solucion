#ifndef AYP2_TP3_SOLUCION_SIMULADOR_HPP
#define AYP2_TP3_SOLUCION_SIMULADOR_HPP

#include "ArbolPlacas.hpp"
#include "InventarioArmas.hpp"
#include "Tablero.hpp"
#include "Camino.hpp"

const size_t NIVEL_FINAL = 5;

const size_t CON_ARMA = 0;
const size_t SIN_ARMA = 1;
const size_t CASO_BORDE = 2;

class Simulador {
private:
    Tablero tablero;
    ArbolPlacas arbol_placas;
    InventarioArmas inventario_armas;
    Camino camino_optimo;
    Arma* arma_actual;
    size_t nivel;
    int puntaje_total;

    // Pre: -
    // Post: Calcula el mejor camino posible según las condiciones actuales de la partida.
    // Si un camino empata con el camino sin arma equipada, se prioriza el camino sin arma.
    Camino obtener_camino_optimo(std::vector<Camino>& caminos);

    // Pre: -
    // Post: Avanza la partida al siguiente nivel, generando un nuevo tablero.
    void avanzar_nivel();

    // Pre: -
    // Post: Rompe las armas de James por cada Pyramid Head por el que pasó en el último camino recorrido.
    void romper_armas();

public:
    Simulador();

    // Pre: -
    // Post: Devuelve true si la partida sigue en curso. Esto es, si el camino no es imposible y si aún no recorrió
    // el NIVEL_FINAL.
    bool partida_en_curso();

    // Pre: -
    // Post: Muestra información relevante sobre el estado actual de la partida.
    void mostrar_informacion();

    // Pre: -
    // Post: Equipa el arma más débil de James en caso de tener una en el inventario y no tener otra equipada.
    void equipar_arma_debil();

    // Pre: -
    // Post: Mueve a James hacia el destino por el camino óptimo, terminando el nivel actual.
    void mover_camino_optimo();

    // Pre: -
    // Post: Muestra el resultado actual de la partida. Esto es, si perdió, ganó, o sigue en curso.
    void mostrar_resultado();

    ~Simulador();
};

#endif