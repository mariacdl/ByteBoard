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
	cout << endl << "    ";
	for (int x = 0; x < largura; ++x) {
		cout << x << "  ";
	}
	cout << endl;
	for (int y = 0; y < altura; ++y) {
		cout << " " << y << " ";

		for (int x = 0; x < largura; ++x) {
			int index = largura * y + x;
			Pieza pieza = lista_piezas[index];

			if (pieza.ver_tipo() == '0') {
				cout << "__ "; // vazio
			}
			else {
				if (pieza.ver_color() == 'N')
					cout << "\033[34m" << pieza.ver_tipo() << "N\033[0m ";
				else cout << pieza.ver_tipo() << "B ";
				
			}
		}
		cout << endl;
	}
}


// Selection overload
void Tablero::dibujar_terminal(const vector<pair<int, int>>& selecionados) {
	cout << endl << "    ";
	for (int x = 0; x < largura; ++x) {
		cout << x << "  ";
	}
	cout << endl;

	for (int y = 0; y < altura; ++y) {
		cout << " " << y << " ";

		for (int x = 0; x < largura; ++x) {
			int index = largura * y + x;
			Pieza pieza = lista_piezas[index];

			bool selecionado = find(selecionados.begin(), selecionados.end(), make_pair(x, y)) != selecionados.end();

			if (selecionado) cout << "\033[100m";

			if (pieza.ver_tipo() == '0') {
				cout << "__"; // vazio
			}
			else {
				if (pieza.ver_color() == 'N')
					cout << "\033[34m" << pieza.ver_tipo() << "N\033[0m";
				else cout << pieza.ver_tipo() << "B";

			}
			if (selecionado)
				cout << "\033[0m";

			cout << " ";
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

void Tablero::mover_pieza(int de_x, int de_y, int para_x, int para_y) {
	Pieza pieza = lista_piezas[largura * de_y + de_x];

	colocar_pieza(para_x, para_y, pieza.ver_tipo(), pieza.ver_color());
	retirar_pieza(de_x, de_y);
}

bool Tablero::verificar_movimiento(int de_x, int de_y, int para_x, int para_y) {
	Pieza pieza = lista_piezas[largura * de_y + de_x];
	Pieza destino = lista_piezas[largura * para_y + para_x]; // Hipotetico, puede estar libre

	// Verificar si movimiento está dentro del tablero
	if (para_x < 0 || para_x >= largura || para_y < 0 || para_y >= altura) {
		return false;
	}

	// Verificar si movimiento es para la misma cedula
	if (para_x == de_x && para_y == de_y) {
		return false;
	}

	// Verificar si movimiento capturaria una pieza amiga
	if (destino.ver_tipo() != '0' && pieza.ver_color() == destino.ver_color()) {
		return false;
	}

	int dx = para_x - de_x;
	int dy = para_y - de_y;

	// Verificar si movimiento es valido para la pieza
	switch (pieza.ver_tipo()) {
	case 'A': // Alfil
		if (abs(dx) != abs(dy))
			return false;
		{
			int paso_x = dx / abs(dx);
			int paso_y = dy / abs(dy);
			int x = de_x + paso_x;
			int y = de_y + paso_y;
			while (x != para_x && y != para_y) {
				if (lista_piezas[y * largura + x].ver_tipo() != '0') return false; // Obstáculo
				x += paso_x;
				y += paso_y;
			}
		}
		break;

	case 'C': // Caballo
		if (!((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)))
			return false;
		break;

	case 'T': // Torre
		if (dx != 0 && dy != 0)
			return false;
		{
			int paso_x = (dx == 0) ? 0 : dx / abs(dx);
			int paso_y = (dy == 0) ? 0 : dy / abs(dy);
			int x = de_x + paso_x;
			int y = de_y + paso_y;
			while (x != para_x || y != para_y) {
				if (lista_piezas[y * largura + x].ver_tipo() != '0') return false;
				x += paso_x;
				y += paso_y;
			}
		}
		break;

	case 'D': // Dama
		if (!(dx == 0 || dy == 0 || abs(dx) == abs(dy)))
			return false;
		{
			int paso_x = (dx == 0) ? 0 : dx / abs(dx);
			int paso_y = (dy == 0) ? 0 : dy / abs(dy);
			int x = de_x + paso_x;
			int y = de_y + paso_y;
			while (x != para_x || y != para_y) {
				if (lista_piezas[y * largura + x].ver_tipo() != '0') return false;
				x += paso_x;
				y += paso_y;
			}
		}
		break;

	case 'R': // Rey
		if (abs(dx) > 1 || abs(dy) > 1)
			return false;
		break;

	case 'P': { // Peón
		int direccion = (pieza.ver_color() == 'B') ? 1 : -1;
		int fila_inicial = (pieza.ver_color() == 'B') ? 1 : altura - 2;

		// Movimiento simple hacia adelante
		if (dx == 0 && dy == direccion && destino.ver_tipo() == '0') return true;

		// Movimiento doble desde la fila inicial
		if (dx == 0 && dy == 2 * direccion &&
			de_y == fila_inicial &&
			destino.ver_tipo() == '0') {

			// Verificar que la celda intermedia también esté vacía
			int y_intermedia = de_y + direccion;
			if (lista_piezas[y_intermedia * largura + de_x].ver_tipo() == '0')
				return true;
		}

		// Captura en diagonal
		if (abs(dx) == 1 && dy == direccion && destino.ver_tipo() != '0')
			return true;

		return false;
		break;
		}
	default:
		return false;
	}
	return true;
}

vector<Pieza> Tablero::listar_piezas() {
	return lista_piezas;
}

int Tablero::ver_altura() {
	return altura;
}

int Tablero::ver_largura() {
	return largura;
}

vector<pair<int, int>> Tablero::listar_movimientos_validos(int position_x, int position_y) {
	vector<pair<int, int>> movimientos_validos;
	for (int x = 0; x < ver_largura(); ++x) {
		for (int y = 0; y < ver_altura(); ++y) {
			if (verificar_movimiento(position_x, position_y, x, y)) {
				movimientos_validos.emplace_back(x, y);
			}
		}
	}
	//cout << "Movimientos validos: ";
	//for (int i = 0; i < movimientos_validos.size(); i++)
	//	cout << "(" << movimientos_validos[i].first << ", " << movimientos_validos[i].second << ") ";
	//cout << endl;

	return movimientos_validos;
}
