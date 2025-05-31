#pragma once
#include <string>
#include <vector>

enum EstadoJuego 
{
MENU_TABLERO,
MENU_MODO_JUEGO,
EN_JUEGO,
PAUSA,
PROMOCION_SPEED,
PROMOCION_4x5,
TABLAS,
VICTORIA_CIENCIAS,
VICTORIA_LETRAS
};

class DMenu
{
    EstadoJuego estado;
    char modoSeleccionado;
    int tipoJuego;

public:
    DMenu();

    void dibujarMenu(int ancho, int alto);
    void procesarClick(int x, int y, int ancho, int alto, char* promocion);
    void iniciarPromocion();
    void setEstado(EstadoJuego est) { estado = est; }
    EstadoJuego getEstado() { return estado; }
    int getModoSeleccionado() const;
    int getTipoJuego() const;
};
