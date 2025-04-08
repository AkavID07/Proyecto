#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdlib.h>

using namespace std;

// Estructura de jugador
struct Jugador { // Angel

	string Nombre;
	int puntos = 0;
};

// Prototipos Utilitarios
void LimpiarConsola();						// Angel
void generarTitulo(const string &);			// Andony
int validarEntrada(const string &);			// Andony
void pausarPrograma(const string &mensaje); // Andony

// Prototipos del juego
void dibujarDado(int cara); // Eduar
int LanzarDado();			// Eduar

// Funcion Principal
int main() {
	srand(time(NULL)); // Nahomy
	int numjugadores, puntaje, dado;
	char rsp, nombres[20];

	generarTitulo("Juego de dados");
	cout << "\n\n";

	do {
		numjugadores = validarEntrada("Ingrese la cantidad de jugadores (2-5)");

		if ((numjugadores < 2 || numjugadores > 5)) cout << "\nERROR. Ingrese un numero valido de jugadores.\n\n";

	} while ((numjugadores < 2 || numjugadores > 5)); // Nahomy

	// Angel
	Jugador *jugadores = new Jugador[numjugadores]; // crear el espacio para cada jugador

	// Nahomy

	LimpiarConsola();
	cin.clear();
	cin.ignore();
	for (int i = 0; i < numjugadores; i++) {
		cout << "\nIngrese el nombre de los jugadores: ";
		cin.getline(nombres, 20);
		jugadores[i].Nombre = nombres;
	}

	puntaje = validarEntrada("\n\nIngrese el puntaje a alcanzar");

	do {
		for (int i = 0; i < numjugadores; i++) {
			while (true) {
				dado = LanzarDado();
				generarTitulo("Turno de " + jugadores[i].Nombre);

				cout << jugadores[i].Nombre << " ha sacado un " << dado << "\n\n";
				dibujarDado(dado);

				if (dado == 1) {
					jugadores[i].puntos = 0;
					cout << jugadores[i].Nombre << " a sacado 1, por ende pierde todos sus puntos.\n";
					pausarPrograma("Salir");
					break;

				} // Nahomy

				jugadores[i].puntos += dado;

				pausarPrograma("Salir");

				if (jugadores[i].puntos >= puntaje) {
					generarTitulo("GANADOR " + jugadores[i].Nombre);

					cout << "FELICIDADES " << jugadores[i].Nombre << " HAS SIDO EL GANADOR!!!\n\n";
					delete[] jugadores;
					pausarPrograma("Salir");
					return 1;
				}

				cout << "\n\n Desea volver a lanzar los dados? (Y/N)";
				cin >> rsp;

				if ((rsp == 'n') or (rsp == 'N')) {
					break;
				};
			}
		}

	} while (true);

	return 0;
}

// Funciones Utilitarias

void LimpiarConsola() { // Angel
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void generarTitulo(const string &titulo) { // Andony
	const string lineas(titulo.length() * 2, '*');

	LimpiarConsola();
	cout << "\t\t" << lineas << endl;
	cout << "\t\t" << setw(titulo.length() + titulo.length() / 2) << titulo << endl;
	cout << "\t\t" << lineas << endl << endl;
}

int validarEntrada(const string &mensaje) { // Andony
	int entrada = 0;

	while (true) {
		cout << mensaje << ": ";
		if (cin >> entrada) {
			if (cin.peek() == '\n') break;
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Entrada no Valida, porfavor ingrese un numero entero." << endl;
	}

	return entrada;
}

void pausarPrograma(const string &mensaje) { // Andony
#ifdef _WIN32
	system("pause");
	(void)mensaje;
#else
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl << "Presione una tecla para " << mensaje << "...";
	cin.get();
#endif
}

void dibujarDado(int cara) { // Eduar
	cout << " ------- " << endl;
	switch (cara) {
	case 1:
		cout << "|       |" << endl;
		cout << "|   *   |" << endl;
		cout << "|       |" << endl;
		break;
	case 2:
		cout << "| *     |" << endl;
		cout << "|       |" << endl;
		cout << "|     * |" << endl;
		break;
	case 3:
		cout << "| *     |" << endl;
		cout << "|   *   |" << endl;
		cout << "|     * |" << endl;
		break;
	case 4:
		cout << "| *   * |" << endl;
		cout << "|       |" << endl;
		cout << "| *   * |" << endl;
		break;
	case 5:
		cout << "| *   * |" << endl;
		cout << "|   *   |" << endl;
		cout << "| *   * |" << endl;
		break;
	case 6:
		cout << "| *   * |" << endl;
		cout << "| *   * |" << endl;
		cout << "| *   * |" << endl;
		break;
	}
	cout << " ------- " << endl;
}

int LanzarDado() { // Eduar o Nohemy

	int num = 1 + rand() % 6;

	return num;
}
