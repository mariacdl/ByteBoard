#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

void Imprimir_Tablero_2(vector<vector<string>> matrix) {
	size_t i, j;
	string celda;
	for (i = 0; i < 8; i++) {
		for (j = 1; j < 9; j++) {
			celda = matrix[i][j];
			if (celda[3] == 'B')
				cout << "\033[31m" << celda << "\033[m ";
			else if (celda[3] == 'N')
				cout << "\033[32m" << celda << "\033[m ";
			else
				cout << celda << " ";
		}
		cout << endl;
	}
}

int Leer_Tablero_2(vector<vector<string>>& matrix)
{

	string linea;
	string elemento;

	// pieza *nums[17];
	ifstream table;
	//table.open("C:/Users/Usuario/Desktop/INFO/pruebasVS/Trabajo/tablero.txt", ios::in); //CAUTION
	table.open("tablero.txt", ios::in); //CAUTION
	if (!table.is_open()) {
		cout << "No se ha conseguido Leer adecuadamente el tablero\n";
		return -1;
	}
	else
	{
		while (getline(table, linea))
		{
			vector<string> fila;  // Vector que guarda los elementos de la linea actual
			stringstream ss(linea);

			while (getline(ss, elemento, ';')) {
				fila.push_back(elemento);
			}
			matrix.push_back(fila);
		}
		return 0;
	}

}

void Death_List(string victim) {
	//cout << "He llegado hasta Death List" << endl;
	ofstream Death_Note;
	Death_Note.open("Death_Note.txt");
	if (!Death_Note.is_open()) {
		cout << "No se ha conseguido Crear la carta \n";
	}
	Death_Note << victim;

	Death_Note.close();
}


//class Tablero {
//private:
//    std::vector<std::vector<std::string>> matrix;
//
//public:
//    // Carga el tablero desde el archivo "tablero.txt"
//    int leer_tablero(const std::string& filename = "tablero.txt");
//
//    // Imprime el tablero en consola con colores
//    void imprimir_tablero() const;
//
//    // Guarda una pieza eliminada en "Death_Note.txt"
//    void registrar_muerte(const std::string& victima) const;
//};
