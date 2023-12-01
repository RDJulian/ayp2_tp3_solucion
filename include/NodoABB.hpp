#ifndef NODOABB_H
#define NODOABB_H

#include <vector>
#include <queue>

template<typename T, bool menor(T, T), bool igual(T, T)>
class NodoABB {
private:
    T dato{};
    NodoABB<T, menor, igual>* padre;
    NodoABB<T, menor, igual>* hijo_izquierdo;
    NodoABB<T, menor, igual>* hijo_derecho;

    // Busca sucesor inmediato del nodo actual.
    NodoABB<T, menor, igual>* buscar_sucesor();

    // Reemplaza el nodo actual con nuevo.
    NodoABB<T, menor, igual>* reemplazar_nodo(NodoABB<T, menor, igual>* nuevo);

public:
    // Constructor.
    NodoABB(T dato);

    // Pre: -
    // Post: Agrega el dato al árbol.
    // NOTA: Ya se debería haber revisado si el dato está o no.
    void alta(T dato_insertar);

    // Pre: -
    // Post: Elimina el dato del árbol y devuelve la nueva raiz, de haberla.
    // NOTA: Ya se debería haber revisado si el dato está o no.
    NodoABB<T, menor, igual>* baja(T dato_bajar);

    // Pre: -
    // Post: Devuelve true si el dato está en el subárbol.
    bool consulta(T dato_consultar);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido inorder.
    void inorder(std::vector<T>& datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido preorder.
    void preorder(std::vector<T>& datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido postorder.
    void postorder(std::vector<T>& datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido en ancho.
    void ancho(std::queue<NodoABB<T, menor, igual>*>& nodos, std::vector<T>& datos);

    // Pre: -
    // Post: Ejecuta el método/función en el subárbol.
    void ejecutar(void metodo(T));

    // Destructor.
    ~NodoABB();
};

template<typename T, bool menor(T, T), bool igual(T, T)>
void NodoABB<T, menor, igual>::ejecutar(void metodo(T)) {
    if (hijo_izquierdo) {
        hijo_izquierdo->ejecutar(metodo);
    }
    metodo(dato);
    if (hijo_derecho) {
        hijo_derecho->ejecutar(metodo);
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
NodoABB<T, menor, igual>* NodoABB<T, menor, igual>::buscar_sucesor() {
    if (hijo_derecho) {
        NodoABB<T, menor, igual>* sucesor = hijo_derecho;
        while (sucesor->hijo_izquierdo) {
            sucesor = sucesor->hijo_izquierdo;
        }
        return sucesor;
    } else {
        return nullptr;
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
NodoABB<T, menor, igual>* NodoABB<T, menor, igual>::reemplazar_nodo(NodoABB<T, menor, igual>* nuevo) {
    NodoABB<T, menor, igual>* nueva_raiz = nullptr;
    if (!padre) {
        nueva_raiz = nuevo;
    } else if (this == padre->hijo_izquierdo) {
        padre->hijo_izquierdo = nuevo;
    } else {
        padre->hijo_derecho = nuevo;
    }
    if (nuevo) {
        nuevo->padre = padre;
    }
    return nueva_raiz;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
NodoABB<T, menor, igual>::NodoABB(T dato) {
    this->dato = dato;
    padre = nullptr;
    hijo_derecho = nullptr;
    hijo_izquierdo = nullptr;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void NodoABB<T, menor, igual>::alta(T dato_insertar) {
    if (menor(dato_insertar, dato)) {
        if (!hijo_izquierdo) {
            hijo_izquierdo = new NodoABB<T, menor, igual>(dato_insertar);
            hijo_izquierdo->padre = this;
        } else {
            hijo_izquierdo->alta(dato_insertar);
        }
    } else {
        if (!hijo_derecho) {
            hijo_derecho = new NodoABB<T, menor, igual>(dato_insertar);
            hijo_derecho->padre = this;
        } else {
            hijo_derecho->alta(dato_insertar);
        }
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
bool NodoABB<T, menor, igual>::consulta(T dato_consultar) {
    if (igual(dato, dato_consultar)) {
        return true;
    } else {
        NodoABB<T, menor, igual>* nodo = (menor(dato_consultar, dato) ? hijo_izquierdo : hijo_derecho);
        if (!nodo) {
            return false;
        } else {
            return nodo->consulta(dato_consultar);
        }
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
NodoABB<T, menor, igual>* NodoABB<T, menor, igual>::baja(T dato_bajar) {
    if (igual(dato, dato_bajar)) {
        NodoABB<T, menor, igual>* nueva_raiz;
        if (!hijo_izquierdo) {
            nueva_raiz = reemplazar_nodo(hijo_derecho);
        } else if (!hijo_derecho) {
            nueva_raiz = reemplazar_nodo(hijo_izquierdo);
        } else {
            NodoABB<T, menor, igual>* sucesor = buscar_sucesor();
            if (sucesor->padre != this) {
                sucesor->reemplazar_nodo(sucesor->hijo_derecho);
                sucesor->hijo_derecho = hijo_derecho;
                sucesor->hijo_derecho->padre = sucesor;
            }
            nueva_raiz = reemplazar_nodo(sucesor);
            sucesor->hijo_izquierdo = hijo_izquierdo;
            sucesor->hijo_izquierdo->padre = sucesor;
        }
        padre = nullptr;
        hijo_izquierdo = nullptr;
        hijo_derecho = nullptr;
        delete this;
        return nueva_raiz;
    } else {
        NodoABB<T, menor, igual>* nodo = (menor(dato_bajar, dato) ? hijo_izquierdo : hijo_derecho);
        return nodo->baja(dato_bajar);
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void NodoABB<T, menor, igual>::inorder(std::vector<T>& datos) {
    if (hijo_izquierdo) {
        hijo_izquierdo->inorder(datos);
    }
    datos.push_back(dato);
    if (hijo_derecho) {
        hijo_derecho->inorder(datos);
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void NodoABB<T, menor, igual>::preorder(std::vector<T>& datos) {
    datos.push_back(dato);
    if (hijo_izquierdo) {
        hijo_izquierdo->preorder(datos);
    }
    if (hijo_derecho) {
        hijo_derecho->preorder(datos);
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void NodoABB<T, menor, igual>::postorder(std::vector<T>& datos) {
    if (hijo_izquierdo) {
        hijo_izquierdo->postorder(datos);
    }
    if (hijo_derecho) {
        hijo_derecho->postorder(datos);
    }
    datos.push_back(dato);
}

template<typename T, bool (* menor)(T, T), bool (* igual)(T, T)>
void NodoABB<T, menor, igual>::ancho(std::queue<NodoABB<T, menor, igual>*>& nodos, std::vector<T>& datos) {
    if (hijo_izquierdo) {
        nodos.push(hijo_izquierdo);
    }
    if (hijo_derecho) {
        nodos.push(hijo_derecho);
    }
    datos.push_back(dato);
}

template<typename T, bool menor(T, T), bool igual(T, T)>
NodoABB<T, menor, igual>::~NodoABB() {
    delete hijo_izquierdo;
    delete hijo_derecho;
}

#endif