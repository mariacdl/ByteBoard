#include <iostream>
#include "GestorJuego.h"
#include "freeglut.h"

using namespace std;


void GestorJuego::dibujar() {
    // Limpiar los buffers y resetear la matriz ModelView una sola vez por frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // Restablece la matriz MODELVIEW para empezar el frame limpio

    // Gestionar la configuración de la proyección y la vista de la cámara
    if (estado_juego == EN_JUEGO) {
        // Configuración 3D para el tablero
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(40.0, glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.1, 150.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); // Vuelve a cargar la identidad para la matriz ModelView antes de la cámara

    }
    else {
        // Configuración 2D para menús, pausa, promoción, fin de juego
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // Usa una proyección ortográfica para 2D. Esto mapea píxeles directamente
       
        glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); // Para 2D, la identidad suele ser suficiente para ModelView
    }

    switch (estado_juego) {
    case MENU:
        switch (estado_menu) {
        case MENU_TABLERO:
            vista_juego->dibujar_menu_tablero();
            break;
        case MENU_OPONENTE:
            vista_juego->dibujar_menu_oponente();
            break;
        default:
            break;
        }
        break;
    case PAUSA:
        vista_juego->dibujar_pausa();
        break;
    case PROMOCION:
        if (tipo_juego == JUEGO_4x5)
            vista_juego->dibujar_promocion_4x5();
        else
            vista_juego->dibujar_promocion_speed();
        break;
    case FIN:
        switch (tipo_fin) {
        case VICTORIA_CIENCIAS:
            vista_juego->dibujar_victoria_ciencias();
            break;
        case VICTORIA_LETRAS:
            vista_juego->dibujar_victoria_letras();
            break;
        case TABLAS:
            vista_juego->dibujar_fin_tablas();
            break;
        default:
            break;
        }
        break;
    case EN_JUEGO:
        partida->dibujar();
        partida->actualizar_casilla(casilla_seleccionada);
        break;
    }

    // Intercambiar los buffers para mostrar el frame renderizado
    glutSwapBuffers();
}

void GestorJuego::interactuar(int cursor_x, int cursor_y) {
    // Gerencia las interaciones
    switch (estado_juego) {
    case MENU:
        seleccionar_menu(cursor_x, cursor_y);
        break;
    case EN_JUEGO:
        seleccionar_casilla(cursor_x, cursor_y);
        break;
    case PAUSA:
        seleccionar_pausa(cursor_x, cursor_y);
        break;
    case PROMOCION:
        seleccionar_promocion(cursor_x, cursor_y);
        break;
    case FIN:
        seleccionar_fin(cursor_x, cursor_y);
        break;
    default:
        break;
    }
}

void GestorJuego::seleccionar_menu(int cursor_x, int cursor_y) {
    // En menu
    switch (estado_menu) {
    case MENU_TABLERO:
        // Seleccionar 4x5
        if (click_area(cursor_x, cursor_y,240,250,580,330)) {
            tipo_juego = JUEGO_4x5;
            estado_menu = MENU_OPONENTE;
        }
        // Seleccionar speed
        if (click_area(cursor_x, cursor_y, 240, 350, 580, 430)) {
            tipo_juego = JUEGO_SPEED;
            estado_menu = MENU_OPONENTE;
        }
        break;
    case MENU_OPONENTE:
        // Seleccionar contra jugador
        if (click_area(cursor_x, cursor_y, 240, 240, 590, 380)) {
            tipo_oponente = JUGADOR;
            estado_menu = MENU_TABLERO;
            estado_juego = EN_JUEGO;
            iniciar_partida();
        }
        // Seleccionar contra IA
        if (click_area(cursor_x, cursor_y, 240, 390, 580, 470)) {
            tipo_oponente = IA;
            estado_menu = MENU_TABLERO;
            estado_juego = EN_JUEGO;
            iniciar_partida();
        }
        // Seleccionar volver
        if (click_area(cursor_x, cursor_y, 50, 40, 260, 130)) {
            tipo_oponente = SIN_OPONENTE;
            estado_menu = MENU_TABLERO;
            estado_juego = MENU;
        }
        break;
    }
}

void GestorJuego::seleccionar_casilla(int cursor_x, int cursor_y) {
      // Si el juego no está en estado válido, anula selección
    if (estado_juego != EN_JUEGO || partida == nullptr) {
        casilla_seleccionada = { -1, -1 };
        return;
    }

    // Obtener matrices y viewport
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = static_cast<float>(cursor_x);
    winY = static_cast<float>(viewport[3]) - static_cast<float>(cursor_y);

    // Leer profundidad (para saber a qué altura está clicando)
    glReadPixels(cursor_x, static_cast<int>(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    // Si la profundidad es 1.0f significa que no hay nada dibujado en ese píxel (clic fuera)
    if (winZ == 1.0f) {
        casilla_seleccionada = { -1, -1 };
        return;
    }

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    float tam = partida->ver_tablero().ver_vista_tablero().getTam();
    float origenX = -((partida->ver_tablero().ver_largura() * tam) / 2.0f);
    float origenZ = -((partida->ver_tablero().ver_altura() * tam) / 2.0f);

    int columna = static_cast<int>((posX - origenX) / tam);
    int fila = static_cast<int>((posZ - origenZ) / tam);

    // Verifica si la posición calculada está dentro del tablero
    if (fila >= 0 && fila < partida->ver_tablero().ver_altura() &&
        columna >= 0 && columna < partida->ver_tablero().ver_largura()) {
        casilla_seleccionada = { fila, columna };
    }
    else {
        // Clic fuera del área del tablero
        casilla_seleccionada = { -1, -1 };
    }
}

void GestorJuego::seleccionar_pausa(int cursor_x, int cursor_y) {
    // En pausa
    // Seleccionar renaudar
    if (click_area(cursor_x, cursor_y, 260, 260, 540, 360)) {
        estado_juego = estado_juego_anterior;
        estado_juego_anterior = PAUSA;
    }
    // Seleccionar menu
    if (click_area(cursor_x, cursor_y, 240, 390, 580, 470)) {
        estado_juego = MENU;
        estado_menu = MENU_TABLERO;
        tipo_fin = NO_FINALIZADO;
        tipo_juego = NO_DECIDIDO;
        tipo_oponente = SIN_OPONENTE;

        estado_juego_anterior = MENU;
    }
}

void GestorJuego::seleccionar_promocion(int cursor_x, int cursor_y) {
    if (tipo_juego == JUEGO_4x5) {
        if (click_area(cursor_x, cursor_y, 300, 110, 520, 120)) {
            partida->promocionar('T'); // Torre
            estado_juego = EN_JUEGO;
        }
        
        if (click_area(cursor_x, cursor_y, 300, 280, 520, 350)) {
            partida->promocionar('A'); // Alfil
            estado_juego = EN_JUEGO;
        }
            
        if (click_area(cursor_x, cursor_y, 300, 400, 520, 480)) {
            partida->promocionar('C'); // Caballo
            estado_juego = EN_JUEGO;
        }
    }
    if (tipo_juego == JUEGO_SPEED) {
        if (click_area(cursor_x, cursor_y, 280, 100, 520, 180)) {
            partida->promocionar('D'); // Dama o Reina
            estado_juego = EN_JUEGO;
        }
        if (click_area(cursor_x, cursor_y, 280, 210, 520, 290)) {
            partida->promocionar('T'); // Torre
            estado_juego = EN_JUEGO;
        }
        if (click_area(cursor_x, cursor_y, 280, 320, 520, 390)) {
            partida->promocionar('A'); // Alfil
            estado_juego = EN_JUEGO;
        }
        if (click_area(cursor_x, cursor_y, 280, 420, 520, 500)) {
            partida->promocionar('C'); // Caballo
            estado_juego = EN_JUEGO;
        }
    }
}

void GestorJuego::seleccionar_fin(int cursor_x, int cursor_y) {
    switch (tipo_fin) {
    case VICTORIA_CIENCIAS:
        if (click_area(cursor_x, cursor_y, 70, 300, 380, 390)) {
            estado_juego = MENU;
            estado_menu = MENU_TABLERO;
            tipo_fin = NO_FINALIZADO;
            tipo_juego = NO_DECIDIDO;
            tipo_oponente = SIN_OPONENTE;

            estado_juego_anterior = MENU;
        }
        break;
    case VICTORIA_LETRAS:
        if (click_area(cursor_x, cursor_y, 240, 490, 560, 560)) {
            estado_juego = MENU;
            estado_menu = MENU_TABLERO;
            tipo_fin = NO_FINALIZADO;
            tipo_juego = NO_DECIDIDO;
            tipo_oponente = SIN_OPONENTE;

            estado_juego_anterior = MENU;
        }
        break;
    case TABLAS:
        if (click_area(cursor_x, cursor_y, 150, 500, 640, 590)) {
            estado_juego = MENU;
            estado_menu = MENU_TABLERO;
            tipo_fin = NO_FINALIZADO;
            tipo_juego = NO_DECIDIDO;
            tipo_oponente = SIN_OPONENTE;

            estado_juego_anterior = MENU;
        }
        break;
    case NO_FINALIZADO:
        break;
    default:
        break;
    }
}

bool GestorJuego::click_area(int cursor_x, int cursor_y, int x1, int y1, int x2, int y2) const {
    return cursor_x >= x1 && cursor_x <= x2 && cursor_y >= y1 && cursor_y <= y2;
}

void GestorJuego::procesar_tecla(unsigned char key) {
    if (key == 27) { // ESC
        switch (estado_juego) {
        // En menu no se activa
        case MENU:
            break;
        case EN_JUEGO:
            estado_juego = PAUSA;
            estado_juego_anterior = EN_JUEGO;
            break;
        // En pausa renauda el estado anterior
        case PAUSA:
            estado_juego = estado_juego_anterior;
            estado_juego_anterior = PAUSA;
            break;
        case PROMOCION:
            estado_juego = PAUSA;
            estado_juego_anterior = PROMOCION;
            break;
        case FIN:
            estado_juego = MENU;
            estado_juego_anterior = MENU;
            break;
        default:
            break;
        }
        glutPostRedisplay();
    }
}

void GestorJuego::iniciar_partida() {
    if (partida) {
        delete partida;
        partida = nullptr; 
    }
    else if (tipo_oponente != SIN_OPONENTE && tipo_juego != NO_DECIDIDO) 
        partida = new Partida(tipo_juego, BLANCO);
    else
        partida = nullptr;
    
    casilla_seleccionada = { -1, -1 };
}