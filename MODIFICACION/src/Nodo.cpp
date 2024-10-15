#include "../include/Nodo.hpp"

/* CONSTRUCTOR */
Nodo::Nodo(int x, int y, int coste) {
  coordenadas_.first = x;
  coordenadas_.second = y;
  valor_coste_real_ = coste;
}


/* SET FUNCION BUSQUEDA */
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


/* SET PADRE */
void Nodo::setPadre(Nodo* padre) {
  padre_ = padre;
}


/* GET COSTE HEURISTICO */
int Nodo::getCosteHeuristico() {
  return valor_funcion_busqueda_;
}


/* GET PADRE */
Nodo* Nodo::getPadre() {
  return padre_;
}