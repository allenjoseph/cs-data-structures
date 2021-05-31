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

/**
 * En este problema, consideramos expresiones que contienen corchetes
 * que están correctamente anidados. Estas expresiones se obtienen por
 * yuxtaposición de expresiones correctamente enredadas en un par de
 * corchetes coincidentes, la izquierda una apertura y la derecha un
 * corchete de cierre.
 * (a+(b=)(a)) está correctamente alineado
 * (a+)b=)(a() no lo está.
 * En este problema tenemos varios pares de corchetes, por lo que tenemos
 * que imponer una segunda condición a la expresión: los corchetes
 * coincidentes deben ser del mismo tipo. En consecuencia, "(())" está
 * bien, pero "([))" no. Los pares de paréntesis son:
 * ( ) [ ] { } < > (* *)
 * Los dos caracteres '(*' deben interpretarse como un símbolo, no como un
 * corchete de apertura '(' seguido inmediatamente por un asterisco, y de
 * manera similar para '*)'. La combinación '()' debe interpretarse como
 * '( 'seguido por ')'.
 * Escriba un programa que compruebe si las expresiones están correctamente
 * anidadas. Si la expresión no está correctamente anidada, su programa debe
 * determinar la posición del corchete infractor, que es la longitud del
 * prefijo más corto de la expresión que no se puede extender a una expresión
 * correctamente anidada. No olvide que "(" cuenta como uno, al igual que ")".
 * Los caracteres que no son paréntesis también cuentan como uno.
 * 
 * Input Format:
 * (a++()
 * (a{+})
 * 
 * Constraints:
 * Entrada: La entrada es un archivo de texto. Cada línea contiene una expresión
 * que se debe verificar seguida de un marcador de fin de línea. Ninguna línea
 * contiene más de 3000 caracteres. La entrada termina con un marcador estándar
 * de fin de archivo.
 * Salida: La salida es un archivo de texto. Cada línea contiene el resultado de
 * la comprobación de la línea de entrada correspondiente, es decir, 'SÍ' (en
 * mayúsculas), si la expresión es correcta y (si no es correcta) 'NO' seguido de
 * un espacio y la posición del error.
 * 
 * Output Format
 * NO 6
 * YES
**/

int main()
{
    LPila<char> *pila = new LPila<char>();
    string line;

    char currChar = 0;
    char lastChar = 0;
    char nextChar = 0;

    //cout << "Enter your line to evalute: ";
    getline(cin >> ws, line);

    int length = line.length();
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
                cout << "NO " << i << endl;
                break;
            }
        }
        else if (currChar == '{')
        {
            lastChar = currChar;
            pila->push(currChar);
        }
        else if (currChar == '}')
        {
            if (pila->valorTop() == '{')
                pila->pop();
            else
            {
                cout << "NO " << i << endl;
                break;
            }
        }
        else if (currChar == '<')
        {
            lastChar = currChar;
            pila->push(currChar);
        }
        else if (currChar == '>')
        {
            if (pila->valorTop() == '<')
                pila->pop();
            else
            {
                cout << "NO " << i << endl;
                break;
            }
        }
        else if (currChar == '(' && nextChar == '*')
        {
            lastChar = nextChar;
            pila->push(nextChar);
        }
        else if (currChar == '*' && nextChar == ')')
        {
            if (pila->valorTop() == '*')
            {
                pila->pop();
                i++;
            }
            else
            {
                cout << "NO " << i << endl;
                break;
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
                cout << "NO " << i << endl;
                break;
            }
        }

        if (i == length - 1)
        {
            if (pila->longitud() > 0)
                cout << "NO " << line.length() << endl;
            else
                cout << "SI" << endl;
        }
    }

    return 0;
}