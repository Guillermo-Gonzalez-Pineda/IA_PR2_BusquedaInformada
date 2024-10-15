#include "../include/Busqueda_A_estrella.hpp"

/* INICIALIZAR BUSQUEDA */
void Busqueda_A::inicializarBusqueda(std::ofstream& archivo_salida) {
  //Si el archivo tiene algo escrito, lo limpiamos
  archivo_salida.clear();
  //Inicializamos las posiciones Entrada y Salida
  std::pair<int, int> posicion_entrada = laberinto_.getPosicionEntrada();
  std::pair<int, int> posicion_salida = laberinto_.getPosicionSalida();

  //Creamos el nodo inicial con un coste real de 0
  nodo_inicio_ = new Nodo(posicion_entrada.first, posicion_entrada.second, 0);
  //Asignamos el coste de la funcion f(n)
  nodo_inicio_->setFuncionBusqueda(posicion_salida, tipo_funcion_busqueda_);

  //Añadimos el nodo inicial a la lista de nodos abiertos o disponibles
  nodos_abiertos_.push_back(nodo_inicio_);
  num_nodos_generados_++;

  imprimrIteracion(archivo_salida);

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
    num_nodos_inspeccionados_++;

    //Eliminamos el nodo actual de nodos_abiertos_
    nodos_abiertos_.erase(nodos_abiertos_.begin() + indice_menor_coste_heuristico);

    //Comprobamos si el nodo actual coincide con la posición final
    if(nodo_actual->getPosicion() == posicion_salida) {
      //Imprimimos la iteración en el archivo de salida
      num_iteraciones_++;
      imprimrIteracion(archivo_salida);

      //Marcamos el camino
      marcarCamino(nodo_actual);

      imprimirTabla(archivo_salida, nodo_actual);
      imprimirCaminoCaracter(archivo_salida);
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
        num_nodos_generados_++;
      } else {
        //Si el vecino se encuentra en la lista abierta, comprobamos si el coste heuristico es menor
        for(auto& nodo : nodos_abiertos_) {
          if(nodo->getPosicion() == vecino.coordenadas) {
            if(nodo_vecino->getCosteHeuristico() < nodo->getCosteHeuristico()) {
              nodo->setPadre(nodo_actual);
              nodo->setCosteReal(coste_real_vecino);
              nodo->setFuncionBusqueda(posicion_salida, tipo_funcion_busqueda_);
            }
            break;
          }
        }
      }
    }
    num_iteraciones_++;
    imprimrIteracion(archivo_salida);
  }
  std::cout << "No se ha encontrado una solución" << std::endl;
}


/* MARCAR CAMINO */
void Busqueda_A::marcarCamino(Nodo* nodo_final) {
  Nodo* actual = nodo_final;
  std::pair<int, int> posicion;

  while(actual != nullptr) {
    laberinto_.setValorCasilla(actual->getPosicion());
    actual = actual->getPadre();
  }
}


/* LIMPIAR CAMINO */
void Busqueda_A::limpiarCamino() {
  for (int i = 0; i < laberinto_.getNumFilas(); ++i) {
    for (int j = 0; j < laberinto_.getNumColumnas(); ++j) {
      if (laberinto_.getValorCasilla({i, j}) == 2) {
        laberinto_.setValorCasilla({i, j}, 0);
      }
    }
  }
  laberinto_.setValorCasilla(laberinto_.getPosicionEntrada(), 3);
  laberinto_.setValorCasilla(laberinto_.getPosicionSalida(), 4);

  //Limpiamos las listas de nodos abiertos y cerrados
  nodos_abiertos_.clear();
  nodos_cerrados_.clear();

  //Reiniciamos el nodo inicial
  nodo_inicio_ = nullptr;
  num_iteraciones_ = 1;
}


/* CAMBIAR FUNCION BUSQUEDA */
void Busqueda_A::cambiarFuncionBusqueda(int tipo_funcion) {
  tipo_funcion_busqueda_ = tipo_funcion;
}


/* IMPRIMIR ITERACION */
void Busqueda_A::imprimrIteracion(std::ofstream& archivo_salida) {
  //Imprimimos la iteración en el archivo de salida
  archivo_salida << "Iteracion " << num_iteraciones_ << std::endl;

  //Imprimimos los nodos generados
  archivo_salida << "Nodos generados: ";
  if(nodos_abiertos_.size() == 1) {
    archivo_salida << "(" << nodos_abiertos_[0]->getPosicion().first << ", " << nodos_abiertos_[0]->getPosicion().second << ")" << std::endl;
  } else {
    for(int i = 0; i < nodos_abiertos_.size() - 1; i++) {
      archivo_salida << "(" << nodos_abiertos_[i]->getPosicion().first << ", " << nodos_abiertos_[i]->getPosicion().second << "), ";
    }
    archivo_salida << "(" << nodos_abiertos_[nodos_abiertos_.size() - 1]->getPosicion().first << ", " << nodos_abiertos_[nodos_abiertos_.size() - 1]->getPosicion().second << ")" << std::endl;
  }

  //Imprimimos los nodos inspeccionados
  archivo_salida << "Nodos inspeccionados: ";
  if(nodos_cerrados_.size() == 1) {
    archivo_salida << "(" << nodos_cerrados_[0]->getPosicion().first << ", " << nodos_cerrados_[0]->getPosicion().second << ")" << std::endl;
  } else if(nodos_cerrados_.size() == 0) {
    archivo_salida << std::endl;
  } else {
    for(int i = 0; i < nodos_cerrados_.size() - 1; i++) {
      archivo_salida << "(" << nodos_cerrados_[i]->getPosicion().first << ", " << nodos_cerrados_[i]->getPosicion().second << "), ";
    }
    archivo_salida << "(" << nodos_cerrados_[nodos_cerrados_.size() - 1]->getPosicion().first << ", " << nodos_cerrados_[nodos_cerrados_.size() - 1]->getPosicion().second << ")" << std::endl;
  }
  archivo_salida << "-----------------------------------------------------------------------------------------------------------------------------" << std::endl;
}


/* IMPRIMIR CAMINO*/
void Busqueda_A::imprimirCamino() {
  const std::string BACK_RED = "\033[41m  \033[0m"; // Muro
  const std::string BACK_WHITE = "\033[47m  \033[0m"; // Espacio libre (blanco)
  const std::string BACK_GREEN = "\033[42m  \033[0m"; // Camino encontrado
  const std::string BACK_RESET = "\033[0m"; // Restablece los colores
  const std::string BACK_BLUE = "\033[44m  \033[0m"; // Camino encontrado

  for (int i = 0; i < laberinto_.getNumFilas(); ++i) {
    for (int j = 0; j < laberinto_.getNumColumnas(); ++j) {
      int valor = laberinto_.getValorCasilla({i, j});
      if (valor == 1) {
        std::cout << BACK_WHITE; // Muro
      } else if (valor == 0) {
        // No aplicar color, usar el color de fondo de la terminal
        std::cout << BACK_RESET; // Restablecer color al fondo de la terminal
        std::cout << "  "; // Espacio para mantener la forma
      } else if (valor == 2) { // Valor para el camino
        std::cout << BACK_BLUE; // Camino encontrado
      } else {
        // Espacio "vacío" que utiliza el fondo de la terminal
        std::cout << BACK_RESET; // Restablecer color al fondo de la terminal
        std::cout << "  "; // Espacio para mantener la forma
      }
    }
    std::cout << std::endl;
  }
  std::cout << "\n" << std::endl;
}


/* IMPRIMIR TABLA */
void Busqueda_A::imprimirTabla(std::ofstream& archivo_salida, Nodo* nodo_final) {
  std::vector<Nodo*> camino;
  Nodo* actual = nodo_final;

  // Encabezado de la tabla
  archivo_salida << "\n=========================================" << std::endl;
  archivo_salida << "         Tabla de Resultados de A*       " << std::endl;
  archivo_salida << "=========================================\n" << std::endl;
  
  // Información básica del laberinto
  archivo_salida << "Número de Filas:                 " << laberinto_.getNumFilas() << std::endl;
  archivo_salida << "Número de Columnas:              " << laberinto_.getNumColumnas() << std::endl;
  archivo_salida << "Posición Celda de Entrada:       (" << laberinto_.getPosicionEntrada().first << ", " << laberinto_.getPosicionEntrada().second << ")" << std::endl;
  archivo_salida << "Posición Celda de Salida:        (" << laberinto_.getPosicionSalida().first << ", " << laberinto_.getPosicionSalida().second << ")" << std::endl;

  // Recuperar el camino encontrado
  archivo_salida << "Camino Encontrado:              ";
  while (actual != nullptr) {
    camino.push_back(actual);
    actual = actual->getPadre();
  }

  // Invertir el camino para mostrarlo desde la entrada hasta la salida
  std::reverse(camino.begin(), camino.end());

  // Imprimir el camino con formato adecuado
  for (size_t i = 0; i < camino.size(); ++i) {
    archivo_salida << "(" << camino[i]->getPosicion().first << ", " << camino[i]->getPosicion().second << ")";
    if (i != camino.size() - 1) {
      archivo_salida << " -> ";
    }
  }
  archivo_salida << std::endl;

  // Coste y estadísticas de la búsqueda
  archivo_salida << "Coste del Camino:                " << nodo_final->getCosteReal() << std::endl;
  archivo_salida << "Número de Nodos Generados:       " << num_nodos_generados_ << std::endl;
  archivo_salida << "Número de Nodos Inspeccionados:  " << num_nodos_inspeccionados_ << std::endl;

  // Final de la tabla
  archivo_salida << "=========================================\n" << std::endl;
}



/* IMPRIMIR CAMINO CARACTER */
void Busqueda_A::imprimirCaminoCaracter(std::ofstream& archivo_salida) {
  for(int i = 0; i < laberinto_.getNumFilas(); i++) {
    for(int j = 0; j < laberinto_.getNumColumnas(); j++) {
      if(laberinto_.getValorCasilla({i, j}) == 2) {
        archivo_salida << "* ";
      } else {
        archivo_salida << laberinto_.getValorCasilla({i, j}) << " ";
      }
    }
    archivo_salida << std::endl;
  }
}


