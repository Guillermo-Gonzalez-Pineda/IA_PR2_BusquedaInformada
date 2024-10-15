#include "../lib/librerias.hpp"

struct Vecino {
  int valor;      // Valor del laberinto
  std::pair<int, int> coordenadas;  // Coordenadas del vecino
  int coste;

  Vecino(int v, std::pair<int, int> c, int z) : valor(v), coordenadas(c), coste(z) {}
};

class Laberinto {
  public:
    Laberinto(std::ifstream& archivo);
    void imprimirLaberinto();

    // Modificadores
    void modificarEntrada(int nueva_entrada_x, int nueva_entrada_y);
    void modificarSalida(int nueva_salida_x, int nueva_salida_y);

    // Getters
    int getNumFilas() {return num_filas_;}
    int getNumColumnas() {return num_columnas_;}
    std::pair<int, int> getPosicionEntrada() {return posicion_entrada_;}
    std::pair<int, int> getPosicionSalida() {return posicion_salida_;}
    std::vector<Vecino> getVecinos(int x, int y);
    int getValorCasilla(std::pair<int, int> coordenadas) {return laberinto_[coordenadas.first][coordenadas.second];}

    //Setters
    void setValorCasilla(std::pair<int, int> coordenadas_cambiar, int valor = 2);

  private:
    std::vector<std::vector<int>> laberinto_;
    int num_filas_;
    int num_columnas_;
    std::pair<int, int> posicion_entrada_;
    std::pair<int, int> posicion_salida_;
};
