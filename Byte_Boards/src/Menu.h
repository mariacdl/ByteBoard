#pragma once
#include <string>
#include <vector>

enum EstadoJuego 
{
MENU_TABLERO,
MENU_MODO_JUEGO,
EN_JUEGO,
PAUSA
};

class Menu
{
    EstadoJuego estado;
    int modoSeleccionado;
    int tipoJuego;

public:
    Menu();

    void dibujarMenu(int ancho, int alto);
    void procesarClick(int x, int y, int ancho, int alto);
    
    EstadoJuego getEstado() const;
    int getModoSeleccionado() const;
    int getTipoJuego() const;
    void setEstado(EstadoJuego nuevoEstado) { estado = nuevoEstado; }
};
