#ifndef CARTA_H
#define CARTA_H

#include <string>
#include "Carta.h"

using namespace std;

class Carta { // Descripcio: Representa un bruixot amb les seves propietats, com ara germandat, màgia i influència.
public:
    // CONSTRUCTORS I DESTRUCTOR 
    Carta();
    // Pre: --; Post: Carta buida

    Carta(char magia, int influencia, char germandat);
    // Pre: --; Post: carta amb dades correctes

    // CONSULTORS 
    void mostrar(const bool revers) const;
    // Pre: carta no buida; 
    // Post: mostra per pantalla tot el contingut de la carta actual en format [mIg] si revers és fals, en cas contrari només la [m]  

    bool comparar(const Carta& c) const;
    // Pre: carta i c no buides; 
    // Post: retorna cert si s'ha convençut un seguidor

    bool buida() const;
    // Pre: --;
    // Post: retorna cert si la carta està buida, fals en cas contrari

    char magia() const;
    // Pre: -- 
    // Post: retorna magia de la carta actual

    char germandat() const;
    // Pre: -- 
    // Post: retorna germandat de la carta actual

    int influencia() const;
    // Pre: -- 
    // Post: retorna influencia de la carta actual

    // MODIFICADORS 
    bool operator ==(const Carta& c) const;
    // Pre: -- ; Post: cert si c és igual a la carta actual, fals altrament
    
    bool operator >(const Carta& c) const;
    // Pre: -- ; Post: cert si c és inferior a la carta actual, fals altrament

    bool operator >=(const Carta& c) const;
    // Pre: -- ; Post: cert si c és inferior o igual a la carta actual, fals altrament

    friend ostream& operator<<(ostream& o, const Carta& c);
    // Pre: es pot escriure a o; 
    // Post: s’ha escrit la informació de c a o

    static const int MAX_MAGIA = 6;
    static const char MAGIA[MAX_MAGIA];

    static const int MAX_GERMANDAT = 3;
    static const char GERMANDAT[MAX_GERMANDAT];

private:
    char a_magia;
    char a_germandat;
    int a_influencia;
};
#endif // CARTA_H