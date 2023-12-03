#ifndef AYP2_TP3_SOLUCION_CONVERSORTABLERO_HPP
#define AYP2_TP3_SOLUCION_CONVERSORTABLERO_HPP

#include "Tablero.hpp"
#include "Grafo.hpp"

const int PESO = 10;
const int PENALIZACION = 5;

class ConversorTablero {
private:
    static void conectar_vertices(std::pair<int, int> i1, std::pair<int, int> i2, Grafo& grafo, Tablero& tablero);

    static void multiplicar_costos(std::pair<int, int> i1, std::pair<int, int> i2, Grafo& grafo, Tablero& tablero);

    static void
    afectar_adyacentes([[maybe_unused]] std::pair<int, int> i1, std::pair<int, int> i2, Grafo& grafo, Tablero& tablero);

    static void verificar_adyacentes(std::pair<int, int> i1, Grafo& grafo, Tablero& tablero,
                                     void accion(std::pair<int, int>, std::pair<int, int>, Grafo&, Tablero&));

    static void
    redirigir_grafo_pyramid_1(std::pair<int, int> i1, std::pair<int, int> i2, Grafo& grafo, Tablero& tablero);

    static void
    redirigir_grafo_pyramid_2(std::pair<int, int> i1, std::pair<int, int> i2, Grafo& grafo, Tablero& tablero);

    static Grafo generar_grafo_base(Tablero& tablero);

public:
    static std::vector<Grafo> generar_grafos(Tablero& tablero);
};

#endif