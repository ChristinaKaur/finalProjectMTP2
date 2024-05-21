#include <iostream>
#include <string>
#include "Baralla.h"

using namespace std;

// CONSTRUCTORS I DESTRUCTOR 
Baralla::Baralla() {
	// Pre: --; Post: baralla buida
	a_n = 0;
	a_max = MAX;
	reserva();

	a_xn = 1;
	omplir_baralla();
	barrejar();
}

Baralla::Baralla(const int llavor) {
	// Pre: --; Post: aquesta baralla te de a_llavor llavor
	a_n = 0;
	a_max = MAX;
	reserva();
	
	a_xn = llavor;
	omplir_baralla();
	barrejar();
}

Baralla::Baralla(const Baralla& o) {
	// Pre: --; Post: aquesta baralla es copia de la Baralla o
	copia(o);
}

Baralla::~Baralla() {
	// Pre: --; Post: memoria alliberada
	allibera();
}

// CONSULTORS 
void Baralla::mostrar(const string titol) const {
	// Pre: baralla no buida; 
	// Post: mostra per pantalla tot el contingut de la baralla actual    
	cout << titol << ":" << endl;
	if (a_n > 0) {
		for (int i = 0; i < a_n; i++)
			cout << a_carta[i] << " ";
		cout << endl;
	}
	else 
		cout << "NO HI HA CAP CARTA";
	cout << endl;
}

int Baralla::aleatori(int rang) {
	//Pre:--; Post: ens retorna un valor aleatori de la baralla 
	return generador_aleatori(rang);
}

int Baralla::mida() const {
	// Pre:--
	// Post: retorna numero de cartes que conté la baralla actual
	return a_n;
}

bool Baralla::buida() const {
	// Pre:--
	// Post: retorna cert si la baralla actual és buida, fals en cas constrari
	return a_n <= 0;
}

// MODIFICADORS 
void Baralla::afegir(const Carta& c) {
	// Pre:--;
	// Post: c s'ha afegit a la taula; 
	if (a_n == a_max) expandeix();
	a_carta[a_n] = c;
	a_n++;
}

Carta Baralla::robar() {
	// Pre: baralla no buida;
	// Post: retorna copia de l'última carta de la baralla
	Carta ultima = a_carta[a_n - 1];
	a_n--;
	return ultima;
}

void Baralla::retirar_cartes(const int n) {
	// Pre: baralla no buida;
	// Post: baralla amb n cartes retirades
	for (int i = 0; i < n; i++)
		robar();
}

void Baralla::barrejar() {
	// Pre:--
	// Post: barreja de forma aleatoria la baralla actual
	for (int i = a_n - 1; i > 0; i--) {
		int pos = aleatori(i + 1);
		intercanvi(a_carta[pos], a_carta[i]);
	}
}

void Baralla::intercanvi(Carta& a, Carta& b) {
	// Pre: a = A i b = B
	// Post: a = B i b = A
	Carta aux = a;
	a = b;
	b = aux;
}

void Baralla::omplir_baralla() {
	// Pre: --
	// Post: s'omple la baralla amb totes les cartes (90)
	for (int i = 0; i < Carta::MAX_MAGIA; i++)
		for (int j = 0; j < Carta::MAX_GERMANDAT; j++)
			for (int z = 0; z <= 4; z++)
				afegir(Carta(Carta::MAGIA[i], z + 1, Carta::GERMANDAT[j]));
}

// OPERADORS REDEFINITS 
Baralla& Baralla::operator=(const Baralla& o) {
	// Pre: -- ; Post: o afegit a la taula
	if (this != &o) {
		allibera();
		copia(o);
	}
	return *this;
}

ostream& operator<<(ostream& o, const Baralla& b) {
	// Pre: es pot escriure a o; 
	// Post: s’ha escrit la informació de b a o
	b.mostrar("BARALLA");
	return o;
}

// METODES PRIVATS

void Baralla::allibera() {
	//Pre: --; Post: memòria alliberada
	delete [] a_carta;
}

void Baralla::copia(const Baralla& b) {
	//Pre: memòria alliberada; Post: aquesta baralla és còpia de la baralla b
	a_n = b.a_n;
	a_max = b.a_max;
	reserva();
	for (int i = 0; i < a_n; i++)
		a_carta[i] = b.a_carta[i];
}

void Baralla::reserva() {
	//Pre: --; Post: memòria reservada per a_max enter
	a_carta = new Carta[a_max];
}

void Baralla::expandeix() {
	//Pre: --; Post: la memòria reservada es dobla
	Carta* aux = a_carta; // taula a substituir
	a_max = 2 * a_max; // s’amplia la capacitat
	reserva(); // es crea la nova taula
	for (int i = 0; i < a_n; i++) // es copien les caselles
		a_carta[i] = aux[i];
	delete[] aux;
}

int Baralla::generador_aleatori(int rang) {
	//Pre: --; Post: es genera un valor aleatoriament 
	int a = 1103515245, c = 12345, m = 32768;
	unsigned a_seg = a * a_xn + c;
	int valor = ((a_seg / 32) % m) % rang;
	a_xn = a_seg;
	return valor;
}
