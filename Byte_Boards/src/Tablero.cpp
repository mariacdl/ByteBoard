#include "Tablero.h"
#include "Pieza.h"
#include "Peon.h"
#include "Torre.h"
#include "Alfil.h"
#include "Rey.h"
#include "Caballo.h"
#include "Dama.h"
#include <iostream>

using namespace std;

Tablero::Tablero(char m) : modalidad(m), ancho((m == 'P') ? 4 : 5), largo((m == 'P') ? 5 : 6) {
    vista_tablero = new VistaTablero(m);
    lista_piezas.resize(ancho * largo, nullptr); // Inicializa con punteros nulos

    if (modalidad == 'P') {
        colocar_pieza({ 0, 0 }, 'R', 'N');
        colocar_pieza({ 1, 0 }, 'C', 'N');
        colocar_pieza({ 2, 0 }, 'A', 'N');
        colocar_pieza({ 3, 0 }, 'T', 'N');
        colocar_pieza({ 0, 1 }, 'P', 'N');

        colocar_pieza({ 3, 4 }, 'R', 'B');
        colocar_pieza({ 0, 4 }, 'T', 'B');
        colocar_pieza({ 3, 3 }, 'P', 'B');
    }
    else {
        colocar_pieza({ 0, 0 }, 'D', 'N');
        colocar_pieza({ 1, 0 }, 'R', 'N');
        colocar_pieza({ 2, 0 }, 'A', 'N');
        colocar_pieza({ 3, 0 }, 'C', 'N');
        colocar_pieza({ 4, 0 }, 'T', 'N');
        for (int i = 0; i < 5; i++) colocar_pieza({ i, 1 }, 'P', 'N');

        colocar_pieza({ 0, 5 }, 'T', 'B');
        colocar_pieza({ 1, 5 }, 'C', 'B');
        colocar_pieza({ 2, 5 }, 'A', 'B');
        colocar_pieza({ 3, 5 }, 'R', 'B');
        colocar_pieza({ 4, 5 }, 'D', 'B');
        for (int i = 0; i < 5; i++) colocar_pieza({ i, 4 }, 'P', 'B');
    }
}

Tablero::~Tablero() {
    delete vista_tablero;
    for (auto pieza : lista_piezas) delete pieza;
}

void Tablero::dibujar(pair<int, int> casilla_seleccionada) {
    vista_tablero->dibujar_tablero(*this);
    vista_tablero->dibujar_seleccion(casilla_seleccionada, *this);
    vista_tablero->dibujar_movimientos(casilla_seleccionada, *this);
}

const VistaTablero& Tablero::ver_vista_tablero() const { return *vista_tablero; }
int Tablero::ver_largo() const { return largo; }
int Tablero::ver_ancho() const { return ancho; }
char Tablero::ver_modalidad() const { return modalidad; }

Pieza* Tablero::ver_pieza(pair<int, int> pos) const {
    return lista_piezas[ancho * pos.second + pos.first];
}

void Tablero::colocar_pieza(pair<int, int> pos, char tipo, char color, int numero_movimientos) {
    int index = ancho * pos.second + pos.first;
    delete lista_piezas[index]; // evita memory leak

    Pieza* nueva = nullptr;
    switch (tipo) {
    case 'P': nueva = new Peon(color); break;
    case 'T': nueva = new Torre(color); break;
    case 'A': nueva = new Alfil(color); break;
    case 'C': nueva = new Caballo(color); break;
    case 'D': nueva = new Dama(color); break;
    case 'R': nueva = new Rey(color); break;
    default: nueva = nullptr;
    }
    lista_piezas[index] = nueva;
}

void Tablero::retirar_pieza(pair<int, int> pos) {
    int index = ancho * pos.second + pos.first;
    delete lista_piezas[index];
    lista_piezas[index] = nullptr;
}

void Tablero::mover_pieza(pair<int, int> origen, pair<int, int> destino) {
    int index_origen = ancho * origen.second + origen.first;
    int index_destino = ancho * destino.second + destino.first;

    if (lista_piezas[index_origen]) {
        delete lista_piezas[index_destino]; // capturar si hay
        lista_piezas[index_destino] = lista_piezas[index_origen];
        lista_piezas[index_origen] = nullptr;
        lista_piezas[index_destino]->incrementar_movimiento();
    }
}

bool Tablero::validar_movimiento(pair<int, int> origen, pair<int, int> destino) const {
    Pieza* pieza = ver_pieza(origen);
    return pieza && pieza->validar_movimiento(origen.first, origen.second, destino.first, destino.second, *this);
}

vector<pair<int, int>> Tablero::listar_movimientos_validos(pair<int, int> casilla) const {
    vector<pair<int, int>> movimientos_validos;
    for (int x = 0; x < ancho; ++x) {
        for (int y = 0; y < largo; ++y) {
            if (validar_movimiento(casilla, { x, y })) {
                movimientos_validos.emplace_back(x, y);
            }
        }
    }
    return movimientos_validos;
}

const vector<Pieza*>& Tablero::listar_piezas() const {
    return lista_piezas;
}