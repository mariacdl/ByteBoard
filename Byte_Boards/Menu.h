#pragma once

class Menu {
	int modo_juego = 0;

public:
	int ver_modo_juego();
	void seleccionar_modo_juego(int nuevo_modo);
	void dibujar_terminal();
};