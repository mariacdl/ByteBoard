#include "Tablero.h"
#include "Pieza.h"
#include "Peon.h"
#include "Torre.h"
#include "Alfil.h"
#include "Rey.h"
#include "Caballo.h"
#include "Dama.h"
#include "Estados.h"
#include <iostream>

using namespace std;

Tablero::Tablero(TipoJuego m) : modalidad(m), largura((m == JUEGO_4x5) ? 4 : 5), altura((m == JUEGO_4x5) ? 5 : 6) {
    vista_tablero = new VistaTablero(m);
    lista_piezas.resize(largura * altura, nullptr); // Inicializa con punteros nulos

    if (modalidad == JUEGO_4x5) {
        colocar_pieza({ 0, 0 }, 'R', NEGRO);
        colocar_pieza({ 0, 1 }, 'C', NEGRO);
        colocar_pieza({ 0, 2 }, 'A', NEGRO);
        colocar_pieza({ 0, 3 }, 'T', NEGRO);
        colocar_pieza({ 1, 0 }, 'P', NEGRO);

        colocar_pieza({ 4, 3 }, 'R', BLANCO);
        colocar_pieza({ 4, 2 }, 'C', BLANCO);
        colocar_pieza({ 4, 1 }, 'A', BLANCO);
        colocar_pieza({ 4, 0 }, 'T', BLANCO);
        colocar_pieza({ 3, 3 }, 'P', BLANCO);
    }
    else {
        colocar_pieza({ 0, 0 }, 'D', NEGRO);
        colocar_pieza({ 0, 1 }, 'R', NEGRO);
        colocar_pieza({ 0, 2 }, 'A', NEGRO);
        colocar_pieza({ 0, 3 }, 'C', NEGRO);
        colocar_pieza({ 0, 4 }, 'T', NEGRO);
        for (int i = 0; i < 5; i++) colocar_pieza({ 1, i }, 'P', NEGRO);

        colocar_pieza({ 5, 0 }, 'T', BLANCO);
        colocar_pieza({ 5, 1 }, 'C', BLANCO);
        colocar_pieza({ 5, 2 }, 'A', BLANCO);
        colocar_pieza({ 5, 3 }, 'R', BLANCO);
        colocar_pieza({ 5, 4 }, 'D', BLANCO);  // 4 5
        for (int i = 0; i < 5; i++) colocar_pieza({ 4, i }, 'P', BLANCO);
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
int Tablero::ver_altura() const { return altura; }
int Tablero::ver_largura() const { return largura; }
char Tablero::ver_modalidad() const { return modalidad; }

Pieza* Tablero::ver_pieza(pair<int, int> pos) const {
    return lista_piezas[largura * pos.first + pos.second];
}

void Tablero::colocar_pieza(pair<int, int> pos, char tipo, EstadoTurno color, int numero_movimientos) {
    int index = largura * pos.first + pos.second;
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
    int index = largura * pos.first + pos.second;
    delete lista_piezas[index];
    lista_piezas[index] = nullptr;
}

void Tablero::mover_pieza(pair<int, int> origen, pair<int, int> destino) {
    int index_origen = largura * origen.first + origen.second;
    int index_destino = largura * destino.first + destino.second;

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
    for (int x = 0; x < altura; ++x) {
        for (int y = 0; y < largura; ++y) {
            if (validar_movimiento(casilla, { x, y })) {
                movimientos_validos.emplace_back(x, y);
            }
        }
    }
    cout << modalidad << "     ";
    for (auto mov : movimientos_validos) {
        cout << "   (" << mov.first << ", " << mov.second << ") ";
        cout << mov.first * largura + mov.second << endl;
    }
    return movimientos_validos;
}

const vector<Pieza*>& Tablero::listar_piezas() const {
    return lista_piezas;
}