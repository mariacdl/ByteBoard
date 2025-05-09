#include "Partida.h"
#include "Oponente.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

Partida::Partida(int altura, int largura, char oponente, char turno_actual) : tablero(altura, largura) {
    this->turno_actual = turno_actual;
    this->oponente = oponente;
}

void Partida::dibujar_terminal() {
    tablero.dibujar_terminal();
}

void Partida::jugar_terminal() {
    if (oponente == 'J' || turno_actual == 'B') {
        mover_jugador();
    }
    else {
        mover_oponente();
    }
}

void Partida::mover_jugador() {
    int de_x, de_y, para_x, para_y;
    bool decision_invalida = true;
    vector<pair<int, int>> jugadas_validas;

    cout << "\nTurno del jugador " << turno_actual << endl;

    while (decision_invalida) {
        cout << "Digite la posición de la pieza a mover (x y): ";
        cin >> de_x >> de_y;

        jugadas_validas = tablero.listar_movimientos_validos(de_x, de_y);

        if (de_x < 0 || de_x >= tablero.ver_largura() || de_y < 0 || de_y >= tablero.ver_altura())
            cout << "¡Escoge una pieza dentro del tablero!" << endl;
        else if (turno_actual != tablero.listar_piezas()[tablero.ver_largura() * de_y + de_x].ver_color())
            cout << "¡Escoge una pieza tuya!" << endl;
        else if (jugadas_validas.empty())
            cout << "¡Esa pieza no tiene movimientos válidos!" << endl;
        else decision_invalida = false;
    }

    decision_invalida = true;
    while (decision_invalida) {
        tablero.dibujar_terminal(jugadas_validas);

        cout << "Digite la posición de destino (x y): ";
        cin >> para_x >> para_y;

        if (!tablero.verificar_movimiento(de_x, de_y, para_x, para_y))
            cout << "¡Movimiento no válido!" << endl;
        else decision_invalida = false;
    }

    tablero.mover_pieza(de_x, de_y, para_x, para_y);
}

void Partida::mover_oponente() {
    Oponente oponente('N', 0.0);

    pair<pair<int, int>, pair<int, int>> jugada = oponente.elegir_proxima_jugada(tablero);

    tablero.mover_pieza(jugada.first.first, jugada.first.second, jugada.second.first, jugada.second.second);
}

void Partida::alternar_turno() {
    turno_actual = (turno_actual == 'B') ? 'N' : 'B';
}

char Partida::ver_turno() const {
    return turno_actual;
}

void Partida::jugar() {
    while (true) {
        dibujar_terminal();
        jugar_terminal();
        alternar_turno();
    }
}
