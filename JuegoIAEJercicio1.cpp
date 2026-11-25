/* Partiendo del codigo entregado en clase completelo para crear un minijuego con un personaje que puede ser de un caracter de su eleccion
que se mueva dentro del marco creado y que si choca con los bordes o con los obstaculos se muestre en pantalla "PERDISTE",por el contrario
si llega a la meta muestre "GANASTE", la meta debe estar randonmizada, es decir en cada intento debe estar en una posicion diferente y debe
haber como minimo 3 obstaculos */
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cmath>

using namespace std;

// Colores nativos de la API de Windows (compatible con Dev-C++ / MinGW)
const int COLOR_DEFECTO  = 7;
const int COLOR_AZUL     = 9;
const int COLOR_VERDE    = 10;
const int COLOR_CIAN     = 11;
const int COLOR_ROJO     = 12;
const int COLOR_MAGENTA  = 13;
const int COLOR_AMARILLO = 14;
const int COLOR_BLANCO   = 15;
const int COLOR_GRIS     = 8;

const int MAX_OBS_FIJOS = 8;
const int MAX_BARRERAS  = 14;
const int MAX_MOVILES   = 5;
const int TOTAL_NIVELES = 5;

struct ConfigNivel {
    int numero;
    const char* nombre;
    int obsFijos;
    int barreras;
    int moviles;
    DWORD intervaloMovilMs;
    double tiempoLimite;
};

struct ObstaculoMovil {
    int x, y;
    int vx, vy;
    int minX, maxX, minY, maxY;
    DWORD ultimoPaso;
};

struct Barrera {
    int x, y;
    int ancho, alto;
    bool horizontal;
};

struct Estela {
    int x, y;
    DWORD creadaEn;
    bool activa;
};

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ocultarCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void limpiarPantalla() {
    setColor(COLOR_DEFECTO);
    system("cls");
}

ConfigNivel obtenerNivel(int nivel) {
    switch (nivel) {
        case 1: { ConfigNivel n = {1, "Iniciacion",      3,  4, 1, 180, 45.0}; return n; }
        case 2: { ConfigNivel n = {2, "Desvio",          4,  6, 2, 150, 40.0}; return n; }
        case 3: { ConfigNivel n = {3, "Interseccion",    5,  8, 3, 130, 35.0}; return n; }
        case 4: { ConfigNivel n = {4, "Alta Tension",    6, 10, 3, 105, 30.0}; return n; }
        default:{ ConfigNivel n = {5, "Laberinto Final", 7, 12, 4,  90, 28.0}; return n; }
    }
}

// Revisa si (px, py) toca algun bloque fijo 2x2
bool esObstaculoFijo(int px, int py, const int obsX[], const int obsY[], int numObs) {
    for (int k = 0; k < numObs; k++) {
        if (px >= obsX[k] && px <= obsX[k] + 1 &&
            py >= obsY[k] && py <= obsY[k] + 1) {
            return true;
        }
    }
    return false;
}

// Revisa si (px, py) toca algun obstaculo movil 2x2
bool esObstaculoMovil(int px, int py, const ObstaculoMovil mov[], int numMov) {
    for (int k = 0; k < numMov; k++) {
        if (px >= mov[k].x && px <= mov[k].x + 1 &&
            py >= mov[k].y && py <= mov[k].y + 1) {
            return true;
        }
    }
    return false;
}

// Revisa si (px, py) toca alguna barrera
bool esBarrera(int px, int py, const Barrera barreras[], int numBarreras) {
    for (int k = 0; k < numBarreras; k++) {
        if (px >= barreras[k].x && px < barreras[k].x + barreras[k].ancho &&
            py >= barreras[k].y && py < barreras[k].y + barreras[k].alto) {
            return true;
        }
    }
    return false;
}

void dibujarBloqueSombreado(int ox, int oy, int colorPrincipal, int colorSombra) {
    setColor(colorPrincipal);
    gotoxy(ox, oy);     cout << "\xDB\xDB";
    setColor(colorSombra);
    gotoxy(ox, oy + 1); cout << "\xB2\xB2";
    setColor(COLOR_DEFECTO);
}

void borrarBloque2x2(int ox, int oy) {
    gotoxy(ox, oy);     cout << "  ";
    gotoxy(ox, oy + 1); cout << "  ";
}

void dibujarBarrera(const Barrera& b, int offsetY) {
    setColor(COLOR_MAGENTA);
    if (b.horizontal) {
        for (int i = 0; i < b.ancho; i++) {
            gotoxy(b.x + i, offsetY + b.y);
            cout << "=";
        }
    } else {
        for (int j = 0; j < b.alto; j++) {
            gotoxy(b.x, offsetY + b.y + j);
            cout << "|";
        }
    }
    setColor(COLOR_DEFECTO);
}

void efectoImpacto(int x, int y, int offsetY) {
    const char chispas[4] = {'*', '+', 'x', '#'};
    for (int i = 0; i < 6; i++) {
        setColor((i % 2 == 0) ? COLOR_ROJO : COLOR_AMARILLO);
        gotoxy(x, y + offsetY);
        cout << chispas[i % 4];
        Sleep(45);
    }
    setColor(COLOR_DEFECTO);
}

// Retorna: 1 = Un jugador, 2 = Dos jugadores, 0 = Salir
int mostrarMenuPrincipal(int Esc) {
    limpiarPantalla();

    const int left = 4;
    const int width = 56;
    const int top = 2;
    const int height = 20;

    // Marco exterior azul y cian
    setColor(COLOR_AZUL);
    gotoxy(left, top); cout << "\xC9";
    for (int i = 1; i < width - 1; i++) {
        gotoxy(left + i, top);            cout << "\xCD";
        gotoxy(left + i, top + height - 1); cout << "\xCD";
    }
    gotoxy(left + width - 1, top); cout << "\xBB";

    for (int j = 1; j < height - 1; j++) {
        gotoxy(left, top + j);             cout << "\xBA";
        gotoxy(left + width - 1, top + j); cout << "\xBA";
    }
    gotoxy(left, top + height - 1);             cout << "\xC8";
    gotoxy(left + width - 1, top + height - 1); cout << "\xBC";

    // Bloques decorativos con el mismo estilo de los obstaculos
    dibujarBloqueSombreado(left + 3, top + 2, COLOR_ROJO, COLOR_MAGENTA);
    dibujarBloqueSombreado(left + width - 5, top + 2, COLOR_ROJO, COLOR_MAGENTA);
    dibujarBloqueSombreado(left + 3, top + height - 4, COLOR_AMARILLO, COLOR_ROJO);
    dibujarBloqueSombreado(left + width - 5, top + height - 4, COLOR_AMARILLO, COLOR_ROJO);

    // Titulo del juego
    gotoxy(left + 12, top + 2);
    setColor(COLOR_CIAN);
    cout << "=== LABERINTO TACTICO (5 NIVELES) ===";

    gotoxy(left + 14, top + 3);
    setColor(COLOR_MAGENTA);
    cout << "===== BARRERAS & OBSTACULOS =====";

    int opcion = 1; // 1: Un jugador, 2: Dos jugadores, 3: Salir

    while (_kbhit()) _getch();

    while (true) {
        // Opcion 1: Un jugador
        gotoxy(left + 11, top + 7);
        if (opcion == 1) {
            setColor(COLOR_AMARILLO);
            cout << ">> [1] UN JUGADOR       (@ - WASD / Flechas) <<";
        } else {
            setColor(COLOR_BLANCO);
            cout << "   [1] Un Jugador       (@ - WASD / Flechas)   ";
        }

        // Opcion 2: Dos jugadores
        gotoxy(left + 11, top + 9);
        if (opcion == 2) {
            setColor(COLOR_CIAN);
            cout << ">> [2] DOS JUGADORES      (@ WASD  vs  & Flechas) <<";
        } else {
            setColor(COLOR_BLANCO);
            cout << "   [2] Dos Jugadores      (@ WASD  vs  & Flechas)   ";
        }

        // Opcion 3: Salir
        gotoxy(left + 11, top + 11);
        if (opcion == 3) {
            setColor(COLOR_ROJO);
            cout << ">> [3] SALIR            (Cerrar juego)        <<";
        } else {
            setColor(COLOR_GRIS);
            cout << "   [3] Salir            (Cerrar juego)           ";
        }

        // Leyenda de elementos del mapa
        gotoxy(left + 8, top + 14);
        setColor(COLOR_ROJO); cout << "##";
        setColor(COLOR_BLANCO); cout << " Obstaculo   ";
        setColor(COLOR_MAGENTA); cout << "==/||";
        setColor(COLOR_BLANCO); cout << " Barrera   ";
        setColor(COLOR_VERDE); cout << "M";
        setColor(COLOR_BLANCO); cout << " Meta";

        gotoxy(left + 8, top + 16);
        setColor(COLOR_GRIS);
        cout << "Elige 1, 2, 3 o usa W/S / Flechas + ENTER";
        setColor(COLOR_DEFECTO);

        if (GetAsyncKeyState('1') & 0x8000) { Sleep(180); return 1; }
        if (GetAsyncKeyState('2') & 0x8000) { Sleep(180); return 2; }
        if (GetAsyncKeyState('3') & 0x8000 || (GetAsyncKeyState(Esc) & 0x8000)) {
            Sleep(180);
            return 0;
        }

        if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000) {
            opcion--;
            if (opcion < 1) opcion = 3;
            Sleep(150);
        }
        if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) {
            opcion++;
            if (opcion > 3) opcion = 1;
            Sleep(150);
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            Sleep(180);
            return (opcion == 3) ? 0 : opcion;
        }

        Sleep(25);
    }
}

void mostrarPantallaVictoria(int numJugadores, int nivelActual, int ganadorIdx, char simGanador,
                             int pasos, double segundos, int ancho, int alto) {
    limpiarPantalla();
    int cx = (ancho - 52) / 2;
    if (cx < 2) cx = 2;
    int cy = alto / 2 - 5;
    if (cy < 2) cy = 2;

    bool esUltimoNivel = (nivelActual >= TOTAL_NIVELES);

    setColor(COLOR_VERDE);
    gotoxy(cx, cy);      cout << "====================================================";
    gotoxy(cx, cy + 1);  cout << (esUltimoNivel ? "      ***   C A M P A N A   C O M P L E T A   *** "
                                               : "       ***   N I V E L   S U P E R A D O   ***    ");
    gotoxy(cx, cy + 2);  cout << "                    G A N A S T E                   ";
    gotoxy(cx, cy + 3);  cout << "====================================================";

    setColor(COLOR_BLANCO);
    gotoxy(cx, cy + 5);
    if (numJugadores == 2) {
        cout << "  Nivel " << nivelActual << "/" << TOTAL_NIVELES
             << " - Ganador: Jugador " << ganadorIdx << " (";
        setColor((ganadorIdx == 1) ? COLOR_AMARILLO : COLOR_CIAN);
        cout << simGanador;
        setColor(COLOR_BLANCO);
        cout << ")";
    } else {
        cout << "  Nivel " << nivelActual << "/" << TOTAL_NIVELES
             << " - Llegaste a la meta (";
        setColor(COLOR_AMARILLO);
        cout << simGanador;
        setColor(COLOR_BLANCO);
        cout << ")";
    }

    gotoxy(cx, cy + 6);  cout << "  Movimientos: ";
    setColor(COLOR_AMARILLO); cout << pasos;
    setColor(COLOR_BLANCO);
    cout << "   |   Tiempo: ";
    setColor(COLOR_CIAN); cout << segundos << " s";

    setColor(COLOR_BLANCO);
    gotoxy(cx, cy + 8);
    if (esUltimoNivel) {
        cout << "  [R] Reiniciar Nivel 1   [M] Menu   [ESC] Salir";
    } else {
        cout << "  [R] Siguiente Nivel     [M] Menu   [ESC] Salir";
    }

    setColor(COLOR_VERDE);
    gotoxy(cx, cy + 10); cout << "====================================================";
    setColor(COLOR_DEFECTO);
}

void mostrarPantallaDerrota(int nivelActual, int pasos, double segundos, int ancho, int alto, const char* razon) {
    limpiarPantalla();
    int cx = (ancho - 52) / 2;
    if (cx < 2) cx = 2;
    int cy = alto / 2 - 5;
    if (cy < 2) cy = 2;

    setColor(COLOR_ROJO);
    gotoxy(cx, cy);      cout << "====================================================";
    gotoxy(cx, cy + 1);  cout << "     ! ! !   I M P A C T O   C R I T I C O   ! ! !  ";
    gotoxy(cx, cy + 2);  cout << "                   P E R D I S T E                  ";
    gotoxy(cx, cy + 3);  cout << "====================================================";

    setColor(COLOR_BLANCO);
    gotoxy(cx, cy + 5);  cout << "  Nivel " << nivelActual << "/" << TOTAL_NIVELES
                              << " - Causa: ";
    setColor(COLOR_MAGENTA); cout << razon;

    setColor(COLOR_BLANCO);
    gotoxy(cx, cy + 6);  cout << "  Movimientos: ";
    setColor(COLOR_AMARILLO); cout << pasos;
    setColor(COLOR_BLANCO);
    cout << "   |   Tiempo: ";
    setColor(COLOR_CIAN); cout << segundos << " s";

    setColor(COLOR_BLANCO);
    gotoxy(cx, cy + 8);  cout << "  [R] Reintentar Nivel    [M] Menu   [ESC] Salir";

    setColor(COLOR_ROJO);
    gotoxy(cx, cy + 10); cout << "====================================================";
    setColor(COLOR_DEFECTO);
}

// Resultado de la ronda:
//  1 = Gano (avanzar nivel o reiniciar si era el 5)
//  0 = Perdio (reintentar mismo nivel)
//  2 = Volver al menu principal
// -1 = Salir
int jugarPartida(int Ancho, int Alto, int Esc, int numJugadores,
                 char Jugador1, char Jugador2, char Meta,
                 const ConfigNivel& cfg, int NumObstaculosBase) {
    limpiarPantalla();

    double posX1 = (numJugadores == 2) ? (Ancho / 3.0) : (Ancho / 2.0);
    double posY1 = Alto / 2.0;
    double velX1 = 0.0, velY1 = 0.0;

    double posX2 = (2.0 * Ancho) / 3.0;
    double posY2 = Alto / 2.0;
    double velX2 = 0.0, velY2 = 0.0;

    int x1 = static_cast<int>(round(posX1));
    int y1 = static_cast<int>(round(posY1));
    int x2 = static_cast<int>(round(posX2));
    int y2 = static_cast<int>(round(posY2));

    int pasos = 0;
    const double tiempoLimite = cfg.tiempoLimite;
    DWORD inicioTick = GetTickCount();
    DWORD ultimoFrame = inicioTick;

    const int MAX_ESTELAS = 32;
    Estela estelas[MAX_ESTELAS];
    for (int i = 0; i < MAX_ESTELAS; i++) estelas[i].activa = false;
    int idxEstela = 0;

    // Generar meta aleatoria lejos de jugador(es)
    int metaX, metaY;
    do {
        metaX = 3 + rand() % (Ancho - 6);
        metaY = 3 + rand() % (Alto - 6);
        bool lejosP1 = (abs(metaX - x1) + abs(metaY - y1) >= 9);
        bool lejosP2 = (numJugadores == 1) || (abs(metaX - x2) + abs(metaY - y2) >= 9);
        if (lejosP1 && lejosP2) break;
    } while (true);

    // Generar obstaculos fijos 2x2 (respetando el minimo de 3 y escalando por nivel)
    int obsX[MAX_OBS_FIJOS], obsY[MAX_OBS_FIJOS];
    int totalObs = cfg.obsFijos;
    if (totalObs < 3) totalObs = 3;
    if (totalObs < NumObstaculosBase && cfg.numero == 1) totalObs = NumObstaculosBase;
    if (totalObs > MAX_OBS_FIJOS) totalObs = MAX_OBS_FIJOS;

    for (int k = 0; k < totalObs; k++) {
        bool valido;
        int intentos = 0;
        do {
            valido = true;
            intentos++;
            obsX[k] = 2 + rand() % (Ancho - 5);
            obsY[k] = 2 + rand() % (Alto - 5);

            if (abs(obsX[k] - x1) <= 2 && abs(obsY[k] - y1) <= 2) valido = false;
            if (numJugadores == 2 && abs(obsX[k] - x2) <= 2 && abs(obsY[k] - y2) <= 2) valido = false;

            if (metaX >= obsX[k] - 1 && metaX <= obsX[k] + 2 &&
                metaY >= obsY[k] - 1 && metaY <= obsY[k] + 2) valido = false;

            for (int prev = 0; prev < k; prev++) {
                if (abs(obsX[k] - obsX[prev]) < 4 && abs(obsY[k] - obsY[prev]) < 4) {
                    valido = false;
                }
            }
        } while (!valido && intentos < 250);
    }

    // Generar barreras segun nivel
    int numBarreras = cfg.barreras;
    if (numBarreras > MAX_BARRERAS) numBarreras = MAX_BARRERAS;
    Barrera barreras[MAX_BARRERAS];

    for (int b = 0; b < numBarreras; b++) {
        bool valido;
        int intentos = 0;
        do {
            valido = true;
            intentos++;
            barreras[b].horizontal = (b % 2 == 0);
            if (barreras[b].horizontal) {
                barreras[b].ancho = 4 + rand() % 4;
                barreras[b].alto = 1;
                barreras[b].x = 2 + rand() % (Ancho - 4 - barreras[b].ancho);
                barreras[b].y = 2 + rand() % (Alto - 4);
            } else {
                barreras[b].ancho = 1;
                barreras[b].alto = 3 + rand() % 3;
                barreras[b].x = 2 + rand() % (Ancho - 4);
                barreras[b].y = 2 + rand() % (Alto - 4 - barreras[b].alto);
            }

            for (int bx = barreras[b].x - 1; bx <= barreras[b].x + barreras[b].ancho; bx++) {
                for (int by = barreras[b].y - 1; by <= barreras[b].y + barreras[b].alto; by++) {
                    bool sobreP1 = (bx == x1 && by == y1);
                    bool sobreP2 = (numJugadores == 2 && bx == x2 && by == y2);
                    if (sobreP1 || sobreP2 ||
                        (bx == metaX && by == metaY) || esObstaculoFijo(bx, by, obsX, obsY, totalObs)) {
                        valido = false;
                    }
                }
            }
        } while (!valido && intentos < 250);
    }

    // Configurar obstaculos moviles de patrulla segun nivel
    int numMov = cfg.moviles;
    if (numMov > MAX_MOVILES) numMov = MAX_MOVILES;
    ObstaculoMovil mov[MAX_MOVILES];
    DWORD ahoraInit = GetTickCount();

    int filasPatrulla[MAX_MOVILES] = {4, Alto - 6, 9, 14, Alto - 4};
    for (int m = 0; m < numMov; m++) {
        int fy = filasPatrulla[m];
        if (fy < 3) fy = 3;
        if (fy > Alto - 4) fy = Alto - 4;

        mov[m].x = (m % 2 == 0) ? 4 : (Ancho - 6);
        mov[m].y = fy;
        mov[m].vx = (m % 2 == 0) ? 1 : -1;
        mov[m].vy = 0;
        mov[m].minX = 3;
        mov[m].maxX = Ancho - 5;
        mov[m].minY = fy;
        mov[m].maxY = fy;
        mov[m].ultimoPaso = ahoraInit;

        bool cercaP1 = (abs(mov[m].x - x1) <= 2 && abs(mov[m].y - y1) <= 2);
        bool cercaP2 = (numJugadores == 2 && abs(mov[m].x - x2) <= 2 && abs(mov[m].y - y2) <= 2);
        if (cercaP1 || cercaP2) {
            mov[m].y = (mov[m].y < Alto / 2) ? Alto - 5 : 3;
            mov[m].minY = mov[m].maxY = mov[m].y;
        }
        if (metaX >= mov[m].x - 1 && metaX <= mov[m].x + 2 &&
            metaY >= mov[m].y - 1 && metaY <= mov[m].y + 2) {
            mov[m].y = (metaY < Alto / 2) ? Alto - 5 : 3;
            mov[m].minY = mov[m].maxY = mov[m].y;
        }
    }

    // Encabezado de estado con nivel actual
    gotoxy(0, 0);
    setColor(COLOR_CIAN);
    cout << "NIVEL " << cfg.numero << "/" << TOTAL_NIVELES << " (" << cfg.nombre << ")";
    setColor(COLOR_DEFECTO);
    cout << " | P1: ";
    setColor(COLOR_AMARILLO); cout << Jugador1;
    if (numJugadores == 2) {
        setColor(COLOR_DEFECTO);
        cout << " | P2: ";
        setColor(COLOR_CIAN); cout << Jugador2;
    }
    setColor(COLOR_DEFECTO);
    cout << " | META: ";
    setColor(COLOR_VERDE); cout << Meta;
    setColor(COLOR_DEFECTO);
    cout << " | PASOS: ";
    setColor(COLOR_BLANCO); cout << "0   ";
    setColor(COLOR_DEFECTO);
    cout << "| T: ";
    setColor(COLOR_CIAN); cout << tiempoLimite << "s  ";
    setColor(COLOR_DEFECTO);

    int offsetY = 2;

    // Dibujar marco con caracteres de borde
    setColor(COLOR_AZUL);
    gotoxy(0, offsetY); cout << "\xC9";
    for (int i = 1; i < Ancho - 1; i++) {
        gotoxy(i, offsetY);            cout << "\xCD";
        gotoxy(i, offsetY + Alto - 1); cout << "\xCD";
    }
    gotoxy(Ancho - 1, offsetY); cout << "\xBB";

    for (int i = 1; i < Alto - 1; i++) {
        gotoxy(0, offsetY + i);         cout << "\xBA";
        gotoxy(Ancho - 1, offsetY + i); cout << "\xBA";
    }
    gotoxy(0, offsetY + Alto - 1);         cout << "\xC8";
    gotoxy(Ancho - 1, offsetY + Alto - 1); cout << "\xBC";
    setColor(COLOR_DEFECTO);

    for (int b = 0; b < numBarreras; b++) {
        dibujarBarrera(barreras[b], offsetY);
    }

    for (int k = 0; k < totalObs; k++) {
        dibujarBloqueSombreado(obsX[k], offsetY + obsY[k], COLOR_ROJO, COLOR_MAGENTA);
    }

    for (int k = 0; k < numMov; k++) {
        dibujarBloqueSombreado(mov[k].x, offsetY + mov[k].y, COLOR_AMARILLO, COLOR_ROJO);
    }

    gotoxy(metaX, offsetY + metaY);
    setColor(COLOR_VERDE);
    cout << Meta;
    setColor(COLOR_DEFECTO);

    gotoxy(x1, offsetY + y1);
    setColor(COLOR_AMARILLO);
    cout << Jugador1;
    if (numJugadores == 2) {
        gotoxy(x2, offsetY + y2);
        setColor(COLOR_CIAN);
        cout << Jugador2;
    }
    setColor(COLOR_DEFECTO);

    gotoxy(0, offsetY + Alto + 1);
    setColor(COLOR_BLANCO);
    if (numJugadores == 2) {
        cout << "P1: ";
        setColor(COLOR_AMARILLO); cout << "WASD";
        setColor(COLOR_BLANCO); cout << " | P2: ";
        setColor(COLOR_CIAN); cout << "Flechas";
        setColor(COLOR_BLANCO); cout << " | Chocar entre si = bloqueados | ";
    } else {
        cout << "Controles: ";
        setColor(COLOR_AMARILLO); cout << "WASD o Flechas";
        setColor(COLOR_BLANCO); cout << " | Evita bordes, bloques y barreras | ";
    }
    setColor(COLOR_GRIS); cout << "[ESC] Salir";
    setColor(COLOR_DEFECTO);

    bool juegoTerminado = false;
    bool gano = false;
    int ganadorIdx = 0;
    char simGanador = ' ';
    int choqueX = x1, choqueY = y1;
    const char* razonDerrota = "";
    double tiempoTranscurrido = 0.0;

    while (_kbhit()) _getch();

    while (!juegoTerminado) {
        DWORD ahora = GetTickCount();
        double dt = (ahora - ultimoFrame) / 1000.0;
        if (dt > 0.05) dt = 0.05;
        ultimoFrame = ahora;

        tiempoTranscurrido = (ahora - inicioTick) / 1000.0;
        double tiempoRestante = tiempoLimite - tiempoTranscurrido;

        if (tiempoRestante <= 0.0) {
            tiempoRestante = 0.0;
            gano = false;
            choqueX = x1;
            choqueY = y1;
            razonDerrota = "Se agoto el tiempo limite del nivel.";
            juegoTerminado = true;
            break;
        }

        if (GetAsyncKeyState(Esc) & 0x8000) {
            return -1;
        }

        static DWORD ultimoReloj = 0;
        if (ahora - ultimoReloj >= 100) {
            ultimoReloj = ahora;
            gotoxy(84, 0);
            setColor((tiempoRestante < 7.0) ? COLOR_ROJO : COLOR_CIAN);
            cout << tiempoRestante << "s   ";
            setColor(COLOR_DEFECTO);
        }

        const double aceleracion = 44.0;
        const double velMax = 15.0;
        const double amortiguacion = 8.5;

        // Entrada Jugador 1 (en 1P acepta WASD o Flechas; en 2P usa WASD)
        double ax1 = 0.0, ay1 = 0.0;
        bool up1    = (GetAsyncKeyState('W') & 0x8000) || (numJugadores == 1 && (GetAsyncKeyState(VK_UP) & 0x8000));
        bool down1  = (GetAsyncKeyState('S') & 0x8000) || (numJugadores == 1 && (GetAsyncKeyState(VK_DOWN) & 0x8000));
        bool left1  = (GetAsyncKeyState('A') & 0x8000) || (numJugadores == 1 && (GetAsyncKeyState(VK_LEFT) & 0x8000));
        bool right1 = (GetAsyncKeyState('D') & 0x8000) || (numJugadores == 1 && (GetAsyncKeyState(VK_RIGHT) & 0x8000));

        if (up1)    ay1 -= aceleracion;
        if (down1)  ay1 += aceleracion;
        if (left1)  ax1 -= aceleracion;
        if (right1) ax1 += aceleracion;

        if (ax1 != 0.0 || ay1 != 0.0) {
            velX1 += ax1 * dt;
            velY1 += ay1 * dt;
        } else {
            double f = exp(-amortiguacion * dt);
            velX1 *= f;
            velY1 *= f;
        }

        // Entrada Jugador 2 (Flechas en modo 2P)
        double ax2 = 0.0, ay2 = 0.0;
        if (numJugadores == 2) {
            if (GetAsyncKeyState(VK_UP) & 0x8000)    ay2 -= aceleracion;
            if (GetAsyncKeyState(VK_DOWN) & 0x8000)  ay2 += aceleracion;
            if (GetAsyncKeyState(VK_LEFT) & 0x8000)  ax2 -= aceleracion;
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000) ax2 += aceleracion;

            if (ax2 != 0.0 || ay2 != 0.0) {
                velX2 += ax2 * dt;
                velY2 += ay2 * dt;
            } else {
                double f = exp(-amortiguacion * dt);
                velX2 *= f;
                velY2 *= f;
            }
        }

        if (velX1 > velMax) velX1 = velMax;
        if (velX1 < -velMax) velX1 = -velMax;
        if (velY1 > velMax) velY1 = velMax;
        if (velY1 < -velMax) velY1 = -velMax;

        if (velX2 > velMax) velX2 = velMax;
        if (velX2 < -velMax) velX2 = -velMax;
        if (velY2 > velMax) velY2 = velMax;
        if (velY2 < -velMax) velY2 = -velMax;

        if (fabs(velX1) < 0.08 && ax1 == 0.0) velX1 = 0.0;
        if (fabs(velY1) < 0.08 && ay1 == 0.0) velY1 = 0.0;
        if (fabs(velX2) < 0.08 && ax2 == 0.0) velX2 = 0.0;
        if (fabs(velY2) < 0.08 && ay2 == 0.0) velY2 = 0.0;

        for (int k = 0; k < numMov; k++) {
            if (ahora - mov[k].ultimoPaso >= cfg.intervaloMovilMs) {
                mov[k].ultimoPaso = ahora;

                int sigMX = mov[k].x + mov[k].vx;
                int sigMY = mov[k].y + mov[k].vy;

                bool chocaFijo = esObstaculoFijo(sigMX, sigMY, obsX, obsY, totalObs) ||
                                 esObstaculoFijo(sigMX + 1, sigMY, obsX, obsY, totalObs) ||
                                 esObstaculoFijo(sigMX, sigMY + 1, obsX, obsY, totalObs) ||
                                 esObstaculoFijo(sigMX + 1, sigMY + 1, obsX, obsY, totalObs) ||
                                 esBarrera(sigMX, sigMY, barreras, numBarreras) ||
                                 esBarrera(sigMX + 1, sigMY, barreras, numBarreras) ||
                                 esBarrera(sigMX, sigMY + 1, barreras, numBarreras) ||
                                 esBarrera(sigMX + 1, sigMY + 1, barreras, numBarreras);

                if (sigMX < mov[k].minX || sigMX > mov[k].maxX || chocaFijo) {
                    mov[k].vx = -mov[k].vx;
                    sigMX = mov[k].x + mov[k].vx;
                }
                if (sigMY < mov[k].minY || sigMY > mov[k].maxY) {
                    mov[k].vy = -mov[k].vy;
                    sigMY = mov[k].y + mov[k].vy;
                }

                if (!(metaX >= mov[k].x && metaX <= mov[k].x + 1 &&
                      metaY >= mov[k].y && metaY <= mov[k].y + 1)) {
                    borrarBloque2x2(mov[k].x, offsetY + mov[k].y);
                }

                mov[k].x = sigMX;
                mov[k].y = sigMY;

                dibujarBloqueSombreado(mov[k].x, offsetY + mov[k].y, COLOR_AMARILLO, COLOR_ROJO);

                for (int b = 0; b < numBarreras; b++) {
                    dibujarBarrera(barreras[b], offsetY);
                }

                gotoxy(metaX, offsetY + metaY);
                setColor(COLOR_VERDE);
                cout << Meta;
                setColor(COLOR_DEFECTO);

                if (esObstaculoMovil(x1, y1, mov, numMov)) {
                    gano = false;
                    choqueX = x1; choqueY = y1;
                    razonDerrota = (numJugadores == 2)
                        ? "Jugador 1 fue interceptado por un obstaculo movil."
                        : "Te intercepto un obstaculo movil.";
                    juegoTerminado = true;
                    break;
                }
                if (numJugadores == 2 && esObstaculoMovil(x2, y2, mov, numMov)) {
                    gano = false;
                    choqueX = x2; choqueY = y2;
                    razonDerrota = "Jugador 2 fue interceptado por un obstaculo movil.";
                    juegoTerminado = true;
                    break;
                }
            }
        }

        if (juegoTerminado) break;

        for (int i = 0; i < MAX_ESTELAS; i++) {
            if (estelas[i].activa && (ahora - estelas[i].creadaEn >= 280)) {
                estelas[i].activa = false;
                int ex = estelas[i].x, ey = estelas[i].y;
                bool sobreP1 = (ex == x1 && ey == y1);
                bool sobreP2 = (numJugadores == 2 && ex == x2 && ey == y2);
                if (!(sobreP1 || sobreP2 ||
                      (ex == metaX && ey == metaY) ||
                      esObstaculoFijo(ex, ey, obsX, obsY, totalObs) ||
                      esObstaculoMovil(ex, ey, mov, numMov) ||
                      esBarrera(ex, ey, barreras, numBarreras))) {
                    gotoxy(ex, offsetY + ey);
                    cout << " ";
                }
            }
        }

        posX1 += velX1 * dt;
        posY1 += velY1 * dt;
        if (numJugadores == 2) {
            posX2 += velX2 * dt;
            posY2 += velY2 * dt;
        }

        int nx1 = static_cast<int>(round(posX1));
        int ny1 = static_cast<int>(round(posY1));
        int nx2 = (numJugadores == 2) ? static_cast<int>(round(posX2)) : x2;
        int ny2 = (numJugadores == 2) ? static_cast<int>(round(posY2)) : y2;

        if (numJugadores == 2) {
            // Si chocan entre si, quedan atorados sin terminar el juego
            if (nx1 == nx2 && ny1 == ny2 && (nx1 != x1 || ny1 != y1 || nx2 != x2 || ny2 != y2)) {
                posX1 = x1; posY1 = y1; velX1 = 0.0; velY1 = 0.0;
                posX2 = x2; posY2 = y2; velX2 = 0.0; velY2 = 0.0;
                nx1 = x1; ny1 = y1; nx2 = x2; ny2 = y2;
            }
            if ((nx1 != x1 || ny1 != y1) && nx1 == x2 && ny1 == y2) {
                posX1 = x1; posY1 = y1; velX1 = 0.0; velY1 = 0.0;
                nx1 = x1; ny1 = y1;
            }
            if ((nx2 != x2 || ny2 != y2) && nx2 == x1 && ny2 == y1) {
                posX2 = x2; posY2 = y2; velX2 = 0.0; velY2 = 0.0;
                nx2 = x2; ny2 = y2;
            }
        }

        if (nx1 != x1 || ny1 != y1) {
            if (nx1 <= 0 || nx1 >= Ancho - 1 || ny1 <= 0 || ny1 >= Alto - 1) {
                gano = false; choqueX = nx1; choqueY = ny1;
                razonDerrota = (numJugadores == 2)
                    ? "Jugador 1 choco contra el borde del marco."
                    : "Chocaste contra el borde del marco.";
                juegoTerminado = true;
            } else if (esObstaculoFijo(nx1, ny1, obsX, obsY, totalObs)) {
                gano = false; choqueX = nx1; choqueY = ny1;
                razonDerrota = (numJugadores == 2)
                    ? "Jugador 1 choco contra un obstaculo fijo."
                    : "Chocaste contra un obstaculo fijo.";
                juegoTerminado = true;
            } else if (esBarrera(nx1, ny1, barreras, numBarreras)) {
                gano = false; choqueX = nx1; choqueY = ny1;
                razonDerrota = (numJugadores == 2)
                    ? "Jugador 1 choco contra una barrera."
                    : "Chocaste contra una barrera.";
                juegoTerminado = true;
            } else if (esObstaculoMovil(nx1, ny1, mov, numMov)) {
                gano = false; choqueX = nx1; choqueY = ny1;
                razonDerrota = (numJugadores == 2)
                    ? "Jugador 1 choco contra un obstaculo movil."
                    : "Chocaste contra un obstaculo movil.";
                juegoTerminado = true;
            } else if (nx1 == metaX && ny1 == metaY) {
                pasos++;
                gotoxy(x1, offsetY + y1); cout << " ";
                x1 = nx1; y1 = ny1;
                gotoxy(x1, offsetY + y1);
                setColor(COLOR_AMARILLO); cout << Jugador1; setColor(COLOR_DEFECTO);
                gano = true; ganadorIdx = 1; simGanador = Jugador1;
                juegoTerminado = true;
            } else {
                pasos++;
                gotoxy(x1, offsetY + y1);
                setColor(COLOR_GRIS); cout << "."; setColor(COLOR_DEFECTO);

                estelas[idxEstela].x = x1; estelas[idxEstela].y = y1;
                estelas[idxEstela].creadaEn = ahora; estelas[idxEstela].activa = true;
                idxEstela = (idxEstela + 1) % MAX_ESTELAS;

                x1 = nx1; y1 = ny1;
                gotoxy(x1, offsetY + y1);
                setColor(COLOR_AMARILLO); cout << Jugador1; setColor(COLOR_DEFECTO);

                gotoxy(70, 0);
                setColor(COLOR_BLANCO); cout << pasos << "   "; setColor(COLOR_DEFECTO);
            }
        }

        if (!juegoTerminado && numJugadores == 2 && (nx2 != x2 || ny2 != y2)) {
            if (nx2 <= 0 || nx2 >= Ancho - 1 || ny2 <= 0 || ny2 >= Alto - 1) {
                gano = false; choqueX = nx2; choqueY = ny2;
                razonDerrota = "Jugador 2 choco contra el borde del marco.";
                juegoTerminado = true;
            } else if (esObstaculoFijo(nx2, ny2, obsX, obsY, totalObs)) {
                gano = false; choqueX = nx2; choqueY = ny2;
                razonDerrota = "Jugador 2 choco contra un obstaculo fijo.";
                juegoTerminado = true;
            } else if (esBarrera(nx2, ny2, barreras, numBarreras)) {
                gano = false; choqueX = nx2; choqueY = ny2;
                razonDerrota = "Jugador 2 choco contra una barrera.";
                juegoTerminado = true;
            } else if (esObstaculoMovil(nx2, ny2, mov, numMov)) {
                gano = false; choqueX = nx2; choqueY = ny2;
                razonDerrota = "Jugador 2 choco contra un obstaculo movil.";
                juegoTerminado = true;
            } else if (nx2 == metaX && ny2 == metaY) {
                pasos++;
                gotoxy(x2, offsetY + y2); cout << " ";
                x2 = nx2; y2 = ny2;
                gotoxy(x2, offsetY + y2);
                setColor(COLOR_CIAN); cout << Jugador2; setColor(COLOR_DEFECTO);
                gano = true; ganadorIdx = 2; simGanador = Jugador2;
                juegoTerminado = true;
            } else {
                pasos++;
                gotoxy(x2, offsetY + y2);
                setColor(COLOR_GRIS); cout << "."; setColor(COLOR_DEFECTO);

                estelas[idxEstela].x = x2; estelas[idxEstela].y = y2;
                estelas[idxEstela].creadaEn = ahora; estelas[idxEstela].activa = true;
                idxEstela = (idxEstela + 1) % MAX_ESTELAS;

                x2 = nx2; y2 = ny2;
                gotoxy(x2, offsetY + y2);
                setColor(COLOR_CIAN); cout << Jugador2; setColor(COLOR_DEFECTO);

                gotoxy(70, 0);
                setColor(COLOR_BLANCO); cout << pasos << "   "; setColor(COLOR_DEFECTO);
            }
        }

        Sleep(12);
    }

    if (!gano && choqueX > 0 && choqueX < Ancho - 1 && choqueY > 0 && choqueY < Alto - 1) {
        efectoImpacto(choqueX, choqueY, offsetY);
    }

    Sleep(250);

    if (gano) {
        mostrarPantallaVictoria(numJugadores, cfg.numero, ganadorIdx, simGanador,
                                pasos, tiempoTranscurrido, Ancho, Alto + offsetY + 2);
    } else {
        mostrarPantallaDerrota(cfg.numero, pasos, tiempoTranscurrido, Ancho, Alto + offsetY + 2, razonDerrota);
    }

    while (_kbhit()) _getch();

    while (true) {
        if (GetAsyncKeyState('R') & 0x8000) {
            Sleep(180);
            return gano ? 1 : 0;
        }
        if (GetAsyncKeyState('M') & 0x8000) {
            Sleep(180);
            return 2;
        }
        if (GetAsyncKeyState(Esc) & 0x8000) {
            Sleep(180);
            return -1;
        }
        Sleep(25);
    }
}

int main() {
    const int Ancho = 64, Alto = 25;
    const int Esc = 27;
    const char Jugador1 = '@';     // Controles: WASD (o Flechas en 1 jugador)
    const char Jugador2 = '&';     // Controles: Flechas (en 2 jugadores)
    const char Meta = 'M';
    const int NumObstaculos = 3;   // Minimo 3 obstaculos fijos

    ocultarCursor();
    srand(static_cast<unsigned int>(time(0)));

    while (true) {
        int modo = mostrarMenuPrincipal(Esc);
        if (modo == 0) {
            break;
        }

        int nivelActual = 1;
        bool volverAlMenu = false;
        bool salirTotal = false;

        while (!volverAlMenu && !salirTotal) {
            ConfigNivel cfg = obtenerNivel(nivelActual);
            int resultado = jugarPartida(Ancho, Alto, Esc, modo, Jugador1, Jugador2, Meta, cfg, NumObstaculos);

            if (resultado == -1) {
                salirTotal = true;
            } else if (resultado == 2) {
                volverAlMenu = true;
            } else if (resultado == 1) {
                if (nivelActual < TOTAL_NIVELES) {
                    nivelActual++;
                } else {
                    nivelActual = 1;
                }
            }
        }

        if (salirTotal) {
            break;
        }
    }

    limpiarPantalla();
    setColor(COLOR_CIAN);
    cout << "Juego finalizado. Hasta pronto!" << endl;
    setColor(COLOR_DEFECTO);
    return 0;
}
