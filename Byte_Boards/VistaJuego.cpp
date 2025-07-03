#include "VistaJuego.h"
#include "freeglut.h"
#include "etsidi.h" 


void VistaJuego::dibujar_textura(const char* ruta_imagen) {
    GLdouble ancho = glutGet(GLUT_WINDOW_WIDTH);
    GLdouble alto = glutGet(GLUT_WINDOW_HEIGHT);

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // Guarda la matriz de proyección actual
    glLoadIdentity();
    gluOrtho2D(0, ancho, alto, 0); // Configura una proyección 2D

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(ruta_imagen).id);
    glDisable(GL_LIGHTING); // Deshabilita la iluminación para texturas 2D planas

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1); // Asegura que la textura no sea "teñida" por un color
    glTexCoord2f(0, 1); glVertex2f(0, alto);
    glTexCoord2f(1, 1); glVertex2f(ancho, alto);
    glTexCoord2f(1, 0); glVertex2f(ancho, 0);
    glTexCoord2f(0, 0); glVertex2f(0, 0);
    glEnd();

    glEnable(GL_LIGHTING); // Habilita la iluminación de nuevo para el resto de la escena 3D
    glDisable(GL_TEXTURE_2D);

    glPopMatrix(); // Restaura la matriz de proyección guardada
    glMatrixMode(GL_MODELVIEW); 
    glEnable(GL_DEPTH_TEST); // Habilita el test de profundidad de nuevo
}

void VistaJuego::dibujar_menu_tablero() {
    dibujar_textura("imagenes/menu_1.png");
}

void VistaJuego::dibujar_menu_oponente() {
    dibujar_textura("imagenes/menu_2.png");
}

void VistaJuego::dibujar_pausa() {
    dibujar_textura("imagenes/pausa.png");
}

void VistaJuego::dibujar_promocion_speed() {
    dibujar_textura("imagenes/promocion_speed.png");
}

void VistaJuego::dibujar_promocion_4x5() {
    dibujar_textura("imagenes/promocion_4x5.png");
}

void VistaJuego::dibujar_fin_tablas() {
    dibujar_textura("imagenes/tablas.png");
}

void VistaJuego::dibujar_victoria_ciencias() {
    dibujar_textura("imagenes/victoria_ciencias.png");
}

void VistaJuego::dibujar_victoria_letras() {
    dibujar_textura("imagenes/victoria_letras.png");
}