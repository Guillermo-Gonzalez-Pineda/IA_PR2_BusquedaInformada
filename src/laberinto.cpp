#include "../include/Laberinto.hpp"

Laberinto::Laberinto(std::ifstream& archivo) {
  std::string linea;

  //Almacenamos el numero de lineas que tiene el laberinto
  std::getline(archivo, linea);
  num_filas_ = stoi(linea);

  //Almacenamos el numero de columnas que tiene el laberinto
  std::getline(archivo, linea);
  num_columnas_ = stoi(linea);

  for(int i = 0; i < num_filas_; i++) {
    std::getline(archivo, linea);
    std::stringstream stream(linea);
    int valor;
    for(int j = 0; j < num_columnas_; j++) {
      stream >> valor;
      //Si el valor que examinamos es un 3, almacenamos sus coordenadas
      if (valor == 3) {
        posicion_entrada_ = {i, j};
        laberinto_[i][j] = valor;

      // Si el valor que examinamos es un 4, almacenamos sus coordenadas
      } else if (valor == 4) {
        posicion_salida_ = {i, j};
        laberinto_[i][j] = valor;

      // Si el valor es distinto de 3 o 4, añadimos el elemento al vector de vectores
      } else {
        laberinto_[i][j] = valor;
      }
    }
  }

}