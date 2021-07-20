#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

//Clase Padre: Lista
template <typename E>
class Lista
{
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
template <typename E>
class ListaArreglo : public Lista<E>
{
private:
    E *arreglo;   //Arreglo de elementos
    int tamMax;   //Tamanho fijo
    int tamLista; //Tamanho de la lista
    int actual;   //Indice "actual"

public:
    //Constructor
    ListaArreglo(int tamMax = 10)
    {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
        for (int i = 0; i < this->tamMax; ++i)
        {
            this->arreglo[i] = nullptr;
        }
    }

    //Destructor
    ~ListaArreglo()
    {
        delete[] this->arreglo;
    }

    //Mover "actual" al inicio de la lista
    void moverAInicio()
    {
        this->actual = 0;
    }

    //Mover "actual" al final de la lista:
    // primer espacio disponible
    void moverAlFinal()
    {
        this->actual = this->tamLista;
    }

    //Mover "actual" a la posicion posterior (derecha)
    void siguiente()
    {
        //Sentinela
        if (this->actual < this->tamLista)
            this->actual++;
    }

    //Mover "actual" a la posicion anterior (izquierda)
    void anterior()
    {
        //Sentinela
        if (this->actual > 0)
            this->actual--;
    }

    //Agregar un elemento a la lista (al final)
    void agregar(E elemento)
    {
        this->arreglo[this->tamLista++] = elemento;
    }

    // Agregar un elemento a la lista (al final)
    void agregarOrdenadamente(E elemento)
    {
        for (this->moverAInicio(); this->posicionActual() < this->longitud(); this->siguiente())
        {
            if (this->getValor() > elemento)
            {
                break;
            }
        }
        this->insertar(elemento);
    }

    //Retornar le numero de elementos de la lista
    int longitud()
    {
        return this->tamLista;
    }

    //Retornar la posicion del elemento "actual"
    int posicionActual()
    {
        return this->actual;
    }

    //"Actual" se mueve a la posicion "pos"
    void moverAPosicion(int pos)
    {
        //Sentinela
        if (pos >= 0 && pos < this->tamLista)
            this->actual = pos;
    }

    //Retorna el valor que estaba en la posicion "actual"
    E getValor()
    {
        return this->arreglo[this->actual];
    }

    //Modificar el valor en la posicion "actual"
    void setValor(E elemento)
    {
        this->arreglo[this->actual] = elemento;
    }

    //Limpiar la lista: dejarla vacia la lista
    void limpiar()
    {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    //Insertar un elemento donde se encuentra el puntero "actual"
    void insertar(E elemento)
    {
        for (int i = this->tamLista; i > this->actual; i--)
            this->arreglo[i] = this->arreglo[i - 1];
        this->arreglo[this->actual] = elemento;
        this->tamLista++;
    }

    //Eliminar y retornar el elemento "actual"
    E eliminar()
    {
        E eliminado = this->arreglo[this->actual];
        for (int i = this->actual; i < this->tamLista; ++i)
            this->arreglo[i] = this->arreglo[i + 1];
        this->tamLista--;
        return eliminado;
    }

    // imprime los valors de la lista
    void imprimir()
    {
        for (this->moverAInicio();
             this->posicionActual() < this->longitud();
             this->siguiente())
        {
            cout << this->posicionActual() << ": " << this->getValor() << endl;
        }
    }
};

//Nodo
template <typename E>
class Nodo
{
public:
    E elemento;      //Valor para este nodo
    Nodo *siguiente; //Puntero al siguiente nodo de la lista

    //Constructor
    Nodo(E elem, Nodo *proximo = NULL)
    {
        this->elemento = elem;
        this->siguiente = proximo;
    }
    Nodo(Nodo *proximo = NULL)
    {
        this->siguiente = proximo;
    }
};

//Par Clave-Valor
template <typename Key, typename E>
class KVPar
{
private:
    Key k;
    E e;

public:
    //Constructor
    KVPar() {}

    KVPar(Key kval, E eval)
    {
        this->k = kval;
        this->e = eval;
    }

    KVPar(KVPar &o)
    {
        this->k = o.k;
        this->e = o.e;
    }

    Key key()
    {
        return this->k;
    }

    void setKey(Key ink)
    {
        this->k = ink;
    }

    E valor()
    {
        return this->e;
    }
};

//Clase hija: ListaEnlazada
template <typename E>
class ListaEnlazada : public Lista<E>
{
private:
    Nodo<E *> *cabeza; //puntero al primer elemento
    Nodo<E *> *cola;   //puntero al ultimo elemento
    Nodo<E *> *actual; //puntero al elemento actual
    int cantidad;      //tamanho de la lista

    void inicializar()
    {
        this->cantidad = 0;
        this->cola = this->actual = this->cabeza = new Nodo<E *>;
    }

    void eliminarTodo()
    {
        while (this->cabeza != NULL)
        {
            this->actual = this->cabeza;
            this->cabeza = this->cabeza->siguiente;
            delete actual;
        }
    }

public:
    //Constructor
    ListaEnlazada()
    {
        inicializar();
    }

    //Destructor
    ~ListaEnlazada()
    {
        eliminarTodo();
    }

    //Limpiar la lista: dejarla vacia la lista
    void limpiar()
    {
        eliminarTodo();
        inicializar();
    }

    //Insertar un elemento donde se encuentra el puntero "actual"
    void insertar(E elemento)
    {
        this->actual->siguiente = new Nodo<E *>(new E(elemento), this->actual->siguiente);
        if (this->cola == this->actual)
            this->cola = this->actual->siguiente;
        this->cantidad++;
    }

    //Agregar un elemento a la lista (al final)
    void agregar(E elemento)
    {
        this->cola = this->cola->siguiente = new Nodo<E *>(new E(elemento), NULL);
        this->cantidad++;
    }

    //Mover "actual" al inicio de la lista
    void moverAInicio()
    {
        this->actual = this->cabeza;
    }

    //Mover "actual" al final de la lista
    // primer espacio disponible
    void moverAlFinal()
    {
        this->actual = this->cola;
    }

    //Mover "actual" a la posicion posterior (derecha)
    void siguiente()
    {
        if (this->actual != this->cola)
            this->actual = this->actual->siguiente;
    }

    //Retornar le numero de elementos de la lista
    int longitud()
    {
        return this->cantidad;
    }

    //Retorna el valor que estaba en la posicion "actual"
    E getValor()
    {
        if (this->actual->siguiente == NULL)
        {
            cout << "Valor no existe";
            return NULL;
        }
        return *this->actual->siguiente->elemento;
    }

    //Modificar el valor en la posicion "actual"
    void setValor(E elemento)
    {
        if (this->actual->siguiente == NULL)
            cout << "Valor no existe";
        else
            *this->actual->siguiente->elemento = elemento;
    }

    //Mover "actual" a la posicion anterior (izquierda)
    void anterior()
    {
        Nodo<E *> *temp = cabeza;
        Nodo<E *> *tempActual = actual;

        moverAInicio();
        // int i;
        for (int i = 0; tempActual != temp; ++i)
        {
            temp = temp->siguiente;
            if (tempActual != temp)
            {
                siguiente();
            }
        }
    }

    //Retornar la posicion del elemento "actual"
    int posicionActual()
    {
        Nodo<E *> *temp = cabeza;
        int i;
        for (i = 0; actual != temp; ++i)
        {
            temp = temp->siguiente;
        }
        return i;
    }

    //Libera de la memoria y retorna el elemento "actual"
    E eliminar()
    {
        Nodo<E *> *tempActual = actual;
        Nodo<E *> *temp = cabeza;

        moverAInicio();
        // int i;
        for (int i = 0; tempActual != temp; ++i)
        {
            temp = temp->siguiente;
            if (temp == tempActual && temp != cola)
            {
                actual = actual->siguiente->siguiente;
            }
            else
            {
                siguiente();
            }
        }

        return *tempActual->elemento;
    }

    //"Actual" se mueve a la posicion "pos"
    void moverAPosicion(int pos)
    {
    }

    Nodo<E *> *getActualNodo()
    {
        return this->actual;
    }

    Nodo<E *> *getCabezaNodo()
    {
        return this->cabeza;
    }

    Nodo<E *> *getColaNodo()
    {
        return this->cola;
    }

    void reportarConNodos()
    {
        Nodo<int *> *temp = this->getCabezaNodo();
        temp = temp->siguiente;

        while (temp != NULL)
        {
            cout << "[" << *temp->elemento << "]";
            temp = temp->siguiente;
        }

        cout << endl;
    }
};

template <typename Key, typename E>
class Diccionario
{
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

template <typename Key, typename E>
class DiccionarioArreglo : public Diccionario<Key, E>
{
private:
    ListaArreglo<KVPar<Key, E> *> *lista;

public:
    DiccionarioArreglo(int tamanio = 10)
    {
        this->lista = new ListaArreglo<KVPar<Key, E> *>(tamanio);
    }

    ~DiccionarioArreglo()
    {
        delete this->lista;
    }

    void limpiar()
    {
        this->limpiar();
    };

    void insertar(Key k, E e)
    {
        KVPar<Key, E> *temp = new KVPar<Key, E>(k, e);
        this->lista->agregar(temp);
    };

    E remover(Key k)
    {
        E temp = this->encontrar(k);
        if (temp != NULL)
        {
            this->lista->eliminar();
        }

        return temp;
    };

    E removerCualquiera()
    {
        this->lista->moverAlFinal();
        this->lista->anterior();
        KVPar<Key, E> *elem = this->lista->eliminar();
        return elem->valor();
    };

    E encontrar(Key k)
    {
        for (
            this->lista->moverAInicio();
            this->lista->posicionActual() < this->lista->longitud();
            this->lista->siguiente())
        {
            KVPar<Key, E> *temp = this->lista->getValor();
            if (k == temp->key())
                return temp->valor();
        }

        return NULL;
    };

    int longitud()
    {
        return this->lista->longitud();
    };

    void imprimir()
    {
        this->imprimir();
    }
};

// HastTable with separate chaining strategy
template <typename Key, typename E>
class DiccionarioHash : public Diccionario<Key, E>
{
private:

    ListaArreglo<KVPar<int, ListaEnlazada<KVPar<Key, E> *> *> *> *lista;
    int tamanio;
    int cantidad;

    int hash(char *k)
    {

        int sum = 0;
        for (char *it = k; *it; ++it)
        {
            int ascii = *it;
            sum += ascii;
        }
        return sum % this->tamanio;
    }

    ListaEnlazada<KVPar<Key, E> *> *encontrarInterno(Key k)
    {
        int hash = this->hash(k);
        for (
            this->lista->moverAInicio();
            this->lista->posicionActual() < this->lista->longitud();
            this->lista->siguiente())
        {
            KVPar<int, ListaEnlazada<KVPar<Key, E> *> *> *temp = this->lista->getValor();
            if (temp != nullptr && hash == temp->key())
            {
                return temp->valor();
            }
        }

        return NULL;
    }

public:
    DiccionarioHash(int tamanio)
    {
        this->tamanio = tamanio;
        this->lista = new ListaArreglo<KVPar<int, ListaEnlazada<KVPar<Key, E> *> *> *>(tamanio);
        this->cantidad = 0;
    }

    ~DiccionarioHash()
    {
        delete this->lista;
    }

    void limpiar()
    {
        this->lista->limpiar();
    };

    void insertar(Key k, E e)
    {
        int hash = this->hash(k);
        ListaEnlazada<KVPar<Key, E> *> *temp = this->encontrarInterno(k);

        KVPar<Key, E> *kv = new KVPar<Key, E>(k, e);
        if (temp == NULL)
        {
            ListaEnlazada<KVPar<Key, E> *> *l = new ListaEnlazada<KVPar<Key, E> *>();
            l->insertar(kv);
            this->lista->insertar(new KVPar<int, ListaEnlazada<KVPar<Key, E> *> *> (hash, l));
        } else{
            temp->insertar(kv);
        }
    };

    E remover(Key k)
    {
        ListaEnlazada<KVPar<Key, E> *> *temp = this->encontrarInterno(k);
        for (
            temp->moverAInicio();
            temp->posicionActual() < temp->longitud();
            temp->siguiente())
        {
            KVPar<Key, E> *val = temp->getValor();
            if (val->key() == k)
            {
                return val->valor();
            }
        }
    };

    E removerCualquiera()
    {
        this->lista->moverAlFinal();
        this->lista->anterior();

        KVPar<int, ListaEnlazada<KVPar<Key, E> *> *> *temp = this->lista->getValor();
        ListaEnlazada<KVPar<Key, E> *> *templist = temp->valor();
        templist->moverAlFinal();
        templist->anterior();
        KVPar<Key, E> * elem = templist->eliminar();
        elem->valor();
    };

    E encontrar(Key k)
    {
        ListaEnlazada<KVPar<Key, E> *> *templist = this->encontrarInterno(k);
        if (templist != NULL)
        {
            for (
                templist->moverAInicio();
                templist->posicionActual() < templist->longitud();
                templist->siguiente())
            {
                KVPar<Key, E> *val = templist->getValor();
                if (val->key() == k)
                {
                    return val->valor();
                }
            }
        }

        return NULL;
    };

    int longitud()
    {
        return this->lista->longitud();
    };

    void imprimir()
    {
        this->lista->imprimir();
    }
};

class pln
{
private:
    ListaEnlazada<string> *listaCorpus;
    DiccionarioArreglo<string, int *> *bagOfWords;
    DiccionarioHash<char *, string> *hashtable;

    void agregarWord(string word)
    {
        // TODO: validar que no es stopword
        int *frecuencia = this->bagOfWords->encontrar(word);
        if (frecuencia != NULL)
        {
            (*frecuencia)++;
        }
        else
        {
            this->bagOfWords->insertar(word, new int(0));
        }
    }

    void actualizarBagOfWords(string corpus)
    {
        char ch = ' ';
        size_t pos = corpus.find(ch);
        size_t initialPos = 0;

        // Decompose statement
        while (pos != std::string::npos)
        {
            this->agregarWord(corpus.substr(initialPos, pos - initialPos));
            initialPos = pos + 1;
            pos = corpus.find(ch, initialPos);
        }

        // Add the last one
        this->agregarWord(corpus.substr(initialPos, min(pos, corpus.size()) - initialPos + 1));
    }

    char *vectorizar(string corpus)
    {
        char ch = ' ';
        size_t pos = corpus.find(ch);
        size_t initialPos = 0;

        string token;
        char *vector = new char[this->bagOfWords->longitud()];
        int idx = 0;

        // Decompose statement
        while (pos != std::string::npos)
        {
            token = corpus.substr(initialPos, pos - initialPos);
            int *fecuencia = this->bagOfWords->encontrar(token);
            vector[idx] = fecuencia == NULL ? '0' : '1';

            initialPos = pos + 1;
            pos = corpus.find(ch, initialPos);
        }

        // Add the last one
        token = corpus.substr(initialPos, min(pos, corpus.size()) - initialPos + 1);
        int *fecuencia = this->bagOfWords->encontrar(token);
        vector[idx] = fecuencia == NULL ? '0' : '1';

        return vector;
    }

    // int distanciaMinkouski(char *query, char *vector)
    // {
    //     int d = 0;
    //     for (int i = 0; i < strlen(query); i++)
    //     {
    //         if (query[i] != vector[i])
    //             d++;
    //     }
    //     return d;
    // }

public:
    pln()
    {
        this->listaCorpus = new ListaEnlazada<string>();
        this->bagOfWords = new DiccionarioArreglo<string, int *>(1000);
    }

    ~pln()
    {
    }

    void limpiar()
    {
        this->bagOfWords->limpiar();
        this->hashtable->limpiar();
    }

    void cargarCorpus()
    {
        ifstream sw("corpus.txt");

        string txt;
        while (sw.good())
        {
            getline(sw, txt);
            this->listaCorpus->insertar(txt);
            // TODO: limpiar corpus de signos de puntacion
            // TODO: transformar en minúsculas
            string corpus = txt;
            this->actualizarBagOfWords(corpus);
        }
        sw.close();

        this->hashtable = new DiccionarioHash<char *, string>(this->bagOfWords->longitud());

        for (
            this->listaCorpus->moverAInicio();
            this->listaCorpus->posicionActual() < this->listaCorpus->longitud();
            this->listaCorpus->siguiente())
        {
            // TODO: limpiar corpus de signos de puntacion
            // TODO: transformar en minúsculas
            string corpus = this->listaCorpus->getValor();
            char *vector = this->vectorizar(corpus);
            this->hashtable->insertar(vector, corpus);
            // this->actualizarHashtable(vector, corpus);
        }
    }

    void rangeQuery(string query, int sensibilidad)
    {
        // ListaEnlazada<string> *textosConSimilitud = new ListaEnlazada<string>();
        // char *queryVectorizado = this->bagOfWords(query);

        // for (this->vectores->moverAInicio();
        //      this->vectores->posicionActual() < this->vectores->longitud();
        //      this->vectores->siguiente())
        // {
        //     char *vectorCorpus = this->vectores->getValor();
        //     int d = this->distanciaMinkouski(queryVectorizado, vectorCorpus);
        //     if (d == sensibilidad)
        //     {
        //         textosConSimilitud->agregar(this->corpusVectorizado->encontrar(vectorCorpus));
        //     }
        // }

        // corpusVectorizado->imprimir();
    }
};

int main()
{
    // EspaciosMetricos *espacioMetrico = new EspaciosMetricos();
    // espacioMetrico->insertarCorpus("oferta celular hoy");
    // espacioMetrico->insertarCorpus("matricula semestre");
    // espacioMetrico->insertarCorpus("oferta viaje");
    // espacioMetrico->insertarCorpus("tarea semestre");

    // espacioMetrico->vectorizarCorpus();

    // espacioMetrico->rangeQuery("oferta matricula", 2);

    return 0;
}
