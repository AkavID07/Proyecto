#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

// Estructura de jugador
struct Jugador { // Angel
	string nombre;
	int puntos = 0;
};

// Prototipos Utilitarios
void LimpiarConsola();				 // Angel
void generarTitulo(const string &);	 // Andony
void pausarPrograma(const string &); // Andony

// Prototipos de validacion
int validarEntrada(const string &); // Andony
int validarNumJugadores();
void validarNombreJugador(Jugador *, const int);
int validarPuntajeObtenido(const string &);
bool pedirContinuar();

// Prototipos del juego
void dibujarDado(const int); // Eduar
int LanzarDado();			 // Eduar

// Funcion Principal
int main() {
	int njugadores, ptsObjetivo, dado, ptsTurno;
	bool finTurno = false, finJuego = false;
	Jugador *jugadores = nullptr;

	srand(time(NULL)); // Nahomy

	generarTitulo("Juego de lanza el dado");

	njugadores = validarNumJugadores();
	jugadores = new Jugador[njugadores]; // crear el espacio para cada jugador

	validarNombreJugador(jugadores, njugadores);

	cout << endl;

	ptsObjetivo = validarPuntajeObtenido("Ingrese el puntaje a alcanzar");

	while (!finJuego) {
		for (int i = 0; i < njugadores; i++) {
			ptsTurno = 0;
			finTurno = false;

			while (!finTurno) {
				generarTitulo("Turno del jugador " + jugadores[i].nombre);
				cout << "Puntajes del turno actual: " << ptsTurno;
				cout << "\tPuntaje Obtenido: " << jugadores[i].puntos << " / " << ptsObjetivo;
				cout << endl << endl;

				cout << jugadores[i].nombre << " esta lanzando los dados...\n";
				dado = LanzarDado();
				cout << jugadores[i].nombre << " ha lanzado un: " << dado;

				if (dado == 1) {
					cout << ", pierdes todos los puntos obtenidos en este turno.\n\n";
					ptsTurno = 0;
					finTurno = true;
					pausarPrograma("continuar");

				} else {
					ptsTurno += dado;
					cout << "\n\nBien hecho " << jugadores[i].nombre << " sumaste ";
					cout << dado << " puntos en este turno.\n";
					finTurno = pedirContinuar();
				}

				if ((ptsTurno + jugadores[i].puntos) >= ptsObjetivo) {
					finTurno = true;
					finJuego = true;
				}
			}

			if (!finJuego) {
				generarTitulo("Fin del Turno de " + jugadores[i].nombre);
				cout << "Total de puntos obtenidos en este turno: " << ptsTurno << endl;
				jugadores[i].puntos += ptsTurno;
				cout << "Total de puntos obtenidos: " << jugadores[i].puntos << " / " << ptsObjetivo << endl;
				pausarPrograma("continuar");
			} else {
				generarTitulo("Fin del juego");
				cout << jugadores[i].nombre << " ha alcanzado el puntaje maximo.\n\n";
				pausarPrograma("salir");
				break;
			}
		}
	}

	delete[] jugadores;
	jugadores = nullptr;

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
	cout << lineas << endl;
	cout << setw(titulo.length() + titulo.length() / 2) << titulo << endl;
	cout << lineas << endl << endl;
}

void pausarPrograma(const string &mensaje) { // Andony
#ifdef _WIN32
	system("pause");
	(void)mensaje;
#else
	cout << endl << "Presione una tecla para " << mensaje << "...";
	cin.get();
#endif
}

// Funciones de validacion

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

int validarNumJugadores() {
	int numJugadores = 0;

	while (true) {
		numJugadores = validarEntrada("Ingrese la cantidad de jugadores");

		if (numJugadores >= 2 && numJugadores <= 5) break;

		cout << "Error: La cantida de jugadores tiene que ser de minimo 2 jugadores y maximo 5.\n\n";
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return numJugadores;
}

void validarNombreJugador(Jugador *jugadores, const int cat) {
	for (int i = 0; i < cat; i++) {
		while (true) {
			cout << "\nIngrese el nombre del jugador " << i + 1 << ": ";
			getline(cin, jugadores[i].nombre);

			if (!(jugadores[i].nombre.length() > 24)) break;

			cout << "Error: El nombre no puede tener mas de 24 caracteres. Intentelo de nuevo.\n";
		}
	}
}

int validarPuntajeObtenido(const string &mensaje) {
	int puntajeMeta = 0;

	while (true) {
		puntajeMeta = validarEntrada("Ingrese el puntaje objetivo a alcanzar");
		if (puntajeMeta >= 10) break;

		cout << "Error: la cantidad del puntaje objetivo tiene que ser mayor o igual a 10." << endl;
	}

	// Limpiar buffer
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return puntajeMeta;
}

bool pedirContinuar() {
	string entrada;

	do {
		cout << "Deseas lanzar de nuevo? (S/N): ";
		getline(cin, entrada);

		if (!entrada.empty()) {
			char respuesta = tolower(entrada[0]);

			if (respuesta == 's' || respuesta == 'n') {
				return (respuesta != 's');
			}
		}
		cout << "Opcion no valida! Por favor ingresa 'S' para continuar o 'N' para salir.\n\n";
	} while (true);
}

// Funciones del juego

void dibujarDado(const int cara) { // Eduar
	cout << endl << " ------- " << endl;
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
	cout << " ------- " << endl << endl;
}

int LanzarDado() { // Eduar o Nohemy
	int dado = 1 + rand() % 6;
	dibujarDado(dado);
	return dado;
}
