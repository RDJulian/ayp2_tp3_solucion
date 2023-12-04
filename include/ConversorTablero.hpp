#ifndef AYP2_TP3_SOLUCION_CONVERSORTABLERO_HPP
#define AYP2_TP3_SOLUCION_CONVERSORTABLERO_HPP

#include "Tablero.hpp"
#include "TDAs/Grafo/Grafo.hpp"

const int PESO_BASE = 10;
const int PENALIZACION = 5;

class ConversorTablero {
private:
    // Todos estos métodos son distintas modificaciones que se van a aplicar sobre vértices adyacentes.

    // Pre: El casillero adyacente debe ser un casillero válido (matricialmente).
    // Post: Une en el grafo el vertice "casillero" con el "adyacente", con peso PESO_BASE.
    static void conectar_adyacentes(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero);

    // Pre: El casillero adyacente debe ser un casillero válido (matricialmente).
    // Post: Multiplica por PENALIZACIÓN el costo PESO_BASE de ir desde el vertice "adyacente" al "casillero".
    static void multiplicar_costos(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero);

    // Pre: El casillero adyacente debe ser un casillero válido (matricialmente).
    // Post: Multiplica los costos de ir desde los adyacentes a "adyacente" hacia "adyacente", en caso de ser posible.
    // Esto no se puede ejecutar sobre PARED o PYRAMID.
    static void multiplicar_adyacentes(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero);

    // Pre: El casillero adyacente debe ser un casillero válido (matricialmente).
    // Post: Redirige el casillero adyacente al correspondiente casillero en el "subgrafo".
    static void redirigir_grafo_pyramid_1(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero);

    // Pre: El casillero adyacente debe ser un casillero válido (matricialmente).
    // Post: Redirige el casillero adyacente al correspondiente casillero en el otro "subgrafo".
    static void redirigir_grafo_pyramid_2(Casillero casillero, Casillero adyacente, Grafo& grafo, Tablero& tablero);

    // Pre: El casillero debe ser válido (matricialmente).
    // Post: Ejecuta la accion sobre todos los casilleros adyacentes válidos a casillero.
    static void ejecutar_adyacentes(Casillero casillero, Grafo& grafo, Tablero& tablero,
                                    void accion(Casillero, Casillero, Grafo&, Tablero&));

    // Pre: -
    // Post: Genera un grafo totalmente conexo (en el sentido de esta consigna), con las mismas dimensiones que el
    // tablero.
    static Grafo generar_grafo_base(Tablero& tablero);

public:
    // Pre: -
    // Post: Devuelve entre dos o tres grafos que corresponden a las diferentes situaciones que se pueden dar durante
    // la partida.
    // En el caso borde en que James tenga una sola arma y haya dos Pyramid Heads en el tablero, se devuelve el tercer
    // grafo que modela esa situación.
    static std::vector<Grafo> generar_grafos(Tablero& tablero);
};

#endif