#include "../lib/librerias.hpp"
#include "../include/Busqueda_A_estrella.hpp"

void menu() {
  std::cout << "\n";
  std::cout << CYAN << "======================================\n";
  std::cout << "         MENÚ DE OPCIONES             \n";
  std::cout << "======================================\n" << RESET;
  std::cout << "  1. Imprimir laberinto\n";
  std::cout << "  2. Modificar entrada\n";
  std::cout << "  3. Modificar salida\n";
  std::cout << "  4. Cambiar Función de Búsqueda\n";
  std::cout << "  5. Buscar salida\n";
  std::cout << "  6. Salir\n";
  std::cout << "======================================\n";
  std::cout << "Elige una opción: ";
}

int main(int argc, char *argv[]) {
  //Comprobamos que el número de argumentos sea el correcto
  if(argc != 3) {
    std::cerr << RED << "La ejecución del programa debe ser: ./Busqueda_A <archivo_entrada> <archivo_salida>" << RESET << std::endl;
    return 1;
  }

  //Guardamos los argumentos en variables
  std::string string_archivo_entrada = argv[1];
  std::string string_archivo_salida = argv[2];

  //Abrimos el archivo de entrada
  std::ifstream archivo_entrada(string_archivo_entrada);
  if(!archivo_entrada.is_open()) {
    std::cerr << RED << "No se pudo abrir el archivo de entrada" << RESET << std::endl;
    return 1;
  }

  std::ofstream archivo_salida(string_archivo_salida);
  if(!archivo_salida.is_open()) {
    std::cerr << RED << "No se pudo abrir el archivo de salida" << RESET << std::endl;
    return 1;
  }

  Laberinto laberinto(archivo_entrada);
  Busqueda_A busqueda(laberinto);

  int opcion = 0;
  while(opcion != 6) {
    menu();
    std::cin >> opcion;

    switch(opcion) {
      case 1:
        std::cout << BLUE << "Laberinto:" << RESET << std::endl;
        laberinto.imprimirLaberinto();
        break;
      case 2:
        int nueva_entrada_x, nueva_entrada_y;
        std::cout << "\nIntroduce la nueva coordenada X de la entrada: ";
        std::cin >> nueva_entrada_x;
        std::cout << "\nIntroduce la nueva coordenada Y de la entrada: ";
        std::cin >> nueva_entrada_y;
        laberinto.modificarEntrada(nueva_entrada_x, nueva_entrada_y);
        std::cout << GREEN << "Entrada modificada correctamente" << RESET << std::endl;
        break;
      case 3:
        int nueva_salida_x, nueva_salida_y;
        std::cout << "\nIntroduce la nueva coordenada X de la salida: ";
        std::cin >> nueva_salida_x;
        std::cout << "\nIntroduce la nueva coordenada Y de la salida: ";
        std::cin >> nueva_salida_y;
        laberinto.modificarSalida(nueva_salida_x, nueva_salida_y);
        std::cout << GREEN << "Salida modificada correctamente" << RESET << std::endl;
        break;
      case 4:
        int nueva_funcion;
        std::cout << "\n¿Qué función de búsqueda deseas utilizar?" << std::endl;
        std::cout << "  1. Distancia Manhattan" << std::endl;
        std::cout << "  2. Distancia Euclidiana" << std::endl;
        std::cout << "  3. Distancia Chebyshev" << std::endl;
        std::cout << "Elige una función: ";
        std::cin >> nueva_funcion;

        busqueda.cambiarFuncionBusqueda(nueva_funcion);
        std::cout << GREEN << "Función de búsqueda cambiada correctamente" << RESET << std::endl;
        break;
      case 5:
        std::cout << YELLOW << "Iniciando Búsqueda A*..." << RESET << std::endl;
        for(int i = 0; i < 10; i++) {
          busqueda.inicializarBusqueda(archivo_salida, i);
          busqueda.imprimirCamino();
          busqueda.limpiarCamino();
        }
        std::cout << GREEN << "Búsqueda A* finalizada" << RESET << std::endl;
        break;
      case 6:
        std::cout << YELLOW << "Saliendo del programa..." << std::endl;
        break;
      default:
        std::cout << RED << "Opción no válida" << std::endl;
        break;
    }

    std::cout << GREEN << "======================================\n" << RESET;
  }

  return 0;
}