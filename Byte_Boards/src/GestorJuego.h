#pragma once
#include "VistaJuego.h"
#include "Partida.h"
#include <utility> 

using namespace std;

enum EstadoJuego { MENU, EN_JUEGO, PAUSA, PROMOCION, FIN };
enum EstadoMenu { MENU_TABLERO, MENU_OPONENTE };
enum TipoFin { VICTORIA_CIENCIAS, VICTORIA_LETRAS, TABLAS, NO_FINALIZADO };
enum TipoJuego { JUEGO_4x5, JUEGO_SPEED, NO_DECIDIDO };
enum TipoOponente { IA, JUGADOR, SIN_OPONENTE };

class GestorJuego {
private:
    Partida* partida;
    VistaJuego* vista_juego;

    EstadoJuego estado_juego = MENU;
    EstadoMenu estado_menu = MENU_TABLERO;
    TipoFin tipo_fin = NO_FINALIZADO;
    TipoJuego tipo_juego = NO_DECIDIDO;
    TipoOponente tipo_oponente = SIN_OPONENTE;

    EstadoJuego estado_juego_anterior = MENU;

    pair<int, int> casilla_seleccionada = { -1, -1 };

public:
    GestorJuego() : partida(), vista_juego() {};
    ~GestorJuego() = default;

    void dibujar();
    void interactuar(int cursor_x, int cursor_y);

    void seleccionar_menu(int cursor_x, int cursor_y);
    void seleccionar_casilla(int cursor_x, int cursor_y);
    void seleccionar_pausa(int cursor_x, int cursor_y);
    void seleccionar_promocion(int cursor_x, int cursor_y);
    void seleccionar_fin(int cursor_x, int cursor_y);

    void procesar_tecla(unsigned char key);
    void iniciar_partida();
    bool click_area(int cursor_x, int cursor_y, int x1, int y1, int x2, int y2) const;

};