#include "freeglut.h"
#include "tablero.h"
#include <iostream>
#include "Menu.h"

//dos modos de tablero
Tablero tablero_unico(5,4,1.5);
Tablero tablero_speed(6,5,1.3);
Menu menu;

enum Jugador {
BLANCAS = 1,
NEGRAS=2
};
Jugador jugador_activo = BLANCAS;
int modo = 1;//para elegir un tablero u otro

void OnDraw(void);
void OnMouseClick(int button, int state, int x, int y);
void OnKeyboard(unsigned char key, int x, int y);

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Ajedrez");

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

    glutDisplayFunc(OnDraw);
    glutMouseFunc(OnMouseClick);
    glutKeyboardFunc(OnKeyboard);
    glutMainLoop();
    return 0;
}
void OnDraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    EstadoJuego estado = menu.getEstado();
    
    if (estado == MENU_TABLERO || estado == MENU_MODO_JUEGO||estado==PAUSA) {
        menu.dibujarMenu(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    }
    else if (estado == EN_JUEGO) {
        gluPerspective(40.0, glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.1, 150.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        if (jugador_activo == 1) {
            gluLookAt(0, 10, 10,
                0, 0, 0,
                0, 1, 0);
        }
        else {
            gluLookAt(0, 10, -10,
                0, 0, 0,
                0, 1, 0);
        }
        GLfloat luzPos[] = { 0.0f, 10.0f, 10.0f, 0.0f }; // Posición relativa a la cámara
        glLightfv(GL_LIGHT0, GL_POSITION, luzPos);
        if (menu.getModoSeleccionado() == 1)
            tablero_unico.dibujar();
        else
            tablero_speed.dibujar();
    }

    glutSwapBuffers();
}
void cambiarJugador() {
    jugador_activo = (jugador_activo == BLANCAS) ? NEGRAS : BLANCAS;
}
void OnMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        menu.procesarClick(x, y, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        glutPostRedisplay();
    }
}
void OnKeyboard(unsigned char key, int x, int y) {
    if (key == 'c'|| key=='C') { //cambio manual vista del jugador
        cambiarJugador();
        glutPostRedisplay();
    }
    if (key == 27) { // 27 = ESC ; pausar en medio del juego
        if (menu.getEstado() == EN_JUEGO)
            menu.setEstado(PAUSA);
        else if (menu.getEstado() == PAUSA)
            menu.setEstado(EN_JUEGO);
        glutPostRedisplay();
    }
}