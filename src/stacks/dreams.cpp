#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
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
        if (this->tam == 0)
        {
            return "";
        }

        E elemento = this->cima->elemento;
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

/**
 * Dom Cobb y su compañero Arthur realizan actividades ilegales al entrar
 * en las mentes subconscientes de sus objetivos. Utilizan el sueño de dos
 * niveles dentro de una estrategia de sueños para extraer información
 * valiosa. Los soñadores se despiertan por un impacto repentino (una “patada”)
 * o pueden morir en el sueño. Ahora Dom quiere tu ayuda. Porque tiene una
 * tarea compleja. Tiene que atravesar los sueños de muchas personas. Viaja
 * del sueño de una persona al sueño de otra. Está demasiado consumido que ya
 * no puede seguir si está despierto o en el sueño de otra persona.
 * Te dará n consultas para procesar, cada una de las consultas estará en una
 * de las siguientes formas:
 * 
 * "SleepX": esto significa que la persona llamada X estará durmiendo y Dom
 * entrará en el sueño de X, del sueño de la persona anterior (si lo hay).
 * 
 * "Kick": esto significa que la persona actual en cuyo sueño ha entrado Dom,
 * se despertará y Dom volverá al sueño de la persona anterior de donde vino
 * a este sueño. Si Dom ya no está en el sueño de nadie, ignora esta consulta.
 * 
 * "Test": esto significa que Dom quiere saber en qué sueño se encuentra en
 * este momento. Tienes que escribir el nombre de la persona. Si Dom no está
 * en el sueño de nadie en este momento, debe imprimir "Not in a dream"
 * (sin las comillas).
 * 
 * Input Format:
 * 20
 * Sleep Dom
 * Sleep Sakin
 * Test
 * Sleep Asif
 * Sleep Mushfiq
 * Test
 * Kick
 * Test
 * Sleep Shafi
 * Test
 * Kick
 * Test
 * Kick
 * Test
 * Kick
 * Test
 * Kick
 * Test
 * Kick
 * Test
 * 
 * Constraints:
 * Utilizar pilas para resolver el problema
 * La primera línea contendrá un número entero n (1 <= n <= 10000), el número
 * de consultas. Cada una de las siguientes n líneas contendrá una de las tres
 * consultas mencionadas anteriormente. Para el caso de la consulta "SleepX",
 * X será una cadena compuesta solo por letras mayúsculas o minúsculas y no
 * tendrá más de 15 caracteres.
 * Para cada una de las consultas "test", escriba el nombre de la persona en
 * cuyo sueño Dom se encuentra en este momento exactamente como apareció en la
 * entrada. Si Dom no está en el sueño de nadie, escriba la línea "Not in a
 * dream". Verifique la entrada y salida de muestra para obtener más detalles.
 * 
 * Output Format
 * Sakin
 * Mushfiq
 * Asif
 * Shafi
 * Asif
 * Sakin
 * Dom
 * Not in a dream
 * Not in a dream
**/

int main()
{
    int queries;
    int maxQueries = 10000;
    cout << "Enter number of queries: ";
    cin >> queries;
    if (queries < 1 || queries > maxQueries)
        cout << "It is a invalid number of queries!" << endl;

    LPila<string> *pila = new LPila<string>();

    string query;
    string command;
    string dreamer;
    int counter = 0;
    while (counter < queries)
    {

        cout << "Enter your query: ";
        getline(cin >> ws, query);

        command = query.substr(0, 4);

        if (command == "Slee")
        {
            dreamer = query.substr(6, 21);
            pila->push(dreamer);
        }
        else if (command == "Kick")
        {
            pila->pop();
        }
        else if (command == "Test")
        {
            if (pila->longitud() == 0)
            {
                cout << "Not in a dream" << endl;
            }
            else
            {
                cout << pila->valorTop() << endl;
            }
            if (counter < queries)
            {
                cout << endl;
            }
        }
        counter++;
    }

    return 0;
}