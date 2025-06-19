#include <iostream>
#include <cstdlib>
#include <ctime>
#include "dados.h"

using namespace std;

int tirarDado6() {
    return rand() % 6 + 1;
}

int tirarDado12() {
    return rand() % 12 + 1;
}

void inicializarJugadores(Jugador* j1, Jugador* j2) {
    cout << "\nIngrese el nombre del Jugador 1: ";
    cin >> j1->nombre;
    j1->puntos = 0;
    j1->cantidadDados = 6;

    cout << "Ingrese el nombre del Jugador 2: ";
    cin >> j2->nombre;
    j2->puntos = 0;
    j2->cantidadDados = 6;
}

Jugador* decidirInicio(Jugador* j1, Jugador* j2) {
    int dado1, dado2;
    do {
        dado1 = tirarDado6();
        dado2 = tirarDado6();
        cout << "\n" << j1->nombre << " tira: " << dado1 << endl;
        cout << j2->nombre << " tira: " << dado2 << endl;

        if (dado1 > dado2) {
            cout << j1->nombre << " comienza la partida." << endl;
            return j1;
        } else if (dado2 > dado1) {
            cout << j2->nombre << " comienza la partida." << endl;
            return j2;
        } else {
            cout << "Empate. Se repite la tirada." << endl;
        }
    } while (dado1 == dado2);

    return nullptr;
}

void mostrarMenu() {
    cout << "\n----- MENU PRINCIPAL -----\n";
    cout << "1 - JUGAR\n";
    cout << "2 - ESTADISTICAS\n";
    cout << "3 - CREDITOS\n";
    cout << "0 - SALIR\n";
    cout << "--------------------------\n";
    cout << "Seleccione una opcion: ";
}

void mostrarCreditos() {
    cout << "\nJuego inventado por Angel Simón.\n";
    cout << "Integrantes del grupo:\n";
    cout << "- Soraya Zaragoza (30656)\n";
    cout << "- Rodrigo Garcia Dieguez (32655)\n";
    cout << "Grupo: Mapache Team\n";
}

void mostrarEstadisticas(Jugador* j1, Jugador* j2) {
    cout << "\n===== ESTADISTICAS =====\n";
    if (j1->puntos > j2->puntos) {
        cout << "Ganador: " << j1->nombre << " con " << j1->puntos << " puntos.\n";
        cout << "Perdedor: " << j2->nombre << " con " << j2->puntos << " puntos.\n";
    } else if (j2->puntos > j1->puntos) {
        cout << "Ganador: " << j2->nombre << " con " << j2->puntos << " puntos.\n";
        cout << "Perdedor: " << j1->nombre << " con " << j1->puntos << " puntos.\n";
    } else {
        cout << "Empate entre ambos jugadores con " << j1->puntos << " puntos.\n";
    }
}

void mostrarDadosConIndices(int dados[], int cantidad) {
    cout << "Dados:     ";
    for (int i = 0; i < cantidad; i++) {
        cout << "[" << dados[i] << "] ";
    }
    cout << "\nIndices:   ";
    for (int i = 0; i < cantidad; i++) {
        cout << " " << i + 1 << "  ";
    }
    cout << endl;
}

void jugarTurno(Jugador* jugadorActual, Jugador* rival) {
    cout << "\nTurno de " << jugadorActual->nombre << ":\n";

    int dadoObj1 = tirarDado12();
    int dadoObj2 = tirarDado12();
    int numeroObjetivo = dadoObj1 + dadoObj2;
    cout << "Dados objetivo: " << dadoObj1 << " + " << dadoObj2 << " = " << numeroObjetivo << " (Numero objetivo)\n";

    for (int i = 0; i < jugadorActual->cantidadDados; i++) {
        jugadorActual->dados[i] = tirarDado6();
    }

    mostrarDadosConIndices(jugadorActual->dados, jugadorActual->cantidadDados);

    int suma = 0;
    int elegidos[20] = {0};
    int usados[20] = {0};
    int cantidadElegidos = 0;

    cout << "\nIngrese el número de índice del dado (0 para rendirse):\n";

    while (suma < numeroObjetivo && cantidadElegidos < jugadorActual->cantidadDados) {
        int seleccion;
        cout << "# " << cantidadElegidos + 1 << ": ";
        cin >> seleccion;

        if (seleccion == 0) {
            cout << "Rendiste la tirada. Se considera fallida.\n";
            break;
        }

        if (seleccion < 1 || seleccion > jugadorActual->cantidadDados || usados[seleccion - 1]) {
            cout << "Índice inválido o ya usado. Intente nuevamente.\n";
            continue;
        }

        int valorSeleccionado = jugadorActual->dados[seleccion - 1];
        suma += valorSeleccionado;
        elegidos[cantidadElegidos++] = seleccion - 1;
        usados[seleccion - 1] = 1;

        cout << "Suma actual: " << suma << endl;

        if (suma == numeroObjetivo) {
            int puntosGanados = numeroObjetivo * cantidadElegidos;
            jugadorActual->puntos += puntosGanados;
            cout << "\n¡Tirada exitosa!\n";
            cout << "Ganaste " << puntosGanados << " puntos.\n";

            for (int i = 0; i < cantidadElegidos && jugadorActual->cantidadDados > 0; i++) {
                if (rival->cantidadDados < 20) {
                    rival->dados[rival->cantidadDados++] = jugadorActual->dados[elegidos[i]];
                }
            }

            jugadorActual->cantidadDados -= cantidadElegidos;

            if (jugadorActual->cantidadDados == 0) {
                cout << jugadorActual->nombre << " se quedo sin dados. ¡Gana automaticamente con 10000 puntos extra!\n";
                jugadorActual->puntos += 10000;
            }

            break;
        }

        if (suma > numeroObjetivo) {
            cout << "La suma superó el objetivo. Tirada fallida.\n";
            break;
        }
    }

    if (suma != numeroObjetivo && rival->cantidadDados > 1) {
        jugadorActual->dados[jugadorActual->cantidadDados++] = rival->dados[--rival->cantidadDados];
        cout << jugadorActual->nombre << " recibe 1 dado de " << rival->nombre << " por tirada fallida.\n";
    }

    cout << "Puntaje actual: " << jugadorActual->nombre << ": " << jugadorActual->puntos << " | ";
    cout << rival->nombre << ": " << rival->puntos << endl;
    cout << "Dados restantes: " << jugadorActual->nombre << ": " << jugadorActual->cantidadDados << " | ";
    cout << rival->nombre << ": " << rival->cantidadDados << endl;
}
