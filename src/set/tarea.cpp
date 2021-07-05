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
    //Arreglo de elementos
    E *arreglo;
    //Tamanho fijo
    int tamMax;
    //Tamanho de la lista
    int tamLista;
    //Indice "actual"
    int actual;

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
        this->arreglo[this->tamLista] = elemento;
        this->tamLista++;
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
        if (pos >= 0 && pos <= this->tamLista)
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
        {
            this->arreglo[i] = this->arreglo[i + 1];
        }
        this->tamLista--;
        return eliminado;
    }
};

//Clase Abstracta: Set
template <typename Key>
class Set
{
public:
    //Constructor
    Set() {}

    //Base destructor
    ~Set() {}

    //Permite reinicializar la estructura de datos
    virtual void limpiar() = 0;

    //La inserción del valor k
    virtual void insertar(Key k) = 0;

    //Dada una clave, el registro correspondiente debe ser removido
    virtual void remover(Key k) = 0;

    //Retorna y remueve un registro arbitrario del set
    virtual Key removerCualquiera() = 0;

    //Retorna una posición del registro que se asocie con k
    virtual int encontrar(Key k) = 0;

    //Retornar el número de registros o claves existentes en el set
    virtual int longitud() = 0;
};

//SetBasico
template <typename Key>
class SetBasico : public Set<Key>
{
private:
    ListaArreglo<Key> *list;

public:
    SetBasico(int tamanho = 100)
    {
        this->list = new ListaArreglo<Key>(tamanho);
    }

    ~SetBasico()
    {
        delete list;
    }

    void limpiar()
    {
        this->list->limpiar();
    }

    void insertar(Key k)
    { // O(N) / O(2N)
        int count = 0;
        this->list->moverAInicio();
        for (int i = 0; i < list->longitud(); i++)
        {
            if (list->getValor() == k)
            {
                count++;
            }
            this->list->siguiente();
        }

        if (count == 0)
        {
            this->list->insertar(k);
        }
    }

    void remover(Key k)
    { // O(2N)
        list->moverAInicio();
        while (list->getValor() != k && list->posicionActual() != list->longitud())
        {
            list->siguiente();
        }

        if (list->getValor() == k)
        {
            list->eliminar();
        }
    }

    Key removerCualquiera()
    { // O(2N)
        list->moverAPosicion(list->longitud() - 1);
        return this->list->eliminar();
    }

    int encontrar(Key k)
    { // O(N)
        list->moverAInicio();
        while (list->posicionActual() != list->longitud() - 1)
        {
            if (list->getValor() == k)
            {
                break;
            }
            list->siguiente();
        }

        if (list->getValor() == k)
        {
            return list->posicionActual();
        }
        else
        {
            return -1;
        }
    }

    //costo O(1)
    int longitud()
    {
        return list->longitud();
    }

    void imprimir()
    {
        list->moverAInicio();
        for (int i = 0; i < list->longitud(); i++)
        {
            cout << list->getValor() << endl;
            list->siguiente();
        }
    }
};

int main()
{
    int tamMax = 100;
    SetBasico<int> *setbasico = new SetBasico<int>(tamMax);
    setbasico->insertar(10);
    setbasico->insertar(10);
    setbasico->insertar(10);
    setbasico->insertar(12);
    setbasico->insertar(15);
    setbasico->insertar(18);
    setbasico->insertar(18);

    // setbasico->imprimir();
    cout << "18 se encuentra en la posicion: " << setbasico->encontrar(18) << endl;
    cout << "longitud del set: " << setbasico->longitud() << endl;
    setbasico->remover(12);

    int longitud = setbasico->longitud();
    int i = 0, valor;

    while (i < longitud)
    {
        valor = setbasico->removerCualquiera();
        cout << valor << endl;
        i++;
    }
    /*
    Reporta: 
      18
      15
      12
      10
    */

    return 0;
}
