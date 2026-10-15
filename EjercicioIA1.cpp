/* Realice un programa que permita simular una ruleta de opciones y que el usuario pueda elegir entre dos opciones, 3 opciones, 4 opciones o 10 opciones. Todas las opciones deben ser ingresada y validadas
por teclado, las opciones pueden ser palabras, numeros, o simbolos especiale. No puede usar funciones, estructuras, arreglos bidimensionales, punteros o listas. Una vez listo el ejercicio subalo
a su repositorio con una pequeña descripcion */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

int main() {
    // ==========================================================
    // CENTRADO EXACTO DE LA VENTANA CMD EN EL MONITOR REAL
    // ==========================================================
    HWND hwnd = GetConsoleWindow();
    
    // Ancho y alto que tendrá nuestra ventana de la consola
    int anchoVentana = 650;
    int altoVentana = 480;

    // Obtener las dimensiones reales de la pantalla (excluyendo la barra de tareas)
    RECT areaTrabajo;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &areaTrabajo, 0);

    // Calcular el centro exacto tomando como base el área de trabajo disponible
    int posX = areaTrabajo.left + (areaTrabajo.right - areaTrabajo.left - anchoVentana) / 2;
    int posY = areaTrabajo.top + (areaTrabajo.bottom - areaTrabajo.top - altoVentana) / 2;

    // Aplicar el movimiento y redimensionamiento centrado
    MoveWindow(hwnd, posX, posY, anchoVentana, altoVentana, TRUE);
    // ==========================================================

    // Configurar la semilla para números aleatorios
    srand(time(0));

    char repetir = 's';

    do {
        system("cls"); // Limpiar pantalla

        int numOpciones = 0;

        // 1. Menú principal estético y centrado visualmente
        cout << "\n";
        cout << "      \033[1;36m=========================================\033[0m\n";
        cout << "      \033[1;33m          SIMULADOR DE RULETA            \033[0m\n";
        cout << "      \033[1;36m=========================================\033[0m\n";
        cout << "        Seleccione la cantidad de opciones:    \n";
        cout << "        \033[1;32m[2]\033[0m 2 opciones     \033[1;32m[3]\033[0m 3 opciones      \n";
        cout << "        \033[1;32m[4]\033[0m 4 opciones     \033[1;32m[10]\033[0m 10 opciones     \n";
        cout << "      \033[1;36m-----------------------------------------\033[0m\n";
        
        // Validar la cantidad de opciones
        do {
            cout << "      \033[1;35m-> Ingrese su seleccion: \033[0m";
            cin >> numOpciones;

            if (numOpciones != 2 && numOpciones != 3 && numOpciones != 4 && numOpciones != 10) {
                cout << "      \033[1;31m[ERROR] Opcion invalida. Elija 2, 3, 4 o 10.\033[0m\n";
            }
        } while (numOpciones != 2 && numOpciones != 3 && numOpciones != 4 && numOpciones != 10);

        // 2. Declaración del arreglo unidimensional de tamaño fijo
        string opciones[10];

        cout << "\n      \033[1;36m-----------------------------------------\033[0m\n";
        cout << "      \033[1;33m          INGRESO DE OPCIONES            \033[0m\n";
        cout << "      \033[1;36m-----------------------------------------\033[0m\n";

        for (int i = 0; i < numOpciones; i++) {
            bool opcionValida = false;
            
            do {
                cout << "        Opcion \033[1;33m" << (i + 1) << "\033[0m de " << numOpciones << ": ";
                cin >> opciones[i];

                if (opciones[i] == "") {
                    cout << "        \033[1;31m[ERROR] No puede estar vacia.\033[0m\n";
                } else {
                    bool repetida = false;
                    for (int j = 0; j < i; j++) {
                        if (opciones[i] == opciones[j]) {
                            repetida = true;
                            break;
                        }
                    }

                    if (repetida) {
                        cout << "        \033[1;31m[ERROR] Opcion duplicada.\033[0m\n";
                    } else {
                        opcionValida = true;
                    }
                }
            } while (!opcionValida);
        }

        // 3. Simulación de giro estético
        cout << "\n      \033[1;36m=========================================\033[0m\n";
        cout << "      \033[1;32m         GIRANDO LA RULETA...            \033[0m\n";
        cout << "      \033[1;36m=========================================\033[0m\n";

        // Generar índice aleatorio
        int indiceGanador = rand() % numOpciones;

        // 4. Mostrar resultado ganador
        cout << "\n";
        cout << "           \033[1;43m\033[1;30m ¡EL RESULTADO GANADOR ES! \033[0m\n";
        cout << "                  \033[1;32m*** " << opciones[indiceGanador] << " ***\033[0m\n\n";
        cout << "      \033[1;36m=========================================\033[0m\n";

        // 5. Preguntar si desea repetir el programa
        cout << "\n        Desea realizar otra simulacion? (s/n): ";
        cin >> repetir;

    } while (repetir == 's' || repetir == 'S');

    system("cls");
    cout << "\n\n\n           \033[1;35m¡Gracias por usar el simulador! Hasta luego.\033[0m\n\n\n";
    system("pause > nul");

    return 0;
}
