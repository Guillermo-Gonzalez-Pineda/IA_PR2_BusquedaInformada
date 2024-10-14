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

void Nodo::setFuncionBusqueda(std::pair<int, int> posicion_salida, int tipo_funcion) {
  int funcion_h = 0;
  switch (tipo_funcion) {
    case 1:  // Distancia Manhattan
      funcion_h = W * (abs(posicion_salida.first - coordenadas_.first) + abs(posicion_salida.second - coordenadas_.second));
      break;
    case 2:  // Distancia Euclidea
      funcion_h = W * sqrt(pow(posicion_salida.first - coordenadas_.first, 2) + pow(posicion_salida.second - coordenadas_.second, 2));
      break;
    case 3:  // Distancia Chebyshev
      funcion_h = W * std::max(abs(posicion_salida.first - coordenadas_.first), abs(posicion_salida.second - coordenadas_.second));
      break;
  }
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