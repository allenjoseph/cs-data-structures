
#include <iostream>
#include <cmath>
#include <iomanip>
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
    ListaArreglo(int tamMax = 100)
    {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
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

    //Agregar un elemento a la lista (al final)
    void agregarOrdenadamente(E elemento)
    {
        if (this->tamLista == 0)
        {
            this->agregar(elemento);
            return;
        }

        for (int i = 0; i < this->tamLista; i++)
        {
            if (this->arreglo[i] >= elemento)
            {
                this->moverAPosicion(i);
                this->insertar(elemento);
                return;
            }
        }

        this->agregar(elemento);
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
};

int main()
{
    int numElements;

    cout << "Enter the number of elements: ";
    cin >> numElements;

    ListaArreglo<int> *listElements = new ListaArreglo<int>(numElements);

    int element;
    for (int i = 0; i < numElements; i++)
    {
        cout << "Enter element " << i + 1 << ": ";
        cin >> element;

        listElements->agregarOrdenadamente(element);
    }

    cout << "Enter element to search: ";
    cin >> element;

    while (listElements->longitud() > 1)
    {
        int centerPos = (listElements->longitud() / 2) - 1;
        listElements->moverAPosicion(centerPos);
        int centerElement = listElements->getValor();

        if (element == centerElement)
        {
            cout << "Element found!" << endl;
            return 0;
        }

        if (element > centerElement)
        {
            for (int i = 0; i <= centerPos; i++)
            {
                listElements->moverAInicio();
                listElements->eliminar();
            }
            continue;
        }

        for (int i = 0; i <= centerPos; i++)
        {
            listElements->moverAPosicion(centerPos + i);
            listElements->eliminar();
        }
    }

    cout << "Element is not found!" << endl;
    return 0;
}