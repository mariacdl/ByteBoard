#include "Partida.h"
#include "Tablero.h"
#include "Pieza.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

Partida::Partida(char m, char c) : modalidad(m), color_jugador1(c) {
    vista_partida = new VistaPartida();
    tablero = new Tablero(m);
    vista_partida->actualizar_camara(c);
};

const Tablero& Partida::ver_tablero() const {
    return *tablero;
}

char Partida::ver_modalidad() const {
    return modalidad;
}

void Partida::alternar_turno() {
    turno_actual = turno_actual == 'B' ? 'N' : 'B';
    vista_partida->actualizar_camara(turno_actual);
    numero_turnos++;
}

char Partida::ver_turno() const {
    return turno_actual;
}

int Partida::ver_numero_turnos() const {
    return numero_turnos;
}

bool Partida::verificar_movimiento(pair<int, int> desde, pair<int, int> para) {
    return tablero->validar_movimiento(desde, para);
}

vector<pair<int, int>> Partida::listar_movimientos_validos(pair<int, int> casilla) {
    return tablero->listar_movimientos_validos(casilla);
}

Partida::~Partida() {
    delete vista_partida;
    delete tablero;
}

void Partida::dibujar() {
    vista_partida->actualizar_camara(turno_actual);
}

void Partida::actualizar_casilla(pair<int, int> casilla_nueva) {
    if (casilla_nueva != casilla_seleccionada)
        casilla_seleccionada = casilla_nueva;

    tablero->dibujar(casilla_seleccionada);
    cout << "(" << casilla_seleccionada.first << ", " << casilla_seleccionada.second << ")" << endl;
}

bool Partida::jugar(pair<int, int> desde, pair<int, int> para) {
    if (tablero->ver_pieza(desde)->ver_color() == turno_actual) {
        if (mover(desde, para)) {
            alternar_turno();
            return true;
        }
        else {
            cout << "Movimiento invalido para: " << tablero->ver_pieza(desde)->ver_tipo() << endl;
            return false;
        }
    }
    cout << "Esta intentando mover una pieza que no es tuya" << endl;
    return false;
}

bool Partida::mover(pair<int, int> desde, pair<int, int> para) {
    if (verificar_movimiento(desde, para)) {
        Tablero copia = *tablero;

        tablero->mover_pieza(desde, para);

        // Si la jugada deja al rey en jaque, no es válida
        if (determinar_jaque(tablero->ver_pieza(para)->ver_color())) {
            *tablero = copia;
            return false;
        }

        // Detectar peon para captura al paso
        if (tablero->ver_pieza(para)->ver_tipo() == 'P' && abs(para.second - desde.second) == 2) {
            peon_passant = para;
        }
        else {
            peon_passant = { -1, -1 };
        }

        int extremo_opuesto;
        if (tablero->ver_pieza(para)->ver_color() == 'B') {
            extremo_opuesto = 0;
        }
        else {
            extremo_opuesto = (modalidad == 'P') ? 4 : 5;
        }

        // Promoción
        if (tablero->ver_pieza(para)->ver_tipo() == 'P' && para.second == extremo_opuesto) {
            promocion = para;
        }

        return true;
    }
    return false;
}

bool Partida::determinar_jaque(char color) {
    char color_opuesto = (color == 'B') ? 'N' : 'B';

    for (int x = 0; x < tablero->ver_ancho(); ++x) {
        for (int y = 0; y < tablero->ver_largo(); ++y) {
            Pieza* p = tablero->ver_pieza({ x, y });
            if (p != nullptr && p->ver_color() == color_opuesto) {
                vector<pair<int, int>> movimientos = listar_movimientos_validos({ x, y });
                for (const auto& mov : movimientos) {
                    Pieza* destino = tablero->ver_pieza(mov);
                    if (destino != nullptr && destino->ver_color() == color && destino->ver_tipo() == 'R') {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Partida::sin_movimientos_validos(char color) {
    Tablero copia = *tablero;
    for (int x = 0; x < tablero->ver_ancho(); ++x) {
        for (int y = 0; y < tablero->ver_largo(); ++y) {
            Pieza* p = tablero->ver_pieza({ x, y });
            if (p != nullptr && p->ver_color() == color) {
                vector<pair<int, int>> movimientos = listar_movimientos_validos({ x, y });
                for (const auto& mov : movimientos) {
                    if (mover({ x, y }, mov)) {
                        *tablero = copia;
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Partida::determinar_jaque_mate(char color) {
    return determinar_jaque(color) && sin_movimientos_validos(color);
}

char Partida::determinar_fin() {
    if (determinar_jaque_mate(turno_actual))
        return turno_actual;
    if (sin_movimientos_validos(turno_actual))
        return 'T';
    return '0';
}

bool Partida::enrocar(char color) {
    pair<int, int> pos_torre;
    pair<int, int> pos_rey;

    if (color == '0') return false;

    if (modalidad == 'P') {
        pos_torre = (color == 'B') ? make_pair(0, 4) : make_pair(3, 0);
        pos_rey = (color == 'B') ? make_pair(3, 4) : make_pair(0, 0);
    }
    else {
        pos_torre = (color == 'B') ? make_pair(0, 5) : make_pair(4, 0);
        pos_rey = (color == 'B') ? make_pair(3, 5) : make_pair(1, 0);
    }

    Pieza* torre = tablero->ver_pieza(pos_torre);
    Pieza* rey = tablero->ver_pieza(pos_rey);

    if (!(torre->ver_tipo() == 'T' && torre->ver_numero_movimientos() == 0 && rey->ver_tipo() == 'R' && rey->ver_numero_movimientos() == 0)) {
        return false;
    }

    if (determinar_jaque(color)) {
        return false;
    }

    int dir = (pos_torre.first - pos_rey.first) / abs(pos_torre.first - pos_rey.first);

    for (int i = 1; i < abs(pos_torre.first - pos_rey.first); i++) {
        if (tablero->ver_pieza({ pos_rey.first + i * dir, pos_rey.second })->ver_tipo() != '0') {
            return false;
        }
    }

    Tablero copia = *tablero;

    tablero->mover_pieza(pos_rey, { pos_rey.first + 2 * dir, pos_rey.second });
    tablero->mover_pieza(pos_torre, { pos_rey.first + dir, pos_rey.second });

    if (determinar_jaque(color)) {
        *tablero = copia;
        return false;
    }
    return true;
}

bool Partida::jugar(char color) {
    if (color == turno_actual) {
        if (enrocar(color)) {
            peon_passant = { -1, -1 };
            alternar_turno();
            return true;
        }
        else {
            cout << "Intento de enroque invalido" << endl;
            return false;
        }
    }
    cout << "No puede realizar un enroque correspondiente al equipo contrario" << endl;
    return false;
}

pair<int, int> Partida::getPromocion() {
    return promocion;
}

bool Partida::promocionar(char tipo) {
    Pieza* pieza = tablero->ver_pieza(promocion);
    if (promocion.first != -1) {
        if (pieza->ver_color() == 'B') {
            for (char t : promocionesB) {
                if (t == tipo) {
                    cout << "No se puede promocionar el peon a una pieza a la que ya se ha promocionado otro anteriormente" << endl;
                    return false;
                }
            }
            promocionesB.push_back(tipo);
        }
        else {
            for (char t : promocionesN) {
                if (t == tipo) {
                    cout << "No se puede promocionar el peon a una pieza a la que ya se ha promocionado otro anteriormente" << endl;
                    return false;
                }
            }
            promocionesN.push_back(tipo);
        }

        tablero->colocar_pieza(promocion, tipo, pieza->ver_color(), pieza->ver_numero_movimientos());
        promocion = { -1, -1 };
        return true;
    }
    return false;
}
