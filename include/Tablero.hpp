#ifndef AYP2_TP3_SOLUCION_TABLERO_HPP
#define AYP2_TP3_SOLUCION_TABLERO_HPP

#include "TDAs/Matriz.hpp"
#include "Casillero.hpp"
#include "Camino.hpp"
#include <vector>

const size_t CANTIDAD_MAXIMA_PYRAMIDS = 2;

const int CAMINO = 0;
const int PARED = 1;
const int INICIO = 2;
const int DESTINO = 3;
const int PYRAMID = 4;
const int MULTIPLICADO = 5;
const int JAMES = 6;
const int CAMINO_OPTIMO = 7;

// Decorator.
class Tablero : public Matriz {
private:
    Casillero destino;
    Casillero posicion_james;
    size_t cantidad_pyramids = 0;

    // Pre: El casillero debe ser válido (matricialmente).
    // Post: Devuelve true si el Pyramid quiere generarse en un casillero de tipo válido.
    // Esto es, esencialmente, que solo puede generarse en CAMINO.
    bool puede_generar_pyramid_head(Casillero pyramid);

    // Pre: -
    // Post: Genera un Pyramid Head en una posición válida.
    void generar_pyramid_head();

    // Pre: -
    // Post: Genera dos Pyramid Heads, cada uno con una chance del 50%.
    void generar_pyramids_aleatorios();

    // Pre: El casillero debe ser válido (matricialmente).
    // Post: Inserta casilleros MULTIPLICADOS en los adyacentes, en caso de ser posible.
    // NOTA: Este método se usa solamente para la parte visual.
    void insertar_multiplicados(Casillero casillero, Matriz& visualizacion);

public:
    Tablero() = default;

    Tablero(std::pair<size_t, size_t> dimensiones, Casillero inicio, Casillero destino,
            const std::vector<Casillero>& paredes);

    // Pre: -
    // Post: Devuelve true si el casillero {i, j} es válido.
    bool casillero_valido(int i, int j);

    // Método para simplificar código. Hace lo mismo que casillero_valido(int, int).
    bool casillero_valido(std::pair<int, int> indices);

    // Pre: -
    // Post: Devuelve el casillero correspondiente al vértice ingresado.
    // NOTA: No se revisa que el vértice sea válido.
    Casillero obtener_casillero(size_t vertice);

    // Pre: El casillero debe ser válido (matricialmente).
    // Post: Devuelve el vértice correspondiente al casillero ingresado.
    size_t obtener_vertice(Casillero casillero);

    // Pre: -
    // Post: Devuelve todos los caminos mínimos según los grafos generados.
    std::vector<Camino> obtener_caminos();

    // Pre: -
    // Post: Devuelve la cantidad de Pyramid Heads actualmente en el tablero.
    size_t obtener_cantidad_pyramids();

    // Pre: -
    // Post: Genera una matriz que representa el estado actual del tablero, para luego ser imprimida por Visual.
    Matriz obtener_visualizacion(std::vector<size_t>& camino);
};

#endif