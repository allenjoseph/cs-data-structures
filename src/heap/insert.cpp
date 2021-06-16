#include <iostream>
using namespace std;

// Clase Padre: Lista
template <typename E>
class Lista
{
private:
public:
  //Constructor
  Lista() {}
  //Destructor
  ~Lista() {}
  //Limpiar lista: dejara la lista vacia
  virtual void limpiar() = 0;
  //Insertar un elemento donde se encuentra el puntero "actual"
  virtual void insertar(E elemento) = 0;
  //Agregar un elemento a la lista (al final)
  virtual void agregar(E elemento) = 0;
  //Libera de la memoria y retorna el elemento eliminado en la posicion actual
  virtual E eliminar() = 0;
  //Mover "actual" al inicio de la lista
  virtual void moverAInicio() = 0;
  //Mover "actual" al final de la lista, primer espacio disponible
  virtual void moverAlFinal() = 0;
  //Mover "actual" a la posicion anterior
  virtual void anterior() = 0;
  //Mover "actual" a la posicion siguiente
  virtual void siguiente() = 0;
  //Retornar el numero de elementos de la lista
  virtual int longitud() = 0;
  //Retorna la posicion del elemento "actual"
  virtual int posicionActual() = 0;
  //"Actual" se mueve a posicion "pos"
  virtual void moverAPosicion(int pos) = 0;
  //Retorna el valor que estaba en la posicion "actual"
  virtual E getValor() = 0;
  //Modificar el valor en la posicion de "actual"
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
  //Indice actual
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

  //Limpiar lista: dejara la lista vacia
  void limpiar()
  {
    delete[] this->arreglo;
    this->actual = this->tamLista = 0;
    this->arreglo = new E[this->tamMax];
  };
  //Insertar un elemento donde se encuentra el puntero "actual"
  void insertar(E elemento)
  {
    if (this->tamLista < this->tamMax)
    {
      int i = this->tamLista;
      while (this->actual < i)
      {
        this->arreglo[i] = this->arreglo[i - 1];
        i--;
      }
      this->arreglo[this->actual] = elemento;
      this->tamLista++;
    }
  };
  //Agregar un elemento a la lista (al final)
  void agregar(E elemento)
  {
    this->arreglo[this->tamLista++] = elemento;
  };
  //Libera de la memoria y retorna el elemento eliminado en la posicion actual
  E eliminar()
  {
    E elemento = this->arreglo[this->actual];
    if (this->tamLista > 0)
    {
      int i = this->actual;
      while (i < this->tamLista - 1)
      {
        this->arreglo[i] = this->arreglo[i + 1];
        i++;
      }
      this->tamLista--;
    }

    return elemento;
  };
  //Mover "actual" al inicio de la lista
  void moverAInicio()
  {
    this->actual = 0;
  };
  //Mover "actual" al final de la lista, primer espacio disponible
  void moverAlFinal()
  {
    this->actual = this->tamLista;
  };
  //Mover "actual" a la posicion anterior
  void anterior()
  {
    if (this->actual > 0)
    {
      this->actual--;
    }
  };
  //Mover "actual" a la posicion siguiente
  void siguiente()
  {
    if (this->actual < this->tamLista)
    {
      this->actual++;
    }
  };
  //Retornar el numero de elementos de la lista
  int longitud()
  {
    return this->tamLista;
  };
  //Retorna la posicion del elemento "actual"
  int posicionActual()
  {
    return this->actual;
  };
  //"Actual" se mueve a posicion "pos"
  void moverAPosicion(int pos)
  {
    if (pos >= 0 && pos < this->tamLista)
    {
      this->actual = pos;
    }
  };
  //Retorna el valor que estaba en la posicion "actual"
  E getValor()
  {
    return this->arreglo[this->actual];
  };
  //Modificar el valor en la posicion de "actual"
  void setValor(E elemento)
  {
    this->arreglo[this->actual] = elemento;
  };

  void incrementarTamLista()
  {
    this->tamLista++;
  }
};

template <typename E>
class ArbolBinario
{
private:
public:
  ArbolBinario() {}
  ~ArbolBinario() {}
  virtual void insertar(E e) = 0;
  virtual E encontrar(E e) = 0;
  virtual int longitud() = 0;
};

template <typename E>
class ArbolBinarioArreglo : ArbolBinario<E>
{
private:
  ListaArreglo<E> *arreglo;
  int tamMax;   //el tamanho maximo fijo del arreglo
  int tamLista; //elementos que realmente estan dentro del arbol binario
public:
  ArbolBinarioArreglo(int tamMax = 100)
  {
    this->tamMax = tamMax;
    this->arreglo = new ListaArreglo<E>(tamMax);
    this->tamLista = 0;
    this->arreglo->moverAInicio();
  }

  ~ArbolBinarioArreglo()
  {
  }

  void insertar(E e)
  {
    int indice = 0;
    while (true)
    {
      this->arreglo->moverAPosicion(indice);
      if (this->arreglo->getValor() == -1)
      {
        this->arreglo->setValor(e);
        this->tamLista++;
        break;
      }
      else if (this->arreglo->getValor() < e)
      {
        indice = (2 * indice + 2);
      }
      else if (this->arreglo->getValor() > e)
      {
        indice = (2 * indice + 1);
      }
      else if (this->arreglo->getValor() == e)
      {
        break;
      }
    }
  }

  void llenarVacios()
  {
    for (int i = 0; i < this->tamMax; i++)
    {
      this->arreglo->insertar(-1);
    }
  }

  void imprimir()
  {
    this->arreglo->moverAInicio();
    for (int i = 0; i < this->tamMax; i++)
    {
      this->arreglo->moverAPosicion(i);
      if (this->arreglo->getValor() > 0)
      {

        cout << "A[" << i << "] : " << this->arreglo->getValor() << endl;
      }
    }
  }

  E encontrar(E e)
  {
    int indice = 0;
    while (true)
    {
      if (this->arreglo->moverAPosicion(indice), this->arreglo->getValor() == -1)
      {
        return -1;
      }
      if (this->arreglo->getValor() == e)
      {
        return this->arreglo->getValor();
      }
      else if (this->arreglo->getValor() < e)
      {
        indice = (2 * indice + 2);
      }
      else if (this->arreglo->getValor() > e)
      {
        indice = (2 * indice + 1);
      }
    }
  }

  int longitud()
  {
    return this->tamLista;
  }

  void moverAPosicion(int pos)
  {
    this->arreglo->moverAPosicion(pos);
  }

  E getValor()
  {
    return this->arreglo->getValor();
  }

  int posicionActual()
  {
    return this->arreglo->posicionActual();
  }
};

// Tu programa debe implementar un arbol binario y debe retornar el hijo izquierdo (si existiese) y derecho (si existiese) de un elemento dado.
// Tu arbol puede tener un tamanio maximo de 100.
// Entrada: un conjunto de elementos enteros que se deben insertar al arbol y un valor buscado. Con -1 se termina la entrada y no debe ser considerado. Salida: el valor del hijo izquierdo (si existiese) y derecho (si existiese) del valor buscado dentro del arbol binario.
// Input Format
// 7
// 13
// 15
// 10
// 6
// 14
// 13
// -1
// Constraints
// Implementar arbol binario
// Output Format
// 10 15

int main()
{
  ArbolBinarioArreglo<int> *arbol = new ArbolBinarioArreglo<int>;
  arbol->llenarVacios();

  int entrada, elemento = -1;
  cin >> entrada;
  while (entrada != -1)
  {
    elemento = entrada;
    arbol->insertar(entrada);
    cin >> entrada;
  }

  if (elemento != -1 && arbol->encontrar(elemento) != -1)
  {
    int pos = arbol->posicionActual();
    int izquierda = pos * 2 + 1;
    int derecha = pos * 2 + 2;
    if (arbol->moverAPosicion(izquierda), arbol->getValor() != -1)
    {
      cout << arbol->getValor() << endl;
    }
    if (arbol->moverAPosicion(derecha), arbol->getValor() != -1)
    {
      cout << arbol->getValor() << endl;
    }
  }

  delete arbol;
  return 0;
}