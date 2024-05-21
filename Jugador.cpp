#include <iostream>
#include <string>
#include "Jugador.h"

using namespace std;

// CONSTRUCTORS 
Jugador::Jugador() {
	// Pre: --; Post: jugador buid
	a_nom = "Nom_jugador";
	n_c = 0;
	a_punts = 0;
}

Jugador::Jugador(string nom) {
	// Pre: --; Post: jugador amb dades correctes
	a_nom = nom;
	n_c = 0;
	a_punts = 0;
}

// CONSULTORS 
Carta Jugador::obt_carta(int pos) const {
	// Pre: --;
	// Post: retorna carta de la posicio pos
	return a_cartes[pos];
}

void Jugador::mostrar_ma(bool resum) const {
	// Pre: jugador no buid; 
	// Post: mostra per pantalla tot el contingut de la ma del jugador actual si resum es fals, en cas contrari nomes mostra magia
	for (int i = 0; i < MAX_CARTES; i++){
		if (!resum) { 
			cout << i << ":"; 
			a_cartes[i].mostrar(false); 
		}
		else a_cartes[i].mostrar(true);
		cout << " ";
	}
}

void Jugador::mostrar_seguidors(bool resum) const {
	// Pre: jugador no buid; 
	// Post: mostra per pantalla tots els seguidors del jugador actual si resum es fals, en cas contrari nomes mostra magia
	a_seguidors.mostrar(resum);	
}

string Jugador::nom() const {
	// Pre: --; 
	// Post: retorna nom del jugador
	return a_nom;
}

bool Jugador::existeix(int pos) const {
	// Pre: --;
	// Post: retorna cert si la carta en la posicio pos existeix
	return !(a_cartes[pos] == Carta('M', 0, 'G'));
}

Seguidors Jugador::obt_seguidors() const {
	// Pre: --;
	// Post: retorna seguidors del jugador actual
	return a_seguidors;
}

int Jugador::punts_decepcio() const {
	// Pre: --; 
	// Post: retorna punts decepcio del jugador
	return a_punts;
}

// MODIFICADORS 
void Jugador::suma_punts_decepcio(int d) {
	// Pre: --;
	// Post: suma d punts als punts de decepcio del jugador actual
	a_punts += d;
}

void Jugador::afegir_carta(const Carta& c) {
	// Pre:--;
	// Post: c s'ha afegit al jugador;
	a_cartes[n_c] = c;
	n_c++;
}

void Jugador::afegir_carta_en_pos(const Carta& c, int pos) {
	// Pre:--;
	// Post: c s'ha afegit al jugador en la posicio pos;
	a_cartes[pos] = c;
}

void Jugador::afegir_seguidor(const Carta& c) {
	// Pre:--;
	// Post: c s'ha afegit als seguidors del jugador
	a_seguidors.inserir(c);
}

void Jugador::afegir_seguidors_a(Jugador& j, char magia) {
	// Pre:--;
	// Post: s'han afegit un conjunt de seguidors d'una màgia que no tingui el jugador
	Seguidors s = a_seguidors;
	j.a_seguidors.inserir_conjunt(s, magia);
	eliminar_seguidors(magia);
}

void Jugador::eliminar_carta(const Carta& c) {
	// Pre:--;
	// Post: c s'ha eliminat del jugador;
	bool trobada = false;
	int i = 0;
	while (i < n_c and !trobada) {
		if (a_cartes[i] == c) {
			a_cartes[i] = Carta();
			trobada = true;
		}
		i++;
	}
}

void Jugador::eliminar_seguidors(const char& m) {
	// Pre:--;
	// Post: s'han eliminat tots els seguidors d'una màgia
	a_seguidors.eliminar_seguidors(m);
}

void Jugador::passar_cartes_a_seguidors() {
	// Pre:--;
	// Post: cartes de la mà passades al conjunt de seguidors
	for (int i = 0; i < MAX_CARTES; i++) {
		if (!obt_carta(i).buida()) {
			a_seguidors.inserir(obt_carta(i));
		}
	}
}

ostream& operator<<(ostream& o, const Jugador& j) {
	// Pre: es pot escriure a o; 
	// Post: s’ha escrit la informació de j a o
	o << j.a_nom;
	return o;
}