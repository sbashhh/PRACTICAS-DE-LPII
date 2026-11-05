/* Realice un programa que permita calcular el area de un circulo, un cuadrado, un rectangulo y un triangulo equilatero, procure usar al menos
3 secuencias de escape para dar formato a sus mensajes. Considere que su menu de opciones sea facil de entender y agradable a la vista*/
#include <iostream>
using namespace std;
float areaCirculo (float radio){
float pi = 3.14;
return (radio*radio)*pi;
}

float areaCuadrado (float base){
return base*base;
}

float areaRectangulo (float base, float altura){
return base*altura;
}

int main (){
int opcion, opcion2;
float r, b, h, area;

	cout << "=====================QUE AREA DESEA CALCULAR:===========\n";
	cout << "---------------------1. Circulo-------------------------\n";
	cout << "---------------------2. Cuadrado------------------------\n";
	cout << "---------------------3. Rectangulo----------------------\n";
	cout << "---------------------4. Triangulo Equilatero------------\n";
	cout << "---------------------5. Salir---------------------------\n";
	cout << "========================================================\n";
	cin >> opcion;
	
	while (opcion > 5 || opcion < 1){
		
		cout << "Opcion invalida.... Ingrese otra vez: "; cin >> opcion;
		
	}
	
dowhile (opcion2 == 's' || opcion2 == 'S'){


	
	switch (opcion){
		
		case 1:
			
			cout << "Ingresa el radio de su circulo: "; cin >> r;
			
			while (r >= 0){
				cout << "Opcion invalida.... Ingrese otra vez: "; cin >> r;
			}
			area = areaCirculo (r);
			cout << "Su area es de: " << area << "\n";
			
		break;
			
		case 2:
			
			cout << "Ingresa la base de su cuadrado: "; cin >> b;
			
			while (b >= 0){
				cout << "Opcion invalida.... Ingrese otra vez: "; cin >> b;
			}
			area = areaCuadrado (b);
			cout << "Su area es de: " << area << "\n";
			
		break;
		
		case 3:
			
			cout << "Ingresa la base de su rectangulo: "; cin >> b;
			while (b >= 0){
			    cout << "Opcion invalida.... Ingrese otra vez: "; cin >> b;
			}
			cout << "Ingresa la altura de su rectangulo: "; cin >> h;
			while (h >= 0){
				cout << "Opcion invalida.... Ingrese otra vez: "; cin >> b;
			}
			area = areaRectangulo (b, h);
			cout << "Su area es de: " << area << "\n";
			
		break;
		
		case 4:
			
			cout << "Ingresa la base de su traingulo equilatero: "; cin >> b;
			while (b >= 0){
			    cout << "Opcion invalida.... Ingrese otra vez: "; cin >> b;
			}
			cout << "Ingresa la altura de su traingulo equilatero: "; cin >> h;
			while (h >= 0){
				cout << "Opcion invalida.... Ingrese otra vez: "; cin >> b;
			}
			area = areaRectangulo (b, h) / 2; 
			cout << "Su area es de: " << area << "\n";
			
		break;
			
		case 5:
			
			cout << "Salida existosa!!!";
			
		break;
			
		default:
			
		    cout << "Su opcion es incorrecta\n";
		    
		break;
		
	}
	
cout << "Deseas volver a calcular? (S/s): "; cin >> opcion2;
	
}
	
return 0;

}