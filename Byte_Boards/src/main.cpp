#include "freeglut.h"
#include "GestorJuego.h"

//Creación de las clases principales
GestorJuego gestor;

void OnDraw(void)
{
    gestor.dibujar();
}

void OnMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        gestor.procesarClick(x, y);
    }
}

void OnKeyboard(unsigned char key, int x, int y) {
    gestor.procesarTecla(key);
}

void OnTimer(int value) {
    glutTimerFunc(25, OnTimer, 0);
    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
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
    glutTimerFunc(25, OnTimer, 0);//llamar en 25ms
    glutMainLoop();
    return 0;
}
