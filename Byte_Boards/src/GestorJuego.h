#pragma once
#include "Estados.h"
#include "VistaJuego.h"
#include "Partida.h"
#include <utility> 

using namespace std;

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
    GestorJuego() : partida(), vista_juego(new VistaJuego()) {};
    ~GestorJuego() = default;

    void dibujar();
    void interactuar(int cursor_x, int cursor_y);

    pair<int, int> seleccionar_casilla(int cursor_x, int cursor_y);
    void iniciar_partida();

    void seleccionar_menu(int cursor_x, int cursor_y);
    void seleccionar_pausa(int cursor_x, int cursor_y);
    void seleccionar_promocion(int cursor_x, int cursor_y);
    void seleccionar_fin(int cursor_x, int cursor_y);

    void procesar_tecla(unsigned char key);
    bool click_area(int cursor_x, int cursor_y, int x1, int y1, int x2, int y2) const;
};