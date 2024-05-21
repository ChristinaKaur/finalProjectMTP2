#include <iostream>
#include <string>
#include "Joc.h"

using namespace std;

const char PILA_E = 'e', PILA_D = 'd';
const int MIDA_TAULER = 4;

// CONSTRUCTORS I DESTRUCTOR 
Joc::Joc() {
	// Pre: --; Post: joc buid
	a_baralla = Baralla();
	a_baralla.barrejar();
	n_j = 0;
	a_pila_dreta = PilaCartes();
	a_pila_esq = PilaCartes();
	a_tauler = Tauler();
}

Joc::Joc(const int llavor) {
	// Pre: --; Post: joc amb dades correctes
	a_baralla = Baralla(llavor);
	n_j = 0;
	a_pila_dreta = PilaCartes();
	a_pila_esq = PilaCartes();
	a_tauler = Tauler();
}

// CONSULTORS 
void Joc::mostrar_piles() const {
	// Pre: piles no buides; 
	// Post: mostra per pantalla el contingut de les dos piles del joc actual  
	cout << endl << "PILA ESQUERRA:" << endl;
	a_pila_esq.mostrar();
	cout << endl << "PILA DRETA:" << endl;
	a_pila_dreta.mostrar();
}

void Joc::mostrar_seguidors() const {
	// Pre: --;
	// Post: mostrar per pantalla els seguidors de cada jugador 
	cout << "TOTS ELS SEGUIDORS:" << endl;
	for (int j = 0; j < n_j; j++) {
		cout << j + 1 << " " << a_jugador[j].nom() << endl << " ";
		a_jugador[j].mostrar_seguidors(false);
		cout << endl;
	}
}

void Joc::mostrar_punts_decepcio() const{
	// Pre: --;
	// Post: mostrar per pantalla els punts de decepcio de cada jugador
	cout << endl << "PUNTS DE DECEPCIO:" << endl;

	Jugador guanyador = a_jugador[0];
	for (int i = 0; i < n_j; i++) {
		cout << setfill(' ') << setw(3) << a_jugador[i].punts_decepcio() << " " << a_jugador[i].nom() << endl;
		if (a_jugador[i].punts_decepcio() < guanyador.punts_decepcio())
			guanyador = a_jugador[i];
	}
	cout << endl << "ENHORABONA " << guanyador.nom() << "! " << "HAS GUANYAT LA PARTIDA!" << endl;
}

void Joc::mostrar_resultat() const {
	// Pre: --; 
	// Post: mostrar per pantalla el resultat de la partida (tots els seguidors, resum dels seguidors i  punts de decepcio)
	cout << endl << "RESULTAT FINAL" << endl;
	cout << string(14, '=') << endl << endl;
	
	mostrar_seguidors();
	mostrar_resum_seguidors(0);
	mostrar_punts_decepcio();	
}

void Joc::mostrar_mans_oponents(const int i) const {
	// Pre: --;
	// Post: mostrar mans dels jugadors
	cout << endl << endl << "MANS DELS OPONENTS:" << endl;
	for (int j = 0; j < n_j; j++) {
		if (j != i) {
			a_jugador[j].mostrar_ma(true);
			cout << "  " << j + 1 << " " << a_jugador[j].nom() << endl;
		}
	}
}

void Joc::mostrar_resum_seguidors(const int i) const {
	// Pre: --;
	// Post: mostrar resum dels seguidors
	cout << endl << "RESUM DELS SEGUIDORS:" << endl;
	a_jugador[i].mostrar_seguidors(true);
	cout << "  " << i + 1 << " " << a_jugador[i].nom() << endl;
	for (int j = 0; j < n_j; j++) {
		if (j != i) {
			a_jugador[j].mostrar_seguidors(true);
			cout << "  " << j + 1 << " " << a_jugador[j].nom() << endl;
		}
	}
}

void Joc::mostrar_joc(const int i) {
	// Pre: --;
	// Post: mostrar informació del jugador a_jugador[i]
	cout << endl << "TORN DE " << a_jugador[i].nom() << endl;
	cout << string(8 + a_jugador[i].nom().size(), '=') << endl;
	cout << endl;

	a_tauler.mostrar(a_pila_esq.cim(), a_pila_dreta.cim());
	cout << endl << "MA DE " << a_jugador[i].nom() << ":" << endl;
	a_jugador[i].mostrar_ma(false);
	mostrar_mans_oponents(i);
	mostrar_resum_seguidors(i);
}

bool Joc::influencia_permesa(char m, int jug, int jug_actual) {
	// Pre: --;
	// Post: retorna cert si es pot cerdir influencia al jugador jug
	bool correcte = ((jug >= 0 and jug < n_j) and a_jugador[jug].obt_seguidors().suma_influencia(m) == 0 and a_jugador[jug_actual].obt_seguidors().suma_influencia(m) != 0 and magia_valida(m));
	return correcte;
}

bool Joc::jugada_permesa(int pos_carta, int pos_tauler_i, int pos_tauler_j, char pila, int jug) {
	// Pre: --;
	// Post: retorna cert si la jugada passada per parametres és valida
	bool valid = false;
	if (a_tauler.pos_valida(pos_tauler_i, pos_tauler_j) and a_tauler.obtElem(pos_tauler_i, pos_tauler_j) == Carta('M', 0, 'G')) {
		if (a_jugador[jug].existeix(pos_carta)) {
			if (pila == PILA_E) {
					valid = true;
			}
			else {
					valid = true;
			}
		}
	}
	return valid;
}

bool Joc::partida_finalitzada() const {
	// Pre: --;
	// Post: retorna si s'ha de finalitzar la partida
	return a_pila_dreta.buida() and a_pila_esq.buida();
}

char Joc::una_pila_buida() const {
	// Pre: --;
	// Post: returna la pila que no esta buida si només una de les dos piles esta buida, en cas contrari retorna 'n'
	char p;
	if ((a_pila_dreta.buida() and !a_pila_esq.buida()) or (!a_pila_dreta.buida() and a_pila_esq.buida())) {
		if (a_pila_esq.buida())
			p = 'd';
		else
			p = 'e';
	}
	else
		p = 'n';
	return p;
}

// MODIFICADORS 
void Joc::calcula_punts_decepcio() {
	// Pre: --;
	// Post: calcula els punts de decepcio de cada jugador
	for (int j = 0; j < n_j; j++) {
		a_jugador[j].passar_cartes_a_seguidors();
	}

	for (int i = 0; i < Carta::MAX_MAGIA; i++) {
		int jugador_amb_menys_influ = 0;
		for (int j = 1; j < n_j; j++) {
			if (a_jugador[j].obt_seguidors().suma_influencia(Carta::MAGIA[i]) > a_jugador[jugador_amb_menys_influ].obt_seguidors().suma_influencia(Carta::MAGIA[i])) {
				jugador_amb_menys_influ = j;
			}
		}
		for (int j = 0; j < n_j; j++) {
			if (j != jugador_amb_menys_influ) {
				a_jugador[j].suma_punts_decepcio(a_jugador[j].obt_seguidors().suma_influencia(Carta::MAGIA[i]));
			}
		}
	}
}

void Joc::enviar_seguidors_de(char magia, int jugador_jugant, int altre_jugador) {
	// Pre: jugada permesa
	// Post: enviar tots els seguidors del jugador_jugant de la magia indicada a l'altre_jugador
	a_jugador[jugador_jugant].afegir_seguidors_a(a_jugador[altre_jugador], magia);
}

void Joc::fer_jugada(int pos_carta, int pos_tauler_i, int pos_tauler_j, char pila, int jug) {
	// Pre: tots els valors son correctes i la jugada està permesa
	// Post: fer jugada amb influencia si influencia és cert, en cas contrari fer jugada sense influencia i retorna si s'ha finalitzat la jugada
	Carta carta = a_jugador[jug].obt_carta(pos_carta);
	a_tauler.posarElem(pos_tauler_i, pos_tauler_j, carta);
	comprovar_tauler(carta, pos_tauler_i, pos_tauler_j, jug);

	if (a_tauler.espais_buits() == 0) resoldre_crisi_magica(jug, pos_tauler_i, pos_tauler_j);

	if (!partida_finalitzada()) {
		if (pila == PILA_E) robar_carta(a_pila_esq, jug, pos_carta);
		else robar_carta(a_pila_dreta, jug, pos_carta);


		if (a_tauler.espais_buits() > 4) {
			int espais_a_omplir = a_tauler.espais_buits() - 4;
			omplir_resta_tauler(pila, espais_a_omplir);
		}
	}
	else {
		a_jugador[jug].eliminar_carta(a_jugador[jug].obt_carta(pos_carta));
	}
}

void Joc::omplir_tauler_pila(PilaCartes& p, int& n) {
	// Pre: p i n forats a omplir correctes
	// Post: omplir tauler amb cartes de la pila p fins n o fins que s'acabin les cartes de la pila p, retorna el numero de cartes posades
	int i = 0;
	while (n > 0 and !p.buida() and i < MIDA_TAULER) {
		int j = 0;
		while (n > 0 and !p.buida() and j < MIDA_TAULER) {
			if (a_tauler.obtElem(i, j).buida()) {
				a_tauler.posarElem(i, j, p.cim());
				p.desempila();
				n--;
			}
			j++;
		}
		i++;
	}
}

bool Joc::omplir_resta_tauler(char pila, int& n) {
	// Pre: pila i n forats a omplir correctes
	// Post: omplir n forats del tauler amb cartes de la pila indicada (si s'acaba, de l'laltre), retorna cert si no hi ha mes cartes a les piles
	if (pila == PILA_E) {
		omplir_tauler_pila(a_pila_esq, n);
		if (n > 0 and !a_pila_dreta.buida())
			omplir_tauler_pila(a_pila_dreta, n);
	}
	else {
		omplir_tauler_pila(a_pila_dreta, n);
		if (n > 0 and !a_pila_esq.buida())
			omplir_tauler_pila(a_pila_esq, n);
	}
	return a_pila_dreta.buida() and a_pila_esq.buida();
}

void Joc::robar_carta(PilaCartes& pila, int jug, int pos_carta) {
	// Pre: pila correcte
	// Post: es roba una carta de la pila indicada per jugador jug
	a_jugador[jug].afegir_carta_en_pos(pila.cim(), pos_carta);
	pila.desempila();
}

void Joc::comprovar_tauler(Carta carta, int pos_tauler_i, int pos_tauler_j, int jug) {
	// Pre: tots els valors son correctes i la jugada està permesa
	// Post: comprovar si s'ha convençut a algun bruixot i posar-los en els seguidors del jugador jug
	int suma_fila = a_tauler.suma_influencies('f', pos_tauler_i, pos_tauler_j);
	if (suma_fila >= 10)
		obtenir_seguidors("fila", pos_tauler_i, pos_tauler_j, jug);
	int suma_columna = a_tauler.suma_influencies('c', pos_tauler_i, pos_tauler_j);
	if (suma_columna >= 10) 
		obtenir_seguidors("columna", pos_tauler_i, pos_tauler_j, jug);
}

void Joc::afegir_jugador(const Jugador& j) {
	// Pre: --
	// Post: jugador afegit a joc
	if (n_j < MAX_JUGADORS) {
		a_jugador[n_j] = j;
		n_j++;
	}
}

void Joc::retirar_cartes() {
	// Pre: baralla omplerta correctament
	// Post: retira n cartes de la baralla
	if (!a_baralla.buida()) {
		int n_mag = 6;
		int n = n_mag * MAX_JUGADORS + n_mag * (MAX_JUGADORS - n_j);
		a_baralla.retirar_cartes(n);
	}
}

void Joc::repartir_cartes() {
	// Pre: baralla omplerta correctament
	// Post: repartir 4 cartes a cada jugador
	if (!a_baralla.buida()) 
		for (int i = 0; i < n_j; i++) 
			for (int j = 0; j < 4; j++)
				a_jugador[i].afegir_carta(a_baralla.robar());
}

void Joc::ompliar_tauler() {
	// Pre: baralla omplerta correctament
	// Post: omplir el tauler amb 12 cartes
	if (!a_baralla.buida()) {
		for (int j = 0; j < 4; j++)
			a_tauler.posarElem(0, j, a_baralla.robar());

		for (int i = 1; i < 3; i++)
			for (int j = 0; j < 4; j++)
				if (j == 0 or j == 3)
					a_tauler.posarElem(i, j, a_baralla.robar());

		for (int j = 0; j < 4; j++)
			a_tauler.posarElem(3, j, a_baralla.robar());
	}
}

void Joc::omplir_piles() {
	// Pre: baralla omplerta correctament 
	// Post omplir piles amb cartes de la baralla
	if (!a_baralla.buida()) {
		int mida_baralla = a_baralla.mida() + 1;
		for (int i = 0; i < mida_baralla / 2; i++)
			a_pila_esq.empilar(a_baralla.robar());
		for (int j = 0; j < mida_baralla / 2; j++)
			a_pila_dreta.empilar(a_baralla.robar());
	}
}

void Joc::preparar() {
	// Pre: --
	// Post: cartes del joc actual barrejades, retirades i repartides
	retirar_cartes();
	repartir_cartes();
	ompliar_tauler();	
	omplir_piles();
}

// PRIVATE
void Joc::obtenir_seguidors(string a, int i, int j, int jug) {
	// Pre: a, i, j i jug valors vàlids 
	// Post: tots els bruixots convencuts del tauler es truen i s'envien com a seguidors del jugador jug
	int pos;
	bool fi = false;
	if (a == "columna") {
		pos = i;
		while (pos >= 0 and !a_tauler.obtElem(pos, j).buida()) {
			if (a_tauler.obtElem(pos, j).comparar(a_tauler.obtElem(i, j))) {
				a_jugador[jug].afegir_seguidor(a_tauler.obtElem(pos, j));
				a_tauler.treureElem(pos, j);
			}
			pos--;
		}
		pos = i;
		while (pos < MIDA_TAULER and !a_tauler.obtElem(pos, j).buida()) {
			if (a_tauler.obtElem(pos, j).comparar(a_tauler.obtElem(i, j))) {
				a_jugador[jug].afegir_seguidor(a_tauler.obtElem(pos, j));
				a_tauler.treureElem(pos, j);
			}
			pos++;
		}
	}
	else if (a == "fila") {
		pos = j;
		while (pos >= 0 and !a_tauler.obtElem(i, pos).buida()) {
			if (a_tauler.obtElem(i, pos).comparar(a_tauler.obtElem(i, j))) {
				a_jugador[jug].afegir_seguidor(a_tauler.obtElem(i, pos));
				a_tauler.treureElem(i, pos);
			}
			pos--;
		}
		pos = j;
		while (pos < MIDA_TAULER and !a_tauler.obtElem(i, pos).buida()) {
			if (a_tauler.obtElem(i, pos).comparar(a_tauler.obtElem(i, j))) {
				a_jugador[jug].afegir_seguidor(a_tauler.obtElem(i, pos));
				a_tauler.treureElem(i, pos);
			}
			pos++;
		}
	}
}

void Joc::resoldre_crisi_magica(int jug, int pos_i, int pos_j) {
	// Pre: jugador jug, i i j correcte
	// Post: tots els bruixots de germandat diferent a jug passen a ser seguidors de jug
	char germ = a_tauler.obtElem(pos_i, pos_j).germandat();
	for (int i = 0; i < MIDA_TAULER; i++) {
		if (a_tauler.obtElem(i, pos_j).germandat() != germ) {
			a_jugador[jug].afegir_seguidor(a_tauler.obtElem(i, pos_j));
			a_tauler.treureElem(i, pos_j);
		}
	}
	for (int j = 0; j < MIDA_TAULER; j++) {
		if (a_tauler.obtElem(pos_i, j).germandat() != germ) {
			a_jugador[jug].afegir_seguidor(a_tauler.obtElem(pos_i, j));
			a_tauler.treureElem(pos_i, j);
		}
	}
}

bool Joc::magia_valida(char m) const {
	// Pre: --;
	// Post: retorna si m és una de les sis magies
	bool magia_correcte = false;
	int i = 0;
	while (!magia_correcte and i < Carta::MAX_MAGIA) {
		if (m == Carta::MAGIA[i]) magia_correcte = true;
		i++;
	}
	return magia_correcte;
}
