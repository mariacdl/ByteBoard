//#include "Tablero.h"
//
//int Tablero::leer_tablero(const std::string& filename) {
//    std::ifstream table(filename);
//    if (!table.is_open()) {
//        std::cout << "No se ha conseguido Leer adecuadamente el tablero\n";
//        return -1;
//    }
//
//    std::string linea;
//    std::string elemento;
//    matrix.clear();
//
//    while (getline(table, linea)) {
//        std::vector<std::string> fila;
//        std::stringstream ss(linea);
//        while (getline(ss, elemento, ';')) {
//            fila.push_back(elemento);
//        }
//        matrix.push_back(fila);
//    }
//
//    return 0;
//}
//
//void Tablero::imprimir_tablero() const {
//    for (size_t i = 0; i < 8; ++i) {
//        for (size_t j = 1; j < 9; ++j) {
//            std::string celda = matrix[i][j];
//            if (celda.length() >= 4) {
//                if (celda[3] == 'B')
//                    std::cout << "\033[31m" << celda << "\033[m ";
//                else if (celda[3] == 'N')
//                    std::cout << "\033[32m" << celda << "\033[m ";
//                else
//                    std::cout << celda << " ";
//            }
//            else {
//                std::cout << celda << " ";
//            }
//        }
//        std::cout << std::endl;
//    }
//}
//
//void Tablero::registrar_muerte(const std::string& victima) const {
//    std::ofstream Death_Note("Death_Note.txt");
//    if (!Death_Note.is_open()) {
//        std::cout << "No se ha conseguido Crear la carta \n";
//        return;
//    }
//    Death_Note << victima;
//    Death_Note.close();
//}
