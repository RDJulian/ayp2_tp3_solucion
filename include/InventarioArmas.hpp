#ifndef AYP2_TP3_SOLUCION_INVENTARIOARMAS_HPP
#define AYP2_TP3_SOLUCION_INVENTARIOARMAS_HPP

#include "TDAs/Heap.hpp"
#include "Arma.hpp"

// TODO: Documentar
class InventarioArmas {
private:
    Heap<Arma*, Arma::menor> inventario_debil;
    Heap<Arma*, Arma::mayor> inventario_fuerte;
    bool estrategia_fuerte;

    void intercambiar_inventarios();

    void generar_arma();

public:
    InventarioArmas();

    Arma* obtener_arma(bool fuerte);

    Arma* consultar_arma(bool fuerte);

    void guardar_arma(Arma* arma);

    void generar_arma_aleatoria();

    size_t tamanio();

    ~InventarioArmas();
};

#endif