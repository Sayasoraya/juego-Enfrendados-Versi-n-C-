#include <iostream>
#include <ctime>
#include "dados.h"
using namespace std;

int main() {
    system("chcp 65001 > nul"); // Fuerza codificación UTF-8 en consola

    int opcion;
    char confirmar;

    // Semilla para aleatoriedad
    srand(time(NULL));

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                jugarPartida();
                break;
            case 2:
                // Nota: necesitas pasar los jugadores si tu función lo requiere
                mostrarEstadisticas();
                break;
            case 3:
                mostrarCreditos();
                break;
            case 0:
                cout << "\n¿Estás segura/o de que querés salir? (s/n): ";
                cin >> confirmar;
                if (confirmar == 's' || confirmar == 'S') {
                    cout << "Saliendo del programa... Hasta luego.\n";
                    return 0;
                }
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }

        system("pause");
        system("cls");

    } while (true);

    return 0;
}
