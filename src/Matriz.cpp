#include "Matriz.hpp"

using namespace std;

Matriz::Matriz() {
    fila = 0;
    columna = 0;
}

Matriz::Matriz(size_t fila, size_t columna, int valor) {
    this->fila = fila;
    this->columna = columna;
    if (fila * columna != 0) {
        matriz = new int[fila * columna];
        for (size_t i = 0; i < fila * columna; i++) {
            matriz[i] = valor;
        }
    }
}

Matriz::Matriz(size_t fila, size_t columna) : Matriz(fila, columna, 0) {}

Matriz::Matriz(size_t tamanio, int valor) : Matriz(tamanio, tamanio, valor) {}

Matriz::Matriz(size_t tamanio) : Matriz(tamanio, tamanio, 0) {}

Matriz::Matriz(const Matriz& matriz1) {
    this->fila = matriz1.fila;
    this->columna = matriz1.columna;
    if (fila * columna != 0) {
        matriz = new int[fila * columna];
        for (size_t i = 0; i < fila * columna; i++) {
            matriz[i] = matriz1.matriz[i];
        }
    }
}

Matriz& Matriz::operator=(const Matriz& matriz1) {
    if (this != &matriz1) {
        delete[] matriz;
        matriz = nullptr;
        this->fila = matriz1.fila;
        this->columna = matriz1.columna;
        if (fila * columna != 0) {
            matriz = new int[fila * columna];
            for (size_t i = 0; i < fila * columna; i++) {
                matriz[i] = matriz1.matriz[i];
            }
        }
    }
    return *this;
}

bool Matriz::indice_valido(int i, int j) {
    return i >= 0 && i < (int) fila && j >= 0 && j < (int) columna;
}

size_t Matriz::calcular_indice(int i, int j) {
    return (size_t) i * columna + (size_t) j;
}

size_t Matriz::calcular_indice(std::pair<int, int> indices) {
    return calcular_indice(indices.first, indices.second);
}

int& Matriz::elemento(int i, int j) {
    if (!indice_valido(i, j) || !matriz) {
        throw Indice_no_valido_exception();
    } else {
        return matriz[calcular_indice(i, j)];
    }
}

int& Matriz::elemento(std::pair<int, int> indices) {
    return elemento(indices.first, indices.second);
}

void Matriz::expandir() {
    int* matriz_aux = new int[(fila + 1) * (columna + 1)];
    for (size_t i = 0; i < fila + 1; i++) {
        for (size_t j = 0; j < columna + 1; j++) {
            try {
                matriz_aux[i * (columna + 1) + j] = elemento((int) i, (int) j);
            } catch (Indice_no_valido_exception& e) {
                matriz_aux[i * (columna + 1) + j] = 0;
            }
        }
    }
    fila++;
    columna++;
    delete[] matriz;
    matriz = matriz_aux;
}

size_t Matriz::filas() {
    return fila;
}

size_t Matriz::columnas() {
    return columna;
}

Matriz::~Matriz() {
    delete[] matriz;
}