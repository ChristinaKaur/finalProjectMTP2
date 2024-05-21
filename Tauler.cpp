#include <iostream>
#include <string>
#include "Tauler.h"

using namespace std;

// CONSTRUCTORS I DESTRUCTOR 
Tauler::Tauler() {
    // Pre: --; Post: tauler buid
    a_n = 4; 
    a_m = 4; 
    a_mp = NULL;
    reserva();
}

// CONSULTORS 
void Tauler::mostrar(Carta cim_esq, Carta cim_dreta) const {
    // Pre: tauler no buid; 
    // Post: mostra per pantalla tot el contingut del tauler actual  
    cout << string(5, ' ');
    for (int i = 0; i < MIDA_TAULER; i++) {
        cout << setfill(' ') << setw(6) << i;
    }
    cout << endl;

    for (int i = 0; i < MIDA_TAULER; i++) {
        if (i == 1) cim_esq.mostrar(true);
        else cout << "   ";

        cout << setfill(' ') << setw(3) << i << " ";
        for (int j = 0; j < MIDA_TAULER; j++) {
            cout << " ";
            a_mp[i][j].mostrar(false);
        }

        if (i == 1) {
            cout << "  ";
            cim_dreta.mostrar(true);
        }

        cout << endl;
    }
}

Carta Tauler::obtElem(int i, int j) const {
    // Pre: --; Post: retorna carta indicada
    return a_mp[i][j];
}

int Tauler::espais_buits() const {
    // Pre: --; Post: retorna el numero d'espais buits en el tauler
    int suma = 0;
    for (int i = 0; i < MIDA_TAULER; i++) {
        for (int j = 0; j < MIDA_TAULER; j++) {
            if (a_mp[i][j].buida())
                suma++;
        }
    }
    return suma;
}

bool Tauler::pos_valida(int i, int j) const {
    // Pre: --;
    // Post: retorna true si la pos [i][j] partany al tauler
    return (i >= 0 or i < MIDA_TAULER) and (j >= 0 or j < MIDA_TAULER);
}

int Tauler::suma_influencies(char a, const int i, const int j) const {
    // Pre: i i j valids; 
    // Post: retorna la suma de les influencies dels bruixots en la fila o columna depenent del valor de a   
    int suma = 0, pos;
    if (a == 'f') {
        pos = j;
        while (pos >= 0 and !a_mp[i][pos].buida()) {
            suma += a_mp[i][pos].influencia();
            pos--;
        }
        pos = j;
        while (pos < MIDA_TAULER and !a_mp[i][pos].buida()) {
            suma += a_mp[i][pos].influencia();
            pos++;
        }
    }
    else {
        pos = i;
        while (pos >= 0 and !a_mp[pos][j].buida()) {
            suma += a_mp[pos][j].influencia();
            pos--;
        }
        pos = i;
        while (pos < MIDA_TAULER and !a_mp[pos][j].buida()) {
            suma += a_mp[pos][j].influencia();
            pos++;
        }
    }
    suma -= a_mp[i][j].influencia();
    return suma;
}

// MODIFICADORS 
void Tauler::posarElem(int i, int j, const Carta& c) {
    // Pre: --; Post: insereix carta c al lloc indicat
    a_mp[i][j] = c;
}

void Tauler::treureElem(int i, int j) {
    // Pre: --; Post: elimina carta 
    a_mp[i][j] = Carta();
}

Tauler& Tauler::operator =(const Tauler& t) {
    // Pre: --; Post: s’ha assignat sense aliasing la informació de t a l’objecte actual
    if (this != &t) {
        allibera();
        copia(t);
    }
    return *this;
}

void Tauler::allibera() {
    // Pre: --; Post: memòria alliberada
    for (int i = 0; i < a_n; i++) // alliberament de cadascuna de les files
        delete[] a_mp[i];
    delete[] a_mp; // alliberament del vector de punters
}

void Tauler::copia(const Tauler& t) {
    // Pre: --; Post: fa un duplicat de la matriu
    a_n = t.a_n; a_m = t.a_m;
    reserva();
    for (int i = 0; i < a_n; i++)
        for (int j = 0; j < a_m; j++)
            a_mp[i][j] = t.a_mp[i][j]; // còpia de les caselles de la matriu
}

void Tauler::reserva() {
    // Pre: a_n>0 ^ a_m>0; Post: memòria reservada
    a_mp = new Carta * [a_n]; // creació d’un vector de punters
    for (int i = 0; i < a_n; i++) // creacó de cada fila
        a_mp[i] = new Carta[a_m];
}