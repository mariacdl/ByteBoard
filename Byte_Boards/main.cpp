
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include "trastero.h" 


int main() {
	struct Death_ID victim { 0, 0, 0 };
	struct Death_ID victima { 0, 0, 0 };

	struct datos_damas D { 2, 1, 1, { 0, 2 }, { 0,1 } };
	struct datos_torres T { 4, 2, 2, { 0, 3, 4 }, { 0,1,2 } };
	struct datos_alfiles A { 4, 2, 2, { 0, 3, 4 }, { 0,1,2 } };
	struct datos_caballos C { 4, 2, 2, { 0, 3, 4 }, { 0,1,2 } };

	int i, leer;
	size_t num = 7, x, y;
	int opt = 8;
	char trash;
	int falsa_alarma = 0;
	int tipo_mov_rey;


	bool turno_blanco = true;
	bool bewegung = false;
	bool jaque = false;
	bool roque = false;


	vector<int> verificar_ascenso{ 0,0 };
	vector<string> opciones{ "rey", "dama", "torre", "alfil", "caballo", "peon" };

	vector<vector<string>> matriz;
	vector<vector<string>>& matriz_live = matriz;
	vector<vector<string>> matriz_aux;

	Peon* num_p[17];
	Torre* num_t[5];	  // + 16 (8 + 8) asume que llegan todos los peones al otro lado del tablero para conevrtirse en torres
	Caballo* num_c[5 + 16]; // + 16 (8 + 8) asume que llegan todos los peones al otro lado del tablero para convertirse en caballos
	Alfil* num_a[5 + 16];	  // + 16 (8 + 8) asume que llegan todos los peones al otro lado del tablero para convertirse en alfiles
	Rey* num_r[3];
	Dama* num_d[3 + 16];	  // + 16 (8 + 8) asume que llegan todos los peones al otro lado del tablero para conevrtirse en damas

	for (i = 1; i < 9; i++)
	{
		num_p[i] = new Peon(i, 2, 5, i, false, true);
	}

	for (i = 1; i < 9; i++)
	{
		num_p[i + 8] = new Peon(i, 7, 5, i, true, true);
	}

	num_r[1] = new Rey(4, 1, 0, 1, false, true);
	num_r[2] = new Rey(4, 8, 0, 1, true, true);

	num_d[1] = new Dama(5, 1, 1, 1, false, true);
	num_d[2] = new Dama(5, 8, 1, 1, true, true);

	num_a[1] = new Alfil(3, 1, 3, 1, false, true);
	num_a[2] = new Alfil(6, 1, 3, 2, false, true);
	num_a[3] = new Alfil(3, 8, 3, 1, true, true);
	num_a[4] = new Alfil(6, 8, 3, 2, true, true);

	num_c[1] = new Caballo(2, 1, 4, 1, false, true);
	num_c[2] = new Caballo(7, 1, 4, 2, false, true);
	num_c[3] = new Caballo(2, 8, 4, 1, true, true);
	num_c[4] = new Caballo(7, 8, 4, 2, true, true);

	num_t[1] = new Torre(1, 1, 2, 1, false, true);
	num_t[2] = new Torre(8, 1, 2, 2, false, true);
	num_t[3] = new Torre(1, 8, 2, 1, true, true);
	num_t[4] = new Torre(8, 8, 2, 2, true, true);

	leer = Leer_Tablero_2(matriz);
	if (leer != 0)
		return -1;

	while (opt != 7)
	{
		num_r[0] = new Rey(0, 0, 0, 0, false, false);
		num_d[0] = new Dama(0, 0, 1, 0, false, false);
		num_t[0] = new Torre(0, 0, 2, 0, false, false);
		num_a[0] = new Alfil(0, 0, 3, 0, false, false);
		num_c[0] = new Caballo(0, 0, 4, 0, false, false);
		num_p[0] = new Peon(0, 0, 5, 0, false, false);

		Death_List("****");
		bewegung = false;
		roque = false;
		opt = 8;
		falsa_alarma = 0;
		tipo_mov_rey = 5;

		Imprimir_Tablero_2(matriz);
		cout << "\t\t\t\t\t\t\tEs el turno de las piezas de color " << (turno_blanco ? "blanco" : "negro") << endl;

		//Comprobante de jaque
		if (turno_blanco)
		{
			num_r[2]->tablero_act(matriz_live);
			jaque = num_r[2]->comp_jaque();
		}
		else
		{
			num_r[1]->tablero_act(matriz_live);
			jaque = num_r[1]->comp_jaque();
		}

		cout << endl << "Escribe a continuacion que tipo de pieza quieres utlizar:" << endl;
		cout << "1. rey\n" << "2. dama\n" << "3. torre\n" << "4. alfil\n" << "5. caballo\n" << "6. peon \n" << "7. Abandonar la partida\n" << endl;

		if (jaque)
		{
			do {
				cout << "Estas en jaque, bloquea el jaque o rindete" << endl;
				cin >> opt;
			} while ((opt >= 8) || (opt < 1));
		}
		else
			do {
				cin >> opt;
			} while (((opt >= 8) || (opt < 1)));


		switch (opt)
		{
		case 1:
		{
			//cout << "Usted ha elegido al rey\n";

			if (turno_blanco && !(num_r[2]->obituary()))
			{
				num_r[2]->mostrar();
				break;
			}
			else
				if (!turno_blanco && !(num_r[1]->obituary()))
				{
					num_r[1]->mostrar();
					break;
				}
				else
					break;
		}
		case 2:
		{
			//cout << "Usted ha elegido a la dama\n";
			if (turno_blanco)
			{
				num = 2;
				if (D.C_D_B > 1)
				{
					do
					{
						do {
							cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
							cin >> num;
						} while (!((num > 0) && (num <= D.C_D_B)) && (num != 0));

					} while ((num != 0) && num_d[D.conv_B_T[num]]->obituary());
					num = D.conv_B_T[num];
					num_d[num]->mostrar();
					break;
				}
				else
					if (!(num_d[num]->obituary()))
					{
						num_d[num]->mostrar();
						break;
					}
					else
					{
						opt = 0;
						break;
					}
			}
			else
				if (!turno_blanco)
				{
					num = 1;
					if (D.C_D_N > 1)		//Queda que en el caso de que existan mas que dos reinas por partida t pregunte cual queires usar
					{
						do
						{
							do {
								cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
								cin >> num;
							} while (!((num > 0) && (num <= D.C_D_N)) && (num != 0));

						} while ((num != 0) && num_d[D.conv_N_T[num]]->obituary());
						num_d[num]->mostrar();
						break;
					}
					else
						if (!(num_d[num]->obituary()))
						{
							num_d[num]->mostrar();
							break;
						}
						else
						{
							opt = 0;
							break;
						}
				}
				else
					break;
		}
		case 3:
		{
			//cout << "Usted ha elegido a la torre\n";
			if (turno_blanco)
			{
				do
				{
					do {
						cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
						cin >> num;
					} while (!((num > 0) && (num <= T.C_T_B)) && (num != 0));
				} while ((num != 0) && num_t[T.conv_B_T[num]]->obituary());
				num = T.conv_B_T[num];
				num_t[num]->mostrar();
				break;
			}
			else
			{
				do
				{
					do {
						cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
						cin >> num;
					} while (!((num > 0) && (num <= T.C_T_N)) && (num != 0));

				} while ((num != 0) && num_t[T.conv_N_T[num]]->obituary());
				num = T.conv_N_T[num];
				num_t[num]->mostrar();
				break;
			}
		}

		case 4:
		{
			//cout << "Usted ha elegido al alfil\n";
			if (turno_blanco)
			{
				do
				{
					do {
						cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
						cin >> num;
					} while (!((num > 0) && (num <= A.C_A_B)) && (num != 0));
				} while ((num != 0) && num_a[A.conv_B_T[num]]->obituary());
				num = A.conv_B_T[num];
				num_a[num]->mostrar();
				break;
			}
			else
			{
				do
				{
					do {
						cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
						cin >> num;
					} while (!((num > 0) && (num <= A.C_A_N)) && (num != 0));

				} while ((num != 0) && num_a[A.conv_N_T[num]]->obituary());
				num = A.conv_N_T[num];
				num_a[num]->mostrar();
				break;
			}
		}
		case 5:
		{
			//cout << "Usted ha elegido al caballo\n";
			if (turno_blanco)
			{
				do
				{
					do {
						cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
						cin >> num;
					} while (!((num > 0) && (num <= C.C_C_B)) && (num != 0));
				} while ((num != 0) && num_c[C.conv_B_T[num]]->obituary());
				num = C.conv_B_T[num];
				num_c[num]->mostrar();

				break;
			}
			else
			{
				do
				{
					do {
						cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
						cin >> num;
					} while (!((num > 0) && (num <= C.C_C_N)) && (num != 0));

				} while ((num != 0) && num_c[C.conv_N_T[num]]->obituary());
				num = C.conv_N_T[num];
				num_c[num]->mostrar();
				break;
			}

		}
		case 6:
		{
			//cout << "Usted ha elegido al peon\n";

			if (turno_blanco)
			{
				do
				{
					do {
						cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
						cin >> num;
					} while (((num < 1) || (num > 8)) && (num != 0));

				} while ((num != 0) && (num_p[num + 8]->obituary()));
				num_p[num + 8]->mostrar();
				break;
			}

			if (!turno_blanco)
			{
				do
				{
					do {
						cout << "Que numero de " << opciones[opt - 1] << " quieres utilizar? " << endl;
						cin >> num;
					} while (((num < 1) || (num > 8)) && (num != 0));

				} while ((num != 0) && (num_p[num]->obituary()));
				num_p[num]->mostrar();
				break;
			}
		}
		case 7:
		{
			cout << "El jugador " << (turno_blanco ? "blanco" : "negro") << " ha decidido rendirse, gana el jugador " << (!turno_blanco ? "blanco" : "negro") << endl;
			break;
		}
		}

		if (((opt != 0) && (opt != 7)) && (num != 0))
		{
			do {
				cout << "Nueva Posicion en \"x\":" << endl;
				cin >> x;
			} while (((x < 1) || (x > 8)) && ((opt != 0) && (num != 0)));

			do {
				cout << "Nueva Posicion en \"y\":" << endl;
				cin >> y;
			} while (((y < 1) || (y > 8)) && ((opt != 0) && (num != 0)));

		}

		if (num != 0)
			switch (opt)
			{
			case 0:
				break;
			case 1:
			{
				matriz_aux = matriz_live;
				//cout << "Usted ha elegido al rey\n";
				if (turno_blanco)
				{
					num_r[2]->tablero_act(matriz_live);
					*num_r[0] = *num_r[2];
					tipo_mov_rey = num_r[2]->mover_rey(x, y, num_t[3]->mov_torre(), num_t[4]->mov_torre());
					switch (tipo_mov_rey)
					{
					case 0:
					{
						bewegung = false;
						roque = false;
						break;
					}
					case 1:
					{
						bewegung = true;
						roque = false;
						break;
					}
					case 2:
					{
						bewegung = true;
						roque = true;
						break;
					}
					case 3:
					{
						bewegung = true;
						roque = true;
						break;
					}
					}

					if (num_r[2]->comp_jaque())
					{
						system("cls");
						Imprimir_Tablero_2(matriz_aux);
						cout << endl << endl << "Estas en jaque, elije otro movimiento" << endl;
						*num_r[2] = *num_r[0];
						matriz_live = matriz_aux;
						num_r[2]->tablero_act(matriz_live);
						bewegung = false;
						roque = false;
						falsa_alarma = 1;

					}
					num_r[2]->mostrar();

				}
				else
				{
					num_r[1]->tablero_act(matriz_live);
					*num_r[0] = *num_r[1];
					tipo_mov_rey = num_r[1]->mover_rey(x, y, num_t[1]->mov_torre(), num_t[2]->mov_torre());
					switch (tipo_mov_rey)
					{
					case 0:
					{
						bewegung = false;
						roque = false;
						break;
					}
					case 1:
					{
						bewegung = true;
						roque = false;
						break;
					}
					case 2:
					{
						bewegung = true;
						roque = true;
						break;
					}
					case 3:
					{
						bewegung = true;
						roque = true;
						break;
					}
					}

					if (num_r[1]->comp_jaque())
					{
						system("cls");
						Imprimir_Tablero_2(matriz_aux);
						cout << endl << endl << "Estas en jaque, elije otro movimiento" << endl;
						*num_r[1] = *num_r[0];
						matriz_live = matriz_aux;
						num_r[1]->tablero_act(matriz_live);
						bewegung = false;
						roque = false;
						falsa_alarma = 1;
					}
					num_r[1]->mostrar();
				}
				break;
			}
			case 2:
			{
				matriz_aux = matriz_live;
				//cout << "Usted ha elegido a la dama\n";
				num_d[num]->tablero_act(matriz_live);
				*num_d[0] = *num_d[num];
				bewegung = num_d[num]->mover_dama(x, y);
				if ((turno_blanco && num_r[2]->comp_jaque()) || (!turno_blanco && num_r[1]->comp_jaque()))
				{
					system("cls");
					Imprimir_Tablero_2(matriz_aux);
					cout << endl << endl << "Estas en jaque, elije otro movimiento" << endl;
					*num_d[num] = *num_d[0];
					matriz_live = matriz_aux;
					num_d[num]->tablero_act(matriz_live);
					bewegung = false;
					falsa_alarma = 1;

				}
				num_d[num]->mostrar();
				break;
			}
			case 3:
			{
				matriz_aux = matriz_live;
				//cout << "Usted ha elegido la torre\n";
				num_t[num]->tablero_act(matriz_live);
				*num_t[0] = *num_t[num];
				bewegung = num_t[num]->mover_torre(x, y);
				if ((turno_blanco && num_r[2]->comp_jaque()) || (!turno_blanco && num_r[1]->comp_jaque()))
				{
					system("cls");
					Imprimir_Tablero_2(matriz_aux);
					cout << endl << endl << "Estas en jaque, elije otro movimiento" << endl;
					*num_t[num] = *num_t[0];
					matriz_live = matriz_aux;
					num_t[num]->tablero_act(matriz_live);
					bewegung = false;
					falsa_alarma = 1;
				}
				num_t[num]->mostrar();
				break;
			}
			case 4:
			{
				matriz_aux = matriz_live;
				//cout << "Usted ha elegido al alfil\n";
				num_a[num]->tablero_act(matriz_live);
				*num_a[0] = *num_a[num];
				bewegung = num_a[num]->mover_alfil(x, y);
				if ((turno_blanco && num_r[2]->comp_jaque()) || (!turno_blanco && num_r[1]->comp_jaque()))
				{
					system("cls");
					Imprimir_Tablero_2(matriz_aux);
					cout << endl << endl << "Estas en jaque, elije otro movimiento" << endl;
					*num_a[num] = *num_a[0];
					matriz_live = matriz_aux;
					num_a[num]->tablero_act(matriz_live);
					bewegung = false;
					falsa_alarma = 1;
				}
				num_a[num]->mostrar();
				break;
			}
			case 5:
			{
				matriz_aux = matriz_live;
				//cout << "Usted ha elegido al caballo\n";

				num_c[num]->tablero_act(matriz_live);
				*num_c[0] = *num_c[num];
				bewegung = num_c[num]->mover_caballo(x, y);
				if ((turno_blanco && num_r[2]->comp_jaque()) || (!turno_blanco && num_r[1]->comp_jaque()))
				{
					system("cls");
					Imprimir_Tablero_2(matriz_aux);
					cout << endl << endl << "Estas en jaque, elije otro movimiento" << endl;
					*num_c[num] = *num_c[0];
					matriz_live = matriz_aux;
					num_c[num]->tablero_act(matriz_live);
					bewegung = false;
					falsa_alarma = 1;

				}
				num_c[num]->mostrar();
				break;
			}
			case 6:
			{

				matriz_aux = matriz_live;
				//cout << "Usted ha elegido al peon\n";
				if (turno_blanco)
				{
					num_p[num + 8]->tablero_act(matriz_live);
					*num_p[0] = *num_p[num + 8];
					bewegung = num_p[num + 8]->mover_peon(x, y);
					if ((turno_blanco && num_r[2]->comp_jaque()) || (!turno_blanco && num_r[1]->comp_jaque()))
					{
						system("cls");
						Imprimir_Tablero_2(matriz_aux);
						cout << endl << endl << "Estas en jaque, elije otro movimiento" << endl;
						*num_p[num + 8] = *num_p[0];
						matriz_live = matriz_aux;
						num_p[num + 8]->tablero_act(matriz_live);
						bewegung = false;
						falsa_alarma = 1;

					}
					num_p[num + 8]->mostrar();
				}
				else
				{
					num_p[num]->tablero_act(matriz_live);
					*num_p[0] = *num_p[num];
					bewegung = num_p[num]->mover_peon(x, y);
					if (num_r[1]->comp_jaque())
					{
						system("cls");
						Imprimir_Tablero_2(matriz_aux);
						cout << endl << endl << "Estas en jaque, elije otro movimiento" << endl;
						*num_p[num] = *num_p[0];
						matriz_live = matriz_aux;
						num_p[num]->tablero_act(matriz_live);
						bewegung = false;
						falsa_alarma = 1;
					}
					num_p[num]->mostrar();
				}
				break;

			}
			case 7:
				break;
			}

		if (roque)
		{

			if (turno_blanco)
			{
				if (tipo_mov_rey == 2)
				{
					num_t[3]->tablero_act(matriz_live);
					num_t[3]->mover_torre(2);
					num_t[3]->mostrar();
				}
				else
					if (tipo_mov_rey == 3)
					{
						num_t[4]->tablero_act(matriz_live);
						num_t[4]->mover_torre(3);
						num_t[4]->mostrar();
					}
			}
			else
			{
				if (tipo_mov_rey == 2)
				{
					num_t[1]->tablero_act(matriz_live);
					num_t[1]->mover_torre(2);
					num_t[1]->mostrar();
				}
				else
					if (tipo_mov_rey == 3)
					{
						num_t[2]->tablero_act(matriz_live);
						num_t[2]->mover_torre(3);
						num_t[2]->mostrar();
					}
			}
		}

		//cout << "He llegado hasta antes de leer Death List" << endl;
		if (falsa_alarma != 1)
			victim = Read_Victim_Data(victima);

		//cout << "He llegado hasta despues de leer Death List" << endl;
		if (victim.num_pieza != 0 && falsa_alarma != 1)
		{
			for (i = 1; i < 9; i++)
				num_p[i]->Juicio_final(victim.num_tipo, victim.num_pieza, victim.blanc);

			for (i = 1; i < 9; i++)
				num_p[i + 8]->Juicio_final(victim.num_tipo, victim.num_pieza, victim.blanc);
			for (i = 1; i <= T.C_T_T; i++)
				num_t[i]->Juicio_final(victim.num_tipo, victim.num_pieza, victim.blanc);
			for (i = 1; i <= C.C_C_T; i++)
				num_c[i]->Juicio_final(victim.num_tipo, victim.num_pieza, victim.blanc);
			for (i = 1; i <= A.C_A_T; i++)
				num_a[i]->Juicio_final(victim.num_tipo, victim.num_pieza, victim.blanc);
			for (i = 1; i < 3; i++)
				num_r[i]->Juicio_final(victim.num_tipo, victim.num_pieza, victim.blanc);
			for (i = 1; i < D.C_D_T; i++)
				num_d[i]->Juicio_final(victim.num_tipo, victim.num_pieza, victim.blanc);
		}

		if (opt == 6)
		{
			if (turno_blanco)
			{
				verificar_ascenso = num_p[num + 8]->comp_tope_peon();
				if (verificar_ascenso[0] != 0)
				{
					num_p[num + 8]->Juicio_final(verificar_ascenso[1]);
					switch (verificar_ascenso[1])
					{
					case 1:
					{
						num_d[++D.C_D_T] = new Dama(verificar_ascenso[0], 1, 1, ++D.C_D_B, true, true);
						num_p[num + 8]->transductor_peon_a_premio(verificar_ascenso[1], D.C_D_B, true);
						D.conv_B_T.push_back(D.C_D_T);
						break;
					}
					case 2:
					{
						num_t[++T.C_T_T] = new Torre(verificar_ascenso[0], 1, 2, ++T.C_T_B, true, true);
						num_p[num + 8]->transductor_peon_a_premio(verificar_ascenso[1], T.C_T_B, true);
						T.conv_B_T.push_back(T.C_T_T);
						break;
					}
					case 3:
					{
						num_a[++A.C_A_T] = new Alfil(verificar_ascenso[0], 1, 3, ++A.C_A_B, true, true);
						num_p[num + 8]->transductor_peon_a_premio(verificar_ascenso[1], A.C_A_B, true);
						A.conv_B_T.push_back(A.C_A_T);
						break;
					}
					case 4:
					{
						num_c[++C.C_C_T] = new Caballo(verificar_ascenso[0], 1, 4, ++C.C_C_B, true, true);
						num_p[num + 8]->transductor_peon_a_premio(verificar_ascenso[1], C.C_C_B, true);
						C.conv_B_T.push_back(C.C_C_T);
						break;
					}
					}
				}
			}
			else
				if (!turno_blanco)
				{
					verificar_ascenso = num_p[num]->comp_tope_peon();
					if (verificar_ascenso[0] != 0)
					{
						num_p[num]->Juicio_final(verificar_ascenso[1]);
						switch (verificar_ascenso[1])
						{
						case 1:
						{
							num_d[++D.C_D_T] = new Dama(verificar_ascenso[0], 8, 1, ++D.C_D_N, false, true);
							num_p[num]->transductor_peon_a_premio(verificar_ascenso[1], D.C_D_N, false);
							D.conv_N_T.push_back(D.C_D_T);
							break;
						}
						case 2:
						{
							num_t[++T.C_T_T] = new Torre(verificar_ascenso[0], 8, 2, ++T.C_T_N, false, true);
							num_p[num]->transductor_peon_a_premio(verificar_ascenso[1], T.C_T_N, false);
							T.conv_N_T.push_back(T.C_T_T);
							break;
						}
						case 3:
						{
							num_a[++A.C_A_T] = new Alfil(verificar_ascenso[0], 8, 3, ++A.C_A_N, false, true);
							num_p[num]->transductor_peon_a_premio(verificar_ascenso[1], A.C_A_N, false);
							A.conv_N_T.push_back(A.C_A_T);
							break;
						}
						case 4:
						{
							num_c[++C.C_C_T] = new Caballo(verificar_ascenso[0], 8, 4, ++C.C_C_N, false, true);
							num_p[num]->transductor_peon_a_premio(verificar_ascenso[1], C.C_C_N, false);
							C.conv_N_T.push_back(C.C_C_T);
							break;
						}
						}
					}
				}
		}
		// num_c[num]->mostrar();
		cout << "Pulse cualquier tecla [...]:" << endl;
		cin >> trash;

		if (bewegung == true)
		{
			turno_blanco = !turno_blanco;
		}

		system("cls");
	}

	return 0;
}

