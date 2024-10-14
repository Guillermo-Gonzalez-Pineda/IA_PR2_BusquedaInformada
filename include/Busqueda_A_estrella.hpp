#include "Laberinto.hpp"
#include "Nodo.hpp"

class Busqueda_A {
  public:
    Busqueda_A(Laberinto& laberinto) : laberinto_(laberinto), nodo_inicio_(nullptr) {}
    void inicializarBusqueda();
    void marcarCamino(Nodo*);
    void limpiarCamino();
    void imprimirCamino();
    void cambiarFuncionBusqueda(int tipo_funcion);

  private:
    Nodo* nodo_inicio_;
    Laberinto& laberinto_;
    std::vector<Nodo*> nodos_abiertos_;
    std::vector<Nodo*> nodos_cerrados_;
    int num_nodos_generados_;
    int num_nodos_inspeccionados_;
    int tipo_funcion_busqueda_ = 1;
    int num_iteraciones_ = 0;
};

void Busqueda_A::inicializarBusqueda() {
  //Inicializamos las posiciones Entrada y Salida
  std::pair<int, int> posicion_entrada;
  std::pair<int, int> posicion_salida;

  //Creamos el nodo inicial con un coste real de 0
  nodo_inicio_ = new Nodo(posicion_entrada.first, posicion_entrada.second, 0);
  //Asignamos el coste de la funcion f(n)
  nodo_inicio_->setFuncionBusqueda(posicion_salida, tipo_funcion_busqueda_);

  //Añadimos el nodo inicial a la lista de nodos abiertos o disponibles
  nodos_abiertos_.push_back(nodo_inicio_);

  while(!nodos_abiertos_.empty()) {
    //Visitamos el nodo abierto con menor coste heurístico
    int coste_heuristico = nodos_abiertos_[0]->getCosteHeuristico();
    int indice_menor_coste_heuristico = 0;
    for(int i = 1; i < nodos_abiertos_.size(); i++) {
      if(nodos_abiertos_[i]->getCosteHeuristico() < coste_heuristico) {
        coste_heuristico = nodos_abiertos_[i]->getCosteHeuristico();
        indice_menor_coste_heuristico = i;
      }
    }

    Nodo* nodo_actual = nodos_abiertos_[indice_menor_coste_heuristico];

    //Guardamos el nodo actual en nodos_cerrados_
    nodos_cerrados_.push_back(nodo_actual);

    //Eliminamos el nodo actual de nodos_abiertos_
    nodos_abiertos_.erase(nodos_abiertos_.begin() + indice_menor_coste_heuristico);

    //Comprobamos si el nodo actual coincide con la posición final
    if(nodo_actual->getPosicion() == posicion_salida) {
      marcarCamino(nodo_actual);
      laberinto_.imprimirLaberinto();
      return;
    }

    //Si no es el nodo final, exploramos sus nodos vecinos
    for(auto& vecino : laberinto_.getVecinos(nodo_actual->getPosicion().first, nodo_actual->getPosicion().second)) {
      //Comprobamos que no sea un muro o un valor externo al laberinto
      if(vecino.valor == 1 || vecino.valor == -1) {
        continue;
      }

      //Comprobar que el vecino no se encuentra en la lista cerrada
      bool encontrado = false;
      for(auto& nodo : nodos_cerrados_) {
        if(nodo->getPosicion() == vecino.coordenadas) {
          encontrado = true;
          break;
        }
      }
      //Si se encuentra en la lista cerrada, continuamos con el siguiente vecino
      if(encontrado) {
        continue;
      }   

      //Calculamos el coste heuristico del vecino
      int coste_real_vecino = nodo_actual->getCosteReal() + vecino.coste;
      Nodo* nodo_vecino = new Nodo(vecino.coordenadas.first, vecino.coordenadas.second, coste_real_vecino);
      nodo_vecino->setFuncionBusqueda(posicion_salida, tipo_funcion_busqueda_);

      //Comprobamos si el vecino se encuentra en la lista abierta
      encontrado = false;
      for(auto& nodo : nodos_abiertos_) {
        if(nodo->getPosicion() == vecino.coordenadas) {
          encontrado = true;
          break;
        }
      }

      //Si el vecino no se encuentra en la lista abierta, lo añadimos
      if(!encontrado) {
        nodo_vecino->setPadre(nodo_actual);
        nodos_abiertos_.push_back(nodo_vecino);
      } else {
        //Si el vecino se encuentra en la lista abierta, comprobamos si el coste heuristico es menor
        for(auto& nodo : nodos_abiertos_) {
          if(nodo->getPosicion() == vecino.coordenadas) {
            if(nodo_vecino->getCosteHeuristico() < nodo->getCosteHeuristico()) {
              nodo->setPadre(nodo_actual);
              nodo->setFuncionBusqueda(posicion_salida, tipo_funcion_busqueda_);
            }
            break;
          }
        }
      
      }
    }

    

  }


  
}

void Busqueda_A::cambiarFuncionBusqueda(int tipo_funcion) {
  tipo_funcion_busqueda_ = tipo_funcion;
}

void Busqueda_A::marcarCamino(Nodo* nodo_final) {
  Nodo* actual = nodo_final;
  std::pair<int, int> posicion;

  while(actual != nullptr) {
    laberinto_.setValorCasilla(actual->getPosicion());
    actual = actual->getPadre();
  }
}

void Busqueda_A::limpiarCamino() {
  for (int i = 0; i < laberinto_.getNumFilas(); ++i) {
    for (int j = 0; j < laberinto_.getNumColumnas(); ++j) {
      if (laberinto_.getValorCasilla({i, j}) == 2) {
        laberinto_.setValorCasilla({i, j}, 0);
      }
    }
  }
}

void Busqueda_A::imprimirCamino() {
  const std::string BACK_RED = "\033[41m  \033[0m"; // Muro
  const std::string BACK_WHITE = "\033[47m  \033[0m"; // Espacio libre (blanco)
  const std::string BACK_GREEN = "\033[42m  \033[0m"; // Camino encontrado
  const std::string BACK_RESET = "\033[0m"; // Restablece los colores

  for (int i = 0; i < laberinto_.getNumFilas(); ++i) {
    for (int j = 0; j < laberinto_.getNumColumnas(); ++j) {
      int valor = laberinto_.getValorCasilla({i, j});
      if (valor == 1) {
        std::cout << BACK_RED; // Muro
      } else if (valor == 0) {
        // No aplicar color, usar el color de fondo de la terminal
        std::cout << BACK_RESET; // Restablecer color al fondo de la terminal
        std::cout << "  "; // Espacio para mantener la forma
      } else if (valor == 2) { // Valor para el camino
        std::cout << BACK_GREEN; // Camino encontrado
      } else {
        // Espacio "vacío" que utiliza el fondo de la terminal
        std::cout << BACK_RESET; // Restablecer color al fondo de la terminal
        std::cout << "  "; // Espacio para mantener la forma
      }
    }
    std::cout << std::endl;
  }
  std::cout << num_iteraciones_ << " iteraciones" << std::endl;
  std::cout << "\n" << std::endl;
}

