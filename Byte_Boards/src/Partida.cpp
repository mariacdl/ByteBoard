#include "Partida.h"
#include "Tablero.h"
#include "Pieza.h"
#include "Estados.h"
#include "GestorJuego.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Partida::Partida(TipoJuego m, EstadoTurno c) : modalidad(m), color_jugador1(c), turno_actual(c) {
    vista_partida = new VistaPartida();
    tablero = new Tablero(m);
    vista_partida->actualizar_camara(c);
};

Partida::~Partida() {
    delete vista_partida;
    delete tablero;
}

const Tablero& Partida::ver_tablero() const {
    return *tablero;
}

char Partida::ver_modalidad() const {
    return modalidad;
}

char Partida::ver_turno() const {
    return turno_actual;
}

int Partida::ver_numero_turnos() const {
    return numero_turnos;
}

void Partida::alternar_turno() {
    turno_actual = (turno_actual == BLANCO) ? NEGRO : BLANCO;
    vista_partida->actualizar_camara(turno_actual);
    numero_turnos++;
}

bool Partida::verificar_movimiento(pair<int, int> desde, pair<int, int> para, bool jaque = false) {
    return tablero->validar_movimiento(desde, para, jaque);
}

vector<pair<int, int>> Partida::listar_movimientos_validos(pair<int, int> casilla) {
    return tablero->listar_movimientos_validos(casilla, turno_actual);
}

void Partida::dibujar() {
    vista_partida->actualizar_camara(turno_actual);
    tablero->dibujar(casilla_seleccionada, ultimos_movimientos_validos);
}

void Partida::actualizar_casilla(pair<int, int> casilla_nueva) {
    if (casilla_nueva != casilla_seleccionada) {
        casilla_seleccionada = casilla_nueva;

        if (casilla_nueva != make_pair(-1, -1))
            ultimos_movimientos_validos = tablero->listar_movimientos_validos(casilla_nueva, turno_actual);
        else
            ultimos_movimientos_validos.clear();
    }
}

void Partida::jugar(pair<int, int> desde, pair<int, int> para) {
    if (validar_jugada(desde, para)) {
        tablero->mover_pieza(desde, para);
        alternar_turno();
    } else {
        ultimos_movimientos_validos.clear();
    }
}

bool Partida::validar_jugada(pair<int, int>desde, pair<int, int>para) {
    auto pieza = tablero->ver_pieza(desde);
    auto copia_tablero = tablero;
    auto rey_en_jaque = (turno_actual == BLANCO) ? rey_blanco_en_jaque : rey_negro_en_jaque;

    // Revisa si pieza existe
    if (pieza == nullptr) {
        cout << "Selecciona una pieza" << endl;
        return false;
    }

    cout << turno_actual << endl;
    cout << pieza->ver_color() << "  " << pieza->ver_tipo() << endl;

    // Verifica si la pieza es del jugador
    if (pieza->ver_color() != turno_actual) {
        cout << "Esta intentando mover una pieza que no es tuya" << endl;
        return false;
    }
        
    // Verifica si la jugada es valida (sin contar jaque)
    auto movimientos_validos = listar_movimientos_validos(desde);
    if (find(movimientos_validos.begin(), movimientos_validos.end(), para) == movimientos_validos.end()) {
        cout << "Movimiento invalido desde (" << desde.first << ", " << desde.second << ")";
        cout << " hasta (" << para.first << ", " << para.second << ")" << endl;
        return false;
    }
        
    return true;
}

bool Partida::verificar_promocion_disponible() {
    pair<int, int> pos_peon = tablero->ver_peon_promocionable();
    pos_peon_promocionable = pos_peon;
    if (pos_peon != make_pair(-1, -1))
        return true;
}

void Partida::promocionar(char nuevo_tipo) const {

    tablero->colocar_pieza(pos_peon_promocionable, nuevo_tipo);
}
