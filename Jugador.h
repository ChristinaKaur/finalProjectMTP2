#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Jugador.h"
#include "Carta.h"
#include "Seguidors.h"

using namespace std;

class Jugador { // Descripcio: Representa un jugador del joc i conté les seves cartes de bruixots, com la zona d'influència.
public:
    // CONSTRUCTORS 
    Jugador();
    // Pre: --; Post: jugador buid
    
    Jugador(string nom);
    // Pre: --; Post: jugador amb dades correctes

    // CONSULTORS 
    Carta obt_carta(int pos) const;
    // Pre: --;
    // Post: retorna carta de la posicio pos
    void mostrar_ma(bool resum) const;
    // Pre: jugador no buid; 
    // Post: mostra per pantalla tot el contingut de la ma del jugador actual si resum es fals, en cas contrari nomes mostra magia

    void mostrar_seguidors(bool resum) const;
    // Pre: jugador no buid; 
    // Post: mostra per pantalla tots els seguidors del jugador actual si resum es fals, en cas contrari nomes mostra magia

    string nom() const;
    // Pre: --; 
    // Post: retorna nom del jugador

    bool existeix(int pos) const;
    // Pre: --;
    // Post: retorna cert si la carta en la posicio pos existeix

    Seguidors obt_seguidors() const;
    // Pre: --;
    // Post: retorna seguidors del jugador actual
    
    int punts_decepcio() const;
    // Pre: --; 
    // Post: retorna punts decepcio del jugador
        
    // MODIFICADORS 
    void suma_punts_decepcio(int d);
    // Pre: --;
    // Post: suma d punts als punts de decepcio del jugador actual

    void afegir_carta(const Carta& c);
    // Pre:--;
    // Post: c s'ha afegit al jugador

    void afegir_carta_en_pos(const Carta& c, int pos);
    // Pre:--;
    // Post: c s'ha afegit al jugador en la posicio pos;

    void afegir_seguidor(const Carta& c);
    // Pre:--;
    // Post: c s'ha afegit als seguidors del jugador

    void afegir_seguidors_a(Jugador& j, char magia);
    // Pre:--;
    // Post: s'han afegit un conjunt de seguidors d'una màgia que no tingui el jugador

    void eliminar_carta(const Carta& c);
    // Pre:--;
    // Post: c s'ha eliminat del jugador

    void eliminar_seguidors(const char& m);
    // Pre:--;
    // Post: s'han eliminat tots els seguidors d'una màgia

    void passar_cartes_a_seguidors();
    // Pre:--;
    // Post: cartes de la mà passades al conjunt de seguidors

    friend ostream& operator<<(ostream& o, const Jugador& j);
    // Pre: es pot escriure a o; 
    // Post: s’ha escrit la informació de j a o
    
    static const int MAX_CARTES = 4;

private:
    string a_nom;
    Seguidors a_seguidors;
    Carta a_cartes[MAX_CARTES];
    int n_c;
    int a_punts;
};
#endif // JUGADOR_H