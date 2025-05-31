#include "DMenu.h"
#include "freeglut.h"
#include "etsidi.h"
#include <iostream>
#include "DFichas.h"


DMenu::DMenu() : estado(MENU_TABLERO), modoSeleccionado(0), tipoJuego(0) {}
GLuint texturaFondo;

int DMenu::getModoSeleccionado() const {
    return modoSeleccionado;
}

int DMenu::getTipoJuego() const {
    return tipoJuego;
}
extern int jugador_activo;

void DMenu::dibujarMenu(int ancho, int alto) {

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, ancho, alto, 0);

    if (estado == MENU_TABLERO)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
            ETSIDI::getTexture("imagenes/menu_1.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glTexCoord2f(0, 1); glVertex2f(0, alto);
        glTexCoord2f(1, 1); glVertex2f(ancho, alto);
        glTexCoord2f(1, 0); glVertex2f(ancho, 0);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }
    else if (estado == MENU_MODO_JUEGO) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
            ETSIDI::getTexture("imagenes/menu_2.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glTexCoord2f(0, 1); glVertex2f(0, alto);
        glTexCoord2f(1, 1); glVertex2f(ancho, alto);
        glTexCoord2f(1, 0); glVertex2f(ancho, 0);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }
    else if (estado == PAUSA) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
            ETSIDI::getTexture("imagenes/pausa.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glTexCoord2f(0, 1); glVertex2f(0, alto);
        glTexCoord2f(1, 1); glVertex2f(ancho, alto);
        glTexCoord2f(1, 0); glVertex2f(ancho, 0);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }
    else if (estado == PROMOCION_SPEED) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
            ETSIDI::getTexture("imagenes/promocion_speed.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glTexCoord2f(0, 1); glVertex2f(0, alto);
        glTexCoord2f(1, 1); glVertex2f(ancho, alto);
        glTexCoord2f(1, 0); glVertex2f(ancho, 0);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }
    else if (estado == PROMOCION_4x5) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
            ETSIDI::getTexture("imagenes/promocion_4x5.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glTexCoord2f(0, 1); glVertex2f(0, alto);
        glTexCoord2f(1, 1); glVertex2f(ancho, alto);
        glTexCoord2f(1, 0); glVertex2f(ancho, 0);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }
    else if (estado == VICTORIA_CIENCIAS) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
            ETSIDI::getTexture("imagenes/victoria_ciencias.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glTexCoord2f(0, 1); glVertex2f(0, alto);
        glTexCoord2f(1, 1); glVertex2f(ancho, alto);
        glTexCoord2f(1, 0); glVertex2f(ancho, 0);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }
    else if (estado == VICTORIA_LETRAS) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
            ETSIDI::getTexture("imagenes/victoria_letras.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glTexCoord2f(0, 1); glVertex2f(0, alto);
        glTexCoord2f(1, 1); glVertex2f(ancho, alto);
        glTexCoord2f(1, 0); glVertex2f(ancho, 0);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }
    else if (estado == TABLAS) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
            ETSIDI::getTexture("imagenes/tablas.png").id);
        glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glTexCoord2f(0, 1); glVertex2f(0, alto);
        glTexCoord2f(1, 1); glVertex2f(ancho, alto);
        glTexCoord2f(1, 0); glVertex2f(ancho, 0);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glEnd();
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}

void DMenu::procesarClick(int x, int y, int ancho, int alto, char *promocion) {
    int centroY = alto / 2;
    if (estado == MENU_TABLERO) {
        //área clic para elegir tablero 4x5
        int y_inicio_4x5 = centroY - 60;
        int y_fin_4x5 = centroY + 30;
        //área clic para elegir tablero speed chess
        int y_inicio_speed = centroY + 50;
        int y_fin_speed = centroY + 160;
        //botón 4x5
        if (y >= y_inicio_4x5 && y <= y_fin_4x5) {
            modoSeleccionado = 'P';
            estado = MENU_MODO_JUEGO;
        }
        //botón speed chess
        else if (y >= y_inicio_speed && y <= y_fin_speed) {
            modoSeleccionado = 'S';
            estado = MENU_MODO_JUEGO;
        }
    }
    else if (estado == MENU_MODO_JUEGO) {
        //diferentes áreas de clic
        int y_inicio_2player = centroY - 60;
        int y_fin_2player = centroY + 30;
        int y_inicio_IA = centroY + 50;
        int y_fin_IA = centroY + 170;
        int y_inicio_volver = centroY - 280;
        int y_fin_volver = centroY - 170;
        //botón ciencias vs letras
        if (y >= y_inicio_2player && y <= y_fin_2player) {
            tipoJuego = 1;
            estado = EN_JUEGO;
        }
        //botón vs IA
        else if (y >= y_inicio_IA && y <= y_fin_IA) {
            tipoJuego = 2;
            estado = EN_JUEGO;
        }
        //botón para volver
        else if (y >= y_inicio_volver && y <= y_fin_volver) {
            estado = MENU_TABLERO;
        }
    }
    else if (estado == PAUSA) {
        //diferentes áreas de clic
        int y_inicio_renaudar = centroY - 40;
        int y_fin_renaudar = centroY + 50;
        int y_inicio_salir = centroY + 70;
        int y_fin_salir = centroY + 200;
        //botón para salir
        if (y >= y_inicio_salir && y <= y_fin_salir) {
            tipoJuego = 1;
            estado = MENU_TABLERO;
        }
        //botón renaudar
        else if (y >= y_inicio_renaudar && y <= y_fin_renaudar) {
            estado = EN_JUEGO;
        }
    }
    else if (estado == PROMOCION_SPEED) {
        int yBoton = alto - y;  //invertir Y si el origen está abajo

        char tipo = 0;
        if (x >= 200 && x <= 600) {
            if (yBoton >= 400 && yBoton <= 460)
                *promocion = 'D';
            else if (yBoton >= 320 && yBoton <= 380)
                *promocion = 'T';
            else if (yBoton >= 240 && yBoton <= 300)
                *promocion = 'A';
            else if (yBoton >= 160 && yBoton <= 220)
                *promocion = 'C';
        }
    }
    else if (estado == PROMOCION_4x5) {
        int yBoton = alto - y;  // invertir Y si el origen está abajo

        char tipo = 0;
        if (x >= 200 && x <= 600) {
            if (yBoton >= 400 && yBoton <= 500)
                *promocion = 'T';
            else if (yBoton >= 240 && yBoton <= 300)
                *promocion = 'A';
            else if (yBoton >= 160 && yBoton <= 220)
                *promocion = 'C';
        }
    }
    else if (estado == VICTORIA_CIENCIAS || estado == VICTORIA_LETRAS || estado == TABLAS) {
        estado = MENU_TABLERO;
    }
}