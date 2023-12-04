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

// TODO: Documentar.
class Simulador {
private:
    Tablero tablero;
    ArbolPlacas arbol_placas;
    InventarioArmas inventario_armas;
    Camino camino_optimo;
    Arma* arma_actual;
    size_t nivel;
    int puntaje_total;

    Camino obtener_camino_optimo(std::vector<Camino>& caminos);

    void avanzar_nivel();

    void romper_armas();

public:
    Simulador();

    bool partida_en_curso();

    void mostrar_informacion();

    void equipar_arma_debil();

    void mover_camino_optimo();

    void mostrar_resultado();

    ~Simulador();
};

#endif