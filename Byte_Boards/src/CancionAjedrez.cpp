#include "CancionAjedrez.h"
#include "ETSIDI.h"

bool SonidoAjedrez::musicaReproducida = false;

void SonidoAjedrez::reproducirMovimiento() {
    ETSIDI::play("sonidos/movimiento.wav");
}

void SonidoAjedrez::reproducirJaqueMate() {
    ETSIDI::play("sonidos/jaquemate.wav");
}

void SonidoAjedrez::reproducirJaque() {
    ETSIDI::play("sonidos/jaque.wav");
}

void SonidoAjedrez::iniciarMusicaMenu() {
    if (!musicaReproducida) {
        ETSIDI::playMusica("sonidos/menus.wav", true);
        musicaReproducida = true;
    }
}

void SonidoAjedrez::detenerMusica() {
    ETSIDI::stopMusica();
    musicaReproducida = false;
}

