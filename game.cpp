#include "game.h"
#include <vector>
#include <chrono>
#include <windows.h>
#include "miniwin.h"

using namespace miniwin;
using namespace std;

game::game() : player(300, 420), juegoActivo(true), disparo(false), balaX(0), balaY(0), score(0), vida(5), nivelActual(1) {
    cargarNivel();
}

struct Bala {
    int x, y;
    std::chrono::steady_clock::time_point tiempoDisparo;
};

std::vector<Bala> balas;

void game::iniciar() {
    vredimensiona(800, 600);
    mostrarPantallaInicio();
}

void game::mostrarPantallaInicio() {
    borra();
    color(VERDE);
    const char* mensaje = "Tecla ESPACIO para comenzar";
    int anchoTexto = strlen(mensaje) * 8;
    int altoTexto = 15;

    int posX = (800 - anchoTexto) / 2;
    int posY = (600 - altoTexto) / 2;

    texto(posX, posY, mensaje);
    refresca();

    while (true) {
        int t = tecla();
        if (t == ESPACIO) {
            break;
        }
        espera(10);
    }
}

void game::loop() {
    while (true) {
        manejarEntradas();
        actualizar();
        dibujar();
        espera(10);
    }
}

void game::manejarEntradas() {
    int t = tecla();

    if (t == ESCAPE) {
        exit(0);
    }

    if (juegoActivo) {
        player.mover();
        datos(player.getX(), player.getY() - 20);
        if (t == ESPACIO) {
            Bala nuevaBala = {player.getX() + 40, player.getY(), std::chrono::steady_clock::now()};
            balas.push_back(nuevaBala);
            PlaySound(TEXT("C:/Users/Leo/Downloads/Videojuegos/VideoJuego_Naves/Sonido.wav"), NULL, SND_ASYNC | SND_NOSTOP);
        }
    }
}

void game::actualizar() {
    auto ahora = std::chrono::steady_clock::now();

    for (auto it = balas.begin(); it != balas.end();) {
        it->y -= 35;

        if (it->y <= 0 || std::chrono::duration_cast<std::chrono::milliseconds>(ahora - it->tiempoDisparo).count() >= 3000) {
            it = balas.erase(it);
        } else {
            ++it;
        }
    }

    for (auto& enemigo : enemigos) {
        enemigo.mover();

        if (rand() % 100 < 5) {
            enemigo.disparar();
            PlaySound(TEXT("C:/Users/Leo/Downloads/Videojuegos/VideoJuego_Naves/sonido_enemigo.wav"), NULL, SND_ASYNC | SND_NOSTOP);
        }

        if (enemigo.disparoEnemigoActivo) {
            enemigo.balaEnemigaY += 10;

            if (enemigo.balaEnemigaY >= 600) {
                enemigo.disparoEnemigoActivo = false;
            }
        }
    }

    verificarColisiones();
}

void game::dibujarBarraVida() {
    color_rgb(255, 0, 0);
    rectangulo_lleno(700, 550, 700 + 100, 560);

    color_rgb(0, 255, 0);
    rectangulo_lleno(700, 550, 700 + (100 * vida / 5), 560);
}

// M�todo para verificar si dos rect�ngulos colisionan
bool game::colision(int x1, int y1, int ancho1, int alto1, int x2, int y2, int ancho2, int alto2) {
    return (x1 < x2 + ancho2 && x1 + ancho1 > x2 &&
            y1 < y2 + alto2 && y1 + alto1 > y2);
}

void game::verificarColisiones() {
    static int cont = 0;

    for (auto& enemigo : enemigos) {
        if (colision(player.getX(), player.getY(),
                     player.getAncho(), player.getAlto(),
                     enemigo.getX(), enemigo.getY(),
                     enemigo.getAncho(), enemigo.getAlto())) {
            vida--;

            if (vida <= 0) {
                PlaySound(TEXT("C:/Users/Leo/Downloads/Videojuegos/VideoJuego_Naves/Sonido.wav"), NULL, SND_ASYNC);

                juegoActivo = false;
                enemigos.clear();
                return;
            }
        }

        if (enemigo.disparoEnemigoActivo) {
            if (colision(player.getX(), player.getY(),
                         player.getAncho(), player.getAlto(),
                         enemigo.balaEnemigaX, enemigo.balaEnemigaY, 4, 10)) {
                vida--;

                if (vida <= 0) {
                    PlaySound(TEXT("C:/Users/Leo/Downloads/Videojuegos/VideoJuego_Naves/Sonido.wav"), NULL, SND_ASYNC);

                    juegoActivo = false;
                    enemigos.clear();
                    return;
                }

                PlaySound(TEXT("C:/Users/Leo/Downloads/Videojuegos/VideoJuego_Naves/sonido_enemigo.wav"), NULL, SND_ASYNC);

                enemigo.disparoEnemigoActivo = false;
            }
        }
    }

    for (auto itBala = balas.begin(); itBala != balas.end();) {
        bool colisionDetectada = false;
        for (size_t i = 0; i < enemigos.size(); ++i) {
            enemy& enemigo = enemigos[i];

            if (itBala->x >= enemigo.getX() &&
                itBala->x <= enemigo.getX() + enemigo.getAncho() &&
                itBala->y >= enemigo.getY() &&
                itBala->y <= enemigo.getY() + enemigo.getAlto()) {
                itBala = balas.erase(itBala);
                enemigos.erase(enemigos.begin() + i);
                score += 10;
                PlaySound(TEXT("C:/Users/Leo/Downloads/Videojuegos/VideoJuego_Naves/Sonido.wav"), NULL, SND_ASYNC);

                cont++;
                colisionDetectada = true;
                break;
            }
        }
        if (!colisionDetectada) {
            ++itBala;
        }
    }

    if (juegoActivo && enemigos.empty()) {
        if (nivelActual < 3) {
            nivelActual++;
            cargarNivel();

            borra();
            color(VERDE);
            char mensaje[50];
            sprintf(mensaje, "Nivel %d Completado", nivelActual);
            int anchoTexto = strlen(mensaje) * 8;
            int altoTexto = 15;

            int posX = (800 - anchoTexto) / 2;
            int posY = (600 - altoTexto) / 2;

            texto(posX, posY, mensaje);
            refresca();
            espera(2000);
        } else {
            borra();
            color(ROJO);
            const char* mensaje = "Ganaste!";
            int anchoTexto = strlen(mensaje) * 8;
            int altoTexto = 15;

            int posX = (800 - anchoTexto) / 2;
            int posY = (600 - altoTexto) / 2;

            texto(posX, posY, mensaje);
            refresca();
            espera(2000);
            juegoActivo = true;
        }
    }
}

void game::cargarNivel() {
    enemigos.clear();

    int cantidadEnemigos;
    if (nivelActual == 1) {
        cantidadEnemigos = 3;
    } else if (nivelActual == 2) {
        cantidadEnemigos = 5;
    } else if (nivelActual == 3) {
        cantidadEnemigos = 6;
    } else {
        cantidadEnemigos = 0;
    }

    // Define posiciones fijas para los enemigos
    vector<pair<int, int>> posiciones = {
        {100, 30}, {200, 100}, {300, 170}, {400, 240}, {500, 310}, {600, 380}
    };

    // No exceder la cantidad de posiciones disponibles
    for (size_t i = 0; i < static_cast<size_t>(cantidadEnemigos) && i < posiciones.size(); ++i) {
        enemy nuevoEnemigo(posiciones[i].first, posiciones[i].second);
        enemigos.push_back(nuevoEnemigo);
    }

    player.setPosicion(300, 420);

    vida = 5;
}

void game::datos(int x, int y) {
    color(ROJO);

    const char* mensaje = "Leonardo Espejo U21315835";
    int anchoTexto = strlen(mensaje) * 8;

    int posX = x + (player.getAncho() - anchoTexto) / 2;
    int posY = y + player.getAlto() + 5;

    texto(posX, posY, mensaje);
}

void game::dibujar() {
    borra();

    if (juegoActivo) {
        player.dibujar();
        color(ROJO);
        char scoreText[50];
        sprintf(scoreText, "Puntaje: %d", score);
        texto(10, 580, scoreText);

        char nivelText[50];
        sprintf(nivelText, "Level: %d", nivelActual);
        texto(10, 560, nivelText);

        dibujarBarraVida();

        datos(player.getX(), player.getY());
    }

    for (auto& enemigo : enemigos) {
        if (nivelActual == 2) {
            enemigo.dibujar_e2();
        } else {
            enemigo.dibujar_e1();
        }

        if (enemigo.disparoEnemigoActivo) {
            color_rgb(255, 0, 0);
            rectangulo_lleno(enemigo.balaEnemigaX, enemigo.balaEnemigaY, enemigo.balaEnemigaX + 4, enemigo.balaEnemigaY + 10);
        }
    }

    for (const auto& bala : balas) {
        color_rgb(255, 242, 0);
        rectangulo_lleno(bala.x, bala.y, bala.x + 4, bala.y + 10);
    }

    if (!juegoActivo) {
        color(ROJO);
        const char* mensaje = "PERDISTE";
        int anchoTexto = strlen(mensaje) * 8;
        int altoTexto = 15;

        int posX = (800 - anchoTexto) / 2;
        int posY = (600 - altoTexto) / 2;

        texto(posX, posY, mensaje);
    }

    refresca();
}
