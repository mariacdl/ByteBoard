#include "Sonido.h"
#include "ETSIDI.h"
#include <iostream>

using namespace std;


bool Sonido::musicaReproducida = false;

void Sonido::reproducirMovimiento() {
    cout << "Reproduciendo sonido de movimiento" << endl;
    ETSIDI::play("sonidos/movimiento.wav");
}

void Sonido::reproducirJaqueMate() {
    cout << "Reproduciendo sonido de jaque-mate" << endl;
    ETSIDI::play("sonidos/jaquemate.wav");
}

void Sonido::reproducirJaque() {
    cout << "Reproduciendo sonido de jaque" << endl;
    ETSIDI::play("sonidos/jaque.wav");
}

void Sonido::iniciarMusicaMenu() {
    if (!musicaReproducida) {
        cout << "Reproduciendo musica de menu" << endl;
        ETSIDI::playMusica("sonidos/menus.wav", true);
        musicaReproducida = true;
    }
}

void Sonido::detenerMusica() {
    cout << "Deteniendo musica" << endl;
    ETSIDI::stopMusica();
    musicaReproducida = false;
}

