#include <iostream>
#include <cstdlib>
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
    int d1, d2;
    do {
        d1 = tirarDado6();
        d2 = tirarDado6();
        cout << j1->nombre << " tira: " << d1 << endl;
        cout << j2->nombre << " tira: " << d2 << endl;

        if (d1 > d2) {
            cout << j1->nombre << " comienza la partida.\n";
            return j1;
        } else if (d2 > d1) {
            cout << j2->nombre << " comienza la partida.\n";
            return j2;
        } else {
            cout << "Empate. Se repite la tirada.\n";
        }
    } while (d1 == d2);

    return nullptr;
}

void mostrarMenu() {
    cout << "\n----- MENU PRINCIPAL -----\n";
    cout << "1 - JUGAR\n";
    cout << "2 - ESTADISTICAS\n";
    cout << "3 - CREDITOS\n";
    cout << "0 - SALIR\n";
    cout << "Seleccione una opcion: ";
}

void mostrarCreditos() {
    cout << "\nTrabajo realizado por:\n";
    cout << "- Soraya Zaragoza (30656)\n";
    cout << "- Rodrigo Garcia Dieguez (32655)\n";
    cout << "Grupo: Mapache Team\n";
}

void mostrarEstadisticas(Jugador j1, Jugador j2) {
    cout << "\n----- ESTADISTICAS -----\n";

    if (j1.puntos > j2.puntos) {
        cout << "Jugador con mas puntaje: " << j1.nombre << " con " << j1.puntos << " puntos.\n";
        cout << "Jugador con menos puntaje: " << j2.nombre << " con " << j2.puntos << " puntos.\n";
    } else if (j2.puntos > j1.puntos) {
        cout << "Jugador con mas puntaje: " << j2.nombre << " con " << j2.puntos << " puntos.\n";
        cout << "Jugador con menos puntaje: " << j1.nombre << " con " << j1.puntos << " puntos.\n";
    } else {
        cout << "Empate entre " << j1.nombre << " y " << j2.nombre << " con " << j1.puntos << " puntos.\n";
    }

    cout << "--------------------------\n";
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
    cout << "\n";
}

void jugarTurno(Jugador* jugadorActual, Jugador* rival) {
    cout << "\nTurno de " << jugadorActual->nombre << ":\n";

    int dado1 = tirarDado12();
    int dado2 = tirarDado12();
    int objetivo = dado1 + dado2;
    cout << "Dados objetivo: " << dado1 << " + " << dado2 << " = " << objetivo << "\n";

    for (int i = 0; i < jugadorActual->cantidadDados; i++) {
        jugadorActual->dados[i] = tirarDado6();
    }

    mostrarDadosConIndices(jugadorActual->dados, jugadorActual->cantidadDados);

    int suma = 0;
    int elegidos[20];
    int cantidadElegidos = 0;
    bool usado[20] = { false };

    cout << "\nIngrese los indices de los dados uno por uno (0 para rendirse):\n";

    while (true) {
        if (cantidadElegidos >= jugadorActual->cantidadDados) {
            cout << "Ya usaste todos los dados disponibles.\n";
            break;
        }

        int seleccion;
        cout << "Seleccion #" << cantidadElegidos + 1 << ": ";
        cin >> seleccion;

        if (seleccion == 0) {
            cout << "Tirada fallida. Te rendiste.\n";
            break;
        }

        if (seleccion < 1 || seleccion > jugadorActual->cantidadDados || usado[seleccion - 1]) {
            cout << "Indice invalido o ya usado. Intenta de nuevo.\n";
            continue;
        }

        int valor = jugadorActual->dados[seleccion - 1];
        suma += valor;
        usado[seleccion - 1] = true;
        elegidos[cantidadElegidos++] = seleccion - 1;

        cout << "Suma actual: " << suma << "\n";

        if (suma == objetivo) {
            int puntosGanados = suma * cantidadElegidos;
            jugadorActual->puntos += puntosGanados;

            cout << "\nTirada exitosa! Ganaste " << puntosGanados << " puntos.\n";

            for (int i = 0; i < cantidadElegidos; i++) {
                if (rival->cantidadDados < 20) {
                    rival->dados[rival->cantidadDados++] = jugadorActual->dados[elegidos[i]];
                }
            }

            for (int i = 0; i < cantidadElegidos; i++) {
                for (int j = elegidos[i]; j < jugadorActual->cantidadDados - 1; j++) {
                    jugadorActual->dados[j] = jugadorActual->dados[j + 1];
                }
                jugadorActual->cantidadDados--;
                for (int k = i + 1; k < cantidadElegidos; k++) {
                    if (elegidos[k] > elegidos[i]) elegidos[k]--;
                }
            }

            if (jugadorActual->cantidadDados == 0) {
                cout << jugadorActual->nombre << " se quedo sin dados. Gana automaticamente con 10000 puntos extra!\n";
                jugadorActual->puntos += 10000;
            }

            break;
        } else if (suma > objetivo) {
            cout << "Te pasaste del objetivo. Tirada fallida.\n";
            break;
        }
    }

    if (suma != objetivo && rival->cantidadDados > 1) {
        jugadorActual->dados[jugadorActual->cantidadDados++] = rival->dados[rival->cantidadDados - 1];
        rival->cantidadDados--;
        cout << jugadorActual->nombre << " recibe 1 dado de " << rival->nombre << " por tirada fallida.\n";
    }

    cout << "Puntaje actual: " << jugadorActual->nombre << ": " << jugadorActual->puntos << " | " << rival->nombre << ": " << rival->puntos << "\n";
    cout << "Dados restantes: " << jugadorActual->nombre << ": " << jugadorActual->cantidadDados << " | " << rival->nombre << ": " << rival->cantidadDados << "\n";
}

void jugarPartida(Jugador& j1, Jugador& j2) {
    cout << "\n=== Iniciando el juego Enfrentados ===\n";

    inicializarJugadores(&j1, &j2);
    Jugador* actual = decidirInicio(&j1, &j2);
    Jugador* rival = (actual == &j1) ? &j2 : &j1;

    for (int ronda = 1; ronda <= 3; ronda++) {
        cout << "\n--- Ronda " << ronda << " ---\n";
        jugarTurno(actual, rival);
        if (actual->cantidadDados == 0) break;

        jugarTurno(rival, actual);
        if (rival->cantidadDados == 0) break;
    }

    cout << "\n--- Fin del juego ---\n";
    cout << j1.nombre << " - Puntaje: " << j1.puntos << " | Dados: " << j1.cantidadDados << endl;
    cout << j2.nombre << " - Puntaje: " << j2.puntos << " | Dados: " << j2.cantidadDados << endl;

    if (j1.puntos > j2.puntos) {
        cout << "Gana " << j1.nombre << " con " << j1.puntos << " puntos!\n";
    } else if (j2.puntos > j1.puntos) {
        cout << "Gana " << j2.nombre << " con " << j2.puntos << " puntos!\n";
    } else {
        cout << "Empate!\n";
    }
}
