#include <iostream>
#include <iomanip>
#include <string>
#include "Seguidors.h"

using namespace std;

// CONSTRUCTORS I DESTRUCTOR 
Seguidors::Seguidors() {
	// Pre: --; Post: llista de seguidors buida
	a_inici = NULL;
}

Seguidors::Seguidors(const Seguidors& o) {
	// Pre: --; Post: aquesta llista de seguidors es copia de Seguidors o
	a_inici = NULL;
	copia(o);
}

Seguidors::~Seguidors() {
	// Pre: --; Post: memoria alliberada
	allibera();
}

Seguidors& Seguidors::operator=(const Seguidors& o) {
	// Pre:--;
	// Post: aquesta llista es copia de o i abans s'ha alliberat la memoria ocupada per aquesta llista
	if (this != &o) {
		allibera();
		copia(o);
	}
	return *this;
}

// CONSULTORS 
int Seguidors::suma_influencia(char magia) const {
	// Pre:--;
	// Post: retorna el numero dinfluencia que te magia
	int suma = 0;
	if (!(*this).buida()) {
		Node* p = a_inici;
		while (p != NULL) {
			if (p->dada.magia() == magia) {
				suma += p->dada.influencia();
			}
			p = p->seg;
		}
	}
	return suma;
}

void Seguidors::mostrar(bool resum) const {
	// Pre:--;
	// Post: mostra la llista de seguidors si resum és fals, en cas contrari mostra un resum dels seguidors
	if (!resum) {
		Node* p = a_inici;
		while (p != NULL) {
			cout << p->dada << " ";
			p = p->seg;
		}
	}
	else {
		for (int i = 0; i < Carta::MAX_MAGIA; i++) {
			cout << "[" << setfill(' ') << setw(2);
			int suma = suma_influencia(Carta::MAGIA[i]);
			if (suma > 0)
				cout << suma; // si la suma > 0
			else if (suma == 0)
				cout << ' '; // si la suma = 0
			cout << Carta::MAGIA[i] << "] ";
		}
	}
}

bool Seguidors::buida() const {
	// Pre: --
	// Post: retorna cert si la llista de seguidors actual és buida, fals en cas constrari
	return a_inici == NULL;
}

bool Seguidors::existeix(Carta c) const {
	// Pre: -- 
	// Post: ens diu si c existeix a la llista
	Node* p = a_inici;
	bool fiCerca = false;
	bool trobat = false;
	while ((p != NULL) && (!fiCerca)) {
		if (p->dada >= c) {
			fiCerca = true;
			trobat = p->dada == c;
		}
		else
			p = p->seg;
	}
	return trobat;
}

// MODIFICADORS 
void Seguidors::inserir_conjunt(Seguidors& s, char m) {
	// Pre: magia correcte i s omplert correctament
	// Post: afegeix el conjunt de seguidors de s de magia m a seguidors actuals
	Node* p;
	p = s.a_inici;
	while (p != NULL) {
		if (p->dada.magia() == m) {
			inserir(p->dada);
			p = p->seg;
		}
		else p = p->seg;
	}
}

void Seguidors::inserir(Carta c) {
	// Pre: --
	// Post: si c no existeix s'ha inserit en el lloc que li toca per mantenir l'ordre; en cas contrari no es fa cap insercio
	Node* ant, * p, * nou;
	bool fiCerca = false;
	bool trobat = false;
	ant = NULL;
	p = a_inici;
	while ((p != NULL) && (!fiCerca)) {
		if (p->dada >= c) {
			fiCerca = true;
			trobat = p->dada == c;
		}
		else {
			ant = p;
			p = p->seg;
		}
	}
	if (!trobat) {
		nou = new Node;
		nou->dada = c;
		nou->seg = p;
		if (ant == NULL)
			a_inici = nou;
		else
			ant->seg = nou;
	}
}

void Seguidors::eliminar(Carta c) {
	// Pre: --
	// Post: si c existeix s'ha eliminat
	Node* ant, * p;
	bool fiCerca = false;
	bool trobat = false;
	ant = NULL;
	p = a_inici;
	while ((p != NULL) and (!fiCerca)) {
		if (p->dada >= c) {
			fiCerca = true;
			trobat = p->dada == c;
		}
		else {
			ant = p;
			p = p->seg;
		}
	}
	if (trobat) {
		if (ant != NULL)
			ant->seg = p->seg;
		else a_inici = p->seg;
		delete p;
	}
}

void Seguidors::eliminar_seguidors(const char m) {
	// Pre:--
	// Post: s'han esborrat els seguidors d'una magia m
	Node *ant, *p;
	ant = NULL;
	p = a_inici;
	while (p != NULL) {
		if (p->dada.magia() == m) {
			Node* aux;
			aux = p;
			if (ant != NULL)
				ant->seg = p->seg;
			else a_inici = p->seg;
			p = aux->seg;
			delete aux;
		}
		else {
			ant = p;
			p = p->seg;
		}
	}
}

// PRIVATE
void Seguidors::copia(const Seguidors& o) {
	// Pre: memoria dinamica alliberada; 
	// Post: aquesta llista es copia de o
	if (!o.buida()) {
		Node* ant, * p, * q;
		p = o.a_inici;
		q = new Node; a_inici = ant = q;
		q->dada = p->dada; q->seg = NULL;
		p = p->seg;
		while (p != NULL) {
			q = new Node;
			q->dada = p->dada; q->seg = NULL;
			ant->seg = q;
			ant = q;
			p = p->seg;
		}
	}
}

void Seguidors::allibera() {
	// Pre: --; Post: memoria dinamica alliberada 
	while (!buida()) {
		Node* aux = a_inici;
		a_inici = a_inici->seg;
		delete aux;
	}
}
