#pragma once


class VistaJuego {
	void dibujar_textura(const char* ruta_imagen);
public:
	VistaJuego();
	~VistaJuego();

	// MENU
	void dibujar_menu_tablero();
	void dibujar_menu_oponente();

	// EN_JUEGO
	// No gerenciado por este objeto

	// PAUSA
	void dibujar_pausa();

	// PROMOCION
	void dibujar_promocion_speed();
	void dibujar_promocion_4x5();

	// FIN
	void dibujar_fin_tablas();
	void dibujar_victoria_ciencias();
	void dibujar_victoria_letras();
};