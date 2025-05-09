#include "Partida.h"
#include <iostream>
#include <vector>

using namespace std;

Partida::Partida(int altura, int largura, char oponente, char turno_actual) : tablero(altura, largura) {
    this->turno_actual = turno_actual;
    this->oponente = oponente;
}

void Partida::dibujar_terminal() {
    tablero.dibujar_terminal();
}

void Partida::mover_terminal() {
    int de_x, de_y, para_x, para_y;
    bool decision_invalida = true;
    vector<pair<int, int>> jugadas_validas;

    cout << "\nTurno del jugador " << turno_actual << endl;

    while (decision_invalida) {
        cout << "Digite la posición de la pieza a mover (x y): " << endl;
        cin >> de_x >> de_y;

        jugadas_validas = tablero.listar_movimientos_validos(de_x, de_y);

        if (de_x < 0 || de_x > tablero.ver_largura() || de_y < 0 || de_y > tablero.ver_altura())
            cout << "Escoje una pieza dentro de juego! " << endl;
        else if (turno_actual != tablero.listar_piezas()[tablero.ver_altura() * de_y + de_x].ver_color())
            cout << "Escoje una pieza tuya! " << endl;
        else if (jugadas_validas.empty())
            cout << "Escoje una con movimientos validos! " << endl;
        else decision_invalida = false;

    }

    decision_invalida = true;
    while (decision_invalida) { 
        tablero.dibujar_terminal(jugadas_validas);

        cout << "Digite la posición de destino (x y): " << endl;
        cin >> para_x >> para_y;
        if(!tablero.verificar_movimiento(de_x, de_y, para_x, para_y))
            cout << "Escoje un movimiento valido! " << endl;
        else decision_invalida = false;
    }

    tablero.mover_pieza(de_x, de_y, para_x, para_y);
}

void Partida::alternar_turno() {
    turno_actual = (turno_actual == 'B') ? 'N' : 'B';
}

char Partida::ver_turno() const {
    return turno_actual;
}

void Partida::jugar()  {
    while (true) {
        dibujar_terminal();
        mover_terminal();
        alternar_turno();
    }
}