#include "Pieza.h"
#include "freeglut.h"

Pieza::Pieza(figuras figuras,equipos equipos):
	_figuras(figuras),_equipos(equipos){}

void Pieza::dibujar(float x, float y, float tam)
{
	glPushMatrix();
	glTranslatef(x, y, 0);

	if (_equipos == Ciencias)

		glColor3f(0.0f, 0.0f, 1.0f); // Color azul para Ciencias
	else
		glColor3f(1.0f, 0.0f, 0.0f); // Color rojo para Letras

	switch (_figuras) {

	case Rey:
		dibujarRey(tam);
		break;

	case Torre:
		dibujarTorre(tam);
		break;

	case Alfil:
		dibujarAlfil(tam);
		break;

	case Caballo:
		dibujarCaballo(tam);
		break;

	case Peon:
		dibujarPeon(tam);
		break;
	}

	glPopMatrix();
}


void Pieza::dibujarRey(float tam) {
	// Código para dibujar el Rey en 3D

	glPushMatrix();
	glutSolidCube(tam); // Base
	glTranslatef(0, tam, 0);
	glutSolidSphere(tam / 2, 20, 20); // Corona
	glPopMatrix();

}


void Pieza::dibujarTorre(float tam) {
	// Código para dibujar la Torre en 3D

	glPushMatrix();
	glScalef(1.0f, 2.0f, 1.0f);
	glutSolidCube(tam); // Base
	glTranslatef(0, tam, 0);
	glutSolidCube(tam / 2); // Parte superior
	glPopMatrix();

}

void Pieza::dibujarAlfil(float tam) {
	// Código para dibujar el Alfil en 3D

	glPushMatrix();
	glTranslatef(0, tam / 2, 0);
	glutSolidSphere(tam / 2, 20, 20); // Base
	glTranslatef(0, tam / 2, 0);
	glutSolidCone(tam / 2, tam, 20, 20); // Parte superior
	glTranslatef(0, tam, 0);
	glutSolidSphere(tam / 4, 20, 20); // Detalle superior
	glPopMatrix();

}

void Pieza::dibujarCaballo(float tam) {
	// Código para dibujar el Caballo en 3D

	glPushMatrix();
	glScalef(1.0f, 1.5f, 0.5f);
	glutSolidCube(tam); // Base
	glTranslatef(0, tam, 0);
	glScalef(0.5f, 1.0f, 1.0f);
	glutSolidCube(tam); // Cabeza
	glPopMatrix();

}

void Pieza::dibujarPeon(float tam) {
	// Código para dibujar el Peón en 3D

	glPushMatrix();
	glTranslatef(0, tam / 2, 0);
	glutSolidSphere(tam / 2, 20, 20); // Base
	glTranslatef(0, tam / 2, 0);
	glutSolidCone(tam / 2, tam, 20, 20); // Parte superior
	glPopMatrix();

}



