/* Realice un programa que permita al usuario registrar 10 numeros y muestre cuantas veces se repite el numero 5, cual es el mayor y cual es el menor */
#include <iostream>
using namespace std;
int main (){
int i = 0;
int mayor, menor;
int cont = 0;
int numeros[9];

for (i = 0; i < 10; i++){

	cout << "Ingrese un numero para el arreglo N:" << i+1 << ": "; cin >> numeros[i];
	
	if (i == 0) {
        mayor = numeros[i];
        menor = numeros[i];
    } else {
        if (numeros[i] > mayor) {
        mayor = numeros[i];
        }
        if (numeros[i] < menor) {
        menor = numeros[i];
        }
    }

	
	if (numeros[i] == 5){
		cont++;
	}
	
}

 cout << "El numero mayor es: " << mayor << " y el numero menor es: " << menor << " y el numero 5 se repite: " << cont << " veces\n";  
 
 return 0;

}
