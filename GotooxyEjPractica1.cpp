/* Realice un programa que permita al usuario ingresar un número y se muestre el día de la semana correspondiente graficada con gotoxy,
valide la entrada y usa swicht*/
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

void L (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){

    for (i = 0; i < n; i++){

        if (j == 0 || i == n - 1){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void A (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){

    for (i = 0; i < n; i++){

        if (j == 0 || j == n-1 || i == 0 || i == n / 2){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void B (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){
    
    for (i = 0; i < n; i++){

        if (j == 0 || j == n - 1 || i == 0 || i == n / 2 || i == n - 1){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void C (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){
    
    for (i = 0; i < n; i++){

        if (i == 0 || j == 0 || i == n - 1){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void D (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){
    
    for (i = 0; i < n; i++){

        if (j == 0 || i == 0 || i == n - 1 || j == n - 1){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void E (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){
    
    for (i = 0; i < n; i++){

        if (j == 0 || i == n - 1 || i == 0 || i == n / 2){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void G (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){
    
    for (i = 0; i < n; i++){

        if (i == 0 || j == 0 || i == n - 1 || (j == n - 1 && i >= n / 2) || i == n / 2){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void I (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){
    
    for (i = 0; i < n; i++){

        if (j == n / 2){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void J (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){
    
    for (i = 0; i < n; i++){

        if (i == 0 || j == n / 2 || (i == n - 1 && j <= n / 2)){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void M (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){
    
    for (i = 0; i < n; i++){

        if (j == 0 || j == n - 1 || (i == j && i <= n / 2) || (i + j == n - 1 && i <= n / 2)){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void N (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){
    
    for (i = 0; i < n; i++){

        if (j == 0 || j == n - 1 || i == j){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void O (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){
    
    for (i = 0; i < n; i++){

        if (i == 0 || j == 0 || j == n - 1 || i == n - 1){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void R (int x, int y, int n){
int i, j;
for (j = 0; j < n; j++){

    for (i = 0; i < n; i++){

        if (j == 0 || j == n-1 || i == 0 || i == n / 2){
        gotoxy (x+j, y+i);
        cout << "*";
    }
}
}
}

void S (int x, int y, int n){
    int i, j;
    for (j = 0; j < n; j++){
        for (i = 0; i < n; i++){
            if (i == 0 && j <= n / 2 || j == 0 && i <= n / 2 || i == n / 2 || j == n - 1 && i >= n / 2 || i == n - 1 && j <= n / 2){
                gotoxy (x + j, y + i);
                cout << "*";
            }
        }
    }
}

void T (int x, int y, int n){
    int i, j;
    for (j = 0; j < n; j++){
        for (i = 0; i < n; i++){
            if (i == 0 || j == n / 2){
                gotoxy (x + j, y + i);
                cout << "*";
            }
        }
    }
}

void U (int x, int y, int n){
    int i, j;
    for (j = 0; j < n; j++){
        for (i = 0; i < n; i++){
            if (j == 0 || j == n - 1 || i == n - 1){
                gotoxy (x + j, y + i);
                cout << "*";
            }
        }
    }
}

void V (int x, int y, int n){
    int i, j;
    for (j = 0; j < n; j++){
        for (i = 0; i < n; i++){
            if ((i == j && i <= n / 2) || (i + j == n - 1 && i <= n / 2)){
            gotoxy (x + j, y + i);
            cout << "*";   
            }
            }
        }
}


int main (){
int dia;

cout << "Ingresa el dia de la semana (1-7): ";
while (!(cin>>dia) || dia < 1 || dia > 7){
    cout << "Error... Vuelvelo a intentar: ";
    cin.clear(); 
    cin.ignore(10000, '\n');
}

switch (dia){

case 1: // LUNES
        L (5, 5, 6);
        U (13, 5, 6);
        N (21, 5, 6);
        E (29, 5, 6);
        S (37, 5, 6);
        break;

    case 2: // MARTES
        M (5, 5, 6);
        A (13, 5, 6);
        R (21, 5, 6);
        T (29, 5, 6);
        E (37, 5, 6);
        S (45, 5, 6);
        break;

    case 3: // MIERCOLES
        M (5, 5, 6);
        I (13, 5, 6);
        E (21, 5, 6);
        R (29, 5, 6);
        C (37, 5, 6);
        O (45, 5, 6);
        L (53, 5, 6);
        E (61, 5, 6);
        S (69, 5, 6);
        break;

    case 4: // JUEVES
        J (5, 5, 6);
        U (13, 5, 6);
        E (21, 5, 6);
        V (29, 5, 6);
        E (37, 5, 6);
        S (45, 5, 6);
        break;

    case 5: // VIERNES
        V (5, 5, 6);
        I (13, 5, 6);
        E (21, 5, 6);
        R (29, 5, 6);
        N (37, 5, 6);
        E (45, 5, 6);
        S (53, 5, 6);
        break;

    case 6: // SABADO
        S (5, 5, 6);
        A (13, 5, 6);
        B (21, 5, 6);
        A (29, 5, 6);
        D (37, 5, 6);
        O (45, 5, 6);
        break;

    case 7: // DOMINGO
        D (5, 5, 6);
        O (13, 5, 6);
        M (21, 5, 6);
        I (29, 5, 6);
        N (37, 5, 6);
        G (45, 5, 6);
        O (53, 5, 6);
        break;
}

return 0;

}