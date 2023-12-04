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

// TODO: Documentar
class Tablero : public Matriz {
private:
    Casillero destino;
    Casillero posicion_james;
    size_t cantidad_pyramids = 0;

    bool puede_generar_pyramid_head(Casillero pyramid);

    void generar_pyramid_head();

    void generar_pyramids_aleatorios();

    void insertar_multiplicados(Casillero casillero, Matriz& visualizacion);

public:
    Tablero() = default;

    Tablero(std::pair<size_t, size_t> dimensiones, Casillero inicio, Casillero destino,
            const std::vector<Casillero>& paredes);

    bool casillero_valido(int i, int j);

    bool casillero_valido(std::pair<int, int> indices);

    Casillero obtener_casillero(size_t vertice);

    size_t obtener_vertice(Casillero casillero);

    std::vector<Camino> obtener_caminos();

    size_t obtener_cantidad_pyramids();

    Matriz obtener_visualizacion(std::vector<size_t>& camino);
};

#endif