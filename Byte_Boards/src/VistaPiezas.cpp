#include "VistaPiezas.h"
#include "freeglut.h"
#include "Pieza.h"

void VistaPiezas::dibujar_piezas(float tam, const Tablero& tablero) {
	for (int indice_x = 0; indice_x < tablero.ver_altura(); indice_x++) {
		for (int indice_y = 0; indice_y < tablero.ver_largura(); indice_y++) {
			pair<int, int> pos = make_pair(indice_x, indice_y);
			Pieza* pieza = tablero.ver_pieza(pos);
			if (pieza != nullptr) {
				switch (pieza->ver_tipo()) {
				case 'P':
					if (pieza->ver_color() == BLANCO)
						dibujar_peon_blanco(pos, tam, tablero);
					else
						dibujar_peon_negro(pos, tam, tablero);
					break;
				case 'T':
					if (pieza->ver_color() == BLANCO)
						dibujar_torre_blanco(pos, tam, tablero);
					else
						dibujar_torre_negro(pos, tam, tablero);
					break;
				case 'C':
					if (pieza->ver_color() == BLANCO)
						dibujar_caballo_blanco(pos, tam, tablero);
					else
						dibujar_caballo_negro(pos, tam, tablero);
					break;
				case 'A':
					if (pieza->ver_color() == BLANCO)
						dibujar_alfil_blanco(pos, tam, tablero);
					else
						dibujar_alfil_negro(pos, tam, tablero);
					break;
				case 'R':
					if (pieza->ver_color() == BLANCO)
						dibujar_rey_blanco(pos, tam, tablero);
					else
						dibujar_rey_negro(pos, tam, tablero);
					break;
				case 'D':
					if (pieza->ver_color() == BLANCO)
						dibujar_dama_blanco(pos, tam, tablero);
					else
						dibujar_dama_negro(pos, tam, tablero);
					break;
				}
			}
		}
	}
}

void VistaPiezas::dibujar_peon_blanco(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float z = offsetZ + pos.first * tam + tam / 2.0f;
	float x = offsetX + pos.second * tam + tam / 2.0f;
	float y = tam * 0.15f; // altura base

	glPushMatrix();
	glTranslatef(x, y, z);

	GLUquadric* quad = gluNewQuadric();

	// Tuerca hexagonal
	glColor3f(0.6f, 0.6f, 0.6f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.25f, 0.25f, 0.05f, 6, 1);
	glTranslatef(0, 0, 0.05f);
	gluDisk(quad, 0.0f, 0.25f, 6, 1); // tapa
	glPopMatrix();

	// Tornillo central
	glColor3f(0.3f, 0.3f, 0.3f);
	glPushMatrix();
	glTranslatef(0.0f, 0.05f, 0.0f);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.07f, 0.07f, 0.4f, 32, 16);
	glPopMatrix();

	// Cabeza semiesférica
	glColor3f(0.6f, 0.6f, 0.6f);
	glPushMatrix();
	glTranslatef(0.0f, 0.48f, 0.0f);
	glutSolidSphere(0.07f, 20, 20);
	glPopMatrix();

	gluDeleteQuadric(quad);
	glPopMatrix();
}

void VistaPiezas::dibujar_torre_blanco(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float z = offsetZ + pos.first * tam + tam / 2.0f;
	float x = offsetX + pos.second * tam + tam / 2.0f;

	glPushMatrix();
	glTranslatef(x, 0.0f, z);

	GLUquadric* quad = gluNewQuadric();

	// Base ancha (cilindro corto)
	glColor3f(0.2f, 0.2f, 0.2f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.25f, 0.25f, 0.05f, 32, 1);
	glPopMatrix();

	// Cuerpo cónico del matraz
	glColor3f(0.4f, 0.7f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.05f, 0.0f);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.25f, 0.08f, 0.6f, 32, 16);
	glPopMatrix();

	// Cuello recto superior
	glColor3f(0.2f, 0.5f, 0.9f);
	glPushMatrix();
	glTranslatef(0.0f, 0.65f, 0.0f);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.08f, 0.08f, 0.2f, 32, 16);
	glPopMatrix();

	// Boca redonda
	glColor3f(0.1f, 0.1f, 0.1f);
	glPushMatrix();
	glTranslatef(0.0f, 0.85f, 0.0f);
	glutSolidTorus(0.01f, 0.08f, 12, 24);
	glPopMatrix();

	gluDeleteQuadric(quad);
	glPopMatrix();
}

void VistaPiezas::dibujar_caballo_blanco(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float z = offsetZ + pos.first * tam + tam / 2.0f;
	float x = offsetX + pos.second * tam + tam / 2.0f;


	glPushMatrix();
	glTranslatef(x, 0.0f, z);

	GLUquadric* quad = gluNewQuadric();

	//  BASE gruesa
	glColor3f(1.0f, 0.3f, 0.1f);
	glPushMatrix();
	glTranslatef(0.0f, 0.07f, 0.0f); // altura del cilindro base
	glRotatef(-90, 1, 0, 0);
	gluDisk(quad, 0.0f, 0.23f, 32, 1);
	glPopMatrix();

	//  BRAZO VERTICAL (cilindro naranja) aumentado
	glColor3f(1.0f, 0.4f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.07f, 0.0f);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.06f, 0.06f, 0.45f, 20, 20); // altura aumentada a 0.45f
	glPopMatrix();

	//  ARTICULACIÓN HORIZONTAL (cilindro acostado) subida y alargada
	glColor3f(0.3f, 0.3f, 0.3f);
	glPushMatrix();
	glTranslatef(0.0f, 0.52f, 0.0f);  // subida desde 0.35f a 0.52f
	glRotatef(90, 0, 0, 1);
	gluCylinder(quad, 0.04f, 0.04f, 0.20f, 16, 16);  // alargado de 0.15f a 0.20f
	glPopMatrix();

	//  SEGUNDO BRAZO inclinado (subido y alargado)
	glColor3f(1.0f, 0.4f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.52f, 0.0f);
	glRotatef(-45, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.04f, 0.04f, 0.40f, 20, 20); // altura aumentada a 0.40f
	glPopMatrix();

	// Pinzas (subidas y separadas)
	glColor3f(1.0f, 0.4f, 0.0f);

	// Pinza izquierda
	glPushMatrix();
	glTranslatef(0.18f, 0.70f, -0.035f);  // subida de 0.53f a 0.70f
	glRotatef(30, 0, 0, 1);
	glScalef(0.08f, 0.02f, 0.02f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Pinza derecha
	glPushMatrix();
	glTranslatef(0.18f, 0.70f, 0.035f);   // subida de 0.53f a 0.70f
	glRotatef(-30, 0, 0, 1);
	glScalef(0.08f, 0.02f, 0.02f);
	glutSolidCube(1.0f);
	glPopMatrix();

	gluDeleteQuadric(quad);
	glPopMatrix();
}

void VistaPiezas::dibujar_alfil_blanco(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float z = offsetZ + pos.first * tam + tam / 2.0f;
	float x = offsetX + pos.second * tam + tam / 2.0f;

	glPushMatrix();
	glTranslatef(x, 0.0f, z);
	glScalef(1.6f, 1.6f, 1.6f);

	GLUquadric* quad = gluNewQuadric();

	// Base del joystick (cilindro bajo)
	glColor3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glutWireCone(0.35f, 0.9f, 32.0f, 1.0f);
	glPopMatrix();

	glColor3f(0.2f, 0.2f, 0.2f);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glPopMatrix();

	// Bola en la punta
	glColor3f(0.1f, 0.1f, 102.0f);
	glPushMatrix();
	glTranslatef(0.0f, 1.05f, 0.0f);
	glutSolidCube(0.1f);
	glPopMatrix();

	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.16f, 1.05f, 0.0f);
	glutSolidCube(0.1f);
	glTranslatef(0.1f, 0.0f, 0.0f);
	glutSolidCube(0.1f);
	glTranslatef(0.1f, 0.0f, 0.0f);
	glutSolidCube(0.1f);
	glTranslatef(0.05f, 0.0f, 0.0f);
	glutSolidCube(0.1f);
	glTranslatef(-0.55f, 0.0f, 0.0f);
	glutSolidCube(0.1f);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidCube(0.1f);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidCube(0.1f);
	glTranslatef(-0.05f, 0.0f, 0.0f);
	glutSolidCube(0.1f);
	glPopMatrix();

	gluDeleteQuadric(quad);

	glPopMatrix();
}

void VistaPiezas::dibujar_rey_blanco(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float z = offsetZ + pos.first * tam + tam / 2.0f;
	float x = offsetX + pos.second * tam + tam / 2.0f;

	glPushMatrix();
	glTranslatef(x, 0.30f, z); // Posición en el tablero

	// Núcleo - esfera azul clara
	glColor3f(0.2f, 0.6f, 1.0f);
	glutSolidSphere(0.35, 30, 30);
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(-45, 1, 0, 0);
	glutWireTorus(0.03, 0.55, 12, 24);
	glPopMatrix();
}

void VistaPiezas::dibujar_dama_blanco(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float z = offsetZ + pos.first * tam + tam / 2.0f;
	float x = offsetX + pos.second * tam + tam / 2.0f;

	glPushMatrix();
	glTranslatef(x, 0.0f, z);

	// Cuerpo de la calculadora
	glColor3ub(10, 10, 10);
	glPushMatrix();
	glScalef(0.75f, 2.0f, 0.4f);  // Alto y plano
	glutSolidCube(1.0f);
	glPopMatrix();

	glColor3ub(0, 150, 255);
	glPushMatrix();
	glTranslatef(0, 0.8, -0.15);
	glScalef(0.6f, 0.15f, 0.2f);  // Alto y plano
	glutSolidCube(1.0f);
	glPopMatrix();

	// Botones simulados como cubos pequeños
	glColor3ub(255, 0, 0);
	glPushMatrix();
	glTranslatef(-0.25, 0.6, -0.2);
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			glPushMatrix();
			glTranslatef(0.15 * i, 0, 0);
			//glScalef(0.1f, 0.05f, 0.1f);
			glutSolidCube(0.05f);
			glPopMatrix();
		}
		glTranslatef(0, -0.15, 0);
	}
	glPopMatrix();
	glPopMatrix();
}

void VistaPiezas::dibujar_peon_negro(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float zPos = offsetZ + pos.first * tam + tam / 2.0f;
	float xPos = offsetX + pos.second * tam + tam / 2.0f;
	float yPos = tam * 0.15f;   

	float x = 0.15f; // tamaño de los cubos

	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);
	glColor3ub(255, 150, 55);

	glutSolidCube(x);
	glTranslatef(x, 0, 0);
	glutSolidCube(x);
	glTranslatef(-2 * x, 0, 0);
	glutSolidCube(x);

	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);

	glTranslatef(2 * x, -2 * (x + 0.01f), 0);
	glutSolidCube(x);

	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);

	glTranslatef(0, x, 0);
	glutSolidCube(x);

	glTranslatef(-x, 0, 0);
	glutSolidCube(x);
	glTranslatef(-x, 0, 0);
	glutSolidCube(x);

	glPopMatrix();
}

void VistaPiezas::dibujar_torre_negro(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float z = offsetZ + pos.first * tam + tam / 2.0f;
	float x = offsetX + pos.second * tam + tam / 2.0f;
	float y = tam * 0.15f; // altura base

	float cuboTam = 0.2f;  // tamaño cubo de la torre

	glPushMatrix();

	glTranslatef(x, y, z);

	glColor3f(1.0f, 0.0f, 0.0f);

	glutSolidCube(cuboTam);

	glTranslatef(0, cuboTam + 0.01f, 0);
	glutSolidCube(cuboTam);

	glTranslatef(0, cuboTam + 0.01f, 0);
	glutSolidCube(cuboTam);

	glTranslatef(0, cuboTam + 0.01f, 0);
	glutSolidCube(cuboTam);

	glTranslatef(-cuboTam, 0, 0);
	glutSolidCube(cuboTam);

	glTranslatef(2 * cuboTam, 0, 0);
	glutSolidCube(cuboTam);

	glPopMatrix();
}

void VistaPiezas::dibujar_caballo_negro(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float z = offsetZ + pos.first * tam + tam / 2.0f;
	float x = offsetX + pos.second * tam + tam / 2.0f;
	float y = tam * 0.15f;

	float cuboTam = 0.2f;
	float ajusteX = -cuboTam;
	float ajusteY = -cuboTam;
	float ajusteZ = 0.0f;

	glPushMatrix();
	glTranslatef(x + ajusteX, y + ajusteY, z + ajusteZ);
	glColor3ub(0, 255, 255);

	float xCube = cuboTam;

	glutSolidCube(xCube);
	glTranslatef(2 * xCube, 0, 0);
	glutSolidCube(xCube);
	glTranslatef(0, xCube, 0);
	glutSolidCube(xCube);
	glTranslatef(-2 * xCube, 0, 0);
	glutSolidCube(xCube);

	glTranslatef(xCube, 0.1f, 0);
	glutSolidCube(xCube);
	glTranslatef(0, xCube, 0);
	glutSolidCube(xCube);
	glTranslatef(-xCube, xCube, 0);
	glutSolidCube(xCube);
	glTranslatef(0, xCube, 0);
	glutSolidCube(xCube);

	glTranslatef(2 * xCube, 0, 0);
	glutSolidCube(xCube);
	glTranslatef(0, -xCube, 0);
	glutSolidCube(xCube);

	glPopMatrix();
}

void VistaPiezas::dibujar_alfil_negro(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float z = offsetZ + pos.first * tam + tam / 2.0f;
	float x = offsetX + pos.second * tam + tam / 2.0f;
	float y = tam * 0.5f;

	float tam1 = 0.2f;  // tamaño de cubo

	glColor3ub(51, 51, 255);

	glPushMatrix();

	// Parte inferior: base
	glTranslatef(x - 0.2f, 0.0f, z);
	glutSolidCube(tam1);

	glTranslatef(tam1, 0.0f, 0.0f);
	glutSolidCube(tam1);
	glTranslatef(tam1, 0.0f, 0.0f);
	glutSolidCube(tam1);

	glTranslatef(-1 * tam1, tam1 + 0.01f, 0.0f);
	glutSolidCube(tam1);
	glTranslatef(0.0f, tam1 + 0.01f, 0.0f);
	glutSolidCube(tam1);
	glTranslatef(0.0f, tam1 + 0.01f, 0.0f);
	glutSolidCube(tam1);
	glTranslatef(0.0f, tam1 + 0.01f, 0.0f);
	glutSolidCube(tam1);
	glTranslatef(0.0f, tam1 + 0.01f, 0.0f);
	glutSolidCube(tam1);

	glTranslatef(-tam1, 0.0f, 0.0f);
	glutSolidCube(tam1);
	glTranslatef(2 * tam1, 0.0f, 0.0f);
	glutSolidCube(tam1);

	glPopMatrix();
}

void VistaPiezas::dibujar_rey_negro(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float zPos = offsetZ + pos.first * tam + tam / 2.0f;
	float xPos = offsetX + pos.second * tam + tam / 2.0f;
	float yPos = tam * 0.15f;

	float x = 0.2f;

	glPushMatrix();
	glTranslatef(xPos + 0.25f, yPos, zPos);
	glColor3ub(153, 255, 153);

	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);

	glTranslatef(-2 * x, -3 * (x + 0.01f), 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(x, -(x + 0.05f), 0);
	glutSolidCube(x);

	glPopMatrix();
}

void VistaPiezas::dibujar_dama_negro(pair<int, int> pos, float tam, const Tablero& tablero) {
	float offsetX = -((tablero.ver_largura() * tam) / 2.0f);
	float offsetZ = -((tablero.ver_altura() * tam) / 2.0f);

	float zPos = offsetZ + pos.first * tam + tam / 2.0f;
	float xPos = offsetX + pos.second * tam + tam / 2.0f;
	float yPos = tam * 0.15f;

	float x = 0.2f;

	glPushMatrix();
	glTranslatef(xPos, yPos - x, zPos);
	glColor3f(248.0f / 255.0f, 0.0f, 0.7f);

	glutSolidCube(x);
	glTranslatef(x, 0, 0);
	glutSolidCube(x);
	glTranslatef(-2 * x, 0, 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(2 * x, -2 * (x + 0.01f), 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(0, x + 0.01f, 0);
	glutSolidCube(x);
	glTranslatef(0, x, 0);
	glutSolidCube(x);
	glTranslatef(-2 * x, 0, 0);
	glutSolidCube(x);

	glPopMatrix();
}