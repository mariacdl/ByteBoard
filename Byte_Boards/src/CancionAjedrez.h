#pragma once
class SonidoAjedrez {

private:

    static bool musicaReproducida;

public:
    static void iniciarMusicaMenu();
    static void detenerMusica();
    static void reproducirJaque();
    static void reproducirMovimiento();
    static void reproducirJaqueMate();
};
