/* Realice un programa que reciba la estatura de un individuo en CM y su peso en kilogramos y calcule el IMC con la clasificacion de la OMS
(1.Desgladez severa < 16; 2. Delgadez moderada  16 - 16.99; 3. Peso aceptable (17 - 18.49); 3. Peso normal (18.5 - 24.99); 4. Sobrepeso (25 - 29.99)
5. Obedidad TIPO I (30 - 34.99); 5. Obesidad TIPO II (35 - 40); 5. Obesidad TIPO III 40>. VALIDE LA ENTRADA*/
#include <iostream>
using namespace std;
int main(){
float altura, peso;
float altura_kg = 0;
float IMC = 0;
int opcion = 0;

while (opcion != 1){

cout << "Ingresa tu altura en CM: "; cin >> altura;

while (altura < 0){
cout << "Estatura invalida... Vuelvelo a intentar.";
cout << "Ingresa tu altura en CM: "; cin >> altura;
}

cout << "Ingresa tu peso en Kg: "; cin >> peso;

while (peso < 0){
cout << "Peso invalido... Vuelvelo a intentar.";
cout << "Ingresa tu altura en CM: "; cin >> peso;
}

altura_kg = altura / 100;
IMC = (peso / (altura_kg * altura_kg));

if (IMC < 16.00){
    cout << "Tienes Desgladez severa\n";
} else if (IMC <= 16.99){
    cout << "Tienes Delgadez moderada\n";
} else if (IMC <= 18.49){
    cout << "Tienes Peso aceptable\n";
} else if (IMC <= 24.99){
    cout << "Tienes Peso normal\n";
} else if (IMC <= 29.99){
    cout << "Tienes Sobrepeso\n";
} else if (IMC <= 34.99){
    cout << "Tienes Obedidad TIPO I\n";
} else if (IMC <= 40.00){
    cout << "Tienes Obedidad TIPO II\n";
} else {
    cout << "Tienes Obedidad TIPO III\n";
}

cout << "Deseas volver a calcular?\n";
cout << "Presiona 0 si deseas volver a calcular.\n";
cout << "Presiona 1 si deseas cerrar.\n"; cin >> opcion;

}
return 0;
}