#include "../lib/librerias.hpp"

int const W = 3;

class Nodo {
  public:
    //Constructor
    Nodo(int x, int y, int coste);

    //Setters
    void setFuncionBusqueda(std::pair<int, int> posicion_salida);
    void setPadre(Nodo*);

    //Getters
    int getFuncionBusqueda();
    Nodo* getPadre();
    std::pair<int, int> getPosicion() {return coordenadas_;}
    int getCosteReal() {return valor_coste_real_;}

  private:
    std::pair<int, int> coordenadas_;
    int valor_funcion_busqueda_ = 0;    //f(n)
    int valor_coste_real_ = 0;           //g(n)
    Nodo* padre_ = nullptr;
};


Nodo::Nodo(int x, int y, int coste) {
  coordenadas_.first = x;
  coordenadas_.second = y;
  valor_coste_real_ = coste;
}


/* SETTERS */

void Nodo::setFuncionBusqueda(std::pair<int, int> posicion_salida) {
  //Calculamos el valor de la funcion h(n)
  int funcion_h = (abs(posicion_salida.first - coordenadas_.first) + abs(posicion_salida.second - coordenadas_.second)) * W;
  //Sumamos el valor de h(n) + g(n), teniendo como resultado: f(n)
  valor_funcion_busqueda_ = funcion_h + valor_coste_real_;
}

void Nodo::setPadre(Nodo* padre) {
  padre_ = padre;
}


/* GETTERS */
int Nodo::getFuncionBusqueda() {
  return valor_funcion_busqueda_;
}

Nodo* Nodo::getPadre() {
  return padre_;
}