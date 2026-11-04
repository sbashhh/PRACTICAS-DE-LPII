/* Realice un programa que permita el calculo de la serie Fibonacci hasta una interaccion que el usuario ingrese */
#include <iostream>
using namespace std;
int main (){
int n, i;
int numeroAnterior = 0;
int numeroAnterior2 = 1;
int resultado;

cout << "Ingrese las interacciones que desee: "; cin >> n;

for (i = 1; i <= n; i++){

resultado = numeroAnterior + numeroAnterior2;

cout << numeroAnterior << " - " << numeroAnterior2 << "\n";
	
numeroAnterior = numeroAnterior2;
numeroAnterior2 = resultado;	
	
}
	
	return 0;
	
	
}
