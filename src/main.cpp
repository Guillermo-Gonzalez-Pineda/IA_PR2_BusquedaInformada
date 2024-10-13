#include "../lib/librerias.hpp"
#include "../include/Busqueda_A_estrella.hpp"

void menu() {
  std::cout << "1. Imprimir laberinto" << std::endl;
  std::cout << "2. Modificar entrada" << std::endl;
  std::cout << "3. Modificar salida" << std::endl;
  std::cout << "4. Buscar salida" << std::endl;
  std::cout << "5. Salir" << std::endl;
}

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

  int opcion;
  int nueva_entrada_x, nueva_entrada_y, nueva_salida_x, nueva_salida_y;
  do {
    menu();
    std::cin >> opcion;

    switch(opcion) {
      case 1:
        laberinto.imprimirLaberinto();
        break;
        
      case 2:
        std::cout << "Introduce la coordenada 'x' de la nueva entrada: ";
        std::cin >> nueva_entrada_x;
        std::cout << "Introduce la coordenada 'y' de la nueva entrada: ";
        std::cin >> nueva_entrada_y;
        laberinto.modificarEntrada(nueva_entrada_x, nueva_entrada_y);
        break;

      case 3:
        std::cout << "Introduce la coordenada 'x' de la nueva salida: ";
        std::cin >> nueva_salida_x;
        std::cout << "Introduce la coordenada 'y' de la nueva salida: ";
        std::cin >> nueva_salida_y;
        laberinto.modificarSalida(nueva_salida_x, nueva_salida_y);
        break;

      case 4:
        busqueda.inicializarBusqueda();
        busqueda.imprimirCamino();
        busqueda.limpiarCamino();
        break;
      case 5:
        std::cout << "Saliendo del programa" << std::endl;
        break;

      default:
        std::cout << "Opción no válida" << std::endl;
        break;
    }
  } while(opcion != 5);

  return 0;
}