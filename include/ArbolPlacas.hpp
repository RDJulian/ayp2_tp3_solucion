#ifndef AYP2_TP3_SOLUCION_ARBOLPLACAS_HPP
#define AYP2_TP3_SOLUCION_ARBOLPLACAS_HPP

#include "Placa.hpp"
#include "ABB.hpp"

class ArbolPlacas : public ABB<Placa*, Placa::menor, Placa::igual> {
public:
    ArbolPlacas();

    void generar_placa_aleatoria();

    ~ArbolPlacas();
};

#endif