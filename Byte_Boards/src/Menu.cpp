#include "Menu.h"
#include "freeglut.h"
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

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();            
    glLoadIdentity();

    int centroX = ancho / 2;
    int centroY = alto / 2;

    if (estado == MENU_TABLERO) 
    {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 1);
        glRasterPos2f(centroX - 100, centroY - 150);
        const char* titulo = "ELEGIR TIPO DE JUEGO:";
        for (const char* c = titulo; *c; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        glEnable(GL_LIGHTING);
        dibujarCuadro(centroX, centroY-50, 50, "Ajedrez 4x5 (un peon)", 0.2, 0.2, 0.6);
        dibujarCuadro(centroX, centroY+50, 50, "Speed Chess", 0.2, 0.2, 0.6);
    }
    else if (estado == MENU_MODO_JUEGO) {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 1);
        glRasterPos2f(centroX - 100, centroY - 150);
        const char* titulo = "ELEGIR CONTRINCANTE:";
        for (const char* c = titulo; *c; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        glEnable(GL_LIGHTING);
        dibujarCuadro(centroX , centroY - 50, 50, "Blancas VS Negras", 0.3, 0.2, 0.2);
        dibujarCuadro(centroX , centroY + 50, 50, "VS IA", 0.3, 0.2, 0.2);
        dibujarCuadro(centroX-300, centroY - 200, 40, "Volver", 0.5, 0.2, 0.2);
    }
    else if (estado == PAUSA) {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 1);
        glRasterPos2f(centroX - 100, centroY - 150);
        const char* titulo = "PAUSA";
        for (const char* c = titulo; *c; ++c)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        glEnable(GL_LIGHTING);
        dibujarCuadro(centroX, centroY-50, 50, "Reanudar", 0.2, 0.5, 0.2);
        dibujarCuadro(centroX-300, centroY-200 , 50, "Volver al inicio", 0.5, 0.2, 0.2);
    }
    glPopMatrix();               
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}

void Menu::procesarClick(int x, int y, int ancho, int alto) {
    int centroX = ancho / 2;
    int centroY = alto / 2;
    if (estado == MENU_TABLERO) {
        //área clic para elegir tablero un peón
        int y_inicio_op1 = centroY-70;
        int y_fin_op1 = centroY-20;
        //área clic para elegir tablero speed chess
        int y_inicio_op2 = centroY-10;
        int y_fin_op2 = centroY+60;

        if (y >= y_inicio_op1 && y <= y_fin_op1) {
            modoSeleccionado = 1;
            estado = MENU_MODO_JUEGO;
        }
        else if (y >= y_inicio_op2 && y <= y_fin_op2) {
            modoSeleccionado = 2;
            estado = MENU_MODO_JUEGO;
        }
    }
    else if (estado == MENU_MODO_JUEGO) {
        int y_inicio_op1 = centroY-70;
        int y_fin_op1 = centroY-20;
        int y_inicio_op2 = centroY-10;
        int y_fin_op2 = centroY+60;
        int y_inicio_volver = centroY -220;
        int y_fin_volver = centroY -180;
        int x_inicio_volver = centroX - 320;
        int x_fin_volver = centroX - 280;
        if (y >= y_inicio_op1 && y <= y_fin_op1) {
            tipoJuego = 1;
            estado = EN_JUEGO;
        }
        else if (y >= y_inicio_op2 && y <= y_fin_op2) {
            tipoJuego = 2;
            estado = EN_JUEGO;
        }
        else if (y >= y_inicio_volver && y <= y_fin_volver) {
            estado = MENU_TABLERO;
        }
    }
    else if (estado == PAUSA){
        int y_inicio_volver = centroY - 220;
        int y_fin_volver = centroY - 180;
        int x_inicio_volver = centroX - 320;
        int x_fin_volver = centroX - 280;
        int y_inicio_op1 = centroY - 70;
        int y_fin_op1 = centroY - 20;
        if (y >= y_inicio_op1 && y <= y_fin_op1) {
            tipoJuego = 1;
            estado = EN_JUEGO;
        }
        else if (y >= y_inicio_volver && y <= y_fin_volver) {
            estado = MENU_TABLERO;
        }
    }
}
