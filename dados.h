#ifndef DADOS_H
#define DADOS_H

struct Jugador {
    char nombre[30];
    int puntos;
    int dados[20];
    int cantidadDados;
};

// Prototipos de funciones
int tirarDado6();
int tirarDado12();

void inicializarJugadores(Jugador* j1, Jugador* j2);
Jugador* decidirInicio(Jugador* j1, Jugador* j2);

void mostrarMenu();
void mostrarCreditos();
void mostrarEstadisticas();  // Corregido: sin parámetros
void mostrarDadosConIndices(int dados[], int cantidad);
void jugarTurno(Jugador* jugadorActual, Jugador* rival);
void jugarPartida();

#endif
