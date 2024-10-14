#include "../lib/librerias.hpp"

int const W = 3;

class Nodo {
  public:
    //Constructor
    Nodo(int x, int y, int coste);
    //Sobrecargar operador ==
    bool operator==(const Nodo& nodo) {
      return coordenadas_ == nodo.coordenadas_;
    }

    //Setters
    void setFuncionBusqueda(std::pair<int, int> posicion_salida, int tipo_funcion = 1);
    void setPadre(Nodo*);

    //Getters
    int getCosteHeuristico();
    Nodo* getPadre();
    std::pair<int, int> getPosicion() {return coordenadas_;}
    int getCosteReal() {return valor_coste_real_;}

  private:
    std::pair<int, int> coordenadas_;
    int valor_funcion_busqueda_ = 0;    //f(n)
    int valor_coste_real_ = 0;           //g(n)
    Nodo* padre_ = nullptr;
};