#include <iostream>
#include "Partida.h"

using namespace std;

int main() {
    Partida partida(8, 8);

    while (true) {
        partida.dibujar_terminal();
        partida.mover_terminal();
        partida.alternar_turno();
    }
}