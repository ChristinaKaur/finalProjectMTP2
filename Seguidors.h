#ifndef SEGUIDORS_H
#define SEGUIDORS_H

#include <string>
#include "Seguidors.h"
#include "Carta.h"

using namespace std;

class Seguidors { // Descripcio: Llista dinàmica ordenada de cartes que conté els seguidors que ha obtingut el jugador durant la partida
public:
    // CONSTRUCTORS I DESTRUCTOR 
    Seguidors();
    // Pre: --; Post: llista de seguidors buida

    Seguidors(const Seguidors& o);
    // Pre: --; Post: aquesta llista de seguidors es copia de Seguidors o

    ~Seguidors();
    // Pre: --; Post: memoria alliberada

    Seguidors &operator=(const Seguidors& o);
    // Pre:--; Post: aquesta llista es copia de o i abans s'ha alliberat la memoria ocupada per aquesta llista

    // CONSULTORS 
    int suma_influencia(char magia) const;
    // Pre:--;
    // Post: retorna el numero dinfluencia que te magia

    void mostrar(bool resum) const;
    // Pre:--; Post: mostra la llista de seguidors si resum és fals, en cas contrari mostra un resum dels seguidors

    bool buida() const;
    // Pre: --
    // Post: retorna cert si la llista de seguidors actual és buida, fals en cas constrari

    bool existeix(Carta c) const;
    // Pre: -- 
    // Post: ens diu si c existeix a la llista

    // MODIFICADORS 
    void inserir_conjunt(Seguidors& s, char m);
    // Pre: magia correcte i s omplert correctament
    // Post: afegeix el conjunt de seguidors de s de magia m a seguidors actuals

    void inserir(Carta c);
    // Pre: --;
    // Post: si c no existeix s'ha inserit en el lloc que li toca per mantenir l'ordre; en cas contrari no es fa cap insercio
    
    void eliminar(Carta c);
    // Pre: --
    // Post: si c existeix s'ha eliminat

    void eliminar_seguidors(const char m);
    // Pre:--;
    // Post: s'han esborrat els seguidors d'una magia m

private:
    struct Node {
        Carta dada;
        Node* seg;
    };
    Node* a_inici;

    void copia(const Seguidors& o);
    // Pre: memoria dinamica alliberada; 
    // Post: aquesta llista es copia de o
    
    void allibera();
    // Pre: --; Post: memoria dinamica alliberada
}; 
#endif // SEGUIDORS_H