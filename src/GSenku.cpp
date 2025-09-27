#include "GSenku.hpp"
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

bool inicializarTablero(const string nombreFichero, tpTablero &tablero) {
    ifstream f(nombreFichero);
    if(!f.is_open()) {
        cerr << "Error al abrir el fichero de configuración" << endl;
        return false;
    }

    f >> tablero.ncols >> tablero.nfils;

    for(int i = 0; i < tablero.nfils; i++) {
        for(int j = 0; j < tablero.ncols; j++) {
            char estado;
            f >> estado;

            switch((int)estado) {
            case 45:
                tablero.matriz[i][j] = NO_USADA;
                break;
            case 111:
                tablero.matriz[i][j] = OCUPADA;
                break;
            case 120:
                tablero.matriz[i][j] = VACIA;
                break;
            default:
                break;
            }
        }
    }

    f.close();
    return true;
}

bool inicializarMovimientosValidos(const string nombreFichero, tpMovimientosValidos &movimientos) {
    ifstream f(nombreFichero);
    if(!f.is_open()) {
        cerr << "Error al abrir el fichero de movimientos válidos" << endl;
        return false;
    }

    int i = 0;
    char estado;

    while(f >> estado) {
        if(estado == '-') {
            movimientos.validos[i] = false;
            i++;
        }
        if(estado == '+') {
            movimientos.validos[i] = true;
            i++;
        }
    }

    f.close();
    return true;
}

void mostrarTablero(const tpTablero & tablero) {
    for(int i = 0; i < tablero.nfils; ++i) {
        for(int j = 0; j < tablero.ncols; ++j) {
            switch(tablero.matriz[i][j]) {
            case NO_USADA:
                // Si es una celda no usada
                cout << "\033[37;40m" << "   " << "\033[0m";
                break;
            case OCUPADA:
                // Si es una celda ocupada, la mostramos en azul
                cout << "\033[1;42m" << " o " << "\033[0m";
                break;
            case VACIA:
                // Si es una celda vacia
                cout << "\033[8;45m" << "   " << "\033[0m";
                break;
            }
        }
        cout << endl;
    }
    cout << endl;
}

tpPosicion obtenerMovimientoValido(const tpTablero &tablero, const tpMovimientosValidos &movValidos, int i, int j, int direccion) {

    // 0 - Arriba izquierda
    // 1 - Arriba
    // 2 - Arriba derecha
    // 3 - Izquierda
    // 4 - Derecha
    // 5 - Abajo izquierda
    // 6 - Abajo
    // 7 - Abajo derecha

    if(!movValidos.validos[direccion]) return {0, 0};

    // direccion correspondiente && se sale del tablero? (2) && hay una ficha ocupada entre la posicion actual y la posicion de destino? && la posicion de destino es vacia?
    if(direccion == 0 && i - 2 >= 0 && j - 2 >= 0 && tablero.matriz[i - 1][j - 1] == OCUPADA && tablero.matriz[i - 2][j - 2] == VACIA) return {-2, -2};
    if(direccion == 1 && i - 2 >= 0 && tablero.matriz[i - 1][j] == OCUPADA && tablero.matriz[i - 2][j] == VACIA) return {0, -2};
    if(direccion == 2 && i - 2 >= 0 && j + 2 < tablero.ncols && tablero.matriz[i - 1][j + 1] == OCUPADA && tablero.matriz[i - 2][j + 2] == VACIA) return {2, -2};
    if(direccion == 3 && j - 2 >= 0 && tablero.matriz[i][j - 1] == OCUPADA && tablero.matriz[i][j - 2] == VACIA) return {-2, 0};
    if(direccion == 4 && j + 2 < tablero.ncols && tablero.matriz[i][j + 1] == OCUPADA && tablero.matriz[i][j + 2] == VACIA) return {2, 0};
    if(direccion == 5 && i + 2 < tablero.nfils && j - 2 >= 0 && tablero.matriz[i + 1][j - 1] == OCUPADA && tablero.matriz[i + 2][j - 2] == VACIA) return {-2, 2};
    if(direccion == 6 && i + 2 < tablero.nfils && tablero.matriz[i + 1][j] == OCUPADA && tablero.matriz[i + 2][j] == VACIA) return {0, 2};
    if(direccion == 7 && i + 2 < tablero.nfils && j + 2 < tablero.ncols && tablero.matriz[i + 1][j + 1] == OCUPADA && tablero.matriz[i + 2][j + 2] == VACIA) return {2, 2};

    return {0, 0}; // Si no se cumple ninguna de las condiciones anteriores, no hay movimiento valido
}

bool hayMovimientosValidos(const tpTablero &tablero, const tpMovimientosValidos &movValidos) {
    for(int i = 0; i < tablero.nfils; i++) {
        for(int j = 0; j < tablero.ncols; j++) {
            // cout << "Comprobando celda: " << i << ", " << j << endl;
            if(tablero.matriz[i][j] == OCUPADA) {
                for(int direccion = 0; direccion < 8; direccion++) {
                    tpPosicion movimientoValido = obtenerMovimientoValido(tablero, movValidos, i, j, direccion);
                    // cout << "Direccion: " << direccion << " Movimiento valido: " << movimientoValido.x << ", " << movimientoValido.y << endl;
                    if(movimientoValido.x != 0 || movimientoValido.y != 0) return true;
                }
            }
        }
    }

    return false;
}

int contarFichas(tpTablero &tablero) {
    int count = 0;

    for(int i = 0; i < tablero.nfils; ++i) {
        for(int j = 0; j < tablero.ncols; ++j) {
            if(tablero.matriz[i][j] == OCUPADA) {
                count++;
            }
        }
    }

    return count;
}

void moverFicha(tpTablero &tablero, const tpMovimientoPieza &mov) {
    tablero.matriz[mov.origen.y][mov.origen.x] = VACIA;
    tablero.matriz[mov.destino.y][mov.destino.x] = OCUPADA;
    tablero.matriz[(mov.origen.y + mov.destino.y) / 2][(mov.origen.x + mov.destino.x) / 2] = VACIA; // Hallamos la ficha del medio ya sea el movimiento en el eje X o en el eje Y
}

void deshacerMovimiento(tpTablero &tablero, const tpMovimientoPieza &mov) {
    tablero.matriz[mov.origen.y][mov.origen.x] = OCUPADA;
    tablero.matriz[mov.destino.y][mov.destino.x] = VACIA;
    tablero.matriz[(mov.origen.y + mov.destino.y) / 2][(mov.origen.x + mov.destino.x) / 2] = OCUPADA;
}

int buscaSolucion(tpTablero &tablero, const tpMovimientosValidos &movValidos, tpListaMovimientos &solucionParcial, const int retardo) {

    if(contarFichas(tablero) == 1) return 1;
    if(!hayMovimientosValidos(tablero, movValidos)) return 0;


    for(int i = 0; i < tablero.nfils; ++i) {
        for(int j = 0; j < tablero.ncols; ++j) {

            if(tablero.matriz[i][j] == OCUPADA) {


                for(int direccion = 0; direccion < 8; direccion++) {

                    tpPosicion movimientoValido = obtenerMovimientoValido(tablero, movValidos, i, j, direccion);

                    if(movimientoValido.x == 0 && movimientoValido.y == 0) continue;  // Si no hay movimiento valido, continuamos

                    // j columnas, i filas
                    // x, y
                    tpMovimientoPieza mov = { {j, i}, {j + movimientoValido.x, i + movimientoValido.y} };

                    moverFicha(tablero, mov);

                    if(retardo > 0) {
                        mostrarTablero(tablero);
                        this_thread::sleep_for(chrono::milliseconds(retardo));
                    }

                    solucionParcial.movs[solucionParcial.numMovs++] = { { mov.origen.y, mov.origen.x }, { mov.destino.y, mov.destino.x } }; // Guardamos el movimiento en la solucion parcial


                    if(buscaSolucion(tablero, movValidos, solucionParcial, retardo)) return 1;
                    deshacerMovimiento(tablero, mov);
                    solucionParcial.numMovs--;
                }

            }
        }
    }


    return 0;
}

void escribeListaMovimientos(string nombreFichero, const tpListaMovimientos &solucion) {
    ofstream f(nombreFichero);
    if(!f.is_open()) {
        cerr << "Error al abrir el fichero de salida" << endl;
        return;
    }

    if(solucion.numMovs == 0) {
        f << -1 << endl; // Si no hay movimientos, se escribe -1
    } else {
        for(int i = 0; i < solucion.numMovs; i++) {
            f << solucion.movs[i].origen.x << "," << solucion.movs[i].origen.y << ":" << solucion.movs[i].destino.x << "," << solucion.movs[i].destino.y << endl;
        }
    }

    f.close();
    return;
}