#include <iostream>
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

//Clase hija: Pila Arreglo: Arreglo Pila (APila)
template <typename E>
class APila : public Pila<E>
{
private:
  E *arregloLista;
  int tamMaximo;
  int cima; //top
public:
  APila(int tam = 100)
  {
    this->tamMaximo = tam;
    this->cima = 0;
    this->arregloLista = new E[this->tamMaximo];
  }

  ~APila()
  {
    delete[] this->arregloLista;
  }

  //En tiempo O(1): borrado lógico
  void limpiar()
  {
    this->cima = 0;
  }

  //En tiempo O(1)
  void push(E elemento)
  {
    this->arregloLista[this->cima++] = elemento;
  }

  //En tiempo O(1): retorna el valor top y SI lo borra de la pila
  E pop()
  {
    return this->arregloLista[--this->cima];
  }

  //En tiempo O(1): retorna el valor top pero NO lo borra de la pila
  E valorTop()
  {
    return this->arregloLista[this->cima - 1];
  }

  //En tiempo O(1)
  int longitud()
  {
    return this->cima;
  }

  bool vacio()
  {
    return (this->cima == 0);
  }
};

int main()
{
  int target[1000];

  int n;
  cin >> n;

  string result = "";
  while (n)
  {
    while (1)
    {
      cin >> target[1];

      if (target[1] == 0)
        break;

      for (int i = 2; i <= n; i++)
      {
        cin >> target[i];
      }

      APila<int> *s = new APila<int>();
      bool flag = true;
      int A = 1, B = 1;
      while (B <= n)
      {
        if (A == target[B])
        {
          A++;
          B++;
        }
        else if (!s->vacio() && s->valorTop() == target[B])
        {
          s->pop();
          B++;
        }
        else if (A <= n)
        {
          s->push(A++);
        }
        else
        {
          flag = false;
          break;
        }
      }

      result += (flag ? "SI\n" : "NO\n");
    }
  }

  cout << result << endl;

  return 0;
}