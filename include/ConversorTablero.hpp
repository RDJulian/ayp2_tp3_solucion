#ifndef AYP2_TP3_SOLUCION_CONVERSORTABLERO_HPP
#define AYP2_TP3_SOLUCION_CONVERSORTABLERO_HPP

#include "Tablero.hpp"
#include "TDAs/Grafo/Grafo.hpp"

const int PESO = 10;
const int PENALIZACION = 5;

// TODO: Documentar. Cambiar firmas para usar Casilleros.
class ConversorTablero {
private:
    static void conectar_adyacentes(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero);

    static void multiplicar_costos(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero);

    static void multiplicar_adyacentes(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero);

    static void redirigir_grafo_pyramid_1(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero);

    static void redirigir_grafo_pyramid_2(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero);

    static void ejecutar_adyacentes(Casillero casillero, Grafo& grafo, Tablero& tablero,
                                    void accion(Casillero, Casillero, Grafo&, Tablero&));

    static Grafo generar_grafo_base(Tablero& tablero);

public:
    static std::vector<Grafo> generar_grafos(Tablero& tablero);
};

#endif