#include "../lib/librerias.hpp"
#include "../include/Busqueda_A_estrella.hpp"


int main(int argc, char *argv[]) {
  //Comprobamos que el número de argumentos sea el correcto
  if(argc != 2) {
    std::cerr << "La ejecución del programa debe ser: ./Busqueda_A <archivo_entrada> <archivo_salida>" << std::endl;
    return 1;
  }

  //Guardamos los argumentos en variables
  std::string archivo_entrada = argv[1];
  //std::string archivo_salida = argv[2];

  //Abrimos el archivo de entrada
  std::ifstream archivo(archivo_entrada);
  if(!archivo.is_open()) {
    std::cerr << "No se pudo abrir el archivo de entrada" << std::endl;
    return 1;
  }

  Laberinto laberinto(archivo);
  Busqueda_A busqueda(laberinto);
  busqueda.inicializarBusqueda();
  busqueda.imprimirCamino();


  std::cout << "Encontro la salida" << std::endl;
  return 0;
}