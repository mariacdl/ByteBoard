#pragma once


enum EstadoJuego { MENU, EN_JUEGO, PAUSA, PROMOCION, FIN };
enum EstadoMenu { MENU_TABLERO, MENU_OPONENTE };
enum TipoFin { VICTORIA_CIENCIAS, VICTORIA_LETRAS, TABLAS, NO_FINALIZADO };
enum TipoJuego { JUEGO_4x5, JUEGO_SPEED, NO_DECIDIDO };
enum TipoOponente { IA, JUGADOR, SIN_OPONENTE };
enum EstadoTurno { BLANCO, NEGRO };