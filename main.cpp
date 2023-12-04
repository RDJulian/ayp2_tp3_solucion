#include "Simulador.hpp"

int main() {
    Simulador simulador;
    do {
        simulador.mostrar_informacion();
        simulador.equipar_arma_debil();
        simulador.mover_camino_optimo();
        simulador.mostrar_resultado();
    } while (simulador.partida_en_curso());
    return 0;
}