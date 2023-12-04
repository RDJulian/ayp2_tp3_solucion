#include "ArbolPlacas.hpp"
#include "Random.hpp"
#include <iostream>

ArbolPlacas::ArbolPlacas() = default;

// NOTA: Se podria obtener una lista de los ID que faltan dentro de los posibles, luego obtener uno al azar.
void ArbolPlacas::generar_placa_aleatoria() {
    bool valido = false;
    Placa* placa;
    size_t i = 0;
    const size_t MAX_ITERACIONES = 100;
    while (!valido && i < MAX_ITERACIONES) {
        placa = new Placa("RIP", "Biggerton Ouncerton", Random::number(100, 666));
        if (consulta(placa)) {
            delete placa;
            i++;
        } else {
            alta(placa);
            valido = true;
        }
    }
    if (i >= MAX_ITERACIONES) {
        std::cout << "WARNING: Se intentaron insertar " << i << " placas distintas, sin éxito." << std::endl;
    }
}

ArbolPlacas::~ArbolPlacas() {
    ejecutar(Placa::liberar);
}