#include "GSenku.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int main() {

    tpTablero tablero;
    tpMovimientosValidos movimientosValidos;
    tpListaMovimientos solucionParcial;

    int tableroOk = inicializarTablero("test/tableros/tableroDos.txt", tablero);
    int movimientosOk = inicializarMovimientosValidos("test/movimientos/movimientosClasicos.txt", movimientosValidos);

    if(tableroOk && movimientosOk) {
        buscaSolucion(tablero, movimientosValidos, solucionParcial, 1000);
        escribeListaMovimientos("solucion.txt", solucionParcial);
    }


    return 0;
}
