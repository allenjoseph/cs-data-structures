#include <iostream>
#include <vector>
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
    ListaArreglo(int tamMax = 1000)
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
        for (int i = 0; this->tamLista; i++)
            if (this->arreglo[i] >= elemento)
            {
                this->moverAPosicion(i);
                this->insertar(elemento);
                break;
            }
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

    //Retornar el numero de registros dentro del diccionario
    virtual int longitud() = 0;
};

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

template <typename Key, typename E>
class DiccionarioArreglo : public Diccionario<Key, E>
{
private:
    ListaArreglo<KVPar<Key, E> > *lista;

public:
    DiccionarioArreglo()
    {
        this->lista = new ListaArreglo<KVPar<Key, E> >();
    }

    ~DiccionarioArreglo()
    {
        delete[] this->lista;
    }

    //Reinicializacion de un diccionario
    void limpiar()
    {
        delete[] this->lista;
        this->lista = new ListaArreglo<KVPar<Key, E> >();
    };

    //Insertar un registro
    //k: la clave para el reigstro
    //e: el registro
    void insertar(Key K, E e)
    {
        this->lista->agregar(*new KVPar<Key, E>(K, e));
    };

    //Remover y retornar un registro
    //k: la clave del registro que debe ser removido
    //Retornar: un registro. Si hay mas de un registro con la misma clave,
    //  se debe remover uno de manera arbitraria
    //Retornar NULL si la clave "K" no se encuentra en el diccionario
    E remover(Key K)
    {
        return "";
    };

    //Remover y retornar un registro arbitrario del diccionario
    //Retornar: el registro que ha sido removido o NULL si no existe
    E removerCualquiera()
    {
        this->lista->moverAlFinal();
        return (this->lista->eliminar()).valor();
    };

    //Return: un registro o NULL si no existe
    //Si hay multiples registros, se debe retornar uno de manera aleatoria
    //K: la clave del registro a encontrar
    E encontrar(Key K)
    {
        this->lista->moverAInicio();
        for (int i = 0; i < this->lista->longitud(); i++)
        {
            if ((this->lista->getValor()).key() == K)
            {
                return (this->lista->getValor()).valor();
            }
            this->lista->siguiente();
        }
        return "";
    };

    //Retornar el numero de registros dentro del diccionario
    int longitud()
    {
        int length = this->lista->longitud();
        return length;
    };
};

/**
 * Jack y Jill han decidido vender algunos de sus discos compactos,
 * mientras todavía tienen algún valor. Han decidido vender uno de
 * cada uno de los títulos de CD que ambos poseen. ¿Cuántos CD pueden
 * vender Jack y Jill? Ni Jack ni Jill poseen más de una copia de cada CD.
 * 
 * Input Format
 * 3 3
 * 1
 * 2
 * 3
 * 1
 * 2
 * 4
 * 0 0
 * 
 * Constraints
 * Entrada: La entrada consta de una secuencia de casos de prueba. La
 * primera línea de cada caso de prueba contiene dos números enteros no
 * negativos N y M, cada uno como máximo un millón, especificando el
 * número de CD que son propiedad de Jack y Jill, respectivamente. A
 * esta línea le siguen N líneas que enumeran los números de catálogo
 * de los CD propiedad de Jack en orden creciente, y M líneas más enumeran
 * los números de catálogo de los CD propiedad de Jill en orden creciente.
 * Cada número de catálogo es un número entero positivo no mayor de mil
 * millones. La entrada termina con una línea que contiene dos ceros.
 * Esta última línea no es un caso de prueba y no debe procesarse.
 * 
 * Salida: Para cada caso de prueba, genere una línea que contenga
 * un número entero con la cantidad de CD que poseen en común Jack y Jill.
 * 
 * Output Format
 * 2
 **/

string delimeter = " ";
int sizeDelimeter = static_cast<int>(delimeter.size());

vector<int> splitTestCases(string stringToSplit)
{
    vector<int> testCase;
    string stringInputTest;
    int intInputTest;

    int startIndex = 0;
    int endIndex = 0;

    while ((endIndex = stringToSplit.find(delimeter, startIndex)) < stringToSplit.size())
    {
        stringInputTest = stringToSplit.substr(startIndex, endIndex - startIndex);
        intInputTest = atoi(stringInputTest.c_str());
        if (intInputTest < 0 || intInputTest >= 1000000)
        {
            return testCase;
        }
        testCase.push_back(intInputTest);
        startIndex = endIndex + sizeDelimeter;
    }

    if (startIndex < stringToSplit.size())
    {
        stringInputTest = stringToSplit.substr(startIndex);
        intInputTest = atoi(stringInputTest.c_str());
        if (intInputTest < 0 || intInputTest >= 1000000)
        {
            return testCase;
        }
        testCase.push_back(intInputTest);
    }

    return testCase;
}

int main()
{
    vector<int> testCase;
    string stringToBeSplitted;
    int cds;
    int cdsInCommon = 0;

    DiccionarioArreglo<int, string> *cdsJack;
    DiccionarioArreglo<int, string> *cdsJill;

    while (true)
    {
        // Input test cases
        getline(cin >> ws, stringToBeSplitted);
        testCase = splitTestCases(stringToBeSplitted);
        if (testCase.size() < 2)
        {
            cout << "Invalid amount of tests" << endl;
            return 0;
        }

        if (testCase.at(0) == 0 && testCase.at(1) == 0)
        {
            cout << cdsInCommon << endl;
            break;
        }

        cdsJack = new DiccionarioArreglo<int, string>;
        for (int j = 0; j < testCase.at(0); j++)
        {
            cin >> cds;
            cdsJack->insertar(cds, "jack");
        }

        cdsJill = new DiccionarioArreglo<int, string>;
        for (int k = 0; k < testCase.at(1); k++)
        {
            cin >> cds;
            cdsJill->insertar(cds, "jill");

            string cdOwner = cdsJack->encontrar(cds);
            if (cdOwner == "jack")
            {
                cdsInCommon++;
            };
        }
    }

    return 0;
}
