#include "enemy.h"
#include "miniwin.h"

using namespace miniwin;
using namespace std;

const int escalado = 2;
const bool pintarBorde = false;
const int DERECHA_ENEMIGO = 1;
const int IZQUIERDA_ENEMIGO = -1;

enemy::enemy(int x, int y) : xPos(x), yPos(y), direccion(DERECHA_ENEMIGO), contadorMovimientos(0) {
    srand(static_cast<unsigned int>(time(0)));

    colorMap = {
        {"c_1", {70, 156, 201}},
        {"c_2", {56, 86, 160}},
        {"c_3", {179, 179, 179}},
        {"c_4", {129, 129, 129}},
        {"c_5", {241, 169, 68}},
        {"c_6", {229, 51, 34}},
        {"c_7", {185, 38, 28}},
        {"c_8", {99, 104, 109}},

        {"c_9", {224, 225, 227}},
        {"c_10", {215, 59, 51}},
        {"c_11", {28, 47, 81}},
        {"c_12", {93, 94, 96}}
    };
}

void enemy::setColor(const string& color) {
    if (colorMap.find(color) != colorMap.end()) {
        vector<int> rgb = colorMap[color];
        color_rgb(rgb[0], rgb[1], rgb[2]);
    }
}

void enemy::mover() {
    contadorMovimientos++;

    if (contadorMovimientos > 20) {
        int cambioDireccion = rand() % 3 - 1;
        direccion = cambioDireccion;
        contadorMovimientos = 0;
    }

    if (direccion == IZQUIERDA_ENEMIGO && xPos > 20) {
        xPos -= 16;

    } else if (direccion == DERECHA_ENEMIGO && xPos < 720) {
        xPos += 16;
    }

    /*if (rand() % 50 == 0) {
        yPos += 10;
    }*/
}

void enemy::disparar() {
    if (!disparoEnemigoActivo) {
        disparoEnemigoActivo = true;
        balaEnemigaX = xPos + ancho / 2;
        balaEnemigaY = yPos + alto;
    }

    if (disparoEnemigoActivo) {
        balaEnemigaY += 10;

        color_rgb(255, 0, 0);
        rectangulo_lleno(balaEnemigaX, balaEnemigaY, balaEnemigaX + 4, balaEnemigaY + 10);

        if (balaEnemigaY >= 600) {
            disparoEnemigoActivo = false;
        }
    }
}

void enemy::dibujaCuadrado(int a, int b, const string& colorRelleno) {
    const int x = a * escalado + xPos;
    const int y = b * escalado + yPos;

    setColor(colorRelleno);

    rectangulo_lleno(x, y, x + escalado, y + escalado);

    if (pintarBorde) {
        color_rgb(100, 100, 100);
        linea(x, y, x, y + escalado);
        linea(x, y + escalado, x + escalado, y + escalado);
        linea(x + escalado, y + escalado, x + escalado, y);
        linea(x + escalado, y, x, y);
    }
}

void enemy::dibujaFila(int fila, const vector<string>& colores) {
    for (size_t i = 0; i < colores.size(); ++i) {
        if (!colores[i].empty()) {
            dibujaCuadrado(i, fila, colores[i]);
        }
    }
}

void enemy::dibujar_e1() {
    dibujaFila(0, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(1, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_7", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(2, {"", "", "", "", "", "", "", "", "", "", "", "", "", "c_7", "c_6", "c_7", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(3, {"", "", "", "", "", "", "", "", "", "", "", "", "c_7", "c_6", "c_5", "c_6", "c_7", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(4, {"", "", "", "", "", "", "", "", "", "", "", "c_7", "c_6", "c_5", "c_5", "c_5", "c_6", "c_7", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(5, {"", "", "", "", "", "", "", "", "", "", "c_7", "c_6", "c_5", "c_5", "c_5", "c_5", "c_5", "c_6", "c_7", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(6, {"", "", "", "", "", "", "", "", "", "", "c_7", "c_6", "c_5", "c_5", "c_5", "c_5", "c_5", "c_6", "c_7", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(7, {"", "", "", "", "", "", "", "", "", "c_7", "c_6", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_6", "c_7", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(8, {"", "", "", "c_7", "", "", "", "", "", "c_7", "c_6", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_6", "c_7", "", "", "", "", "", "c_7", "", "", "", ""});
    dibujaFila(9, {"", "", "c_7", "c_5", "c_7", "", "", "", "c_7", "c_6", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_6", "c_7", "", "", "", "c_7", "c_5", "c_7", "", "", ""});
    dibujaFila(10, {"", "", "c_7", "c_5", "c_7", "", "", "", "c_7", "c_6", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_6", "c_7", "", "", "", "c_7", "c_5", "c_7", "", "", ""});
    dibujaFila(11, {"", "c_7", "c_5", "c_5", "c_5", "c_7", "", "", "", "c_7", "c_6", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_6", "c_7", "", "", "", "c_7", "c_5", "c_5", "c_5", "c_7", "", ""});
    dibujaFila(12, {"", "c_7", "c_5", "c_5", "c_5", "c_7", "", "", "", "c_7", "c_6", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_5", "c_6", "c_7", "", "", "", "c_7", "c_5", "c_5", "c_5", "c_7", "", ""});
    dibujaFila(13, {"c_7", "c_5", "c_5", "c_5", "c_5", "c_5", "c_7", "", "", "", "c_7", "c_6", "c_5", "c_5", "c_5", "c_5", "c_5", "c_6", "c_7", "", "", "", "c_7", "c_5", "c_5", "c_5", "c_5", "c_5", "c_7", ""});
    dibujaFila(14, {"c_7", "c_5", "c_5", "c_5", "c_5", "c_5", "c_7", "", "", "", "c_7", "c_6", "c_5", "c_5", "c_5", "c_5", "c_5", "c_6", "c_7", "", "", "", "c_7", "c_5", "c_5", "c_5", "c_5", "c_5", "c_7", ""});
    dibujaFila(15, {"", "c_7", "c_5", "c_5", "c_5", "c_7", "", "", "", "", "", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "", "", "", "", "", "c_7", "c_5", "c_5", "c_5", "c_7", "", ""});
    dibujaFila(16, {"", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "", "", "", "c_8", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_8", "", "", "", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "", ""});
    dibujaFila(17, {"c_8", "c_2", "c_1", "c_1", "c_1", "c_1", "c_1", "c_8", "c_8", "", "c_8", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_8", "", "c_8", "c_8", "c_1", "c_1", "c_1", "c_1", "c_1", "c_8", "c_8", ""});
    dibujaFila(18, {"", "c_8", "c_2", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "c_2", "c_8", "", ""});
    dibujaFila(19, {"", "c_8", "c_2", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "c_8", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_8", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "c_2", "c_8", "", ""});
    dibujaFila(20, {"", "", "c_8", "c_2", "c_1", "c_1", "c_1", "c_1", "c_1", "c_8", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_8", "c_1", "c_1", "c_1", "c_1", "c_1", "c_2", "c_8", "", "", ""});
    dibujaFila(21, {"", "", "", "c_8", "c_2", "c_1", "c_1", "c_1", "c_1", "c_8", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_8", "c_1", "c_1", "c_1", "c_1", "c_2", "c_8", "", "", "", ""});
    dibujaFila(22, {"", "", "", "", "c_8", "c_2", "c_1", "c_1", "c_1", "c_8", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_8", "c_1", "c_1", "c_1", "c_2", "c_8", "", "", "", "", ""});
    dibujaFila(23, {"", "", "", "", "", "c_8", "c_2", "c_1", "c_1", "c_8", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_8", "c_1", "c_1", "c_2", "c_8", "", "", "", "", "", ""});
    dibujaFila(24, {"", "", "", "", "", "c_8", "c_2", "c_1", "c_1", "c_8", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_8", "c_1", "c_1", "c_2", "c_8", "", "", "", "", "", ""});
    dibujaFila(25, {"", "", "", "", "", "", "c_8", "c_8", "c_8", "c_8", "c_2", "c_2", "c_8", "c_8", "c_8", "c_8", "c_8", "c_2", "c_2", "c_8", "c_8", "c_8", "c_8", "", "", "", "", "", "", ""});
    dibujaFila(26, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_8", "c_3", "c_3", "c_3", "c_3", "c_3", "c_8", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(27, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_8", "c_3", "c_3", "c_4", "c_3", "c_3", "c_8", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(28, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_8", "c_3", "c_4", "c_3", "c_3", "c_3", "c_8", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(29, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_8", "c_3", "c_4", "c_3", "c_3", "c_3", "c_8", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(30, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_8", "c_4", "c_3", "c_3", "c_3", "c_3", "c_8", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(31, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_8", "c_4", "c_3", "c_3", "c_3", "c_3", "c_8", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(32, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_8", "c_4", "c_3", "c_3", "c_3", "c_3", "c_8", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(33, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_2", "c_8", "c_8", "c_8", "c_8", "c_8", "c_2", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(34, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(35, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(36, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(37, {"", "", "", "", "", "", "", "", "", "c_8", "c_2", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "c_8", "c_2", "c_8", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(38, {"", "", "", "", "", "", "", "", "", "", "c_8", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "c_8", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(39, {"", "", "", "", "", "", "", "", "", "", "c_8", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "c_1", "c_8", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(40, {"", "", "", "", "", "", "", "", "", "", "", "c_8", "c_1", "c_1", "c_1", "c_1", "c_1", "c_8", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(41, {"", "", "", "", "", "", "", "", "", "", "", "c_8", "c_1", "c_1", "c_1", "c_1", "c_1", "c_8", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(42, {"", "", "", "", "", "", "", "", "", "", "", "", "c_8", "c_1", "c_1", "c_1", "c_8", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(43, {"", "", "", "", "", "", "", "", "", "", "", "", "c_8", "c_1", "c_1", "c_1", "c_8", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(44, {"", "", "", "", "", "", "", "", "", "", "", "", "", "c_8", "c_1", "c_8", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(45, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_8", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});

}

void enemy::dibujar_e2() {
    dibujaFila(0, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(1, {"", "", "", "", "", "", "", "", "", "", "", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(2, {"", "", "", "", "", "", "", "", "", "", "c_12", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_12", "", "", "", "", "", "", "", "", ""});
    dibujaFila(3, {"", "", "", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "", ""});
    dibujaFila(4, {"", "", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", ""});
    dibujaFila(5, {"", "", "c_12", "c_9", "c_12", "c_12", "c_12", "c_12", "c_12", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_12", "c_12", "c_12", "c_12", "c_12", "c_9", "c_12", ""});
    dibujaFila(6, {"", "", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_10", "c_10", "c_10", "c_10", "c_10", "c_10", "c_10", "c_10", "c_10", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", ""});
    dibujaFila(7, {"", "c_12", "c_11", "c_11", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_10", "c_10", "c_10", "c_10", "c_10", "c_10", "c_10", "c_10", "c_10", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_11", "c_11", "c_12"});
    dibujaFila(8, {"", "c_12", "c_11", "c_11", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_11", "c_11", "c_12"});
    dibujaFila(9, {"", "c_12", "c_11", "c_11", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_11", "c_11", "c_12"});
    dibujaFila(10, {"", "", "c_12", "c_11", "c_11", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_11", "c_11", "c_12", ""});
    dibujaFila(11, {"", "", "", "c_12", "c_11", "c_11", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_9", "c_11", "c_11", "c_12", "", ""});
    dibujaFila(12, {"", "", "", "", "c_12", "c_11", "c_11", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_12", "c_9", "c_12", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_11", "c_11", "c_12", "", "", ""});
    dibujaFila(13, {"", "", "", "", "", "c_12", "c_11", "c_11", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_12", "c_9", "c_12", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_11", "c_11", "c_12", "", "", "", ""});
    dibujaFila(14, {"", "", "", "", "", "c_12", "c_11", "c_11", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_12", "c_9", "c_12", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_11", "c_11", "c_12", "", "", "", ""});
    dibujaFila(15, {"", "", "", "", "", "", "c_12", "c_11", "c_11", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_11", "c_11", "c_12", "", "", "", "", ""});
    dibujaFila(16, {"", "", "", "", "", "", "", "c_12", "c_11", "c_11", "c_9", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_9", "c_11", "c_11", "c_12", "", "", "", "", "", ""});
    dibujaFila(17, {"", "", "", "", "", "", "", "", "c_12", "c_11", "c_11", "c_9", "c_12", "c_9", "c_12", "c_12", "c_12", "c_9", "c_12", "c_9", "c_11", "c_11", "c_12", "", "", "", "", "", "", ""});
    dibujaFila(18, {"", "", "", "", "", "", "", "", "c_12", "c_11", "c_11", "c_9", "c_12", "c_12", "c_9", "c_9", "c_9", "c_12", "c_12", "c_9", "c_11", "c_11", "c_12", "", "", "", "", "", "", ""});
    dibujaFila(19, {"", "", "", "", "", "", "", "", "c_12", "c_11", "c_11", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_11", "c_11", "c_12", "", "", "", "", "", "", ""});
    dibujaFila(20, {"", "", "", "", "", "", "", "", "c_12", "c_11", "c_11", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_11", "c_11", "c_12", "", "", "", "", "", "", ""});
    dibujaFila(21, {"", "", "", "", "", "", "", "", "c_12", "c_11", "c_11", "c_9", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_9", "c_11", "c_11", "c_12", "", "", "", "", "", "", ""});
    dibujaFila(22, {"", "", "", "", "", "", "", "", "c_12", "c_11", "c_11", "c_11", "c_12", "c_9", "c_12", "c_12", "c_12", "c_9", "c_12", "c_11", "c_11", "c_11", "c_12", "", "", "", "", "", "", ""});
    dibujaFila(23, {"", "", "", "", "", "", "", "", "", "c_12", "c_12", "c_11", "c_12", "c_12", "c_9", "c_9", "c_9", "c_12", "c_12", "c_11", "c_12", "c_12", "", "", "", "", "", "", "", ""});
    dibujaFila(24, {"", "", "", "", "", "", "", "", "", "", "", "c_12", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "c_12", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(25, {"", "", "", "", "", "", "", "", "", "", "", "", "c_12", "c_9", "c_9", "c_9", "c_9", "c_9", "c_12", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(26, {"", "", "", "", "", "", "", "", "", "", "", "", "c_12", "c_9", "c_12", "c_9", "c_12", "c_9", "c_12", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(27, {"", "", "", "", "", "", "", "", "", "", "", "", "c_12", "c_9", "c_12", "c_12", "c_12", "c_9", "c_12", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(28, {"", "", "", "", "", "", "", "", "", "", "", "", "c_12", "c_12", "c_9", "c_12", "c_9", "c_9", "c_12", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(29, {"", "", "", "", "", "", "", "", "", "", "", "", "", "c_12", "c_12", "c_9", "c_9", "c_12", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(30, {"", "", "", "", "", "", "", "", "", "", "", "", "", "c_12", "c_12", "c_12", "c_12", "c_12", "", "", "", "", "", "", "", "", "", "", "", ""});
    dibujaFila(31, {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "c_12", "c_12", "c_12", "", "", "", "", "", "", "", "", "", "", "", "", ""});
}


