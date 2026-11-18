/* Lea el ancho (20 a 70) y el alto (5 a 20) de un marco y dibújelo centrado en la pantalla con = en los bordes horizontales 
y | en los verticales. Escriba el título MENU PRINCIPAL centrado sobre el borde superior */
#include <iostream>
#include <windows.h> 
using namespace std;

 void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
}  

void techoArriba (int ancho, int alto, int x, int y) {
 int i, j, n;
 n = ancho;

    for (j = 0; j < n; j++){
        for (i = 0; i < n; i++){
            if(i == 0){
                gotoxy (x + j, y);
                cout << "=";
            }
        }
    }
}

void pisoAbajo (int ancho, int alto, int x, int y) {
 int i, j, n;
 n = ancho;

    for (j = 0; j < n; j++){
        for (i = 0; i < n; i++){
            if(i == 0){
                gotoxy (x + j, y + alto - 1);
                cout << "=";
            }
        }
    }
}

void horizontalIzquierda (int ancho, int alto, int x, int y) {
 int i, j, n;
 n = alto;

    for (j = 0; j < n; j++){
        for (i = 0; i < n; i++){
            if(i == 0){
                gotoxy (x, y + j);
                cout << "|";
            }
        }
    }
}

void horizontalDerecha (int ancho, int alto, int x, int y) {
 int i, j, n;
 n = alto;

    for (j = 0; j < n; j++){
        for (i = 0; i < n; i++){
            if(i == 0){
                gotoxy (x + ancho - 1, y + j);
                cout << "|";
            }
        }
    }
}

int main(){
    int ancho, alto;
    
    cout << "Ingrese el ancho del marco (20 a 70): ";
    while (!(cin >> ancho) || ancho < 20 || ancho > 70) {
        cout << "Error... Ingrese un ancho valido (20 a 70): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }


    cout << "Ingrese el alto del marco (5 a 20): ";
    while (!(cin >> alto) || alto < 5 || alto > 20) {
        cout << "Error... Ingrese un alto valido (5 a 20): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }


    int x = (80 - ancho) / 2;
    int y = (25 - alto) / 2;


    gotoxy(x + (ancho / 2) - 7, y - 1);
    cout << "MENU PRINCIPAL";


    techoArriba(ancho, alto, x, y);
    pisoAbajo(ancho, alto, x, y);
    horizontalIzquierda(ancho, alto, x, y);
    horizontalDerecha(ancho, alto, x, y);


    gotoxy(0, y + alto + 2);
    
    return 0;
}