#include <iostream>
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

    void insertarsinrepeticion(E elemento)
    {
        int control=0;
        for (int oo = this->tamLista; oo > this->actual; oo--)
        {
            if(this->arreglo[oo]==elemento) control++;

        }
        if(control==0)
        {
            // cout << "insertarsinrepeticion: " << elemento <<endl;
            agregar(elemento);
        }
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

void splitString(ListaArreglo<string> *listaStrings, string stringToSplit, string delimeter)
{
    int sizeDelimeter = static_cast<int>(delimeter.size());
    string stringInputTest;

    int startIndex = 0;
    int endIndex = 0;

    while ((endIndex = stringToSplit.find(delimeter, startIndex)) < stringToSplit.size())
    {
        stringInputTest = stringToSplit.substr(startIndex, endIndex - startIndex);
        listaStrings->agregar(stringInputTest);
        startIndex = endIndex + sizeDelimeter;
    }

    if (startIndex < stringToSplit.size())
    {
        stringInputTest = stringToSplit.substr(startIndex);
        listaStrings->agregar(stringInputTest);
    }
}

int main()
{
    int columnas = 0;
    int instancias = 0;
    int dirichlet = 0;

    cin >> columnas;
    cin >> instancias;
    cin >> dirichlet;

    string columnasToBeSplitted;
    // cin >> columnasToBeSplitted;
    getline(cin >> ws, columnasToBeSplitted);

    ListaArreglo<string> *listaColumnas = new ListaArreglo<string>();
    splitString(listaColumnas, columnasToBeSplitted, ",");

    ListaArreglo<DiccionarioArreglo<string, string> *> *listaInstancias =  new ListaArreglo<DiccionarioArreglo<string, string> *>();

    string instanciaValues;
    for (int instanciaIndex = 0; instanciaIndex < instancias; instanciaIndex++)
    {
        // cin >> instanciaValues;
        getline(cin >> ws, instanciaValues);

        ListaArreglo<string> *listaInstanciaValues = new ListaArreglo<string>();
        splitString(listaInstanciaValues, instanciaValues, ",");

        DiccionarioArreglo<string, string> *diccionarioInstancia = new DiccionarioArreglo<string, string>;
        int columnaIndex = 0;
        for (columnaIndex = 0; columnaIndex < columnas; columnaIndex++)
        {
            diccionarioInstancia->insertar(listaColumnas->getValor(), listaInstanciaValues->getValor());
            listaColumnas->siguiente();
            listaInstanciaValues->siguiente();
        }
        
        listaInstancias->agregar(diccionarioInstancia);
        listaColumnas->moverAInicio();
    }

    string estimar;
    getline(cin >> ws, estimar);
    // cin >> estimar;
    ListaArreglo<string> *listaValoresAEstimar = new ListaArreglo<string>();
    splitString(listaValoresAEstimar, estimar, ",");
    int valoresAEstimar = listaValoresAEstimar->longitud();
    ListaArreglo<string>* counterValoresAEstimar = new ListaArreglo<string>[valoresAEstimar];

    for (int hh = 0; hh < valoresAEstimar; hh++)
    {
        counterValoresAEstimar[hh] = *(new ListaArreglo<string>());
    }

    int counterM = 0;
    int counterCard = 0;

    for (int ii = 0; ii < instancias; ii++)
    {
        int valoresAEstimarEncontrados = 0;
        for (int kkk = 0; kkk < valoresAEstimar; kkk++)
        {
            string columnKeyValue = listaValoresAEstimar->getValor(); //Ej: outlook=rainy
            int columnKeyValueLength = columnKeyValue.size();
            int indiceDelimitador = columnKeyValue.find("=", 0);
            string columnKey = columnKeyValue.substr(0, indiceDelimitador);
            string columnValue = columnKeyValue.substr(indiceDelimitador + 1, columnKeyValueLength - indiceDelimitador);

            string columnValueEncontrado = listaInstancias->getValor()->encontrar(columnKey);

            // cout << "insertar: " << columnValueEncontrado <<endl;
            (&counterValoresAEstimar[kkk])->insertarsinrepeticion(columnValueEncontrado);

            if (columnValueEncontrado == columnValue)
            {
                valoresAEstimarEncontrados++;
            }

            listaValoresAEstimar->siguiente();
        }
        if (valoresAEstimarEncontrados == valoresAEstimar)
        {
            counterM++;
        }

        listaValoresAEstimar->moverAInicio();
        listaInstancias->siguiente();
    }

    double productoCards = 1;
    for (int kk = 0; kk < valoresAEstimar; kk++)
    {
        productoCards = productoCards * ((&counterValoresAEstimar[kk])->longitud() - 1);
    }

    // cout << "counterM: " << counterM <<" productoCards:"<<productoCards<<endl;

    double resultado = (counterM + dirichlet) / (instancias + (dirichlet * productoCards));

    string estimarStr = "";
    for (int zz = 0; zz < columnas; zz++)
    {
        for (int zzz = 0; zzz < valoresAEstimar; zzz++)
        {
            string kv = listaValoresAEstimar->getValor(); //Ej: outlook=rainy
            int kvLength = kv.size();
            int id = kv.find("=", 0);
            string ck = kv.substr(0, id);
            string cv = kv.substr(id + 1, kvLength - id);

            if(ck == listaColumnas->getValor())
            {
                estimarStr = estimarStr + kv + ",";
            }
            listaValoresAEstimar->siguiente();
        }
        listaValoresAEstimar->moverAInicio();
        listaColumnas->siguiente();
    }

    int end = estimarStr.length() - 1;

    cout << "P(" << estimarStr.substr(0, end) << ")=" <<fixed<<setprecision(6)<< resultado << endl;

    return 0;
}
