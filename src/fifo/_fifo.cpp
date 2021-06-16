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


template <typename E> class LCola : public Cola<E> {
private:
    Nodo<E>* base;
    Nodo<E>* cima;
    int tam;  //Tamanio de la cola
public:

    /*
     * Constructor
     */
    LCola(){
        this->base = NULL;
        this->cima = NULL;
        this->tam = 0;
    }

    /*
     * Destructor
     */
    ~LCola(){
        clear();
    }

    void clear(){
        while (this->base!=NULL){
            Nodo<E> *toDelete = this->base;
            this->base = this->base->siguiente;
            delete toDelete;
        }
        this->tam=0;
    }

    void encolar(E val){

        Nodo<E> *aux = new Nodo<E>(val,NULL);

        if(this->tam==0)
        {
            this->base = aux;
        }else
        {
            this->cima->siguiente = aux;
        }
        this->cima=aux;
        this->tam++;
    }

    E desencolar(){
        E elemento = this->base->elemento;
        if(this->tam==0){
            return NULL;
        }
        Nodo<E> *toDelete = this->base;
        this->base=this->base->siguiente;
        delete toDelete;
        this->tam--;
        return elemento;
    }

    E valorFrontal(){
        return this->base->elemento;
    }

    int longitud(){
        return this->tam;
    }
};

int main()
{
    ACola<int> *cola = new ACola<int>(3);
    cola->encolar(10);
    cola->encolar(20);
    cola->encolar(30);
    cola->encolar(100);

    cout << "numero de elementos: " << cola->longitud() << endl;
    cout << "desencolar: " << cola->desencolar() << endl;

    // FIXME: corregir el encolamiento luego de haber desencolado 1 elemento
    cola->encolar(100);

    cout << "desencolar: " << cola->desencolar() << endl;

    delete cola;

    LCola<int> *Colatest = new LCola<int>();

    Colatest->encolar(10);
    Colatest->encolar(20);
    Colatest->encolar(30);
    Colatest->encolar(40);

    while(Colatest->longitud()>0){
        cout<<Colatest->desencolar()<<endl;
    }
    delete Colatest;

    return 0;
}
