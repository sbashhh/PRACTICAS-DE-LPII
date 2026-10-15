/* Realice un programa que permita hacer conversiones entre unidades de longitud, masa y tiempo. Considere las mas usadas. Valide la entrada por
teclado y considere las restricciones del ultimo ejercicio. IMPORTANTE: EL USUARIO DEBE SER CAPAZ DE SELECCIONAR LAS UNIDADES QUE DESEA
CONVERTIR*/
#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

int main() {
    // ==========================================================
    // CENTRADO EXACTO DE LA VENTANA CMD EN EL MONITOR REAL
    // ==========================================================
    HWND hwnd = GetConsoleWindow();
    
    int anchoVentana = 780;
    int altoVentana = 620;

    RECT areaTrabajo;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &areaTrabajo, 0);

    int posX = areaTrabajo.left + (areaTrabajo.right - areaTrabajo.left - anchoVentana) / 2;
    int posY = areaTrabajo.top + (areaTrabajo.bottom - areaTrabajo.top - altoVentana) / 2;

    MoveWindow(hwnd, posX, posY, anchoVentana, altoVentana, TRUE);
    // ==========================================================

    char repetir = 's';

    do {
        system("cls"); // Limpiar pantalla

        int categoria = 0;

        // 1. Menú principal con colores alternados palabra por palabra (Azul, Amarillo, Rojo)
        cout << "\n";
        cout << "      \033[1;36m=========================================================\033[0m\n";
        cout << "      \033[1;34mSUPER \033[1;33mCONVERSOR \033[1;31mDE \033[1;34mESCALAS \033[1;33mY \033[1;31mUNIDADES \033[1;34mCOMPLETAS       \033[0m\n";
        cout << "      \033[1;36m=========================================================\033[0m\n";
        cout << "        \033[1;34mSeleccione \033[1;33mla \033[1;31mcategoria \033[1;34mde \033[1;33mconversion:                \033[0m\n";
        cout << "        \033[1;32m[1]\033[0m Longitud    (Km, Hm, Dam, m, cm, mm)\n";
        cout << "        \033[1;32m[2]\033[0m Masa        (Ton, Kg, g, mg, lb, oz)\n";
        cout << "        \033[1;32m[3]\033[0m Tiempo      (Ano, Dia, Hora, Min, Seg, ms)\n";
        cout << "        \033[1;32m[4]\033[0m Temperatura (Celsius, Fahrenheit, Kelvin)\n";
        cout << "      \033[1;36m---------------------------------------------------------\033[0m\n";

        // Validar la categoría
        do {
            cout << "        \033[1;35m-> Ingrese su seleccion (1-4): \033[0m";
            cin >> categoria;

            if (categoria < 1 || categoria > 4) {
                cout << "        \033[1;31m[ERROR] Categoria invalida. Elija entre 1 y 4.\033[0m\n";
            }
        } while (categoria < 1 || categoria > 4);

        int origen = 0, destino = 0, maxOpciones = (categoria == 4) ? 3 : 6;
        double valor = 0.0, resultado = 0.0;
        string nombreOrigen = "", nombreDestino = "";

        // ==========================================
        // CATEGORÍA 1: LONGITUD (Escala completa)
        // ==========================================
        if (categoria == 1) {
            cout << "\n      \033[1;36m---------------------------------------------------------\033[0m\n";
            cout << "      \033[1;34mCONVERSION \033[1;33mDE \033[1;31mLONGITUD (ESCALA COMPLETA)           \033[0m\n";
            cout << "      \033[1;36m---------------------------------------------------------\033[0m\n";
            cout << "        [1] Kilometros (km)    [2] Hectometros (hm)\n";
            cout << "        [3] Decametros (dam)   [4] Metros (m - SI)\n";
            cout << "        [5] Centimetros (cm)   [6] Milimetros (mm)\n";

            do {
                cout << "        \033[1;35m-> Unidad de origen (1-6): \033[0m";
                cin >> origen;
                if (origen < 1 || origen > 6) cout << "        \033[1;31m[ERROR] Opcion invalida (1 a 6).\033[0m\n";
            } while (origen < 1 || origen > 6);

            do {
                cout << "        \033[1;35m-> Unidad de destino (1-6): \033[0m";
                cin >> destino;
                if (destino < 1 || destino > 6) cout << "        \033[1;31m[ERROR] Opcion invalida (1 a 6).\033[0m\n";
            } while (destino < 1 || destino > 6);

            do {
                cout << "        \033[1;35m-> Ingrese el valor a convertir: \033[0m";
                cin >> valor;
                if (valor < 0) cout << "        \033[1;31m[ERROR] La longitud no puede ser negativa.\033[0m\n";
            } while (valor < 0);

            if (origen == 1) nombreOrigen = "Kilometros";
            else if (origen == 2) nombreOrigen = "Hectometros";
            else if (origen == 3) nombreOrigen = "Decametros";
            else if (origen == 4) nombreOrigen = "Metros";
            else if (origen == 5) nombreOrigen = "Centimetros";
            else if (origen == 6) nombreOrigen = "Milimetros";

            if (destino == 1) nombreDestino = "Kilometros";
            else if (destino == 2) nombreDestino = "Hectometros";
            else if (destino == 3) nombreDestino = "Decametros";
            else if (destino == 4) nombreDestino = "Metros";
            else if (destino == 5) nombreDestino = "Centimetros";
            else if (destino == 6) nombreDestino = "Milimetros";

            // Convertir todo a Metros (unidad base de longitud)
            double enMetros = valor;
            if (origen == 1) enMetros = valor * 1000.0;       // km a m
            else if (origen == 2) enMetros = valor * 100.0;     // hm a m
            else if (origen == 3) enMetros = valor * 10.0;      // dam a m
            else if (origen == 5) enMetros = valor / 100.0;     // cm a m
            else if (origen == 6) enMetros = valor / 1000.0;    // mm a m

            // Convertir de Metros a destino
            resultado = enMetros;
            if (destino == 1) resultado = enMetros / 1000.0;       // m a km
            else if (destino == 2) resultado = enMetros / 100.0;     // m a hm
            else if (destino == 3) resultado = enMetros / 10.0;      // m a dam
            else if (destino == 5) resultado = enMetros * 100.0;     // m a cm
            else if (destino == 6) resultado = enMetros * 1000.0;    // m a mm

        } 
        // ==========================================
        // CATEGORÍA 2: MASA (Escala completa)
        // ==========================================
        else if (categoria == 2) {
            cout << "\n      \033[1;36m---------------------------------------------------------\033[0m\n";
            cout << "      \033[1;34mCONVERSION \033[1;33mDE \033[1;31mMASA (ESCALA COMPLETA)               \033[0m\n";
            cout << "      \033[1;36m---------------------------------------------------------\033[0m\n";
            cout << "        [1] Toneladas (t)      [2] Kilogramos (kg - SI)\n";
            cout << "        [3] Gramos (g)         [4] Miligramos (mg)\n";
            cout << "        [5] Libras (lb)        [6] Onzas (oz)\n";

            do {
                cout << "        \033[1;35m-> Unidad de origen (1-6): \033[0m";
                cin >> origen;
                if (origen < 1 || origen > 6) cout << "        \033[1;31m[ERROR] Opcion invalida (1 a 6).\033[0m\n";
            } while (origen < 1 || origen > 6);

            do {
                cout << "        \033[1;35m-> Unidad de destino (1-6): \033[0m";
                cin >> destino;
                if (destino < 1 || destino > 6) cout << "        \033[1;31m[ERROR] Opcion invalida (1 a 6).\033[0m\n";
            } while (destino < 1 || destino > 6);

            do {
                cout << "        \033[1;35m-> Ingrese el valor a convertir: \033[0m";
                cin >> valor;
                if (valor < 0) cout << "        \033[1;31m[ERROR] La masa no puede ser negativa.\033[0m\n";
            } while (valor < 0);

            if (origen == 1) nombreOrigen = "Toneladas";
            else if (origen == 2) nombreOrigen = "Kilogramos";
            else if (origen == 3) nombreOrigen = "Gramos";
            else if (origen == 4) nombreOrigen = "Miligramos";
            else if (origen == 5) nombreOrigen = "Libras";
            else if (origen == 6) nombreOrigen = "Onzas";

            if (destino == 1) nombreDestino = "Toneladas";
            else if (destino == 2) nombreDestino = "Kilogramos";
            else if (destino == 3) nombreDestino = "Gramos";
            else if (destino == 4) nombreDestino = "Miligramos";
            else if (destino == 5) nombreDestino = "Libras";
            else if (destino == 6) nombreDestino = "Onzas";

            // Convertir todo a Gramos (unidad base de masa)
            double enGramos = valor;
            if (origen == 1) enGramos = valor * 1000000.0;     // Ton a g
            else if (origen == 2) enGramos = valor * 1000.0;   // kg a g
            else if (origen == 4) enGramos = valor / 1000.0;   // mg a g
            else if (origen == 5) enGramos = valor * 453.592;  // lb a g
            else if (origen == 6) enGramos = valor * 28.3495;  // oz a g

            // Convertir de Gramos a destino
            resultado = enGramos;
            if (destino == 1) resultado = enGramos / 1000000.0;     // g a Ton
            else if (destino == 2) resultado = enGramos / 1000.0;   // g a kg
            else if (destino == 4) resultado = enGramos * 1000.0;   // g a mg
            else if (destino == 5) resultado = enGramos / 453.592;  // g a lb
            else if (destino == 6) resultado = enGramos / 28.3495;  // g a oz

        } 
        // ==========================================
        // CATEGORÍA 3: TIEMPO (Escala completa)
        // ==========================================
        else if (categoria == 3) {
            cout << "\n      \033[1;36m---------------------------------------------------------\033[0m\n";
            cout << "      \033[1;34mCONVERSION \033[1;33mDE \033[1;31mTIEMPO (ESCALA COMPLETA)             \033[0m\n";
            cout << "      \033[1;36m---------------------------------------------------------\033[0m\n";
            cout << "        [1] Anios              [2] Dias\n";
            cout << "        [3] Horas              [4] Minutos\n";
            cout << "        [5] Segundos (SI)      [6] Milisegundos (ms)\n";

            do {
                cout << "        \033[1;35m-> Unidad de origen (1-6): \033[0m";
                cin >> origen;
                if (origen < 1 || origen > 6) cout << "        \033[1;31m[ERROR] Opcion invalida (1 a 6).\033[0m\n";
            } while (origen < 1 || origen > 6);

            do {
                cout << "        \033[1;35m-> Unidad de destino (1-6): \033[0m";
                cin >> destino;
                if (destino < 1 || destino > 6) cout << "        \033[1;31m[ERROR] Opcion invalida (1 a 6).\033[0m\n";
            } while (destino < 1 || destino > 6);

            do {
                cout << "        \033[1;35m-> Ingrese el valor a convertir: \033[0m";
                cin >> valor;
                if (valor < 0) cout << "        \033[1;31m[ERROR] El tiempo no puede ser negativo.\033[0m\n";
            } while (valor < 0);

            if (origen == 1) nombreOrigen = "Anios";
            else if (origen == 2) nombreOrigen = "Dias";
            else if (origen == 3) nombreOrigen = "Horas";
            else if (origen == 4) nombreOrigen = "Minutos";
            else if (origen == 5) nombreOrigen = "Segundos";
            else if (origen == 6) nombreOrigen = "Milisegundos";

            if (destino == 1) nombreDestino = "Anios";
            else if (destino == 2) nombreDestino = "Dias";
            else if (destino == 3) nombreDestino = "Horas";
            else if (destino == 4) nombreDestino = "Minutos";
            else if (destino == 5) nombreDestino = "Segundos";
            else if (destino == 6) nombreDestino = "Milisegundos";

            // Convertir todo a Segundos (unidad base de tiempo)
            double enSegundos = valor;
            if (origen == 1) enSegundos = valor * 31536000.0;   // Años a s (365 días)
            else if (origen == 2) enSegundos = valor * 86400.0;   // Días a s
            else if (origen == 3) enSegundos = valor * 3600.0;    // Horas a s
            else if (origen == 4) enSegundos = valor * 60.0;      // Min a s
            else if (origen == 6) enSegundos = valor / 1000.0;    // ms a s

            // Convertir de Segundos a destino
            resultado = enSegundos;
            if (destino == 1) resultado = enSegundos / 31536000.0;   // s a Años
            else if (destino == 2) resultado = enSegundos / 86400.0;   // s a Días
            else if (destino == 3) resultado = enSegundos / 3600.0;    // s a Horas
            else if (destino == 4) resultado = enSegundos / 60.0;      // s a Min
            else if (destino == 6) resultado = enSegundos * 1000.0;    // s a ms
        }
        // ==========================================
        // CATEGORÍA 4: TEMPERATURA
        // ==========================================
        else if (categoria == 4) {
            cout << "\n      \033[1;36m---------------------------------------------------------\033[0m\n";
            cout << "      \033[1;34mCONVERSION \033[1;33mDE \033[1;31mTEMPERATURA                      \033[0m\n";
            cout << "      \033[1;36m---------------------------------------------------------\033[0m\n";
            cout << "        [1] Celsius (°C)       [2] Fahrenheit (°F)\n";
            cout << "        [3] Kelvin (K - SI)\n";

            do {
                cout << "        \033[1;35m-> Unidad de origen (1-3): \033[0m";
                cin >> origen;
                if (origen < 1 || origen > 3) cout << "        \033[1;31m[ERROR] Opcion invalida (1 a 3).\033[0m\n";
            } while (origen < 1 || origen > 3);

            do {
                cout << "        \033[1;35m-> Unidad de destino (1-3): \033[0m";
                cin >> destino;
                if (destino < 1 || destino > 3) cout << "        \033[1;31m[ERROR] Opcion invalida (1 a 3).\033[0m\n";
            } while (destino < 1 || destino > 3);

            do {
                cout << "        \033[1;35m-> Ingrese el valor a convertir: \033[0m";
                cin >> valor;
            } while (false);

            if (origen == 1) nombreOrigen = "Celsius";
            else if (origen == 2) nombreOrigen = "Fahrenheit";
            else if (origen == 3) nombreOrigen = "Kelvin";

            if (destino == 1) nombreDestino = "Celsius";
            else if (destino == 2) nombreDestino = "Fahrenheit";
            else if (destino == 3) nombreDestino = "Kelvin";

            // Convertir origen a Celsius primero
            double enCelsius = valor;
            if (origen == 2) enCelsius = (valor - 32.0) * 5.0 / 9.0;
            else if (origen == 3) enCelsius = valor - 273.15;

            // Convertir de Celsius a destino
            resultado = enCelsius;
            if (destino == 2) resultado = (enCelsius * 9.0 / 5.0) + 32.0;
            else if (destino == 3) resultado = enCelsius + 273.15;
        }

        // 4. Mostrar el resultado detallado con las unidades exactas de origen y destino
        cout << "\n      \033[1;36m=========================================================\033[0m\n";
        cout << "           \033[1;43m\033[1;30m ¡RESULTADO DE LA CONVERSION EXITOSA! \033[0m\n";
        cout << "      \033[1;32m>>> " << valor << " " << nombreOrigen << " equivalen a " << resultado << " " << nombreDestino << " <<<\033[0m\n";
        cout << "      \033[1;36m=========================================================\033[0m\n";

        // 5. Preguntar claramente si desea repetir el programa
        cout << "\n        \033[1;33mDesea realizar otra conversion? (s/n): \033[0m";
        cin >> repetir;

    } while (repetir == 's' || repetir == 'S');

    system("cls");
    cout << "\n\n\n           \033[1;35m¡Gracias por usar el conversor de escalas! Hasta luego.\033[0m\n\n\n";
    system("pause > nul");

    return 0;
}
