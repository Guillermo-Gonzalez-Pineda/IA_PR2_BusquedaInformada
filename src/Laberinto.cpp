#include "../include/Laberinto.hpp"


/* CONSTRUCTOR LABERINTO */
Laberinto::Laberinto(std::ifstream& archivo) {
  std::string linea;

  //Almacenamos el numero de lineas que tiene el laberinto
  std::getline(archivo, linea);
  num_filas_ = stoi(linea);

  //Almacenamos el numero de columnas que tiene el laberinto
  std::getline(archivo, linea);
  num_columnas_ = stoi(linea);

  // Leemos cada línea y la dividimos en columnas
  for (int i = 0; i < num_filas_; i++) {
    std::getline(archivo, linea);
    std::stringstream stream(linea);
    std::vector<int> fila;
    int valor;

    // Leemos cada valor en la línea
    while (stream >> valor) {
      fila.push_back(valor);

      // Si el valor es 3 (entrada), almacenamos sus coordenadas
      if (valor == 3) {
        posicion_entrada_ = {i, static_cast<int>(fila.size() - 1)};
      }
      // Si el valor es 4 (salida), almacenamos sus coordenadas
      if (valor == 4) {
        posicion_salida_ = {i, static_cast<int>(fila.size() - 1)};
      }
    }
    // Añadimos la fila al laberinto
    laberinto_.push_back(fila);
  }
}


/* IMPRIMIR LABERINTO */
void Laberinto::imprimirLaberinto() {
  const std::string BACK_RED = "\033[41m  \033[0m"; // Muro
  const std::string BACK_WHITE = "\033[47m  \033[0m"; // Espacio libre (blanco)
  const std::string BACK_GREEN = "\033[42m  \033[0m"; // Camino encontrado
  const std::string BACK_RESET = "\033[0m"; // Restablece los colores
  const std::string BACK_YELLOW = "\033[43m  \033[0m"; // Espacio amarillo
  const std::string BACK_BLUE = "\033[44m  \033[0m"; // Camino encontrado

  for (int i = 0; i < num_filas_; ++i) {
    for (int j = 0; j < num_columnas_; ++j) {
      int valor = laberinto_[i][j];
      if (valor == 1) {
        std::cout << BACK_WHITE; // Muro
      } else if (valor == 0) {
        // No aplicar color, usar el color de fondo de la terminal
        std::cout << BACK_RESET; // Restablecer color al fondo de la terminal
        std::cout << "  "; // Espacio para mantener la forma
      } else if (valor == 3) { // Valor para el camino
        std::cout << BACK_GREEN; // Camino encontrado
      } else if (valor == 4) {
        std::cout << BACK_YELLOW;
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


/* MODIFICAR ENTRADA */
void Laberinto::modificarEntrada(int nueva_entrada_x, int nueva_entrada_y) {
  laberinto_[posicion_entrada_.first][posicion_entrada_.second] = 1;
  // Actualizamos la posición de la entrada
  posicion_entrada_ = {nueva_entrada_y, nueva_entrada_x};
  // Marcamos la nueva entrada en el laberinto
  laberinto_[nueva_entrada_y][nueva_entrada_x] = 3;
}


/* MODIFICAR SALIDA */
void Laberinto::modificarSalida(int nueva_salida_x, int nueva_salida_y) {
  laberinto_[posicion_salida_.first][posicion_salida_.second] = 1;
  // Actualizamos la posición de la salida
  posicion_salida_ = {nueva_salida_y, nueva_salida_x};
  // Marcamos la nueva salida en el laberinto
  laberinto_[nueva_salida_y][nueva_salida_x] = 4;
}


/* GET VECINOS */
std::vector<Vecino> Laberinto::getVecinos(int pos_x, int pos_y) {
  std::vector<Vecino> vector_vecinos;

  // Recorremos todas las posibles direcciones de los vecinos
  for (int dir = 0; dir < 8; ++dir) {
    int vecino_x = pos_x;
    int vecino_y = pos_y;
    int coste_temp = 0;

    switch (dir) {
      case 0:  // Vecino superior
        vecino_x = pos_x - 1;
        coste_temp = 5;
        break;
      case 1:  // Vecino inferior
        vecino_x = pos_x + 1;
        coste_temp = 5;
        break;
      case 2:  // Vecino izquierdo
        vecino_y = pos_y - 1;
        coste_temp = 5;
        break;
      case 3:  // Vecino derecho
        vecino_y = pos_y + 1;
        coste_temp = 5;
        break;
      case 4:  // Vecino diagonal superior-izquierda
        vecino_x = pos_x - 1;
        vecino_y = pos_y - 1;
        coste_temp = 7;
        break;
      case 5:  // Vecino diagonal superior-derecha
        vecino_x = pos_x - 1;
        vecino_y = pos_y + 1;
        coste_temp = 7;
        break;
      case 6:  // Vecino diagonal inferior-izquierda
        vecino_x = pos_x + 1;
        vecino_y = pos_y - 1;
        coste_temp = 7;
        break;
      case 7:  // Vecino diagonal inferior-derecha
        vecino_x = pos_x + 1;
        vecino_y = pos_y + 1;
        coste_temp = 7;
        break;
    }

    // Verificamos que el vecino está dentro de los límites del laberinto
    if ((vecino_x >= 0 && vecino_x < laberinto_.size()) && (vecino_y >= 0 && vecino_y < laberinto_[vecino_x].size())) {
      std::pair<int, int> coordenadas_vecino = {vecino_x, vecino_y};
      vector_vecinos.emplace_back(laberinto_[vecino_x][vecino_y], coordenadas_vecino, coste_temp);
    } else {
      vector_vecinos.emplace_back(-1, std::pair<int, int>{-1, -1}, -1);  // Indicador de que no hay vecino
    }
  }
  return vector_vecinos;
}


/* SET VALOR CASILLA */
void Laberinto::setValorCasilla(std::pair<int, int> coordenadas_cambiar, int valor) {
  laberinto_[coordenadas_cambiar.first][coordenadas_cambiar.second] = valor;
}