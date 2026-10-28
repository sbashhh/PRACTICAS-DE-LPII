/* Realice un programa que permita separar en cifras numeros entre 10 y 999.999, ademas de separar en cifras y mostrarlas
 en pantallas su programa debe ser capaz de identificar si el numero ingresado es par, impar, primo o perfecto */
#include <iostream>
using namespace std;
int main (){
int numero;
int unidad, decena, centena, unidaddemil, decenademil, centenademil;

cout << "Ingresa un numero (10-999.999): "; cin >> numero;

while (numero < 10 || numero > 999999){
	cout << "Error... El numero ingresado es invalido. Intentelo de nuevo.\n";
	cout << "Ingresa un numero (10-999.999): "; cin >> numero;
}

if (numero > 99999){
	unidad = numero % 10;
	decena = (numero / 10) % 10;
	centena = (numero / 100) % 10;
	unidaddemil = (numero / 1000) % 10;
	decenademil = (numero / 10000) % 10;
	centenademil = (numero / 100000) % 10;
	
	cout << "Las cifras del numero son:\n";
	cout << "U: " << unidad << "\n";
	cout << "D: " << decena << "\n";
	cout << "C: " << centena << "\n";
	cout << "UM: " << unidaddemil << "\n";
	cout << "DM: " << decenademil << "\n";
	cout << "DM: " << centenademil << "\n";
	
} else if (numero > 9999){
	unidad = numero % 10;
	decena = (numero / 10) % 10;
	centena = (numero / 100) % 10;
	unidaddemil = (numero / 1000) % 10;
	decenademil = (numero / 10000) % 10;
	
	cout << "Las cifras del numero son:\n";
	cout << "U: " << unidad << "\n";
	cout << "D: " << decena << "\n";
	cout << "C: " << centena << "\n";
	cout << "UM: " << unidaddemil << "\n";
	cout << "DM: " << decenademil << "\n";
	
} else if (numero > 999){
	unidad = numero % 10;
	decena = (numero / 10) % 10;
	centena = (numero / 100) % 10;
	unidaddemil = (numero / 1000) % 10;
	
	cout << "Las cifras del numero son:\n";
	cout << "U: " << unidad << "\n";
	cout << "D: " << decena << "\n";
	cout << "C: " << centena << "\n";
	cout << "UM: " << unidaddemil << "\n";
	
} else if (numero > 99){
	unidad = numero % 10;
	decena = (numero / 10) % 10;
	centena = (numero / 100) % 10;
	
	cout << "Las cifras del numero son:\n";
	cout << "U: " << unidad << "\n";
	cout << "D: " << decena << "\n";
	cout << "C: " << centena << "\n";
	
} else {
	unidad = numero % 10;
	decena = (numero / 10) % 10;
	
	cout << "Las cifras del numero son:\n";
	cout << "U: " << unidad << "\n";
	cout << "D: " << decena << "\n";
	
}

if (numero % 2 == 0){
cout << "Su numero es par\n";
} else {
cout << "Su numero es impar\n";
}


return 0;

}
	
	
	
	
	
