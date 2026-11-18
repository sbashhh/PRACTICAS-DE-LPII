/* Conversor de divisas. Lea al inicio la tasa del dólar y la del euro en bolívares (mayores que 0). 
Muestre un menú: 1. $ a Bs, 2. Bs a $, 3.€ a Bs, 4. Bs a €, 5. Salir. Cada conversión es una función que recibe el monto y la tasa y devuelve el resultado. 
Muestre los montos condos decimales; use al menos dos secuencias de escape y un operador ternario.*/
#include <iostream>
#include <iomanip>
using namespace std;

float converDolarBs (float d, float bcv){
return d*bcv;
}


float converBsDolar (float b, float bcv){
return b/bcv;
}

float converEuBs (float e, float bcvEu){
return e*bcvEu;
}

float converBsEu (float b, float bcvEu){
return b/bcvEu;
}


int main(){
 float tasaBsBCV, tasaEuBCV, dolares, bolivares, euros, conversion;
 int opcion;
 char opcion2 = 's';
 

    cout << "Ingresa la tasa BCV 'DOLAR' del dia(>0): ";
    while ( !(cin >> tasaBsBCV) || tasaBsBCV <= 0){
        cout << "Error... Intente de nuevo";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Ingresa la tasa BCV 'EURO' del dia (>0): ";
    while ( !(cin >> tasaEuBCV) || (tasaEuBCV <= 0) ){
        cout << "Error... Intente de nuevo";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    
while (opcion2 == 's' || opcion2 == 'S'){

    cout << "\n=================QUE DESEAS CONVERTIR=================\n";
    cout << "1. Dolares a Bolivares.\n";
    cout << "2. Bolivares a Dolares.\n";
    cout << "3. Euros a Bolivares.\n";
    cout << "5. Bolivares a Euros.\n";
    cout << "=====================================================\n"; cin >> opcion;

    switch (opcion){

        case 1:
        cout << "Ingresa la cantidad de dolares: "; cin >> dolares;
        conversion = converDolarBs (dolares, tasaBsBCV);
        cout << "Su conversion es: " << fixed << setprecision(2) << conversion << "Bs\n";
        break;

        case 2:
        cout << "Ingresa la cantidad de bolivares: "; cin >> bolivares;
        conversion = converBsDolar (bolivares, tasaBsBCV);
        cout << "Su conversion es: " << fixed << setprecision(2) << conversion << "$\n";
        break;

        case 3:
        cout << "Ingresa la cantidad de euros: "; cin >> euros;
        conversion = converEuBs (euros, tasaEuBCV);
        cout << "Su conversion es: " << fixed << setprecision(2) << conversion << "Bs\n";
        break;

        case 4:
        cout << "Ingresa la cantidad de bolivares: "; cin >> bolivares;
        conversion = converBsEu (bolivares, tasaEuBCV);
        cout << "Su conversion es: " << fixed << setprecision(2) << conversion << " Euros\n";
        break;
        
        case 5:
        cout << "Has salido exitosamente...\n";
        break;

        default:
        cout << "Opcion invalida... Vuelvelo a intentar. ";

    }

    cout << "Deseas volver a convertir (S/N)?: "; cin >> opcion2;
    opcion2 = (opcion2 == 's' || opcion2 == 'S')? 's' : 'n';

} 

return 0;

}