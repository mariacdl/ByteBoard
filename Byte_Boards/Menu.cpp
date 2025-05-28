/*#include <iostream>
#include "Menu.h"
#include "Partida.h"

using namespace std;

int Menu::ver_modo_juego() {
	return modo_juego;
}

void Menu::seleccionar_modo_juego(int nuevo_modo) {
	switch (nuevo_modo) {
	case 0: { // Cerrar juego
		modo_juego = nuevo_modo;
		break; 
	}
	case 1: { // vs Jugador
		modo_juego = nuevo_modo;
		Partida partida(8, 8, 'J', 'B');
		partida.jugar();
		break; 
	}	
	case 2: { // vs IA
		modo_juego = nuevo_modo;
		Partida partida(8, 8, 'O', 'B');
		partida.jugar();
		break; 
	}
	case 3: { // 
		modo_juego = nuevo_modo;
		break; 
	}
	default: break;
	}
}

void Menu::dibujar_terminal() {
	int modo;

	cout << endl;
	cout << " ========== BYTE BOARD ========== " << endl;
	
	while (true) {
		cout << endl;
		cout << "1. Jugar contra jugador" << endl;
		cout << "2. Jugar contra IA (WORK IN PROGRESS)" << endl;
		cout << "0. Salir" << endl;
		cout << "Escojer opcion: ";
		cin >> modo;

		if (modo == 0 || modo == 1 || modo == 2) {
			seleccionar_modo_juego(modo);
			break;
		}
		else {
			std::cout << "Opci�n fuera de rango. Intente nuevamente.\n";
		}
	}
}*/
