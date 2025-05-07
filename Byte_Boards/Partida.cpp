#include "Partida.h"
#include <iostream>
#include <vector>

using namespace std;

Partida::Partida(int altura, int largura) : tablero(altura, largura) {
    turno_actual = 'B'; // Empieza con blanco
}

void Partida::dibujar_terminal() {
    tablero.dibujar_terminal();
}

void Partida::mover_terminal() {
    int pos_x, pos_y, para_x, para_y;
    bool decision_valida = true;

    cout << "\nTurno del jugador " << turno_actual << endl;

    while (decision_valida) {
        cout << "Digite la posición de la pieza a mover (x y): ";
        cin >> pos_x >> pos_y;

        if (pos_x < 0 || pos_x > tablero.ver_largura() || pos_y < 0 || pos_y > tablero.ver_altura())
            cout << "Escoje una pieza dentro de juego! " << endl;
        else if (turno_actual != tablero.listar_piezas()[tablero.ver_altura() * pos_y + pos_x].ver_color())
            cout << "Escoje una pieza tuya! " << endl;
        else decision_valida = false;
    }

    decision_valida = true;
    while (decision_valida) {
        cout << "Digite la posición de destino (x y): ";
        cin >> para_x >> para_y;
        if(!tablero.verificar_movimiento(pos_x, pos_y, para_x, para_y))
            cout << "Escoje un movimiento valido! " << endl;
        else decision_valida = false;
    }
}

void Partida::alternar_turno() {
    turno_actual = (turno_actual == 'B') ? 'N' : 'B';
}

char Partida::ver_turno() const {
    return turno_actual;
}
