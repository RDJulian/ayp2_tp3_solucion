#ifndef ALGO2_TP3_PT2_HEAP_H
#define ALGO2_TP3_PT2_HEAP_H

#include <vector>
#include <cstdlib>
#include <exception>

class Heap_exception : public std::exception {
};

template<typename T, bool comp(T, T)>
class Heap {
private:
    std::vector<T> datos;

    // Calcula el índice del padre.
    size_t obtener_index_padre(size_t index_hijo);

    // Calcula el índice del hijo izquierdo.
    size_t obtener_index_hijo_izquierdo(size_t index_padre);

    // Calcula el índice del hijo derecho.
    size_t obtener_index_hijo_derecho(size_t index_padre);

    // Obtiene el índice del dato más grande/chico, dependiendo de la comparación.
    size_t obtener_index_comparacion(size_t index_padre);

    // Devuelve true si el nodo está fuera de lugar (no cumple condición de Heap).
    bool nodo_fuera_de_lugar(size_t index_nodo_actual);

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Intercambia de lugar los datos de los indices indicados.
    void swap(size_t index_1, size_t index_2);

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Realiza un "upheap" sobre los índices indicados.
    // (El dato "sube" en el heap.)
    void upheap(size_t& index_insertado, size_t index_padre);

    // Post: El índice debe ser menor que la cantidad de datos.
    // Post: Realiza un "downheap" sobre el índice indicado.
    // (El dato "baja" en el heap, intercambiándose con el menor/mayor dato.)
    void downheap(size_t& index_movido);

    // NOTA: No es necesario que lancen excepciones en estos métodos porque son privados.
    // Deberian siempre asegurar que los indices pasados por parámetros son válidos.
    // Consideren cada caso con detenimiento.
    // Adicionalmente, tengan cuidado con el casteo de las variables, porque son size_t.
    // Hacer, por ejemplo, size_t i = 0; i - 1; produce un underflow.
public:
    // Constructor.
    Heap() = default;

    // Pre: -
    // Post: Agrega el dato al Heap.
    void alta(T dato);

    // Pre: El heap no puede estar vacío.
    // Post: Elimina y devuelve el primer dato.
    T baja();

    // Pre: El heap no puede estar vacío.
    // Post: Devuelve el primer dato.
    T primero();

    // Pre: -
    // Post: Devuelve true si el heap está vacío.
    bool vacio();

    // Pre: -
    // Post: Devuelve la cantidad de datos en el heap.
    size_t tamanio();

    // El constructor de copia está deshabilitado.
    Heap(const Heap& heap) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Heap& heap) = delete;

    // Destructor.
    ~Heap() = default;
};

template<typename T, bool comp(T, T)>
void Heap<T, comp>::swap(size_t index_1, size_t index_2) {
    T aux = datos[index_1];
    datos[index_1] = datos[index_2];
    datos[index_2] = aux;
}

template<typename T, bool comp(T, T)>
size_t Heap<T, comp>::obtener_index_padre(size_t index_hijo) {
    return (size_t) abs(((int) index_hijo - 1) / 2);
}

template<typename T, bool comp(T, T)>
size_t Heap<T, comp>::obtener_index_hijo_izquierdo(size_t index_padre) {
    return (2 * index_padre) + 1;
}

template<typename T, bool comp(T, T)>
size_t Heap<T, comp>::obtener_index_hijo_derecho(size_t index_padre) {
    return (2 * index_padre) + 2;
}

template<typename T, bool comp(T, T)>
size_t Heap<T, comp>::obtener_index_comparacion(size_t index_padre) {
    size_t index_hijo_izquierdo = obtener_index_hijo_izquierdo(index_padre);
    size_t index_hijo_derecho = obtener_index_hijo_derecho(index_padre);
    if (index_hijo_derecho > datos.size() - 1 || comp(datos[index_hijo_izquierdo], datos[index_hijo_derecho])) {
        return index_hijo_izquierdo;
    } else {
        return index_hijo_derecho;
    }
}

template<typename T, bool comp(T, T)>
bool Heap<T, comp>::nodo_fuera_de_lugar(size_t index_nodo_actual) {
    size_t index_hijo = obtener_index_comparacion(index_nodo_actual);
    if (index_hijo > datos.size() - 1) {
        return false;
    } else {
        return comp(datos[index_hijo], datos[index_nodo_actual]);
    }
}

template<typename T, bool comp(T, T)>
void Heap<T, comp>::upheap(size_t& index_insertado, size_t index_padre) {
    swap(index_insertado, index_padre);
    index_insertado = index_padre;
}

template<typename T, bool comp(T, T)>
void Heap<T, comp>::downheap(size_t& index_movido) {
    size_t index_hijo_menor = obtener_index_comparacion(index_movido);
    swap(index_movido, index_hijo_menor);
    index_movido = index_hijo_menor;
}

template<typename T, bool comp(T, T)>
void Heap<T, comp>::alta(T dato) {
    datos.push_back(dato);
    if (datos.size() > 1) {
        size_t index_acolado = datos.size() - 1;
        size_t index_padre = obtener_index_padre(index_acolado);
        while (comp(dato, datos[index_padre])) {
            upheap(index_acolado, index_padre);
            index_padre = obtener_index_padre(index_acolado);
        }
    }
}

// AGREGAR EXCEPCIONES
template<typename T, bool comp(T, T)>
T Heap<T, comp>::baja() {
    if (datos.empty()) {
        throw Heap_exception();
    }
    T dato = primero();
    datos[0] = datos[datos.size() - 1];
    datos.pop_back();
    if (!datos.empty()) {
        size_t index_dato_movido = 0;
        while (nodo_fuera_de_lugar(index_dato_movido)) {
            downheap(index_dato_movido);
        }
    }
    return dato;
}


template<typename T, bool comp(T, T)>
T Heap<T, comp>::primero() {
    if (datos.empty()) {
        throw Heap_exception();
    }
    return datos[0];
}

template<typename T, bool comp(T, T)>
bool Heap<T, comp>::vacio() {
    return datos.empty();
}

template<typename T, bool comp(T, T)>
size_t Heap<T, comp>::tamanio() {
    return datos.size();
}

#endif