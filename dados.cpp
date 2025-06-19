#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "dados.h"
using namespace std;

static int maxPuntaje = 0;
static char nombreMaxPuntaje[30] = "";
static int minPuntaje = 99999;
static char nombreMinPuntaje[30] = "";

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
            cout << j1->nombre << " comienza la partida.\n";
            return j1;
        } else if (dado2 > dado1) {
            cout << j2->nombre << " comienza la partida.\n";
            return j2;
        } else {
            cout << "Empate. Se repite la tirada.\n";
        }
    } while (true);
}

void mostrarMenu() {
    cout << "\n----- MENÚ PRINCIPAL -----\n";
    cout << "1 - JUGAR\n";
    cout << "2 - ESTADÍSTICAS\n";
    cout << "3 - CRÉDITOS\n";
    cout << "0 - SALIR\n";
    cout << "--------------------------\n";
    cout << "Seleccione una opción: ";
}

void mostrarCreditos() {
    cout << "\nTrabajo práctico realizado por:\n";
    cout << "- Soraya Zaragoza (30656)\n";
    cout << "- Rodrigo Garcia Dieguez (32655)\n";
    cout << "Equipo: Mapache Team\n";
    cout << "Docente: Ángel Simón\n";
}

void mostrarEstadisticas() {
    cout << "\n--- ESTADÍSTICAS ---\n";
    if (strlen(nombreMaxPuntaje) > 0) {
        cout << "Mayor puntaje registrado: " << nombreMaxPuntaje << " con " << maxPuntaje << " puntos.\n";
        cout << "Menor puntaje registrado: " << nombreMinPuntaje << " con " << minPuntaje << " puntos.\n";
    } else {
        cout << "Aún no se ha registrado ninguna partida.\n";
    }
}

void mostrarDadosConIndices(int dados[], int cantidad) {
    cout << "\nDados:     ";
    for (int i = 0; i < cantidad; i++) {
        cout << "[" << dados[i] << "] ";
    }
    cout << "\nÍndices:   ";
    for (int i = 0; i < cantidad; i++) {
        cout << " " << (i + 1) << "   ";
    }
    cout << "\n";
}

void jugarTurno(Jugador* jugadorActual, Jugador* rival) {
    cout << "\nTurno de " << jugadorActual->nombre << ":\n";

    int dadoObj1 = tirarDado12();
    int dadoObj2 = tirarDado12();
    int numeroObjetivo = dadoObj1 + dadoObj2;
    cout << "Dados objetivo: " << dadoObj1 << " + " << dadoObj2 << " = " << numeroObjetivo << endl;

    for (int i = 0; i < jugadorActual->cantidadDados; i++) {
        jugadorActual->dados[i] = tirarDado6();
    }

    mostrarDadosConIndices(jugadorActual->dados, jugadorActual->cantidadDados);

    int suma = 0;
    int elegidos[20];
    int usados[20] = {0};
    int cantidadElegidos = 0;

    cout << "\nSelecciona los dados uno por uno (ingrese el índice). Ingrese 0 para rendirse:\n";

    while (true) {
        if (cantidadElegidos >= jugadorActual->cantidadDados) {
            cout << "Ya usaste todos tus dados disponibles.\n";
            break;
        }

        int seleccion;
        cout << "Selección #" << (cantidadElegidos + 1) << ": ";
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

            for (int i = 0; i < cantidadElegidos; i++) {
                if (rival->cantidadDados < 20) {
                    rival->dados[rival->cantidadDados++] = jugadorActual->dados[elegidos[i]];
                }
            }

            jugadorActual->cantidadDados -= cantidadElegidos;

            if (jugadorActual->cantidadDados == 0) {
                cout << jugadorActual->nombre << " se quedó sin dados. ¡Gana automáticamente con 10000 puntos extra!\n";
                jugadorActual->puntos += 10000;
            }
            break;
        } else if (suma > numeroObjetivo) {
            cout << "La suma superó el objetivo. Tirada fallida.\n";
            break;
        }
    }

    if (suma != numeroObjetivo && rival->cantidadDados > 1) {
        jugadorActual->dados[jugadorActual->cantidadDados++] = rival->dados[rival->cantidadDados - 1];
        rival->cantidadDados--;
        cout << jugadorActual->nombre << " recibe 1 dado de " << rival->nombre << " por tirada fallida.\n";
    }

    cout << "Puntaje actual: " << jugadorActual->nombre << ": " << jugadorActual->puntos
         << " | " << rival->nombre << ": " << rival->puntos << endl;
    cout << "Dados restantes: " << jugadorActual->nombre << ": " << jugadorActual->cantidadDados
         << " | " << rival->nombre << ": " << rival->cantidadDados << endl;
}

void jugarPartida() {
    Jugador jugador1, jugador2;

    cout << "\n=== Iniciando el juego Enfrentados ===\n";

    inicializarJugadores(&jugador1, &jugador2);
    Jugador* quienEmpieza = decidirInicio(&jugador1, &jugador2);
    Jugador* otro = (quienEmpieza == &jugador1) ? &jugador2 : &jugador1;

    cout << "\nComienza la partida real!\n";

    for (int ronda = 1; ronda <= 3; ronda++) {
        cout << "\n==== RONDA " << ronda << " ====\n";

        jugarTurno(quienEmpieza, otro);
        if (quienEmpieza->cantidadDados == 0) break;

        jugarTurno(otro, quienEmpieza);
        if (otro->cantidadDados == 0) break;
    }

    cout << "\n==== FIN DEL JUEGO ====\n";
    cout << jugador1.nombre << ": " << jugador1.puntos << " puntos\n";
    cout << jugador2.nombre << ": " << jugador2.puntos << " puntos\n";

    if (jugador1.puntos > jugador2.puntos) {
        cout << "Ganó " << jugador1.nombre << "!\n";
    } else if (jugador2.puntos > jugador1.puntos) {
        cout << "Ganó " << jugador2.nombre << "!\n";
    } else {
        cout << "Empate!\n";
    }

    if (jugador1.puntos > maxPuntaje) {
        maxPuntaje = jugador1.puntos;
        strcpy(nombreMaxPuntaje, jugador1.nombre);
    }
    if (jugador2.puntos > maxPuntaje) {
        maxPuntaje = jugador2.puntos;
        strcpy(nombreMaxPuntaje, jugador2.nombre);
    }

    if (jugador1.puntos < minPuntaje) {
        minPuntaje = jugador1.puntos;
        strcpy(nombreMinPuntaje, jugador1.nombre);
    }
    if (jugador2.puntos < minPuntaje) {
        minPuntaje = jugador2.puntos;
        strcpy(nombreMinPuntaje, jugador2.nombre);
    }
}
