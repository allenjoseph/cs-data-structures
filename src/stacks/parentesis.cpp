
#include <cmath>
#include <cstdio>
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
            return 0;
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
        if (this->cima == NULL)
            return 0;
        else
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

// Se le proporciona una cadena que consta de paréntesis () y [].
// Se dice que una cadena de este tipo es correcta:
// (a) si es la cadena vacía
// (b) si A y B son correctos, AB es correcto,
// (c) si A es correcto, (A) y [A] es correcto.
// Escriba un programa que tome una secuencia de cadenas de este tipo
// y verifique su corrección. Su programa puede asumir que la longitud
// máxima de la cadena es 128.
// Input Format
// 3
// ([])
// (([()])))
// ([()])()
// Constraints
// Entrada: El archivo contiene un número entero positivo n y una secuencia
// de n cadenas de paréntesis "()" y "[]", una cadena por línea.
// Salida: Una secuencia de "Yes" o "No" en el archivo de salida.
// Output Format
// Yes
// No
// Yes

string evaluateSequence(string line)
{
    LPila<char> *pila = new LPila<char>();
    char currChar = 0;
    char lastChar = 0;
    char nextChar = 0;
    int length = line.length();

    if (length == 0)
    {
        return "Yes";
    }

    for (int i = 0; i < length; i++)
    {
        currChar = line[i];

        if (i < length - 1)
        {
            nextChar = line[i + 1];
        }

        if (currChar == '[')
        {
            lastChar = currChar;
            pila->push(currChar);
        }
        else if (currChar == ']')
        {
            if (pila->valorTop() == '[')
                pila->pop();
            else
            {
                return "No";
            }
        }
        else if (currChar == '(')
        {
            lastChar = currChar;
            pila->push(currChar);
        }
        else if (currChar == ')')
        {
            if (pila->valorTop() == '(')
                pila->pop();
            else
            {
                return "No";
            }
        }
        if (i == length - 1 && pila->longitud() > 0)
        {
            return "No";
        }
    }
    return "Yes";
}

int main()
{
    int cases = 0;
    cin >> cases;

    string sequence;
    string sequenceFormated;
    string testCases[100];

    int caseIndex = 0;
    while (caseIndex < cases)
    {
        getline(cin >> ws, sequence);
        sequenceFormated = sequence.substr(0, 128);
        testCases[caseIndex] = sequenceFormated;
        caseIndex++;
    }

    for (int k = 0; k < cases; k++)
    {
        cout << evaluateSequence(testCases[k]) << endl;
    }

    return 0;
}