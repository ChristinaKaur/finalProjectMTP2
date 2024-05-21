#ifndef JOC_H
#define JOC_H

#include <string>
#include "Joc.h"
#include "Jugador.h"
#include "Tauler.h"
#include "Baralla.h"
#include "PilaCartes.h"
#include "Carta.h"

using namespace std;

class Joc { // Descripcio: Representa un joc, gestiona el fluxe del joc, els torns dels jugadors i els càlculs de puntuació.
public:
    // CONSTRUCTORS I DESTRUCTOR 
    Joc();
    // Pre: --; Post: joc buid

    Joc(const int llavor);
    // Pre: --; Post: joc amb dades correctes

    // CONSULTORS 
    void mostrar_piles() const;
    // Pre: piles no buides; 
    // Post: mostra per pantalla el contingut de les dos piles del joc actual  

    void mostrar_seguidors() const;
    // Pre: --;
    // Post: mostrar per pantalla els seguidors de cada jugador 

    void mostrar_punts_decepcio() const;
    // Pre: --;
    // Post: mostrar per pantalla els punts de decepcio de cada jugador 

    bool partida_finalitzada() const;
    // Pre: --;
    // Post: retorna si s'ha de finalitzar la partida

    void mostrar_resultat() const;
    // Pre: --; 
    // Post: mostrar per pantalla el resultat de la partida (tots els seguidors, resum dels seguidors i  punts de decepcio)

    void mostrar_mans_oponents(const int i) const;
    // Pre: --;
    // Post: mostrar mans dels jugadors

    void mostrar_resum_seguidors(const int i) const;
    // Pre: --;
    // Post: mostrar resum dels seguidors

    void mostrar_joc(const int i);
    // Pre: --;
    // Post: mostrar informació del jugador a_jugador[i]

    bool influencia_permesa(char magia, int jug, int jug_actual);
    // Pre: --;
    // Post: retorna cert si es pot cerdir influencia al jugador jug

    bool jugada_permesa(int pos_carta, int pos_tauler_i, int pos_tauler_j, char pila, int jug);
    // Pre: --;
    // Post: retorna cert si la jugada passada per parametres és valida
   
    char una_pila_buida() const;
    // Pre: --;
    // Post: returna la pila que no esta buida si només una de les dos piles esta buida, en cas contrari retorna 'n'

    // MODIFICADORS
    void calcula_punts_decepcio();
    // Pre: --;
    // Post: calcula els punts de decepcio de cada jugador

    void enviar_seguidors_de(char magia, int jugador_jugant, int altre_jugador);
    // Pre: jugada permesa
    // Post: enviar tots els seguidors del jugador_jugant de la magia indicada a l'altre_jugador

    void fer_jugada(int pos_carta, int pos_tauler_i, int pos_tauler_j, char pila, int jug);
    // Pre: tots els valors son correctes i la jugada està permesa
    // Post: fer jugada amb influencia si influencia és cert, en cas contrari fer jugada sense influencia

    void omplir_tauler_pila(PilaCartes& p, int& n);
    // Pre: p i n forats a omplir correctes
    // Post: omplir tauler amb cartes de la pila p fins n o fins que s'acabin les cartes de la pila p, retorna el numero de cartes posades

    bool omplir_resta_tauler(char pila, int& n);
    // Pre: pila i n forats a omplir correctes
    // Post: omplir n forats del tauler amb cartes de la pila indicada (si s'acaba, de l'laltre), retorna cert si no hi ha mes cartes a les piles

    void robar_carta(PilaCartes& pila, int jug, int pos_carta);
    // Pre: pila correcte
    // Post: es roba una carta de la pila indicada per jugador jug

    void comprovar_tauler(Carta carta, int pos_tauler_i, int pos_tauler_j, int jug);
    // Pre: tots els valors son correctes i la jugada està permesa
    // Post: comprovar si s'ha convençut a algun bruixot i posar-los en els seguidors del jugador jug
    
    void afegir_jugador(const Jugador& j);
    // Pre: --
    // Post: jugador afegit a joc

    void retirar_cartes();
    // Pre: baralla omplerta correctament
    // Post: retira n cartes de la baralla

    void repartir_cartes();
    // Pre: baralla omplerta correctament
    // Post: repartir 4 cartes a cada jugador

    void ompliar_tauler();
    // Pre: baralla omplerta correctament
    // Post: omplir el tauler amb 12 cartes i retorna 

    void omplir_piles();
    // Pre: baralla omplerta correctament 
    // Post omplir piles amb cartes de la baralla

    void preparar();
    // Pre: --
    // Post: cartes del joc actual barrejades, retirades i repartides

    static const int MAX_JUGADORS = 4;

private:
    int n_j;
    Jugador a_jugador[MAX_JUGADORS];
    Tauler a_tauler;
    Baralla a_baralla;
    PilaCartes a_pila_dreta;
    PilaCartes a_pila_esq;

    void obtenir_seguidors(string a, int i, int j, int jug);
    // Pre: a, i, j i jug valors vàlids 
    // Post: tots els bruixots convencuts del tauler es truen i s'envien com a seguidors del jugador jug

    void resoldre_crisi_magica(int jug, int pos_i, int pos_j);
    // Pre: jugador jug, i i j correcte
    // Post: tots els bruixots de germandat diferent a jug passen a ser seguidors de jug

    bool magia_valida(char m) const;
    // Pre: --;
    // Post: retorna si m és una de les sis magies
};
#endif // JOC_H