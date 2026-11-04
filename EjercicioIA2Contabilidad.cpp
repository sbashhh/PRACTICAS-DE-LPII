/* En contabilidad cada asiento debe cumplir la partida doble, la suma del debe es igual a la suma del haber.
Escriba un programa que registre los movimientos de un asiento (codigo de cuenta de uno a 9.999, d o h y monto mayor que 0)
hasta que se escriba el codigo 0. Al terminar muestre el total del debe, haber y si el asiento cuadra; si no cuadra
indique cuanto falta y en que lado. Un asiento necesita al menos dos movimientos. */

#include <iostream>

using namespace std;

int main() {
    int codigo;
    char tipo;
    double monto;
    
    double totalDebe = 0;
    double totalHaber = 0;
    int cantidadMovimientos = 0;

    // --- INTERFAZ DE BIENVENIDA ---
    cout << "========================================\n";
    cout << "     REGISTRO DE ASIENTOS CONTABLES     \n";
    cout << "========================================\n";
    cout << " Instrucciones:\n";
    cout << " -> Ingresa al menos 2 movimientos.\n";
    cout << " -> Escribe 0 en el codigo para terminar.\n";
    cout << "========================================\n\n";

    // Bucle para pedir los movimientos uno por uno
    while (true) {
        cout << "----------------------------------------\n";
        cout << " MOVIMIENTO NUMERO " << (cantidadMovimientos + 1) << "\n";
        cout << "----------------------------------------\n";
        
        // 1. Pedir Codigo
        cout << " Codigo de cuenta (1 al 9999) o 0 para salir: ";
        cin >> codigo;

        // Si pone 0, verificamos si ya puede salir
        if (codigo == 0) {
            if (cantidadMovimientos < 2) {
                cout << "\n [!] AVISO: Faltan movimientos. Necesitas al menos 2 para finalizar.\n\n";
                continue; // Vuelve a empezar el ciclo para pedir otro movimiento
            } else {
                break; // Sale del bucle porque ya cumplio el minimo
            }
        }

        // 2. Pedir Tipo
        cout << " Tipo ('d' para Debe, 'h' para Haber): ";
        cin >> tipo;

        // 3. Pedir Monto
        cout << " Monto en dinero: $";
        cin >> monto;

        // Sumar segun la opcion elegida
        if (tipo == 'd' || tipo == 'D') {
            totalDebe = totalDebe + monto;
            cout << " --> Guardado exitosamente en el DEBE.\n";
        } else if (tipo == 'h' || tipo == 'H') {
            totalHaber = totalHaber + monto;
            cout << " --> Guardado exitosamente en el HABER.\n";
        } else {
            cout << " [!] Letra incorrecta, este movimiento no se sumo. Intentalo de nuevo.\n";
            continue; // Si escribe mal la letra, repetimos este movimiento
        }

        cantidadMovimientos++;
    }

    // --- PANTALLA DE RESULTADOS ESTETICA ---
    cout << "\n\n========================================\n";
    cout << "        ESTADO FINAL DEL ASIENTO        \n";
    cout << "========================================\n";
    cout << " Total acumulado en el DEBE:  $" << totalDebe << "\n";
    cout << " Total acumulado en el HABER: $" << totalHaber << "\n";
    cout << "----------------------------------------\n";

    // Comprobacion de la partida doble
    if (totalDebe == totalHaber) {
        cout << " [OK] EXCELENTE: El asiento CUADRA perfecto.\n";
    } else {
        cout << " [X] CUIDADO: El asiento NO cuadra.\n";
        
        if (totalDebe > totalHaber) {
            double falta = totalDebe - totalHaber;
            cout << " --> Falta registrar: $" << falta << " en el HABER.\n";
        } else {
            double falta = totalHaber - totalDebe;
            cout << " --> Falta registrar: $" << falta << " en el DEBE.\n";
        }
    }
    cout << "========================================\n";
    cout << " Programa finalizado con exito.\n";

    return 0;
}
