#ifndef AYP2_TP3_SOLUCION_TABLERO_HPP
#define AYP2_TP3_SOLUCION_TABLERO_HPP

#include "Matriz.hpp"
#include <vector>

const int CAMINO = 0;
const int PARED = 1;
const int INICIO = 2;
const int DESTINO = 3;
const int PYRAMID = 4;
const int MULTIPLICADO = 5;
const int JAMES = 6;
const int CAMINO_OPTIMO = 7;

class Tablero : public Matriz {
private:
    std::pair<int, int> destino;
    std::pair<int, int> posicion_james;

    bool puede_generar_pyramid_head(std::pair<int, int> pyramid);

    void generar_pyramid_head();

    void generar_pyramids_aleatorios();

    void afectar_adyacente(int i, int j, Matriz& visualizacion);

    void quitar_pyramid_head(std::pair<int, int> indices);

public:
    Tablero(std::pair<size_t, size_t> dimensiones, std::pair<int, int> inicio, std::pair<int, int> destino,
            const std::vector<std::pair<int, int>>& paredes);

    std::pair<int, int> obtener_indices(size_t casillero);

    Matriz obtener_visualizacion(std::vector<size_t>& camino);
};

#endif