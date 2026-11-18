#include <iostream>

using namespace std;

int main() {
    int num;
    int i;

    cout << "Ingresa un numero entero: ";
    cin >> num;

    if (num <= 1) {
        cout << num << " no es un numero primo." << endl;
    } else {
        // El ciclo for busca un divisor exacto
        for (i = 2; i <= num / 2; i++) {
            if (num % i == 0) {
                break; // Si encuentra un divisor, rompe el ciclo prematuramente
            }
        }

        // Si el ciclo terminó por el 'break', 'i' será menor o igual a num/2
        // Si el ciclo terminó de forma natural, 'i' superará a num/2
        if (i > num / 2) {
            cout << num << " es un numero primo." << endl;
        } else {
            cout << num << " no es un numero primo." << endl;
        }
    }

    return 0;
}