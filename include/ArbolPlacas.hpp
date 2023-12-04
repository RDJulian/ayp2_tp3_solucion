#ifndef AYP2_TP3_SOLUCION_ARBOLPLACAS_HPP
#define AYP2_TP3_SOLUCION_ARBOLPLACAS_HPP

#include "Placa.hpp"
#include "TDAs/ABB.hpp"

// Decorator.
class ArbolPlacas : public ABB<Placa*, Placa::menor, Placa::igual> {
public:
    ArbolPlacas();

    // Pre: -
    // Post: Genera una placa aleatoria (cuyo ID no esté en el árbol) y la agrega.
    void generar_placa_aleatoria();

    ~ArbolPlacas();
};

#endif