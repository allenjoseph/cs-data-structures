#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <cmath>

using namespace std;
using timer = std::chrono::system_clock;
timer::time_point clock_start;
timer::time_point clock_stop;
std::chrono::duration<float> elapsed_time;

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

    void imprimir()
    {
        Nodo<E *> *temp = this->getCabezaNodo();
        temp = temp->siguiente;

        while (temp != NULL)
        {
            cout << *temp->elemento << endl;
            temp = temp->siguiente;
            cout << endl;
        }
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

//clase abstracta cola
template <typename E>
class Cola
{
private:
    void operator=(const Cola &) {} //Proteccion asignada
    Cola(const Cola &) {}           //Constructor Proteccion copia
public:
    Cola() {}          //por defecto
    virtual ~Cola() {} //Base destructor

    //Reinicializar la cola. El usuario es responsable
    //por reclamar el espacio utilizado por el elemento
    //de la cola
    virtual void clear() = 0;

    //colocar un elemento en la parte de atras de la cola
    //it: el elemento siendo encolado
    virtual void encolar(E) = 0;

    //Remover y retornar elementos al frente de la cola
    //Retornar: El elemento en el frente de la cola.
    virtual E desencolar() = 0;

    //Retornar: Una copia de el elemento frontal
    virtual E valorFrontal() = 0;

    //Retornar: El numero de elementos in la cola .
    virtual int longitud() = 0;
};

template <typename E>
class LCola : public Cola<E>
{
private:
    Nodo<E> *base;
    Nodo<E> *cima;
    int tam; //Tamanio de la cola
public:
    LCola()
    {
        this->base = NULL;
        this->cima = NULL;
        this->tam = 0;
    }

    ~LCola()
    {
        clear();
    }

    void clear()
    {
        while (this->base != NULL)
        {
            Nodo<E> *tmp = this->base;
            this->base = this->base->siguiente;
            delete tmp;
        }
        this->tam = 0;
    }

    void encolar(E val)
    {
        Nodo<E> *tmp = new Nodo<E>(val, NULL);
        if (this->tam == 0)
            this->base = tmp;
        else
            this->cima->siguiente = tmp;

        this->cima = tmp;
        this->tam++;
    }

    E desencolar()
    {
        E elemento = this->base->elemento;
        if (this->tam == 0)
            return NULL;

        Nodo<E> *tmp = this->base;
        this->base = this->base->siguiente;
        delete tmp;

        this->tam--;
        return elemento;
    }

    E valorFrontal()
    {
        return this->base->elemento;
    }

    int longitud()
    {
        return this->tam;
    }
};

template <typename Key, typename E>
class DiccionarioTablasHash : public Diccionario<Key, E>
{
private:
    using KVParTHValue = KVPar<int, E>;
    ListaArreglo<KVParTHValue *> *lista;
    int tamanio;
    int cantidad;

    int hash(Key k)
    {
        int sum = 0;
        int idx = 0;
        for_each(k.begin(), k.end(), [&](char ch)
                 {
                     int ascii = ch;
                     //  sum += ascii;
                     sum += ascii * (10 ^ idx);
                     idx++;
                 });
        return sum % this->tamanio;
    }

    E encontrarInterno(Key k)
    {
        int hash = this->hash(k);
        for (
            this->lista->moverAInicio();
            this->lista->posicionActual() < this->lista->longitud();
            this->lista->siguiente())
        {
            KVParTHValue *temp = this->lista->getValor();
            if (temp != nullptr && hash == temp->key())
            {
                return temp->valor();
            }
        }

        return NULL;
    }

public:
    DiccionarioTablasHash(int tamanio)
    {
        this->tamanio = tamanio;
        this->lista = new ListaArreglo<KVParTHValue *>(tamanio);
        this->cantidad = 0;
    }

    ~DiccionarioTablasHash()
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
        E temp = this->encontrarInterno(k);

        if (temp == NULL)
        {
            this->lista->insertar(new KVParTHValue(hash, e));
        }
        else
        {
            temp->insertar(e->getValor());
        }
    };

    E remover(Key k)
    {
        int hash = this->hash(k);
        E temp = this->encontrarInterno(k);

        if (temp != NULL)
        {
            for (
                this->lista->moverAInicio();
                this->lista->posicionActual() < this->lista->longitud();
                this->lista->siguiente())
            {
                if (this->lista->getValor()->key() == hash)
                {
                    this->lista->eliminar();
                    break;
                }
            }
        }
        return temp;
    };

    E removerCualquiera()
    {
        this->lista->moverAlFinal();
        this->lista->anterior();

        KVParTHValue *temp = this->lista->getValor();
        this->lista->eliminar();
        return temp->valor();
    };

    E encontrar(Key k)
    {
        return this->encontrarInterno(k);
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

//Nodo Arbol
template <typename E>
class NodoArbol
{
private:
    E e;
    NodoArbol *izq;
    NodoArbol *der;
    NodoArbol *pad;

public:
    int altura = 0;

    NodoArbol()
    {
        this->izq = this->der = NULL;
    }

    NodoArbol(E eval, NodoArbol *ival = NULL, NodoArbol *dval = NULL)
    {
        this->e = eval;
        this->izq = ival;
        this->der = dval;
        this->pad = NULL;
    }

    ~NodoArbol() {}

    E valor()
    {
        return e;
    };

    void setValor(E eval)
    {
        this->e = eval;
    };

    NodoArbol *izquierda()
    {
        return this->izq;
    };

    void setIzquierda(NodoArbol *ival)
    {
        this->izq = ival;
    };

    NodoArbol *derecha()
    {
        return this->der;
    };

    void setDerecha(NodoArbol *dval)
    {
        this->der = dval;
    };

    NodoArbol *padre()
    {
        return this->pad;
    };

    void setPadre(NodoArbol *pval)
    {
        this->pad = pval;
    };

    bool esHoja()
    {
        return this->izq == NULL && this->der == NULL;
    };
};

template <typename E>
class ArbolBalanceado
{
private:
    using KVParAB = KVPar<int, ListaEnlazada<E> *>;
    NodoArbol<KVParAB *> *raiz;
    int tam;

    int hash(string k)
    {
        int sum = 0;
        int idx = 0;
        for_each(k.begin(), k.end(), [&](char ch)
                 {
                     int ascii = ch;
                     //  sum += ascii;
                     sum += ascii * (10 ^ idx);
                     idx++;
                 });
        return sum % 300;
    }

public:
    ArbolBalanceado()
    {
        this->raiz = NULL;
        this->tam = 0;
    }

    ~ArbolBalanceado()
    {
        delete raiz;
    }

    void limpiar()
    {
        this->raiz = NULL;
        this->tam = 0;
    }

    void actualizarAlturaNodo(NodoArbol<KVParAB *> *nodo)
    {
        if (nodo->izquierda() != NULL && nodo->derecha() != NULL)
            nodo->altura = 1 + max(nodo->izquierda()->altura, nodo->derecha()->altura);
        else if (nodo->izquierda() != NULL)
            nodo->altura = 1 + nodo->izquierda()->altura;
        else if (nodo->derecha() != NULL)
            nodo->altura = 1 + nodo->derecha()->altura;
        else
            nodo->altura = 0;
    }

    NodoArbol<KVParAB *> *actualizarAlturaArbol(NodoArbol<KVParAB *> *nodo)
    {
        NodoArbol<KVParAB *> *temp = nodo->padre();
        while (temp != NULL)
        {
            this->actualizarAlturaNodo(temp);
            temp = temp->padre();
        }
        return temp;
    }

    int calcularDiferenciaAltura(NodoArbol<KVParAB *> *nodo)
    {
        if (nodo == NULL)
            return 0;
        else if (nodo->esHoja())
            return 0;
        else if (nodo->izquierda() == NULL)
            return (-1 - (nodo->derecha()->altura));
        else if (nodo->derecha() == NULL)
            return (nodo->izquierda()->altura + 1);
        else
            return (nodo->izquierda()->altura - nodo->derecha()->altura);
    }

    NodoArbol<KVParAB *> *rotarDerecha(NodoArbol<KVParAB *> *nodo)
    {
        NodoArbol<KVParAB *> *temp = nodo->izquierda();
        NodoArbol<KVParAB *> *aux = temp->derecha();

        temp->setDerecha(nodo);
        nodo->setIzquierda(aux);

        if (aux != NULL)
            aux->setPadre(nodo);
        nodo->setPadre(temp);

        this->actualizarAlturaNodo(nodo);
        this->actualizarAlturaNodo(temp);

        return temp;
    }

    NodoArbol<KVParAB *> *rotarIzquierda(NodoArbol<KVParAB *> *nodo)
    {
        NodoArbol<KVParAB *> *temp = nodo->derecha();
        NodoArbol<KVParAB *> *aux = temp->izquierda();

        temp->setIzquierda(nodo);
        nodo->setDerecha(aux);
        if (aux != NULL)
            aux->setPadre(nodo);
        nodo->setPadre(temp);

        this->actualizarAlturaNodo(nodo);
        this->actualizarAlturaNodo(temp);

        return temp;
    }

    void balancearArbol(NodoArbol<KVParAB *> *nodo)
    {
        NodoArbol<KVParAB *> *temp, *aux1, *aux2, *aux3, *aux4;
        int diferenciaAltura;

        temp = nodo->padre();

        aux1 = nodo->padre();
        aux2 = nodo;
        aux3 = NULL;

        while (aux1 != NULL)
        {
            diferenciaAltura = this->calcularDiferenciaAltura(aux1);

            // si existe diferencia de alturas realizar las rotaciones
            if ((diferenciaAltura > 1) || (diferenciaAltura < (-1)))
            {
                aux4 = aux1->padre();
                if (aux1->izquierda() == aux2 && aux2->izquierda() == aux3)
                    temp = this->rotarDerecha(aux1);
                else if (aux1->izquierda() == aux2 && aux2->derecha() == aux3)
                {
                    temp = this->rotarIzquierda(aux2);
                    temp->setPadre(aux1);
                    aux1->setIzquierda(temp);

                    temp = rotarDerecha(aux1);
                }
                else if (aux1->derecha() == aux2 && aux2->derecha() == aux3)
                    temp = this->rotarIzquierda(aux1);
                else
                {
                    temp = rotarDerecha(aux2);
                    temp->setPadre(aux1);
                    aux1->setDerecha(temp);

                    temp = this->rotarIzquierda(aux1);
                }
                if (aux4 != NULL)
                {
                    temp->setPadre(aux4);
                    if (aux4->derecha() == aux1)
                        aux4->setDerecha(temp);
                    else
                        aux4->setIzquierda(temp);
                }
                else
                {
                    this->raiz = temp;
                    temp->setPadre(NULL);
                }
                temp = this->actualizarAlturaArbol(temp);
            }
            aux3 = aux2;
            aux2 = aux1;
            aux1 = aux1->padre();
        }
    }

    void agregar(E e)
    {
        int key = this->hash(e->key());
        ListaEnlazada<E> *listaE = new ListaEnlazada<E>();
        listaE->agregar(e);
        KVParAB *nodoValue = new KVParAB(key, listaE);
        NodoArbol<KVParAB *> *nodo = new NodoArbol<KVParAB *>(nodoValue);
        NodoArbol<KVParAB *> *temp = this->raiz;
        this->tam++;

        while (true)
        {
            if (temp == NULL)
            {
                this->raiz = nodo;
                return;
            }
            if (key > temp->valor()->key()) // Si el nodo entrante es >= entonces lo ubicamos a la derecha
            {
                if (temp->derecha() == NULL)
                {
                    nodo->setPadre(temp);
                    temp->setDerecha(nodo);
                    break;
                }
                else
                    temp = temp->derecha();
            }
            else if (key < temp->valor()->key()) // Si el nodo entrante es menor entonces lo ubicamos a la izquierda
            {
                if (temp->izquierda() == NULL)
                {
                    nodo->setPadre(temp);
                    temp->setIzquierda(nodo);
                    break;
                }
                else
                    temp = temp->izquierda();
            } else // Si el nodo entrante ya existe entonces se agregar a la lista
            {
                temp->valor()->valor()->agregar(e);
                this->tam--;
                break;
            }
        }

        // actualizar la altura del arbol
        this->actualizarAlturaArbol(nodo);

        // balancear el arbol
        this->balancearArbol(nodo);
    }

    int numNodos()
    {
        return this->tam;
    }

    int altura() {
        NodoArbol<KVParAB *> * cabeza = this->raiz;
        if (cabeza == NULL)
            return 0;
        return cabeza->altura;
    }

    ListaEnlazada<E> * buscarNodos(string queryVector)
    {
        ListaEnlazada<E> *resultados = new ListaEnlazada<E>();
        if (this->raiz == NULL)
            return resultados;

        int key = this->hash(queryVector);
        // cout << "key a buscar: " << key << endl;

        NodoArbol<KVParAB *> *nodo = this->raiz;
        while (true)
        {
            if (nodo == NULL)
                break;

            // cout << "nodo: [" << nodo->valor()->key() << "] ";
            // if (nodo->izquierda() != NULL) {
            //     cout << "nodo izq: [" << nodo->izquierda()->valor()->key() << "] ";
            // }
            // if (nodo->derecha() != NULL) {
            //     cout << "nodo der: [" << nodo->derecha()->valor()->key() << "]" << endl;
            // }

            if (nodo->valor()->key() == key) {
                resultados = nodo->valor()->valor();
                break;
            }
            else if (nodo->valor()->key() < key)
                nodo = nodo->derecha();
            else
                nodo = nodo->izquierda();
        }
        return resultados;
    }
};

class PLN
{
private:
    ListaEnlazada<string> *listaCorpus;
    ListaEnlazada<string> *listaStopwords;
    ListaEnlazada<string> *listaTokens;
    ListaEnlazada<string> *textosConSimilitud;

    ListaEnlazada<KVPar<string, int *> *> *bagOfWords;
    DiccionarioTablasHash<string, ListaEnlazada<KVPar<string, string> *> *> *tablaHash;
    ArbolBalanceado<KVPar<string, string> *> *arbolBalanceado;

    int pMinkouski = 1;
    bool usarHashTable = false;
    bool usarArbolBalanceado = false;

    void agregarWord(string word)
    {
        if (word[0] == '@')
            return;

        string cleanWord;
        for_each(word.begin(), word.end(), [&](char ch)
                 {
                     if (ch == ' ')
                         cleanWord += ch;
                     else if ((int)ch == -95 || (int)ch == -127) // á y Á
                         cleanWord += 'a';
                     else if ((int)ch == -87 || (int)ch == -119) // é y É
                         cleanWord += 'e';
                     else if ((int)ch == -83 || (int)ch == -115) // í y Í
                         cleanWord += 'i';
                     else if ((int)ch == -77 || (int)ch == -109) // ó y Ó
                         cleanWord += 'o';
                     else if ((int)ch == -70 || (int)ch == -102) // ú y Ú
                         cleanWord += 'u';
                     else if ((int)ch == -79 || (int)ch == -111) // ñ y Ñ
                         cleanWord += 'n';
                     else if (isalnum(ch))
                         cleanWord += tolower(ch);
                 });

        if (cleanWord.empty())
            return;

        for (
            this->listaStopwords->moverAInicio();
            this->listaStopwords->posicionActual() < this->listaStopwords->longitud();
            this->listaStopwords->siguiente())
        {
            string stopword = this->listaStopwords->getValor();
            if (stopword == cleanWord)
                return;
        }

        bool wordExists = false;
        for (
            this->bagOfWords->moverAInicio();
            this->bagOfWords->posicionActual() < this->bagOfWords->longitud();
            this->bagOfWords->siguiente())
        {
            KVPar<string, int *> *wordFrecuencia = this->bagOfWords->getValor();
            if (wordFrecuencia->key() == cleanWord)
            {
                (*wordFrecuencia->valor())++;
                wordExists = true;
                break;
            }
        }

        if (!wordExists)
        {
            KVPar<string, int *> *newword = new KVPar<string, int *>(cleanWord, new int(1));
            this->bagOfWords->insertar(newword);
        }
    }

    void actualizarBagOfWords(string corpus)
    {
        char ch = ' ';
        size_t pos = corpus.find(ch);
        size_t initialPos = 0;
        string word;

        // Decompose statement
        while (pos != std::string::npos)
        {
            word = corpus.substr(initialPos, pos - initialPos);
            this->agregarWord(word);
            initialPos = pos + 1;
            pos = corpus.find(ch, initialPos);
        }

        // Add the last one
        word = corpus.substr(initialPos, min(pos, corpus.size()) - initialPos + 1);
        this->agregarWord(word);
    }

    string vectorizar(string corpus)
    {
        char ch = ' ';
        size_t pos = corpus.find(ch);
        size_t initialPos = 0;

        ListaEnlazada<string> *tokens = new ListaEnlazada<string>();
        string token;
        string vector;
        bool exists;
        string freqword;

        // Decompose statement
        while (pos != std::string::npos)
        {
            token = corpus.substr(initialPos, pos - initialPos);
            tokens->insertar(token);

            initialPos = pos + 1;
            pos = corpus.find(ch, initialPos);
        }

        // Add the last one
        token = corpus.substr(initialPos, min(pos, corpus.size()) - initialPos + 1);
        tokens->insertar(token);

        for (
            this->listaTokens->moverAInicio();
            this->listaTokens->posicionActual() < this->listaTokens->longitud();
            this->listaTokens->siguiente())
        {
            freqword = this->listaTokens->getValor();
            exists = false;
            for (
                tokens->moverAInicio();
                tokens->posicionActual() < tokens->longitud();
                tokens->siguiente())
            {
                if (tokens->getValor() == freqword)
                {
                    exists = true;
                    break;
                }
            }
            vector += exists ? '1' : '0';
        }

        return vector;
    }

    int distanciaMinkouski(string vQuery, string vCorpus)
    {
        int d = 0;
        int idx = 0;
        while (idx < vQuery.size())
        {
            d += pow(abs((int)vQuery.at(idx) - (int)vCorpus.at(idx)), pMinkouski);
            idx++;
        }
        return pow(d, 1 / pMinkouski);
    }

    void readFile(string filename, ListaEnlazada<string> *lista)
    {
        string line;
        ifstream reader(filename);

        if (reader)
            while (!reader.eof())
            {
                getline(reader, line);
                lista->insertar(line);
            }

        if (!reader)
            cout << "No pudimos abrir el archivo " << filename << endl;

        reader.close();
    }

public:
    PLN()
    {
        this->listaCorpus = new ListaEnlazada<string>();
        this->listaStopwords = new ListaEnlazada<string>();
        this->bagOfWords = new ListaEnlazada<KVPar<string, int *> *>();
        this->listaTokens = new ListaEnlazada<string>();
        this->textosConSimilitud = new ListaEnlazada<string>();
    }

    ~PLN()
    {
        delete this->listaCorpus;
        delete this->listaStopwords;
        delete this->listaTokens;
        delete this->bagOfWords;
        delete this->tablaHash;
        delete this->arbolBalanceado;
    }

    void limpiar()
    {
        this->bagOfWords->limpiar();
        this->listaTokens->limpiar();
        this->tablaHash->limpiar();
        this->arbolBalanceado->limpiar();
    }

    void cargarCorpusStopwords()
    {
        cout << "\nCargando archivo de corpus y de stopwords..." << endl;
        this->readFile("corpus.txt", this->listaCorpus);
        this->readFile("stopwords-es.txt", this->listaStopwords);
    }

    void extraerTokens()
    {
        cout << "\nExtrayendo tokens del corpus..." << endl;
        string corpusText;
        for (
            this->listaCorpus->moverAInicio();
            this->listaCorpus->posicionActual() < this->listaCorpus->longitud();
            this->listaCorpus->siguiente())
        {
            corpusText = this->listaCorpus->getValor();
            this->actualizarBagOfWords(corpusText);
        }
        cout << "Tokens extraidos: " << this->bagOfWords->longitud() << endl;
    }

    void filtrarTokensFrecuentes(int frecuencia = 10)
    {
        for (
            this->bagOfWords->moverAInicio();
            this->bagOfWords->posicionActual() < this->bagOfWords->longitud();
            this->bagOfWords->siguiente())
        {
            if (*this->bagOfWords->getValor()->valor() >= frecuencia)
            {
                this->listaTokens->insertar(this->bagOfWords->getValor()->key());
            }
        }
        cout << "Tokens con frecuencia >= " << frecuencia << ": " << this->listaTokens->longitud() << endl;
    }

    void almacenarEnTablasHash()
    {
        this->usarHashTable = true;
        this->usarArbolBalanceado = false;
        cout << "\nAlmacenando en tablas hash..." << endl;
        string corpusText;
        this->tablaHash = new DiccionarioTablasHash<string, ListaEnlazada<KVPar<string, string> *> *>(300);
        for (
            this->listaCorpus->moverAInicio();
            this->listaCorpus->posicionActual() < this->listaCorpus->longitud();
            this->listaCorpus->siguiente())
        {
            corpusText = this->listaCorpus->getValor();
            string vector = this->vectorizar(corpusText);
            KVPar<string, string> *KVVectorCorpus = new KVPar<string, string>(vector, corpusText);

            ListaEnlazada<KVPar<string, string> *> *vectorCorpus = new ListaEnlazada<KVPar<string, string> *>();
            vectorCorpus->insertar(KVVectorCorpus);
            this->tablaHash->insertar(vector, vectorCorpus);
        }
        cout << "Espacios ocupados: " << this->tablaHash->longitud() << endl;
    }

    void almacenarEnArbolBalanceado()
    {
        this->usarHashTable = false;
        this->usarArbolBalanceado = true;
        cout << "\nAlmacenando en arbol balanceado AVL..." << endl;
        string corpusText;
        this->arbolBalanceado = new ArbolBalanceado<KVPar<string, string> *>();
        for (
            this->listaCorpus->moverAInicio();
            this->listaCorpus->posicionActual() < this->listaCorpus->longitud();
            this->listaCorpus->siguiente())
        {
            corpusText = this->listaCorpus->getValor();
            string vector = this->vectorizar(corpusText);
            KVPar<string, string> *KVVectorCorpus = new KVPar<string, string>(vector, corpusText);

            this->arbolBalanceado->agregar(KVVectorCorpus);
        }
        cout << "Cantidad de nodos: " << this->arbolBalanceado->numNodos() << endl;
        cout << "Altura del arbol: " << this->arbolBalanceado->altura() << endl;
    }

    void rangeQuery(string query, int sensibilidad)
    {
        clock_start = timer::now();

        this->textosConSimilitud->limpiar();

        string queryVectorizado = this->vectorizar(query);

        KVPar<string, string> *vectorCorpus;
        ListaEnlazada<KVPar<string, string> *> *listaResultados;
        int distancia;

        if (this->usarHashTable)
        {
            listaResultados = this->tablaHash->encontrar(queryVectorizado);
            for (
                listaResultados->moverAInicio();
                listaResultados->posicionActual() < listaResultados->longitud();
                listaResultados->siguiente())
            {
                vectorCorpus = listaResultados->getValor();
                distancia = this->distanciaMinkouski(queryVectorizado, vectorCorpus->key());
                if (distancia <= sensibilidad)
                {
                    textosConSimilitud->agregar(vectorCorpus->valor());
                }
            }
        } else if (this->usarArbolBalanceado)
        {
            listaResultados = this->arbolBalanceado->buscarNodos(queryVectorizado);
            for (
                listaResultados->moverAInicio();
                listaResultados->posicionActual() < listaResultados->longitud();
                listaResultados->siguiente())
            {
                vectorCorpus = listaResultados->getValor();
                distancia = this->distanciaMinkouski(queryVectorizado, vectorCorpus->key());
                if (distancia <= sensibilidad)
                {
                    textosConSimilitud->agregar(vectorCorpus->valor());
                }
            }
        }

        clock_stop = timer::now();
        elapsed_time = clock_stop - clock_start;

        cout << textosConSimilitud->longitud() << " resultados en ";
        cout << elapsed_time.count() << " segundos.\n"
             << endl;

        textosConSimilitud->imprimir();
    }
};

int main()
{
    PLN *programa = new PLN();

    programa->cargarCorpusStopwords();

    programa->extraerTokens();

    programa->filtrarTokensFrecuentes();

    programa->almacenarEnTablasHash();
    // programa->almacenarEnArbolBalanceado();

    string query;
    int distancia;
    while (true)
    {
        cout << "\nINGRESA UN TEXTO A BUSCAR: ";
        getline(cin, query);

        cout << "RADIO DE BUSQUEDA: ";
        cin >> distancia;

        programa->rangeQuery(query, distancia);

        cin.ignore();
    }

    delete programa;
    return 0;
}
