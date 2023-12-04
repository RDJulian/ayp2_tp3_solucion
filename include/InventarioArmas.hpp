#ifndef AYP2_TP3_SOLUCION_INVENTARIOARMAS_HPP
#define AYP2_TP3_SOLUCION_INVENTARIOARMAS_HPP

#include "TDAs/Heap.hpp"
#include "Arma.hpp"

class InventarioArmas {
private:
    Heap<Arma*, Arma::menor> inventario_debil;
    Heap<Arma*, Arma::mayor> inventario_fuerte;
    bool estrategia_fuerte;

    // Pre: -
    // Post: Intercambia los datos entre los inventarios, cambiando la estrategia.
    void intercambiar_inventarios();

    // Pre: -
    // Post: Genera un arma con potencia aleatoria y la agrega al inventario.
    void generar_arma();

public:
    InventarioArmas();

    // Pre: -
    // Post: Devuelve la primer arma del inventario, dependiendo del parámetro, quitándola.
    // Si no hay armas en el inventario, devuelve nullptr.
    // NOTA: Capaz sería mejor que el inventario simplemente "burbujee" la excepción de baja de Heap vacio.
    Arma* obtener_arma(bool fuerte);

    // Pre: -
    // Post: Devuelve la primer arma del inventario, dependiendo del parámetro, sin quitarla.
    // Si no hay armas en el inventario, devuelve nullptr.
    // NOTA: Capaz sería mejor que el inventario simplemente "burbujee" la excepción de consulta de Heap vacio.
    Arma* consultar_arma(bool fuerte);

    // Pre: -
    // Post: Guarda el arma en el inventario.
    void guardar_arma(Arma* arma);

    // Pre: -
    // Post: Genera un arma, con una chance del 20%.
    void generar_arma_aleatoria();

    // Pre: -
    // Post: Devuelve la cantidad de armas en el inventario.
    size_t tamanio();

    ~InventarioArmas();
};

#endif