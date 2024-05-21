#ifndef TAULER_H
#define TAULER_H

#include <string>
#include <iomanip>
#include "Tauler.h"
#include "Carta.h"

using namespace std;

class Tauler { // Descripcio: Representa el tauler de joc i les seves funcions relacionades amb l'ocupació dels espais del tauler, comprovació de punts d'influència, etc.
public:
    // CONSTRUCTOR
    Tauler();
    // Pre: --; Post: tauler buid

    // CONSULTORS 
    void mostrar(Carta cim_esq, Carta cim_dreta) const;
    // Pre: tauler no buid; 
    // Post: mostra per pantalla tot el contingut del tauler actual  

    Carta obtElem(int i, int j) const;
    // Pre: --; Post: retorna carta indicada

    bool pos_valida(int i, int j) const;
    // Pre: --;
    // Post: retorna true si la pos [i][j] partany al tauler

    int espais_buits() const;
    // Pre: --; Post: retorna el numero d'espais buits en el tauler

    int suma_influencies(char a, const int i, const int j) const;
    // Pre: i i j valids; 
    // Post: retorna la suma de les influencies dels bruixots en la fila o columna   

    // MODIFICADORS 
    void posarElem(int i, int j, const Carta& c);
    // Pre: --; Post: insereix carta c al lloc indicat

    void treureElem(int i, int j);
    // Pre: tauler no buit; 
    // Post: elimina l'ultima carta 

    Tauler &operator =(const Tauler& t);
    // Pre: --; Post: s’ha assignat sense aliasing la informació de t a l’objecte actual

private:
    // ATRIBUTS
    int a_n;
    int a_m;
    Carta** a_mp;

    const int MIDA_TAULER = 4;

    void allibera();
    // Pre: --; Post: memòria alliberada

    void copia(const Tauler& t);
    // Pre: --; Post: fa un duplicat de la matriu

    void reserva();
    // Pre: a_n>0 ^ a_m>0; Post: memòria reservada
};
#endif // TAULER_H