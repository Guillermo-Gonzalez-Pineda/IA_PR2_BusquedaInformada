#include "../lib/librerias.hpp"

struct Vecino {
  int valor;      // Valor del laberinto (0, 1, 3, 4, etc.)
  int pos_x;     // Coordenada X del vecino
  int pos_y;     // Coordenada Y del vecino
  int coste;

  Vecino(int v, int x, int y, int z) : valor(v), pos_x(x), pos_y(y), coste(z) {}
};

class Laberinto {
  public:
    Laberinto(std::ifstream& archivo);

    // Getters
    int getNumFilas() {return num_filas_;}
    int getNumColumnas() {return num_columnas_;}
    std::pair<int, int> getPosicionEntrada() {return posicion_entrada_;}
    std::pair<int, int> getPosicionSalida() {return posicion_salida_;}
    std::vector<Vecino> getVecinos(int x, int y);
    int getValorCasilla(std::pair<int, int> coordenadas) {return laberinto_[coordenadas.first][coordenadas.second];}

    //Setters
    void setValorCasilla(std::pair<int, int> coordenadas_cambiar) {
      laberinto_[coordenadas_cambiar.first][coordenadas_cambiar.second] = 2;
    }

  private:
    std::vector<std::vector<int>> laberinto_;
    int num_filas_;
    int num_columnas_;
    std::pair<int, int> posicion_entrada_;
    std::pair<int, int> posicion_salida_;
};


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
      vector_vecinos.emplace_back(laberinto_[vecino_x][vecino_y], vecino_x, vecino_y, coste_temp);
    } else {
      vector_vecinos.emplace_back(-1, -1, -1, -1);  // Indicador de que no hay vecino
    }
  }

  return vector_vecinos;
}