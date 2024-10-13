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