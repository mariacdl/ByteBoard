#include "DibujanteMenus.h"
#include "DibujanteTablero.h"
#include "Partida.h"


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

class GestorJuego {
	DibujanteMenus dibujantemenus;
	DibujanteTablero* dibujantetablero;
	Partida* partida;
	EstadoJuego estado{MENU_TABLERO};
	char modoSeleccionado;
	int tipoJuego;
	bool fichasInicializadas = false;
	bool fichaSeleccionada = false;
	bool mostrarPlanoSeleccion = false;
	int filaSeleccionada = -1;
	int columnaSeleccionada = -1;
public:
	~GestorJuego();
	void dibujar();
	void procesarClick(int x, int y);
	void procesarTecla(unsigned char key);
};