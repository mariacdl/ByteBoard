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

float anguloCamara = 0.0f;         // ángulo actual
float anguloCamaraObjetivo = 0.0f; // hacia dónde rotar
bool esperandoGiro = false;        // indica si está esperando para girar
int framesEspera = 0;              // contador de frames
const int delayFrames = 20;        // 0.5 segundo ya que es 25msx20=0.5s

public:
	~GestorJuego();
	void dibujar();
	void procesarClick(int x, int y);
	void procesarTecla(unsigned char key);
};
