#include "Laberinto.hpp"
#include "Nodo.hpp"

class Busqueda_A {
  public:
    Busqueda_A(Laberinto& laberinto) : laberinto_(laberinto), nodo_inicio_(nullptr) {}
    void inicializarBusqueda();
    void marcarCamino(Nodo*);
    void imprimirCamino();

  private:
    Nodo* nodo_inicio_;
    Laberinto& laberinto_;
    std::vector<Nodo*> nodos_disponibles_;
    int num_nodos_generados_;
    int num_nodos_inspeccionados_;
};

void Busqueda_A::inicializarBusqueda() {
  //Obtenemos la posicion del nodo de entrada
  std::pair<int, int> posicion_entrada = laberinto_.getPosicionEntrada();
  std::pair<int, int> posicion_salida = laberinto_.getPosicionSalida();
  nodo_inicio_ = new Nodo(posicion_entrada.first, posicion_entrada.second, 0);
  nodo_inicio_->setFuncionBusqueda(posicion_salida);

  nodos_disponibles_.push_back(nodo_inicio_);
  std::set<std::pair<int, int>> nodos_visitados;
  
  while (!nodos_disponibles_.empty()) {
    //Calculamos cual es el nodo disponible con menor coste
    int coste = nodos_disponibles_[0]->getFuncionBusqueda();
    int indice_min_coste = 0;
    for(int i = 1; i < nodos_disponibles_.size(); i++) {
      if(nodos_disponibles_[i]->getFuncionBusqueda() < coste) {
        coste = nodos_disponibles_[i]->getFuncionBusqueda();
        indice_min_coste = i;
      }
    }

    //Inspeccionamos el nodo disponible de menor coste
    Nodo* nodo_actual = nodos_disponibles_[indice_min_coste];
    num_nodos_inspeccionados_++;

    //Eliminamos del vector, el nodo que acabamos de seleccionar
    nodos_disponibles_.erase(nodos_disponibles_.begin() + indice_min_coste);

    // Añadimos el nodo actual a los visitados
    nodos_visitados.insert(nodo_actual->getPosicion());

    //Si el nodo inspeccionado coincide con la posición de salida marcamos el camino de ese nodo
    if(nodo_actual->getPosicion() == posicion_salida) {
      marcarCamino(nodo_actual);
      return;
    }

    for(Vecino vecino : laberinto_.getVecinos(nodo_actual->getPosicion().first, nodo_actual->getPosicion().second)) {
      //Si el elemento evaluado es -1, quiere decir que no existe un vecino (será un borde)
      //Asi que no generamos ningun nodo y continuamos con el siguiente
      if(vecino.valor == -1 || vecino.valor == 1) {
        continue;
      }

      std::pair<int, int> posicion_vecino = {vecino.pos_x, vecino.pos_y};

      if(nodos_visitados.find(posicion_vecino) != nodos_visitados.end()) {
        continue;
      }  

      //Calculamos el coste de la funcion g(n), sumando el coste de la transicion con el coste real del padre
      int coste_real = nodo_actual->getCosteReal() + vecino.coste;
      //Creamos el nodo con sus atributos
      Nodo* nodo_vecino = new Nodo(vecino.pos_x, vecino.pos_y, coste_real);
      nodo_vecino->setPadre(nodo_actual);
      nodo_vecino->setFuncionBusqueda(posicion_salida);

      //Guardamos el nodo en el vector de nodos disponibles
      nodos_disponibles_.push_back(nodo_vecino);
    }

  }

  std::cout << "No se ha encontrado ninguna salida" << std::endl;
}

void Busqueda_A::marcarCamino(Nodo* nodo_final) {
  Nodo* actual = nodo_final;
  std::pair<int, int> posicion;

  while(actual != nullptr) {
    laberinto_.setValorCasilla(actual->getPosicion());
    actual = actual->getPadre();
  }
}

void Busqueda_A::imprimirCamino() {
  const int CAMINO = 2;
  const int MURO = 1;
  const int LIBRE = 0;
  for (int i = 0; i < laberinto_.getNumFilas(); i++) {
    for (int j = 0; j < laberinto_.getNumColumnas(); j++) {
      int valor = laberinto_.getValorCasilla({i, j});

      if (valor == CAMINO) {
        std::cout << YELLOW << "* " << RESET;
      } else if (valor == MURO) {
        std::cout << RED << valor << " " << RESET;
      } else {
        std::cout << valor << " ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

