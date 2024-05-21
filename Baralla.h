#ifndef BARALLA_H
#define BARALLA_H

#include <string>
#include <cstdlib>
#include "Baralla.h"
#include "Carta.h"

using namespace std;

class Baralla { // Descripcio: Taula dinàmica ampliable (una baralla)
public:
    // CONSTRUCTORS I DESTRUCTOR 
    Baralla();
    // Pre: --; Post: baralla buida
    
    Baralla(const int llavor);
    // Pre: --; Post: aquesta baralla te de a_llavor llavor
    
    Baralla(const Baralla& o);
    // Pre: --; Post: aquesta baralla es copia de la Baralla o
    
    ~Baralla();
    // Pre: --; Post: memoria alliberada

    // CONSULTORS 
    void mostrar(const string titol) const;
    // Pre: baralla no buida; 
    // Post: mostra per pantalla tot el contingut de la baralla actual    

    int aleatori(int rang);
    //Pre:--; Post: ens retorna un valor aleatori de la baralla 

    int mida() const;
    // Pre:--
    // Post: retorna numero de cartes que conté la baralla actual

    bool buida() const;
    // Pre:--
    // Post: retorna cert si la baralla actual és buida, fals en cas constrari

    // MODIFICADORS 
    void afegir(const Carta& c);
    // Pre:--;
    // Post: c s'ha afegit a la taula; 

    Carta robar();
    // Pre: baralla no buida;
    // Post: retorna copia de l'últim enter de la baralla

    void retirar_cartes(const int n);
    // Pre: baralla no buida;
    // Post: baralla amb n cartes retirades

    void barrejar();
    // Pre:--
    // Post: barreja de forma aleatoria la baralla actual
    
    void intercanvi(Carta& a, Carta& b);
    // Pre: a = A i b = B
    // Post: a = B i b = A

    void omplir_baralla();
    // Pre: --
    // Post: s'omple la baralla amb totes les cartes (90)

    // OPERADORS REDEFINITS 
    Baralla& operator=(const Baralla& o);
    // Pre: -- ; Post: o afegit a la taula

    friend ostream& operator<<(ostream& o, const Baralla& c);
    // Pre: es pot escriure a o; 
    // Post: s’ha escrit la informació de b a o

private:
    const int MAX = 5;

    int a_n; // nombre de caselles ocupades
    int a_max; // nombre de posicions reservades (capacitat)
    Carta *a_carta;

    unsigned a_xn;

    void allibera();
    //Pre: --; Post: memòria alliberada

    void copia(const Baralla& b);
    //Pre: memòria alliberada; Post: aquesta baralla és còpia de la baralla b

    void reserva();
    //Pre: --; Post: memòria reservada per a_max enter

    void expandeix();
    //Pre: --; Post: la memòria reservada es dobla

    int generador_aleatori(int rang);
    //Pre: --; Post: es genera una baralla aleatoriament 
};
#endif // BARALLA_H