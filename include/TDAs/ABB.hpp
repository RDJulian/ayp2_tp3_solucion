#ifndef ABB_H
#define ABB_H

#include <exception>
#include "NodoABB.hpp"

class ABB_exception : public std::exception {
};

template<typename T, bool menor(T, T), bool igual(T, T)>
class ABB {
private:
    NodoABB<T, menor, igual>* raiz;
    std::size_t cantidad_datos;
public:
    // Constructor.
    ABB();

    // Pre: El dato a ingresar no puede estar en el árbol.
    // Post: Agrega el dato al árbol. Si no hay datos, crea una nueva raiz.
    void alta(T dato);

    // Pre: -
    // Post: Elimina el dato del árbol. Si no existe, no hace nada.
    // NOTA: Si la raiz cambia (sin importar el caso), se debe reasignar correctamente.
    void baja(T dato);

    // Pre: -
    // Post: Devuelve true si el dato está en el árbol. Si no hay datos, devuelve false.
    bool consulta(T dato);

    // Pre: -
    // Post: Devuelve el recorrido inorder.
    std::vector<T> inorder();

    // Pre: -
    // Post: Devuelve el recorrido preorder.
    std::vector<T> preorder();

    // Pre: -
    // Post: Devuelve el recorrido postorder.
    std::vector<T> postorder();

    // Pre: -
    // Post: Devuelve el recorrido en ancho.
    std::vector<T> ancho();

    // Pre: -
    // Post: Ejecuta el método/función en cada uno de los nodos.
    // NOTA: No abusar de este método, está solamente para simplificar
    // algunas cosas, como liberar la memoria de los nodos de usar punteros
    // o imprimir por pantalla el contenido. Pueden usar cualquier recorrido.
    void ejecutar(void metodo(T));

    // Pre: -
    // Post: Devuelve la cantidad de datos en el árbol.
    std::size_t tamanio();

    // Pre: -
    // Post: Devuelve true si el árbol está vacio.
    bool vacio();

    // Pre: -
    // Post: Devuelve la altura del árbol. Si el árbol está vacio, devuelve 0.
    size_t altura();

    // El constructor de copia está deshabilitado.
    ABB(const ABB& abb) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const ABB& abb) = delete;

    // Destructor.
    ~ABB();
};

template<typename T, bool menor(T, T), bool igual(T, T)>
size_t ABB<T, menor, igual>::altura() {
    if (vacio()) {
        return 0;
    } else {
        return raiz->altura();
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
ABB<T, menor, igual>::ABB() {
    raiz = nullptr;
    cantidad_datos = 0;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void ABB<T, menor, igual>::alta(T dato) {
    if (!consulta(dato)) {
        if (!raiz) {
            raiz = new NodoABB<T, menor, igual>(dato);
        } else {
            raiz->alta(dato);
        }
        cantidad_datos++;
    } else {
        throw ABB_exception();
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
bool ABB<T, menor, igual>::consulta(T dato) {
    if (!raiz) {
        return false;
    } else {
        return raiz->consulta(dato);
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void ABB<T, menor, igual>::baja(T dato) {
    if (consulta(dato)) {
        NodoABB<T, menor, igual>* nueva_raiz = raiz->baja(dato);
        if (nueva_raiz) {
            raiz = nueva_raiz;
        }
        cantidad_datos--;
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
std::vector<T> ABB<T, menor, igual>::inorder() {
    std::vector<T> datos;
    if (raiz) {
        raiz->inorder(datos);
    }
    return datos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
std::vector<T> ABB<T, menor, igual>::preorder() {
    std::vector<T> datos;
    if (raiz) {
        raiz->preorder(datos);
    }
    return datos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
std::vector<T> ABB<T, menor, igual>::postorder() {
    std::vector<T> datos;
    if (raiz) {
        raiz->postorder(datos);
    }
    return datos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
std::vector<T> ABB<T, menor, igual>::ancho() {
    std::vector<T> datos;
    std::queue<NodoABB<T, menor, igual>*> nodos;
    if (raiz) {
        nodos.push(raiz);
    }
    while (!nodos.empty()) {
        nodos.front()->ancho(nodos, datos);
        nodos.pop();
    }
    return datos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void ABB<T, menor, igual>::ejecutar(void metodo(T)) {
    if (raiz) {
        raiz->ejecutar(metodo);
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
size_t ABB<T, menor, igual>::tamanio() {
    return cantidad_datos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
bool ABB<T, menor, igual>::vacio() {
    return cantidad_datos == 0;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
ABB<T, menor, igual>::~ABB() {
    delete raiz;
}

#endif