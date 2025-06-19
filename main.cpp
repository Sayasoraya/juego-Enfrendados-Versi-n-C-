#include <iostream>
#include <ctime>
#include "dados.h"

using namespace std;

int main() {
    int opcion;
    char confirmar;

    srand(time(NULL)); // Semilla para numeros aleatorios

    Jugador jugador1, jugador2;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                jugarPartida(jugador1, jugador2);
                break;
            case 2:
                mostrarEstadisticas(jugador1, jugador2);
                break;
            case 3:
                mostrarCreditos();
                break;
            case 0:
                cout << "\nEstas segura/o de que queres salir? (s/n): ";
                cin >> confirmar;
                if (confirmar == 's' || confirmar == 'S') {
                    cout << "Saliendo del programa... Hasta luego." << endl;
                    return 0;
                }
                break;
            default:
                cout << "Opcion no valida. Intenta nuevamente." << endl;
        }

        system("pause");
        system("cls");
    } while (true);

    return 0;
}
