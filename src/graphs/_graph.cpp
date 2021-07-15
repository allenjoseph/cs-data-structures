#include <iostream>
#include <iomanip>
using namespace std;

class Grafo{
private:
public:
    //Constructor
    Grafo(){}
    //Metodo de inicializacion
    virtual void init(int n) = 0;
    //Retornar el numero de vertices y aristas
    virtual int get_N_Vertices()=0;
    virtual int get_N_Aristas()=0;
    //Retornar el primer vecino
    virtual int primero(int v) = 0;
    //Retornar el siguiente vecino
    virtual int siguiente(int v, int w) = 0;
    //Cambiar el peso de las aristas
    // i, j: los vertices
    // w: peso
    virtual void setArista(int i, int j, int w) = 0;
    //Eliminar arista
    virtual void eliminarArista(int i, int j) = 0;
    //Determinar si una arista esta en el grafo
    //i, j: los vertices
    //retorna: true si la arista existe, y false en caso contrario
    virtual bool esArista(int i, int j) = 0;
    //Retornar el peso de una arista
    virtual int getPeso(int i, int j) = 0;
    //Valores de marca para cada nodo o vertice
    //v: el vertice
    //val: el valor a modificar
    virtual int getMarca(int v) = 0;
    virtual void setMarca(int v, int val) = 0;
};

//Implementacion usando representacion de matriz de adyacencia
class GrafoMA : public Grafo{
private:
    int numeroVertices;
    int numeroAristas;
    int **matriz;
    int *marca;
public:
    //Metodo de inicializacion: inicializar la matriz
    void init(int n) {
        int i,j;
        this->numeroVertices = n;
        this->numeroAristas = 0;
        this->marca = new int[n];
        //Inicializamos el arreglo de marca (visitados)
        for (i = 0; i < this->numeroVertices; i++) {
            this->marca[i] = 0; //NO VISITADO
        }
        //Inicializar la matriz de adyacencia
        this->matriz = new int*[this->numeroVertices];
        for (i = 0; i < this->numeroVertices; i++) {
            this->matriz[i] = new int[this->numeroVertices];
        }
        //Debemos colocar a la matriz con valores CERO
        for (i = 0; i < this->numeroVertices; i++) {
            for (j = 0; j < this->numeroVertices; j++) {
                this->matriz[i][j] = 0; //Peso CERO
            }
        }
    }

    GrafoMA(int numVert){
        this->init(numVert);
    }

    ~GrafoMA(){
        delete[] this->marca;
        delete[] this->matriz;
    }

    //Retornar el numero de vertices y aristas
    int get_N_Vertices(){
        return this->numeroVertices;
    }

    int get_N_Aristas(){
        return this->numeroAristas;
    }

    //Retornar el primer vecino de v
    int primero(int v) {
        for (int i = 0; i < this->numeroVertices; ++i) {
            if(this->matriz[v][i]!=0){
                return i;
            }
        }
        return this->numeroVertices;
    }

    //Retornar el siguiente vecino
    int siguiente(int v, int w) {
        for (int i = w+1; i < this->numeroVertices; ++i) {
            if(this->matriz[v][i]!=0){
                return i;
            }
        }
        return this->numeroVertices;
    }

    //Cambiar el peso de las aristas
    // i, j: los vertices
    // w: peso
    void setArista(int i, int j, int w) {
        this->matriz[i][j] = w;
        this->numeroAristas++;
    }

    //Eliminar arista
    void eliminarArista(int i, int j) {
        this->matriz[i][j] = 0;
        this->numeroAristas--;
    }

    //Determinar si una arista esta en el grafo
    //i, j: los vertices
    //retorna: true si la arista existe, y false en caso contrario
    bool esArista(int i, int j) {
        return this->matriz[i][j] != 0;
    }

    //Retornar el peso de una arista
    int getPeso(int i, int j) {
        return this->matriz[i][j];
    }

    //Valores de marca para cada nodo o vertice
    //v: el vertice
    //val: el valor a modificar
    int getMarca(int v) {
        return this->marca[v];
    }

    void setMarca(int v, int val) {
        this->marca[v] = val;
    }
};

void testGrafo() {
    GrafoMA *grafo = new GrafoMA(4);
    grafo->setArista(0,1, 1);
    grafo->setArista(1,2, 1);
    grafo->setArista(1,3, 1);
    grafo->setArista(2,3, 1);

    int peru = 1;
    int vecino = grafo->primero(peru);
    cout<<"Vecino: "<<vecino<<endl;
    while(vecino<grafo->get_N_Vertices()){
        vecino = grafo->siguiente(peru, vecino);
        if(vecino < grafo->get_N_Vertices())
            cout<<"Vecino: "<<vecino<<endl;
    }

    delete grafo;
}

void calcularDensidad() {
    int ciudades;
    int conexiones;

    cin >> ciudades >> conexiones;

    // cout << "ciudades " << ciudades << endl;
    // cout << "conexiones " << conexiones << endl;

    int v1;
    int v2;
    int w;

    GrafoMA *grafo = new GrafoMA(ciudades);
    for (int i = 0; i < conexiones; i++) {
        cin >> v1 >> v2 >> w;
        grafo->setArista(v1, v2, w);
    }

    // cout << "grafo->get_N_Aristas() " << grafo->get_N_Aristas() << endl;
    // cout << "grafo->get_N_Vertices() " << grafo->get_N_Vertices() << endl;

    double density = (double) grafo->get_N_Aristas() / (grafo->get_N_Vertices() * grafo->get_N_Vertices());
    cout << fixed << setprecision(4) << density << endl;

    double sparsity = (double) 1 - density;
    cout << fixed << setprecision(4) << sparsity << endl;

    delete grafo;
}

void ubicarCiudad() {
    int ciudades;
    int conexiones;
    cin >> ciudades >> conexiones;

    int v1;
    int v2;
    int w;
    GrafoMA *grafo = new GrafoMA(ciudades);
    for (int i = 0; i < conexiones; i++) {
        cin >> v1 >> v2 >> w;
        grafo->setArista(v1, v2, w);
        grafo->setArista(v2, v1, w);
    }

    int c1;
    int c2;
    cin >> c1 >> c2;

    bool hayConexion = false;
    int vecino;

    for(int ciudad = 0; ciudad < ciudades; ciudad++) {
        // cout << "CIUDAD: " << ciudad << endl;

        vecino = grafo->primero(ciudad);
        while(vecino < grafo->get_N_Vertices()) {
            // cout << "VECINO: " << vecino << endl;
            if (vecino == c2) {
                hayConexion = true;
                break;
            }
            vecino = grafo->siguiente(ciudad, vecino);
        }
    }

    if (hayConexion)
        cout << "SI" << endl;
    else
        cout << "NO" << endl;

    delete grafo;
}

int main() {
    // testGrafo();
    // calcularDensidad();
    ubicarCiudad();

    return 0;
}
