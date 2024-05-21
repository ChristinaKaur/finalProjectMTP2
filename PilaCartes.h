#ifndef PILACARTES_H
#define PILACARTES_H

#include <string>
#include "PilaCartes.h"
#include "Carta.h"

using namespace std;

class PilaCartes { // Descripcio: una carta
public:
    // CONSTRUCTORS I DESTRUCTOR 
    PilaCartes();
    // Pre: --; Post: pila buida
    // COST: O(1)

    PilaCartes(const PilaCartes& o);
    // Pre: --; Post: aquesta pila es copia de la PilaCartes o
    // COST: O(n)

    ~PilaCartes();
    // Pre: --; Post: memoria alliberada
    // COST: O(n)

    PilaCartes& operator=(const PilaCartes& o);
    // Pre: -- ; Post: pila actual = pila o

    // CONSULTORS 
    bool buida() const;
    // Pre: -- ; Post: retorna cert si la pila es buida; fals en cas contrari
    // COST: O(1)

    Carta cim();
    // Pre: pila no buida; Post: retorna copia del primer de la pila
    // COST: O(1)
    
    int mida() const;
    // Pre: -- ; 
    // Post: retorna mida de la pila 

    void mostrar() const;
    // Pre: pila no buida; 
    // Post: mostra per pantalla tot el contingut de la Pila de Cartes actual 

    // MODIFICADORS
    void empilar(Carta c);
    // Pre: --; Post: ha afegit c al final de la pila
    // COST: O(1)

    void desempila();
    // Pre: pila no buida; Post: ha eliminat el primer de la pila
    // COST: O(1)

private:
    struct Node {
        Carta c;
        Node* seg;
    };

    // ATRIBUTS
    Node* a_cim; // punter al primer de la pila
    int a_mida;

    void copia(const PilaCartes& o);
    // Pre: pila buida; Post: aquesta pila es copia de o
    void allibera();
    // Pre: --; Post: pila buida
};
#endif // PILACARTES_H
