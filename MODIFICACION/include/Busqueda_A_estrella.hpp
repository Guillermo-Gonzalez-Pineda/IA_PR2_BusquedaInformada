#include "Laberinto.hpp"
#include "Nodo.hpp"

class Busqueda_A {
  public:
    Busqueda_A(Laberinto& laberinto) : laberinto_(laberinto), nodo_inicio_(nullptr) {}
    void inicializarBusqueda(std::ofstream& archivo_salida, int indice_ejecucion);
    void marcarCamino(Nodo*);
    void limpiarCamino();
    void cambiarFuncionBusqueda(int tipo_funcion);

    // Funciones de Impresión
    void imprimrIteracion(std::ofstream& archivo_salida);
    void imprimirCamino();
    void imprimirTabla(std::ofstream& archivo_salida, Nodo* nodo_final);
    void imprimirCaminoCaracter(std::ofstream& archivo_salida);

  private:
    Nodo* nodo_inicio_;
    Laberinto& laberinto_;
    std::vector<Nodo*> nodos_abiertos_;
    std::vector<Nodo*> nodos_cerrados_;
    int num_nodos_generados_ = 0;
    int num_nodos_inspeccionados_ = 0;
    int tipo_funcion_busqueda_ = 1;
    int num_iteraciones_ = 1;
};