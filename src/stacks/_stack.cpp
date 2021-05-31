#include <iostream>
using namespace std;
//Clase Padre: Pila
template <typename E>
class Pila
{
public:
    Pila() {}
    ~Pila() {}
    virtual void limpiar() = 0;
    virtual void push(E var) = 0;
    virtual E pop() = 0;
    virtual E valorTop() = 0;
    virtual int longitud() = 0;
};

//Clase hija: Pila Arreglo: Arreglo Pila (APila)
template <typename E>
class APila : public Pila<E>
{
private:
    E *arregloLista;
    int tamMaximo;
    int cima; //top
public:
    APila(int tam = 100)
    {
        this->tamMaximo = tam;
        this->cima = 0;
        this->arregloLista = new E[this->tamMaximo];
    }

    ~APila()
    {
        delete[] this->arregloLista;
    }

    //En tiempo O(1): borrado lógico
    void limpiar()
    {
        this->cima = 0;
    }

    //En tiempo O(1)
    void push(E elemento)
    {
        this->arregloLista[this->cima++] = elemento;
    }

    //En tiempo O(1): retorna el valor top y SI lo borra de la pila
    E pop()
    {
        return this->arregloLista[--this->cima];
    }

    //En tiempo O(1): retorna el valor top pero NO lo borra de la pila
    E valorTop()
    {
        return this->arregloLista[this->cima - 1];
    }

    //En tiempo O(1)
    int longitud()
    {
        return this->cima;
    }

    bool vacio()
    {
        return (this->cima == 0);
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

template <typename E>
class LPila : public Pila<E>
{
private:
    Nodo<E> *cima; //Puntero al ultimo elemento: Top
    int tam;       //Numero de elementos en la Pila
public:
    /*
     * Constructor
     */
    LPila()
    {
        this->cima = NULL;
        this->tam = 0;
    }

    /*
     * Destructor
     */
    ~LPila()
    {
        limpiar();
    }

    /*
     * Elimina los nodos enlazados dentro de la pila
     * O(n) en tiempo
     * */
    void limpiar()
    {
        while (this->tam != 0)
        {
            Nodo<E> *toDelete = this->cima;
            cima = cima->siguiente;
            delete toDelete;
            this->tam--;
        }
    }

    /**
     * Permite agregar "var" a la pila.
     * Debe almacenarse en la cima
     * O(1) en tiempo
     * */
    void push(E var)
    {
        Nodo<E> *nuevo = new Nodo<E>(var, cima);
        this->cima = nuevo;
        this->tam++;
    }

    /**
     * Retornar y eliminar el elemento
     * que se encuentra en la cima de la Pila
     * O(1) en tiempo
     * */
    E pop()
    {
        E elemento = this->cima->elemento;
        if (this->tam == 0)
        {
            return 0;
        }

        Nodo<E> *toDelete = this->cima;
        cima = cima->siguiente;
        delete toDelete;
        this->tam--;
        return elemento;
    }

    /*
     * Retornar el elemento que
     * se encuentra en la cima de la Pila
     * O(1) en tiempo
     * */
    E valorTop()
    {
        return this->cima->elemento;
    }

    /*
     * Retorna la cantidad de elementos guardados en la pila
     * O(1) en tiempo
     */
    int longitud()
    {
        return this->tam;
    }
};

int main()
{
    LPila<int> *pila = new LPila<int>();
    pila->push(10);
    pila->push(20);
    pila->push(30);
    pila->push(40);
    /*
     * Debe reportarse en pantalla:
     * 40
     * 30
     * 20
     * 10
     */
    while (pila->longitud() > 0)
    {
        cout << "Valor top: " << pila->valorTop() << endl;
        cout << "Metodo pop: " << pila->pop() << endl;
    }

    cout << "Eliminando toda la pila: " << endl;
    pila->limpiar();
    cout << "tam lista: " << pila->longitud() << endl;

    delete pila;
    return 0;
}