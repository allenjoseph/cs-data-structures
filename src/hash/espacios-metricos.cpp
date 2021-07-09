#include <iostream>
#include <chrono>

using namespace std;

//Clase Padre: Lista
template<typename E>
class Lista {
private:
public:
    //Constructor
    Lista() {}

    //Destructor
    ~Lista() {}

    //Limpiar la lista: dejarla vacia la lista
    virtual void limpiar() = 0;

    //Insertar un elemento donde se encuentra el puntero "actual"
    virtual void insertar(E elemento) = 0;

    //Agregar un elemento a la lista (al final)
    virtual void agregar(E elemento) = 0;

    //Libera de la memoria y retorna el elemento "actual"
    virtual E eliminar() = 0;

    //Mover "actual" al inicio de la lista
    virtual void moverAInicio() = 0;

    //Mover "actual" al final de la lista

    // primer espacio disponible
    virtual void moverAlFinal() = 0;

    //Mover "actual" a la posicion anterior (izquierda)
    virtual void anterior() = 0;

    //Mover "actual" a la posicion posterior (derecha)
    virtual void siguiente() = 0;

    //Retornar le numero de elementos de la lista
    virtual int longitud() = 0;

    //Retornar la posicion del elemento "actual"
    virtual int posicionActual() = 0;

    //"Actual" se mueve a la posicion "pos"
    virtual void moverAPosicion(int pos) = 0;

    //Retorna el valor que estaba en la posicion "actual"
    virtual E getValor() = 0;

    //Modificar el valor en la posicion "actual"
    virtual void setValor(E elemento) = 0;
};

//Clase Hija: ListaArreglo
template<typename E>
class ListaArreglo : public Lista<E> {
private:
    E *arreglo;   //Arreglo de elementos
    int tamMax;   //Tamanho fijo
    int tamLista; //Tamanho de la lista
    int actual;   //Indice "actual"

public:
    //Constructor
    ListaArreglo(int tamMax = 10) {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
        for (int i = 0; i < this->tamMax; ++i) {
            this->arreglo[i] = nullptr;
        }
    }

    //Destructor
    ~ListaArreglo() {
        delete[] this->arreglo;
    }

    //Mover "actual" al inicio de la lista
    void moverAInicio() {
        this->actual = 0;
    }

    //Mover "actual" al final de la lista:
    // primer espacio disponible
    void moverAlFinal() {
        this->actual = this->tamLista;
    }

    //Mover "actual" a la posicion posterior (derecha)
    void siguiente() {
        //Sentinela
        if (this->actual < this->tamLista)
            this->actual++;
    }

    //Mover "actual" a la posicion anterior (izquierda)
    void anterior() {
        //Sentinela
        if (this->actual > 0)
            this->actual--;
    }

    //Agregar un elemento a la lista (al final)
    void agregar(E elemento) {
        this->arreglo[this->tamLista++] = elemento;
    }

    // Agregar un elemento a la lista (al final)
    void agregarOrdenadamente(E elemento) {
        for (this->moverAInicio(); this->posicionActual() < this->longitud(); this->siguiente()) {
            if (this->getValor() > elemento) {
                break;
            }
        }
        this->insertar(elemento);
    }

    //Retornar le numero de elementos de la lista
    int longitud() {
        return this->tamLista;
    }

    //Retornar la posicion del elemento "actual"
    int posicionActual() {
        return this->actual;
    }

    //"Actual" se mueve a la posicion "pos"
    void moverAPosicion(int pos) {
        //Sentinela
        if (pos >= 0 && pos < this->tamLista)
            this->actual = pos;
    }

    //Retorna el valor que estaba en la posicion "actual"
    E getValor() {
        return this->arreglo[this->actual];
    }

    //Modificar el valor en la posicion "actual"
    void setValor(E elemento) {
        this->arreglo[this->actual] = elemento;
    }

    //Limpiar la lista: dejarla vacia la lista
    void limpiar() {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    //Insertar un elemento donde se encuentra el puntero "actual"
    void insertar(E elemento) {
        for (int i = this->tamLista; i > this->actual; i--)
            this->arreglo[i] = this->arreglo[i - 1];
        this->arreglo[this->actual] = elemento;
        this->tamLista++;
    }

    //Eliminar y retornar el elemento "actual"
    E eliminar() {
        E eliminado = this->arreglo[this->actual];
        for (int i = this->actual; i < this->tamLista; ++i)
            this->arreglo[i] = this->arreglo[i + 1];
        this->tamLista--;
        return eliminado;
    }
};

template<typename Key, typename E>
class Diccionario {
private:
public:
    Diccionario() {}  //Constructor
    ~Diccionario() {} //Destructor

    //Reinicializacion de un diccionario
    virtual void limpiar() = 0;

    //Insertar un registro
    //k: la clave para el reigstro
    //e: el registro
    virtual void insertar(Key K, E e) = 0;

    //Remover y retornar un registro
    //k: la clave del registro que debe ser removido
    //Retornar: un registro. Si hay mas de un registro con la misma clave,
    //  se debe remover uno de manera arbitraria
    //Retornar NULL si la clave "K" no se encuentra en el diccionario
    virtual E remover(Key K) = 0;

    //Remover y retornar un registro arbitrario del diccionario
    //Retornar: el registro que ha sido removido o NULL si no existe
    virtual E removerCualquiera() = 0;

    //Return: un registro o NULL si no existe
    //Si hay multiples registros, se debe retornar uno de manera aleatoria
    //K: la clave del registro a encontrar
    virtual E encontrar(Key K) = 0;

    //Retornar el número de registros dentro del diccionario
    virtual int longitud() = 0;
};

template<typename Key, typename E>
class KVPar {
private:
    Key k;
    E e;

public:
    //Constructor
    KVPar() {}

    KVPar(Key kval, E eval) {
        this->k = kval;
        this->e = eval;
    }

    KVPar(KVPar &o) {
        this->k = o.k;
        this->e = o.e;
    }

    Key key() {
        return this->k;
    }

    void setKey(Key ink) {
        this->k = ink;
    }

    E valor() {
        return this->e;
    }
};

template<typename Key, typename E>
class DiccionarioArreglo : public Diccionario<Key, E> {
private:
    ListaArreglo<KVPar<Key, E>*> *lista;

public:
    DiccionarioArreglo(int tamanio) {
        this->lista = new ListaArreglo<KVPar<Key, E>*>(tamanio);
    }

    ~DiccionarioArreglo() {
        delete this->lista;
    }

    //Reinicializacion de un diccionario
    void limpiar() {
        this->limpiar();
    };

    //Insertar un registro
    //k: la clave para el reigstro
    //e: el registro
    void insertar(Key k, E e) {
        KVPar<Key, E> *temp = new KVPar<Key, E> (k, e);
        this->lista->agregar(temp);
    };

    //Remover y retornar un registro
    //k: la clave del registro que debe ser removido
    //Retornar: un registro. Si hay mas de un registro con la misma clave,
    //  se debe remover uno de manera arbitraria
    //Retornar NULL si la clave "K" no se encuentra en el diccionario
    E remover(Key k) {
        E temp = this->encontrar(k);
        if (temp != 0) {
            this->lista->eliminar();
        }
        return temp;
    };

    //Remover y retornar un registro arbitrario del diccionario
    //Retornar: el registro que ha sido removido o NULL si no existe
    E removerCualquiera() {
        this->lista->moverAlFinal();
        this->lista->anterior();
        KVPar<Key, E> *elem = this->lista->eliminar();
        return elem->valor();
    };

    //Return: un registro o NULL si no existe
    //Si hay multiples registros, se debe retornar uno de manera aleatoria
    //K: la clave del registro a encontrar
    E encontrar(Key k) {
        for (
                this->lista->moverAInicio();
                this->lista->posicionActual() < this->lista->longitud();
                this->lista->siguiente()) {
            KVPar<Key, E> *temp = this->lista->getValor();
            if (k == temp->key())
                return temp->valor();
        }
        return 0;
    };

    //Retornar el número de registros dentro del diccionario
    int longitud() {
        return this->lista->longitud();
    };

    void imprimir() {
        for(this->lista->moverAInicio();
            this->lista->posicionActual() < this->lista->longitud();
            this->lista->siguiente()){
            cout << "Token: " << this->lista->getValor()->key() << ", Frecuencia: " << this->lista->getValor()->valor() << endl;
        }
    }
};

template<typename Key, typename E>
class EspaciosMetricos {
private:
    DiccionarioArreglo<Key, E> *diccionario;
    int tamanio;

public:
    int colisiones = 0;

    EspaciosMetricos(int tamanio) {
        this->tamanio = tamanio;
        this->diccionario = new DiccionarioArreglo<Key, E>(tamanio);
    }

    ~EspaciosMetricos() {
        delete this->diccionario;
    }

    void limpiar() {
        this->diccionario->limpiar();
    }

    void insertar(Key k) {
        this->splitString(k);
    }

    int longitud() {
        return this->diccionario->longitud();
    }

    void agregarToken(string token) {
        int frecuencia = this->diccionario->encontrar(token);
        if (frecuencia == 0) {
            cout << "fecuencia es 0" << endl;
        }
        this->diccionario->insertar(token, frecuencia++);
    }

    string splitString(string txt, char ch = ' ')
    {
        size_t pos = txt.find( ch );
        size_t initialPos = 0;

        // Decompose statement
        while( pos != std::string::npos ) {
            this->agregarToken( txt.substr( initialPos, pos - initialPos ) );
            initialPos = pos + 1;

            pos = txt.find( ch, initialPos );
        }

        // Add the last one
        this->agregarToken( txt.substr( initialPos, min( pos, txt.size() ) - initialPos + 1 ) );
    }

    void imprimirTokens() {
        this->diccionario->imprimir();
    }
};

int main() {
    EspaciosMetricos<string, int> *corpus = new EspaciosMetricos<string, int>(100);
    corpus->insertar("oferta celular hoy");
    corpus->insertar("matricula semestre");
    corpus->insertar("oferta viaje");
    corpus->insertar("tarea semestre");

    corpus->imprimirTokens();

    return 0;
}
