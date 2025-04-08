#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

// Estructura de un jugador
struct Jugador {
	string nombre;
	int puntos = 0;
};

// Prototipos Utilitarios
void LimpiarConsola();
void generarTitulo(const string &);
void pausarPrograma(const string &);

// Prototipos de validacion
int validarEntrada(const string &);
int validarNumJugadores();
void pedirNombreJugadores(Jugador *, const int);
int validarPuntajeObtenido(const string &);
bool pedirContinuar();

// Prototipos del juego
void dibujarDado(const int);
int LanzarDado();

// Funcion Principal
int main() {
	int njugadores, ptsObjetivo, dado, ptsTurno;
	bool finTurno = false, finJuego = false;
	Jugador *jugadores = nullptr; // Arreglo de jugadores

	srand(time(NULL)); // Inicializar la semilla aleatoria

	generarTitulo("Juego de lanza el dado");

	njugadores = validarNumJugadores();	 // Validar la cantidad de jugadores
	jugadores = new Jugador[njugadores]; // Crear arreglo de jugadores

	pedirNombreJugadores(jugadores, njugadores);
	cout << endl;
	ptsObjetivo = validarPuntajeObtenido("Ingrese el puntaje a alcanzar");

	while (!finJuego) {
		// Iterar por cada jugador
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
					ptsTurno = 0;	 // Reinicia el puntaje del turno
					finTurno = true; // Termina el turno
					pausarPrograma("continuar");

				} else {
					ptsTurno += dado; // Sumar el puntaje del dado al puntaje del turno
					cout << "\n\nBien hecho " << jugadores[i].nombre << " sumaste ";
					cout << dado << " puntos en este turno.\n";
					finTurno = pedirContinuar(); // Pregunta si desea continuar lanzando
				}

				if ((ptsTurno + jugadores[i].puntos) >= ptsObjetivo) {
					// Si el jugador alcanza el puntaje objetivo
					finTurno = true;
					finJuego = true;
				}
			}

			jugadores[i].puntos += ptsTurno;

			if (!finJuego) { // Si el jugador no alcanza el puntaje objetivo
				generarTitulo("Fin del Turno de " + jugadores[i].nombre);
				cout << "Total de puntos obtenidos en este turno: " << ptsTurno << endl;
				cout << "Total de puntos obtenidos: " << jugadores[i].puntos << " / " << ptsObjetivo << endl;
				pausarPrograma("continuar");
			} else { // Si el jugador alcanza el puntaje objetivo
				generarTitulo("Fin del juego");
				cout << jugadores[i].nombre << " ha alcanzado el puntaje maximo.\n\n";
				pausarPrograma("salir");
				break;
			}
		}
	}

	// Limpiar la memoria dinamica
	delete[] jugadores;
	jugadores = nullptr;

	return 0;
}

// Funciones Utilitarias

void LimpiarConsola() {
#ifdef _WIN32 // Windows

	system("cls");
#else // Linux o MacOS
	system("clear");
#endif
}

void generarTitulo(const string &titulo) {
	// Generar un titulo con asteriscos y el nombre del juego centrado
	const string lineas(titulo.length() * 2, '*');

	LimpiarConsola();
	cout << lineas << endl;
	cout << setw(titulo.length() + titulo.length() / 2) << titulo << endl;
	cout << lineas << endl << endl;
}

void pausarPrograma(const string &mensaje) {
#ifdef _WIN32 // Windows
	system("pause");
	(void)mensaje;
#else // Linux o MacOS
	cout << endl << "Presione una tecla para " << mensaje << "...";
	cin.get();
#endif
}

// Funciones de validacion

int validarEntrada(const string &mensaje) {
	int entrada = 0;

	while (true) {
		cout << mensaje << ": ";
		if (cin >> entrada) {
			if (cin.peek() == '\n') break;
		}

		cin.clear();										 // Limpiar el estado de error
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
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

	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

	return numJugadores;
}

void pedirNombreJugadores(Jugador *jugadores, const int cat) {
	// Pedir los nombre de los jugadores
	for (int i = 0; i < cat; i++) {
		while (true) {
			cout << "\nIngrese el nombre del jugador " << i + 1 << ": ";
			getline(cin, jugadores[i].nombre);

			if (!(jugadores[i].nombre.length() > 24)) break; // Validar que el nombre no exceda 24 caracteres

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
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

	return puntajeMeta;
}

bool pedirContinuar() {
	string entrada;

	do {
		cout << "Deseas lanzar de nuevo? (S/N): ";
		getline(cin, entrada);

		if (!entrada.empty()) {					  // Verificar que la entrada no esté vacía
			char respuesta = tolower(entrada[0]); // convertir a minuscula

			if (respuesta == 's' || respuesta == 'n') {
				return (respuesta != 's');
			}
		}
		cout << "Opcion no valida! Por favor ingresa 'S' para continuar o 'N' para salir.\n\n";
	} while (true);
}

// Funciones del juego

void dibujarDado(const int cara) {
	// Dibuja un dado en la consola dependiendo de la cara que se le pase como argumento
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

int LanzarDado() {
	int dado = 1 + rand() % 6; // Generar un número aleatorio entre 1 y 6
	dibujarDado(dado);
	return dado;
}
