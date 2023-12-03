#include <iostream>
#include "color.hpp"
#include "Visual.hpp"

void Visual::imprimir_tablero(Matriz& visualizacion) {
    for (int i = 0; i < (int) visualizacion.filas(); i++) {
        for (int j = 0; j < (int) visualizacion.columnas(); j++) {
            int vertice = visualizacion.elemento(i, j);
            switch (vertice) {
                case PARED:
                    std::cout << color::rize("...", "Dark Gray", "Dark Gray");
                    break;
                case INICIO:
                    std::cout << color::rize("...", "Red", "Red");
                    break;
                case DESTINO:
                    std::cout << color::rize("...", "Green", "Green");
                    break;
                case PYRAMID:
                    std::cout << color::rize(".", "Red", "Red");
                    std::cout << color::rize("P", "White", "Red", "Bold");
                    std::cout << color::rize(".", "Red", "Red");
                    break;
                case MULTIPLICADO:
                    std::cout << color::rize("...", "Yellow", "Yellow");
                    break;
                case JAMES:
                    std::cout << color::rize(".", "Cyan", "Cyan");
                    std::cout << color::rize("J", "White", "Cyan", "Bold");
                    std::cout << color::rize(".", "Cyan", "Cyan");
                    break;
                case CAMINO_OPTIMO:
                    std::cout << color::rize("...", "Magenta", "Megenta");
                    break;
                default:
                    std::cout << color::rize("...", "Light Gray", "Light Gray");
            }
        }
        std::cout << std::endl;
    }
}