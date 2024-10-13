#include "../lib/librerias.hpp"
#include "../include/Busqueda_A_estrella.hpp"

void menu() {
  std::cout << "1. Imprimir laberinto" << std::endl;
  std::cout << "2. Modificar entrada" << std::endl;
  std::cout << "3. Modificar salida" << std::endl;
  std::cout << "4. Cambiar Funcion de Busqueda" << std::endl;
  std::cout << "5. Buscar salida" << std::endl;
  std::cout << "6. Salir" << std::endl;
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

  int opcion = 0;
  while(opcion != 6) {
    menu();
    std::cin >> opcion;

    switch(opcion) {
      case 1:
        laberinto.imprimirLaberinto();
        break;
      case 2:
        int nueva_entrada_x, nueva_entrada_y;
        std::cout << "Introduce la nueva coordenada X de la entrada: ";
        std::cin >> nueva_entrada_x;
        std::cout << "Introduce la nueva coordenada Y de la entrada: ";
        std::cin >> nueva_entrada_y;
        laberinto.modificarEntrada(nueva_entrada_x, nueva_entrada_y);
        break;
      case 3:
        int nueva_salida_x, nueva_salida_y;
        std::cout << "Introduce la nueva coordenada X de la salida: ";
        std::cin >> nueva_salida_x;
        std::cout << "Introduce la nueva coordenada Y de la salida: ";
        std::cin >> nueva_salida_y;
        laberinto.modificarSalida(nueva_salida_x, nueva_salida_y);
        break;
      case 4:
        int nueva_funcion;
        std::cout << "¿Qué función de búsqueda deseas utilizar?" << std::endl;
        std::cout << "  1. Distancia Euclidiana" << std::endl;
        std::cout << "  2. Distancia Manhattan" << std::endl;
        std::cout << "  3. Distancia Chebyshev" << std::endl;
        std::cin >> nueva_funcion;

        busqueda.cambiarFuncionBusqueda(nueva_funcion);
        break;
      case 5:
        busqueda.inicializarBusqueda();
        busqueda.imprimirCamino();
        busqueda.limpiarCamino();
        break;
      case 6:
        std::cout << "Saliendo del programa..." << std::endl;
        break;
      default:
        std::cout << "Opción no válida" << std::endl;
        break;
    }
  }

  return 0;
}