/* Realice un programa que permita registrar los pesos de estudiantes de una seccion de 23. Calcule el promedio general de pesos y usando de referencia
su programa de IMC. Calcule en que rango esta cada estudiante.*/
#include <iostream>
using namespace std;
int main(){
float altura[22];
float peso[22];
float altura_kg[22];
float IMC[22];
int i;
	
for (i = 0; i < 26; i++){

cout << "Ingresa tu altura en CM: "; cin >> altura[i];

while (altura[i] < 0){
cout << "Estatura invalida... Vuelvelo a intentar.";
cout << "Ingresa tu altura en CM: "; cin >> altura[i];
}

cout << "Ingresa tu peso en Kg: "; cin >> peso[i];

while (peso[i] < 0){
cout << "Peso invalido... Vuelvelo a intentar.";
cout << "Ingresa tu altura en CM: "; cin >> peso[i];
}

altura_kg[i] = altura[i] / 100;
IMC[i] = (peso[i] / (altura_kg[i] * altura_kg[i]));

if (IMC[i] < 16.00){
    cout << "El estudiante N" << i + 1 << " Tiene Desgladez severa\n";
} else if (IMC[i] <= 16.99){
    cout << "El estudiante N" << i + 1 << " Tiene Delgadez moderada\n";
} else if (IMC[i] <= 18.49){
    cout << "El estudiante N" << i + 1 << "Tiene Peso aceptable\n";
} else if (IMC[i] <= 24.99){
    cout << "El estudiante N" << i + 1 << " Tiene Peso normal\n";
} else if (IMC[i] <= 29.99){
    cout << "El estudiante N" << i + 1 << " Tiene Sobrepeso\n";
} else if (IMC[i] <= 34.99){
    cout << "El estudiante N" << i + 1 << " Tiene Obedidad TIPO I\n";
} else if (IMC[i] <= 40.00){
    cout << "El estudiante N" << i + 1 << " Tiene Obedidad TIPO II\n";
} else {
    cout << "El estudiante N" << i + 1 << " Tiene Obedidad TIPO III\n";
}

}

return 0;

}
