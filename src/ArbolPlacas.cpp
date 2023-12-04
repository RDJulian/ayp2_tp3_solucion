#include "ArbolPlacas.hpp"
#include "Random.hpp"

ArbolPlacas::ArbolPlacas() = default;

void ArbolPlacas::generar_placa_aleatoria() {
    bool valido = false;
    Placa* placa;
    while (!valido) {
        placa = new Placa("RIP", "Biggerton Ouncerton", Random::number(100, 666));
        if (consulta(placa)) {
            delete placa;
        } else {
            alta(placa);
            valido = true;
        }
    }
}

ArbolPlacas::~ArbolPlacas() {
    ejecutar(Placa::liberar);
}