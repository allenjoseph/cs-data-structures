#include <iostream>
using namespace std;

template <typename E>
class Lista
{
private:
    void operator=(const Lista &) {} //Asignación
    Lista(const Lista &) {}          // Copia de constructor
public:
    Lista() {}          //Constructor por defecto
    virtual ~Lista() {} //destructor base

    //Limpiar contenidos desde la lista, para hacerla vacía
    virtual void limpiar() = 0;

    //Insertar un elemento al final de la lista
    //item: el elemento a ser insertado
    virtual void insertar(E item) = 0;

    //Agregar un elemento al final de la lista
    //item: el elemento a ser agregado
    virtual void agregar(E item) = 0;

    //Eliminar y retornar el elemento actual
    //retornar: el elemento que fue eliminado
    virtual E eliminar() = 0;

    // Modificar la posici'on actual al inicio de la lista
    virtual void moverAInicio() = 0;

    //Modificar la posición al final de la lista
    virtual void moverAlFinal() = 0;

    //Mover la posición actual un paso a la izquierda.
    //No cambia si ya est'a al inicio
    virtual void anterior() = 0;

    //Mover la posición actual un paso a la derecha.
    //No cambia si ya está al final
    virtual void siguiente() = 0;

    //Retornar: el número de elementos en la lista
    virtual int longitud() = 0;

    //Retornar: la posición del elemento actual
    virtual int posicionActual() = 0;

    //Modificar la posición actual
    //pos: la posición para hacer actual
    virtual void moverAPosicion(int pos) = 0;

    //Retornar: el elemento actual
    virtual E getValor() = 0;
    virtual int get_tamMax() = 0;
};

//ArrayList
template <typename E>
class ListaArreglo : public Lista<E>
{
private:
    int tamMax;   //tamaño predeterminado
    int tamLista; //nro elementos ingresados hasta ahora
    int actual;   //índice actual (equivalente al puntero actual en la lista enlazada)
    //Arreglo de elementos
    E *arreglo;

public:
    //Constructor
    ListaArreglo(int tamMax = 100)
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

    void moverAInicio()
    {
        this->actual = 0;
    }

    void moverAlFinal()
    {
        this->actual = this->tamLista;
    }

    void siguiente()
    {
        //if( this->actual<this->tamLista )
        this->actual++;
    }

    void anterior()
    {
        if (this->actual > 0)
        {
            this->actual--;
        }
    }

    void agregar(E elemento)
    {
        this->arreglo[this->tamLista++] = elemento;
    }

    void insertar(E elemento)
    {
        for (int i = tamLista; i > actual; i--)
        {
            this->arreglo[i] = this->arreglo[i - 1];
        }
        this->arreglo[actual] = elemento;
        this->tamLista++;
    }

    void limpiar()
    {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    E eliminar()
    {
        if (this->tamLista <= 0)
        {
            return nullptr;
        }

        E temp = this->arreglo[actual];
        if (!temp) {
            return nullptr;
        }

        for (int i = actual; i < this->tamLista - 1; i++)
        {
            this->arreglo[i] = this->arreglo[i + 1];
        }
        this->tamLista--;
        this->arreglo[actual] = 0;
        return temp;
    }

    int longitud()
    {
        return this->tamMax;
    }

    int posicionActual()
    {
        return this->actual;
    }

    void moverAPosicion(int pos)
    {
        if (pos >= 0 && pos < this->tamLista)
        {
            this->actual = pos;
        }
    }

    E getValor()
    {
        return this->arreglo[this->actual];
    }

    int get_tamMax()
    {
        return this->tamMax;
    }

    void imprimirArreglo()
    {
        this->moverAInicio();
        for (this->moverAInicio(); this->posicionActual() < longitud(); this->siguiente())
        {
            cout << "Elemento [" << this->posicionActual() << "] = " << this->getValor() << endl;
        }
    };
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
    ListaArreglo<Key *> *lista;

public:
    SetBasico(int tamanio = 100)
    {
        this->lista = new ListaArreglo<Key *>(tamanio);
    }

    ~SetBasico()
    {
        delete lista;
    }

    void limpiar()
    {
        this->lista->limpiar();
    }

    void insertar(Key k)
    {
        int pos = this->encontrar(k);
        if (pos == -1)
        {
            this->lista->agregar(new Key(k));
        }
    }

    void remover(Key k)
    {
        int pos = this->encontrar(k);
        if (pos > -1)
        {
            this->lista->moverAPosicion(pos);
            this->lista->eliminar();
        }
    }

    Key removerCualquiera()
    {
        this->lista->moverAlFinal();
        this->lista->anterior();
        return *this->lista->eliminar();
    }

    int encontrar(Key k)
    {
        this->lista->moverAInicio();
        for (
            this->lista->moverAInicio();
            this->lista->posicionActual() < this->lista->longitud();
            this->lista->siguiente())
        {
            if (this->lista->getValor() != nullptr && *this->lista->getValor() == k)
            {
                return this->lista->posicionActual();
            }
        }
        return -1;
    }

    int longitud()
    {
        return this->lista->longitud();
    }

    void imprimirArreglo()
    {
        this->lista->imprimirArreglo();
    }
};

int main()
{
    int tamMax = 10;
    SetBasico<int> *conjunto = new SetBasico<int>(tamMax);
    conjunto->insertar(10);
    conjunto->insertar(10);
    conjunto->insertar(10);
    conjunto->insertar(12);
    conjunto->insertar(15);
    conjunto->insertar(18);
    conjunto->insertar(18);
    conjunto->insertar(22);
    conjunto->imprimirArreglo();
    cout << "- - - - - - - - - - -" << endl;
    cout << "remover el elemento[4]: 22" << endl;
    conjunto->remover(22);
    conjunto->imprimirArreglo();
    cout << "- - - - - - - - - - -" << endl;
    cout << "removerCualquiera:" << endl;
    /*Debe reportar: 
      18
      15
      12
      10
    */
    int i = 0, valor;
    while (i < conjunto->longitud())
    {
        valor = conjunto->removerCualquiera();
        cout << valor << endl;
        i++;
    }
    return 0;
}
