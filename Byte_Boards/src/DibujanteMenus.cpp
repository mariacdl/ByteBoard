#include "DibujanteMenus.h"
#include "freeglut.h"
#include "etsidi.h"

void DibujanteMenus::dibujarMenuTablero() {
    GLdouble ancho = glutGet(GLUT_WINDOW_WIDTH);
    GLdouble alto = glutGet(GLUT_WINDOW_HEIGHT);

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,
        ETSIDI::getTexture("imagenes/menu_1.png").id);
    glDisable(GL_LIGHTING);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 1); glVertex2f(0, glutGet(GLUT_WINDOW_HEIGHT));
    glTexCoord2f(1, 1); glVertex2f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glTexCoord2f(1, 0); glVertex2f(glutGet(GLUT_WINDOW_WIDTH), 0);
    glTexCoord2f(0, 0); glVertex2f(0, 0);
    glEnd();
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}

void DibujanteMenus::dibujarMenuModoJuego() {
    GLdouble ancho = glutGet(GLUT_WINDOW_WIDTH);
    GLdouble alto = glutGet(GLUT_WINDOW_HEIGHT);

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);

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

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}

void DibujanteMenus::dibujarMenuPausa() {
    GLdouble ancho = glutGet(GLUT_WINDOW_WIDTH);
    GLdouble alto = glutGet(GLUT_WINDOW_HEIGHT);

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);

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

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}

void DibujanteMenus::dibujarMenuPromSpeed() {
    GLdouble ancho = glutGet(GLUT_WINDOW_WIDTH);
    GLdouble alto = glutGet(GLUT_WINDOW_HEIGHT);

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);

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

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}

void DibujanteMenus::dibujarMenuProm4x5() {
    GLdouble ancho = glutGet(GLUT_WINDOW_WIDTH);
    GLdouble alto = glutGet(GLUT_WINDOW_HEIGHT);

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);

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

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}

void DibujanteMenus::dibujarMenuTablas() {
    GLdouble ancho = glutGet(GLUT_WINDOW_WIDTH);
    GLdouble alto = glutGet(GLUT_WINDOW_HEIGHT);

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);

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

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}

void DibujanteMenus::dibujarMenuVicCiencias() {
    GLdouble ancho = glutGet(GLUT_WINDOW_WIDTH);
    GLdouble alto = glutGet(GLUT_WINDOW_HEIGHT);

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);

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

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}

void DibujanteMenus::dibujarMenuVicLetras() {
    GLdouble ancho = glutGet(GLUT_WINDOW_WIDTH);
    GLdouble alto = glutGet(GLUT_WINDOW_HEIGHT);

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);

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

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
}