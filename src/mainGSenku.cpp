#include "GSenku.hpp"
#include <iostream>
#include <string>

using namespace std;

/*
 *  Pre: argc representa el número de argumentos dados al ejecutar el programa y argv[] los argumentos de la línea de comandos:
 *  <ruta_tablero> <ruta_movimiento> <retardo> [fichero_salida]
 *  Post: Programa que busca la solución al juego de Senku obteniendo la lista de movimientos validos y el tablero inicial a partir
 *  de los ficheros que se le pasan como argumentos.
*/
int main(int argc, char *argv[]) {
    if(argc < 5) {
        cout << "Error: Se necesitan argumentos ruta_tablero ruta_movimiento retardo [fichero_salida]" << endl;
        return 1;
    }

    tpTablero tablero;
    tpMovimientosValidos movimientosValidos;
    tpListaMovimientos solucionParcial;

    int tableroOk = inicializarTablero(argv[1], tablero);
    int movimientosOk = inicializarMovimientosValidos(argv[2], movimientosValidos);

    if(tableroOk && movimientosOk) {
        mostrarTablero(tablero);
        buscaSolucion(tablero, movimientosValidos, solucionParcial, stoi(argv[3]));

        if(argc == 5) escribeListaMovimientos(argv[4], solucionParcial);
    }


    return 0;
}
