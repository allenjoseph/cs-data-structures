#include <iostream>

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
        this->arreglo[this->tamLista++] = elemento;
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
        if (pos >= 0)
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
        //for (int i = this->tamLista; i > this->actual; i--)
        //    this->arreglo[i] = this->arreglo[i - 1];
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
 
template<typename E>
class ArbolBinario{
private:
public:
  ArbolBinario(){}
  ~ArbolBinario(){}
  virtual void insertar(E e) = 0;
  virtual E encontrar(E e) = 0;
  virtual int longitud()=0;
};

template<typename E>
class ArbolBinarioArreglo : ArbolBinario<E>{
private:
  ListaArreglo<E> *arreglo;
  int tamMax; //el tamanho maximo fijo del arreglo
  int tamLista;//elementos que realmente estan dentro del arbol binario

public:
  ArbolBinarioArreglo(int tamMax = 1000){
    this->tamMax = tamMax;
    this->arreglo = new ListaArreglo<E>(tamMax);
    this->tamLista = 0;
    this->arreglo->moverAInicio();
  }

  int obtenerPosicion(E e, int pos) {
  
    std::cout << "valora a insertar: " << e << std::endl;
    this->arreglo->moverAPosicion(pos);

    int valor = this->arreglo->getValor();
    std::cout << "pos: " << pos << " valor : " << valor << std::endl;
    if (valor == 0) {
      return pos;
    }

    if (e < valor) {
      std::cout << "izquierda: " << std::endl;
      return this->obtenerPosicion(e, (2 * pos) + 1);
    } else {
      std::cout << "derecha: " << std::endl;
      return this->obtenerPosicion(e, (2 * pos) + 2);
    }
  }

  void insertar(E e) {
    if (this->longitud() == 0) {
     this->arreglo->agregar(e);
     //this->tamLista++;
     return;
    }

    int pos = this->obtenerPosicion(e, 0);
    this->arreglo->moverAPosicion(pos);
    this->arreglo->insertar(e);
    //this->tamLista++;
  };

  E encontrar(E e) {

  };

  //Retorna el numero de registros en el arbol binario
  int longitud() {
    return this->arreglo->longitud();
  };

  void imprimirArreglo() {
    this->arreglo->moverAInicio();
    for (int i = 0; i < 15; i++)
    {
      std::cout << "Elemento [" << i << "] = " << this->arreglo->getValor() << std::endl;
      this->arreglo->siguiente();
    }
  }
};

int main() {
  ArbolBinarioArreglo<int> *arbol = new ArbolBinarioArreglo<int>;

  // 13, 7, 15, 20, 22, 9, 6, 14, 19
  arbol->insertar(13);
  arbol->insertar(7);
  arbol->insertar(15);
  arbol->insertar(20);
  arbol->insertar(22);
  arbol->insertar(9);
  arbol->insertar(6);
  arbol->insertar(14);
  arbol->insertar(19);

  arbol->imprimirArreglo();
  
  return 0;
}