#include "Menu.h"
#include "freeglut.h"
#include "etsidi.h"
#include <iostream>


Menu::Menu() : estado(MENU_TABLERO), modoSeleccionado(0), tipoJuego(0) {}
GLuint texturaFondo;

EstadoJuego Menu::getEstado() const {
    return estado;
}

int Menu::getModoSeleccionado() const {
    return modoSeleccionado;
}

int Menu::getTipoJuego() const {
    return tipoJuego;
}

void dibujarCuadro(int centroX, int y, int alto, const char* texto,
    double rFondo, double gFondo, double bFondo)
{
    int len = strlen(texto);
    int textWidth = len * 9;
    // Ancho del botón con margen horizontal adicional
    int paddingHorizontal = 40;
    int ancho = textWidth + paddingHorizontal;
    // Marco exterior
    glColor3f(rFondo, gFondo, bFondo);
    glBegin(GL_QUADS);
    glVertex2f(centroX - ancho / 2, y - alto / 2);
    glVertex2f(centroX + ancho / 2, y - alto / 2);
    glVertex2f(centroX + ancho / 2, y + alto / 2);
    glVertex2f(centroX - ancho / 2, y + alto / 2);
    glEnd();
    // Texto centrado
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    glRasterPos2f(centroX - textWidth / 2, y + 5);
    for (const char* c = texto; *c; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    glEnable(GL_LIGHTING);
}

void Menu::dibujarMenu(int ancho, int alto) {

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
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}

void Menu::procesarClick(int x, int y, int ancho, int alto) {
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
            modoSeleccionado = 1;
            estado = MENU_MODO_JUEGO;
        }
        //botón speed chess
        else if (y >= y_inicio_speed && y <= y_fin_speed) {
            modoSeleccionado = 2;
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
}
