#include <iostream>
#include "dados.h"  // Incluye las funciones y estructuras definidas en dados.h
using namespace std;

int main() {
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
