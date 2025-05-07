#include "Tablero.h"
#include "Pieza.h"

using namespace std;

Tablero::Tablero(int altura, int largura) {
	this->altura = altura;
	this->largura = largura;
	lista_piezas.resize(altura * largura);

	lista_piezas[largura * 0 + 0] = Pieza('T', 'B');
	lista_piezas[largura * 0 + 1] = Pieza('C', 'B');
	lista_piezas[largura * 0 + 2] = Pieza('A', 'B');
	lista_piezas[largura * 0 + 3] = Pieza('R', 'B');
	lista_piezas[largura * 0 + 4] = Pieza('D', 'B');
	lista_piezas[largura * 0 + 5] = Pieza('A', 'B');
	lista_piezas[largura * 0 + 6] = Pieza('C', 'B');
	lista_piezas[largura * 0 + 7] = Pieza('T', 'B');

	lista_piezas[largura * 1 + 0] = Pieza('P', 'B');
	lista_piezas[largura * 1 + 1] = Pieza('P', 'B');
	lista_piezas[largura * 1 + 2] = Pieza('P', 'B');
	lista_piezas[largura * 1 + 3] = Pieza('P', 'B');
	lista_piezas[largura * 1 + 4] = Pieza('P', 'B');
	lista_piezas[largura * 1 + 5] = Pieza('P', 'B');
	lista_piezas[largura * 1 + 6] = Pieza('P', 'B');
	lista_piezas[largura * 1 + 7] = Pieza('P', 'B');

	lista_piezas[largura * 7 + 0] = Pieza('T', 'N');
	lista_piezas[largura * 7 + 1] = Pieza('C', 'N');
	lista_piezas[largura * 7 + 2] = Pieza('A', 'N');
	lista_piezas[largura * 7 + 3] = Pieza('D', 'N');
	lista_piezas[largura * 7 + 4] = Pieza('R', 'N');
	lista_piezas[largura * 7 + 5] = Pieza('A', 'N');
	lista_piezas[largura * 7 + 6] = Pieza('C', 'N');
	lista_piezas[largura * 7 + 7] = Pieza('T', 'N');

	lista_piezas[largura * 6 + 0] = Pieza('P', 'N');
	lista_piezas[largura * 6 + 1] = Pieza('P', 'N');
	lista_piezas[largura * 6 + 2] = Pieza('P', 'N');
	lista_piezas[largura * 6 + 3] = Pieza('P', 'N');
	lista_piezas[largura * 6 + 4] = Pieza('P', 'N');
	lista_piezas[largura * 6 + 5] = Pieza('P', 'N');
	lista_piezas[largura * 6 + 6] = Pieza('P', 'N');
	lista_piezas[largura * 6 + 7] = Pieza('P', 'N');
}

void Tablero::dibujar() {
}

void Tablero::dibujar_terminal() {
	for (int y = 0; y < altura; ++y) {
		for (int x = 0; x < largura; ++x) {
			int index = largura * y + x;
			Pieza pieza = lista_piezas[index];

			if (pieza.ver_tipo() == '0') {
				cout << "__ "; // vazio
			}
			else {
				cout << pieza.ver_tipo() << pieza.ver_color() << " ";
			}
		}
		cout << endl;
	}
}

void Tablero::colocar_pieza(int pos_x, int pos_y, char tipo, char color) {
	lista_piezas[largura * pos_y + pos_x] = Pieza(tipo, color);
}

void Tablero::retirar_pieza(int pos_x, int pos_y) {
	lista_piezas[largura * pos_y + pos_x] = Pieza('0', '0'); // Pieza vazia
}

bool Tablero::verificar_movimiento(int posicion_x, int posicion_y, int next_posicion_x, int next_posicion_y) {
	Pieza pieza = lista_piezas[largura * posicion_y + posicion_x];
	Pieza destino = lista_piezas[largura * next_posicion_y + next_posicion_x]; // Hipotetico, puede estar libre

	// Verificar si movimiento está dentro del tablero
	if (next_posicion_x < 0 || next_posicion_x >= largura || next_posicion_y < 0 || next_posicion_y >= altura) {
		return false;
	}

	// Verificar si movimiento es para la misma cedula
	if (next_posicion_x == posicion_x && next_posicion_y == posicion_y) {
		return false;
	}

	// Verificar si movimiento capturaria una pieza amiga
	if (destino.ver_tipo() != '0' && pieza.ver_color() == destino.ver_color()) {
		return false;
	}

	// Verificar si movimiento es valido para la pieza
	switch (pieza.ver_tipo()) {
	case 'A':
	case 'C':
		if (!((abs(posicion_x - next_posicion_x) == 2 && abs(posicion_y - next_posicion_y) == 1) ||
			(abs(posicion_x - next_posicion_x) == 1 && abs(posicion_y - next_posicion_y) == 2)))
			return false;
		break;
	case 'D':
	case 'P':
		if (!(posicion_x == next_posicion_x || abs(posicion_y - next_posicion_y) > 1)) return false;
		break;
	case 'R':
	case 'T':
		if (!(posicion_x == next_posicion_x || posicion_y == next_posicion_y)) return false;
		break;
	default:
		break;
	}
	return true;
}

vector<Pieza> Tablero::listar_piezas() {
	return lista_piezas;
}

// Apenas para terminal
int Tablero::ver_altura() {
	return altura;
}


// Apenas para terminal
int Tablero::ver_largura() {
	return largura;
}

