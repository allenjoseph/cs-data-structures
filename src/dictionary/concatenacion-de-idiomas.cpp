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
        return NULL;
    };

    //Retornar el numero de registros dentro del diccionario
    int longitud()
    {
        int length = this->lista->longitud();
        return length;
    };
};

/**
 * Un idioma es un conjunto de cadenas. Y la concatenación de dos idiomas es el conjunto
 * de todas las cadenas que se forman al concatenar las cadenas del segundo idioma al
 * final de las cadenas del primer idioma. Por ejemplo, si tenemos dos idiomas A y B
 * tales que: A={cat, dog, mouse} B={rat, bat} La concatenación de A y B seria: C =
 * {catrat, catbat, dograt, dogbat, mouserat, mousebat} Dados dos idiomas, su tarea es
 * solo contar el numero de cadenas en la concatenación de los dos idiomas.
 * 
 * Input Format:
 * 2
 * 3 2
 * Cat
 * Dog
 * Mouse
 * Rat
 * Bat
 * 1 1
 * Abc
 * Cab
 * 
 * Constraints:
 * Entrada: Puede haber varios casos de prueba. La primera linea del archivo de entrada
 * contiene el numero de casos de prueba, T (1 <= T <= 25). Luego siguen los casos de prueba T.
 * La primera linea de cada caso de prueba contiene dos números enteros, M y N (M; N <1500),
 * el numero de cadenas en cada uno de los idiomas. Luego, las siguientes M lineas contienen
 * las cadenas del primer idioma. Las siguientes N lineas le dan las cadenas del segundo
 * idioma. Puede asumir que las cadenas están formadas por letras minusculas (de la 'a' a la 'z')
 * únicamente, que tienen menos de 10 caracteres y que cada cadena se presenta en una linea sin
 * espacios iniciales o finales. Es posible que las cadenas en los idiomas de entrada no estén
 * ordenadas y no habrá cadenas duplicadas.
 * 
 * Salida: Para cada uno de los casos de prueba, debe imprimir una linea de salida. La salida
 * para cada caso de prueba comienza con el numero de serie del caso de prueba, seguido del numero
 * de cadenas en la concatenación del segundo idioma después del primer idioma.
 * 
 * Output Format:
 * Case 1: 6
 * Case 2: 1
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
        if (intInputTest < 1 || intInputTest >= 1500)
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
        if (intInputTest < 1 || intInputTest >= 1500)
        {
            return testCase;
        }
        testCase.push_back(intInputTest);
    }

    return testCase;
}

int main()
{

    int cases = 0;
    cin >> cases;

    // El numero de casos de prueba, T (1 <= T <= 25)
    if (cases < 0 || cases > 25)
    {
        cout << "Invalid number of cases" << endl;
        return 0;
    }

    vector<int> testCase;
    string stringToBeSplitted;
    string word;

    DiccionarioArreglo<int, string> *diccionario1;
    DiccionarioArreglo<int, string> *diccionario2;
    DiccionarioArreglo<int, string> *language;

    DiccionarioArreglo<int, string> *languages[cases];

    int caseIndex = 0;
    while (caseIndex < cases)
    {

        // Input test cases
        getline(cin >> ws, stringToBeSplitted);
        testCase = splitTestCases(stringToBeSplitted);
        if (testCase.size() < 2)
        {
            cout << "Invalid amount of tests" << endl;
            return 0;
        }

        diccionario1 = new DiccionarioArreglo<int, string>;
        for (int j = 0; j < testCase.at(0); j++)
        {
            getline(cin >> ws, word);
            diccionario1->insertar(j, word);
        }

        diccionario2 = new DiccionarioArreglo<int, string>;
        for (int k = 0; k < testCase.at(1); k++)
        {
            getline(cin >> ws, word);
            diccionario2->insertar(k, word);
        }

        int correlative = 0;
        language = new DiccionarioArreglo<int, string>;

        for (int l = 0; l < diccionario2->longitud(); l++)
        {
            string word1 = diccionario2->encontrar(l);
            // cout << "word1 " << word1 << endl;

            for (int m = 0; m < diccionario1->longitud(); m++)
            {
                string word2 = diccionario1->encontrar(m);
                // cout << "word2 " << word2 << endl;
                language->insertar(correlative++, (word1 + word2));
            }
        }

        // cout << "language: " << language << endl;
        languages[caseIndex] = language;
        caseIndex++;
    }

    for (int x = 0; x < cases; x++)
    {
        cout << "Case " << (x + 1) << ": " << languages[x]->longitud() << endl;
    }

    return 0;
}
