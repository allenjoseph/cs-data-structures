#include <iostream>
using namespace std;

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

//clase abstracta cola
template <typename E>
class Cola
{
private:
    void operator=(const Cola &) {} //Proteccion asignada
    Cola(const Cola &) {}           //Constructor Proteccion copia
public:
    Cola() {}          //por defecto
    virtual ~Cola() {} //Base destructor

    //Reinicializar la cola. El usuario es responsable
    //por reclamar el espacio utilizado por el elemento
    //de la cola
    virtual void clear() = 0;

    //colocar un elemento en la parte de atras de la cola
    //it: el elemento siendo encolado
    virtual void encolar(E) = 0;

    //Remover y retornar elementos al frente de la cola
    //Retornar: El elemento en el frente de la cola.
    virtual E desencolar() = 0;

    //Retornar: Una copia de el elemento frontal
    virtual E valorFrontal() = 0;

    //Retornar: El numero de elementos in la cola .
    virtual int longitud() = 0;
};

template <typename E>
class ACola : public Cola<E>
{
private:
    int tamañoMax;   //Tamaño maximo de la cola
    int frente;      //Indice del elemento frontal
    int elemFin;     //Indice del elemento final
    E *listaArreglo; //Arreglo conteniendo los elementos de la cola

public:
    ACola(int tam = 100)
    {
        this->tamañoMax = tam;
        this->frente = 1;
        this->elemFin = 0;
        this->listaArreglo = new E[this->tamañoMax + 1];
    }

    void clear()
    {
        this->frente = 1;
        this->elemFin = 0;
    }

    void encolar(E elem)
    {
        cout << "encolar: " << elem << endl;

        if (this->longitud() == this->tamañoMax)
        {
            cout << "sin espacio!" << endl;
            return;
        }

        int pos = this->longitud() + 1;
        this->listaArreglo[pos] = elem;
        this->elemFin = pos;

        cout << "frente: " << this->frente << endl;
        cout << "ultimo: " << this->elemFin << endl;
        cout << "longitud: " << this->longitud() << endl;
    }

    E desencolar()
    {
        E elemento = this->valorFrontal();

        if (this->frente == this->tamañoMax)
        {
            this->clear();
        }
        else
        {
            this->frente++;
        }

        return elemento;
    }

    E valorFrontal()
    {
        return this->listaArreglo[this->frente];
    }

    int longitud()
    {
        if (this->frente == 1 && this->elemFin == this->tamañoMax)
        {
            return this->tamañoMax;
        }

        return (this->tamañoMax - this->frente + this->elemFin + 1) % this->tamañoMax;
    }
};

/**
 * Cuando un estudiante está demasiado cansado, no puede evitar dormir en clase,
 * incluso si su maestro favorito está justo frente a él. Imagina que tienes una
 * clase de estudiantes extraordinariamente cansados, ¿cuánto tiempo tienes que
 * esperar antes de que todos los estudiantes te escuchen y no duerman más? Para
 * completar esta tarea, debe comprender cómo se comportan los estudiantes. Cuando
 * un alumno se despierta, lucha durante unos minutos para escuchar al maestro
 * (después de todo, es una lástima dormir todo el tiempo). Después de eso, cuenta
 * el número de estudiantes despiertos y dormidos (incluido él mismo). Si hay
 * estrictamente más estudiantes durmiendo que estudiantes despiertos, duerme durante
 * b minutos. De lo contrario, lucha por unos minutos más, porque sabía que cuando
 * hay muy pocos estudiantes durmiendo, ¡hay una gran posibilidad de que sean
 * castigados! Tenga en cuenta que un estudiante cuenta el número de estudiantes que
 * duermen solo cuando quiere volver a dormir. Ahora que comprende, cada estudiante
 * podría describirse con dos números enteros a y b, la duración del período de
 * despertar y dormir. Si siempre hay más estudiantes durmiendo, estos dos períodos
 * continúan una y otra vez. Combinamos un período de despertar con un período de sueño
 * posterior, y llamamos al período combinado un período de despertar-dormir. Por
 * ejemplo, un estudiante con a = 1 y b = 4 tiene un período de despertar-dormir de
 * despertar-dormir-dormir-dormir-dormir. En este problema, necesitamos otro parámetro
 * c (1 <= c <= a + b) para describir la condición inicial de un estudiante: la posición
 * inicial en su período de despertar-dormir. La primera y segunda posición del período
 * discutido anteriormente son despertar y dormir, respectivamente. Ahora usamos un
 * triple (a, b, c) para describir a un estudiante. Supongamos que hay tres estudiantes
 * (2, 4, 1), (1, 5, 2) y (1, 4, 3), todos los estudiantes se despertarán en el momento 18.
 * 
 * Escribe un programa para calcular la primera vez que todos los estudiantes no duermen.
 *
 * Input Format:
 * 3
 * 2 4 1 // despertar,despertar,dormir,dormir,dormir,dormir
 * 1 5 2 // despertar,dormir,dormir,dormir,dormir,dormir
 * 1 4 3 // despertar,dormir,dormir,dormir,dormir
 * 3
 * 1 2 1
 * 1 2 2
 * 1 2 3
 * 0
 * 
 * Constraints:
 * Entrada: La entrada consta de varios casos de prueba. La primera línea de cada
 * caso contiene un solo entero n (1 <= n <= 10), el número de estudiantes. A esto
 * le siguen n líneas, cada una de las cuales describe a un estudiante. Cada una de
 * estas líneas contiene tres números enteros a, b, c (1 <= a, b <= 5), descritos
 * anteriormente. El último caso de prueba va seguido de un solo cero, que no debe
 * procesarse.
 * Salida: Para cada caso de prueba, imprima el número de caso y la primera vez que
 * todos los estudiantes se despierten. Si nunca sucederá, envíe "-1".
 * 
 * Output Format:
 * Caso 1: 18
 * Caso 2: -1
 **/

int main()
{
    return 0;
}
