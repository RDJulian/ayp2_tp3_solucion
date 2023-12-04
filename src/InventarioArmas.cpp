#include "InventarioArmas.hpp"
#include "Random.hpp"

InventarioArmas::InventarioArmas() {
    estrategia_fuerte = true;
}

void InventarioArmas::intercambiar_inventarios() {
    if (estrategia_fuerte) {
        while (!inventario_fuerte.vacio()) {
            inventario_debil.alta(inventario_fuerte.baja());
        }
    } else {
        while (!inventario_debil.vacio()) {
            inventario_fuerte.alta(inventario_debil.baja());
        }
    }
    estrategia_fuerte = !estrategia_fuerte;
}

Arma* InventarioArmas::obtener_arma(bool fuerte) {
    Arma* arma = nullptr;
    if (fuerte != estrategia_fuerte) {
        intercambiar_inventarios();
    }
    if (fuerte && !inventario_fuerte.vacio()) {
        arma = inventario_fuerte.baja();
    } else if (!fuerte && !inventario_debil.vacio()) {
        arma = inventario_debil.baja();
    }
    return arma;
}

Arma* InventarioArmas::consultar_arma(bool fuerte) {
    Arma* arma = nullptr;
    if (fuerte != estrategia_fuerte) {
        intercambiar_inventarios();
    }
    if (fuerte && !inventario_fuerte.vacio()) {
        arma = inventario_fuerte.primero();
    } else if (!fuerte && !inventario_debil.vacio()) {
        arma = inventario_debil.primero();
    }
    return arma;
}

void InventarioArmas::guardar_arma(Arma* arma) {
    if (estrategia_fuerte) {
        inventario_fuerte.alta(arma);
    } else {
        inventario_debil.alta(arma);
    }
}

void InventarioArmas::generar_arma() {
    Arma* arma = new Arma("MP727", (size_t) Random::number(10, 100));
    guardar_arma(arma);
}

void InventarioArmas::generar_arma_aleatoria() {
    int chance = Random::number(1, 5);
    if (chance == 5) {
        generar_arma();
    }
}

size_t InventarioArmas::tamanio() {
    if (estrategia_fuerte) {
        return inventario_fuerte.tamanio();
    } else {
        return inventario_debil.tamanio();
    }
}

InventarioArmas::~InventarioArmas() {
    if (estrategia_fuerte) {
        while (!inventario_fuerte.vacio()) {
            delete inventario_fuerte.baja();
        }
    } else {
        while (!inventario_debil.vacio()) {
            delete inventario_debil.baja();
        }
    }
}