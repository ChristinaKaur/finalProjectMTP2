#include <iostream>
#include <string>
#include "PilaCartes.h"

using namespace std;

// CONSTRUCTORS I DESTRUCTOR 
PilaCartes::PilaCartes() {
	// Pre: --; Post: pila buida
	// COST: O(1)
	a_cim = NULL;
}

PilaCartes::PilaCartes(const PilaCartes& o) {
	// Pre: --; Post: aquesta pila es copia de la PilaCartes o
	// COST: O(n)
	a_cim = NULL;
	copia(o); // crida a metode privat
}

PilaCartes::~PilaCartes() {
	// Pre: --; Post: memoria alliberada
	// COST: O(n)
	allibera(); // crida a metode privat
}

// CONSULTORS 
bool PilaCartes::buida() const {
	// Pre: -- ; Post: retorna cert si la pila es buida; fals en cas contrari
	// COST: O(1)
	return a_cim == NULL;
}

Carta PilaCartes::cim() {
	// Pre: pila no buida; Post: retorna copia del primer de la pila
	// COST: O(1)
	Carta cim;
	if (mida() > 0) cim = a_cim->c;
	return cim;
}

int PilaCartes::mida() const {
	// Pre: -- ; 
	// Post: retorna mida de la pila 
	int comptador = 0;
	if (not buida()) {
		Node* aux = a_cim;
		while (aux != NULL) {
			comptador++;
			aux = aux->seg;
		}
	}
	return comptador;
}

void PilaCartes::mostrar() const {
	// Pre: pila no buida; 
	// Post: mostra per pantalla tot el contingut de la Pila de Cartes actual 
	if (!buida()) {
		Node* actual = a_cim;
		while (actual != NULL) {
			actual->c.mostrar(true);
			cout << " ";
			actual = actual->seg;
		}
		cout << endl;
	}
	else cout << "NO HI HA CAP CARTA" << endl;
}

// MODIFICADORS
void PilaCartes::empilar(Carta c) {
	// Pre: --; Post: ha afegit c al final de la pila
	// COST: O(1)
	Node* nou = new Node; // necessari reservar memoria
	nou->c = c;
	nou->seg = a_cim;
	a_cim = nou;
}

void PilaCartes::desempila() {
	// Pre: pila no buida; Post: ha eliminat el primer de la pila
	// COST: O(1)
	Node* aux = a_cim;
	a_cim = a_cim->seg;
	delete aux;
}

// OPERADORS
PilaCartes& PilaCartes::operator=(const PilaCartes& o) {
	// Pre: -- ; Post: pila actual = pila o
	if (this != &o) {
		allibera();
		copia(o);
	}
	return *this;
}

void PilaCartes::copia(const PilaCartes& o) {
	// Pre: pila buida; Post: aquesta pila es copia de o
	if (not o.buida()) {
		Node* p, * q, * aux;
		p = new Node; a_cim = p;
		aux = o.a_cim; p->c = aux->c; p->seg = NULL;
		q = p;
		while (aux->seg != NULL) {
			aux = aux->seg;
			p = new Node; q->seg = p;
			p->c = aux->c; p->seg = NULL;
			q = p;
		}
	}
}

void PilaCartes::allibera() {
	// Pre: --; Post: pila buida
	while (not buida()) {
		Node* aux = a_cim;
		a_cim = a_cim->seg;
		delete aux;
	}
}
