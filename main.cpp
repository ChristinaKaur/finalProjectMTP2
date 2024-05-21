/********************
 *     MTP2-S11     *
 *        -         *
 *  Christina Kaur  *
 *     Krishan      *
 *        -         *
 *     u1980983     *
 ********************/


/* Entrada: Abans de comenençar la partida, es requirirà entrar per teclat la llavor per barrejar les 
cartes, el nombre de jugadors i els seus noms. A continuació, se li presentarà un menú amb diverses 
opcions per seleccionar:
  Ocions:
  - I: per jugar cedint influencia a un altre jugador
  - J: per jugar sense cedir influencia a un altre jugador
  - P: per veure les dos piles de cartes
  - F: per abandornar la partida

* Sortida: La partida consistirà en rondes de jugades de cada jugador fins que un dells abandoni el 
joc o les dos piles de cartes es quedin buides.*/

#include <iostream>
#include "Joc.h"

using namespace std;

const char FI = 'F', PILA_E = 'e', PILA_D = 'd';
const int MIN_J = 2, MAX_J = 4, MIN_T = 0, MAX_T = 3;

void mostrar_menu() {
    // Pre: --;
    // Post: mostra per pantalla el menu
    cout << endl << "OPCIONS:" << endl;
    cout << "(I) FER JUGADA CEDINT INFLUENCIA" << endl;
    cout << "(J) FER JUGADA SENSE CEDIR INFLUENCIA" << endl;
    cout << "(P) MOSTRAR PILES" << endl;
    cout << "(F) ABANDONAR PARTIDA" << endl;
}

int entrada_jugadors(Joc& joc) {
    // Pre: --;
    // Post: afegeix els jugadors entrats per teclat al joc i retorna el numero de jugadors
    int n = 0;
    while (n > MAX_J or n < MIN_J) {
        cout << "ENTRA EL NUMERO DE JUGADORS (" << MIN_J << "-" << MAX_J << "):" << endl;
        cin >> n;
        if ((n > MAX_J or n < MIN_J))
            cout << "NUMERO DE JUGADORS INCORRECTE" << endl;
    }

    cin.ignore();
    for (int i = 0; i < n; i++) {
        string nom;
        cout << "ENTRA EL NOM DEL JUGADOR " << i+1 << ":" << endl;
        getline(cin, nom);
        joc.afegir_jugador(Jugador(nom));
    }
    return n;
}

void entrar_opcio(char& opcio) {
    // Pre: --;
    // Post: opcio entrada per teclat
    cout << endl << "ENTRA UNA OPCIO:" << endl;
    cin >> opcio;
}

unsigned entrar_llavor() {
    // Pre: --;
    // Post: retorna llavor entrada per teclat
    unsigned llavor;

    cout << "ENTRA LA LLAVOR:" << endl;
    cin >> llavor;

    return llavor;
}

int demana_pos_carta() {
    // Pre: --;
    // Post: retorna enter entrat per teclat
    int pos_carta;
    cout << "ENTRA LA POSICIO DE LA CARTA QUE VOLS COL.LOCAR:" << endl;
    cin >> pos_carta;
    if (pos_carta > MAX_T or pos_carta < MIN_T) {
        cout << "POSICIO NO VALIDA" << endl;
        return demana_pos_carta();
    }
    return pos_carta;
}

void demana_pos_tauler(int& i, int& j) {
    // Pre: --;
    // Post: entra dos enters per teclat
    cout << "ENTRA LA POSICIO DEL TAULER ON VOLS COL.LOCAR LA CARTA:" << endl;
    cin >> i >> j;
    if ((i < MIN_T or i > MAX_T) or (j < MIN_T or j > MAX_T)) {
        cout << "POSICIO NO VALIDA" << endl;
        demana_pos_tauler(i, j);
    }
}

char demana_pila() {
    // Pre: --;
    // Post: retorna caracter entrat per teclat
    char pila;
    cout << "DE QUINA PILA VOLS ROBAR LA CARTA? (" << PILA_E << "/" << PILA_D << ")" << endl;
    cin >> pila;
    if (pila != PILA_E and pila != PILA_D) {
        cout << "AQUESTA PILA NO EXISTEIX" << endl;
        return demana_pila();
    }
    return pila;
}

void demana_jugada(Joc joc, int& pos_carta, int& pos_tauler_i, int& pos_tauler_j, char& pila, int jugador) {
    // Pre: --;
    // Post: entra per teclat la jugada que es vol fer
    pos_carta = demana_pos_carta();
    demana_pos_tauler(pos_tauler_i, pos_tauler_j);
    if (!joc.jugada_permesa(pos_carta, pos_tauler_i, pos_tauler_j, pila, jugador)) {
        cout << "JUGADA NO PERMESA" << endl;
        cout << "TORNA A INDICAR LA JUGADA" << endl;
        demana_jugada(joc, pos_carta, pos_tauler_i, pos_tauler_j, pila, jugador);
    }
    else if (!joc.partida_finalitzada()) {
        char p = joc.una_pila_buida();
        if (p == 'n')
            pila = demana_pila();
        else 
            pila = p;
    }
}

char demana_jugada_amb_influencia(Joc joc, char& magia, int& jug, int& jug_actual, int num_jugadors) {
    // Pre: --;
    // Post: entra per teclat la jugada que es vol fer
    cout << "ENTRA LA MAGIA QUE VOLS CEDIR:" << endl;
    cin >> magia;
    cout << "ENTRA EL JUGADOR A QUI LA VOLS CEDIR:" << endl;
    cin >> jug;
    jug--;

    char cedir_influ = 's';
    if (!joc.influencia_permesa(magia, jug, jug_actual)) {
        cout << "MOVIMENT NO VALID" << endl;
        cout << "ENCARA T'INTERESSA CEDIR INFLUENCIA? (s/n)" << endl;
        cin >> cedir_influ;
        if (cedir_influ == 's') {
            return demana_jugada_amb_influencia(joc, magia, jug, jug_actual, num_jugadors);
        }
    }
    return cedir_influ;
}

void jugada(Joc& joc, int jugador, bool influencia, const int num_jugadors) {
    // Pre: --;
    // Post: el jugador ha fet jugada sense cedir influencia 
    int pos_carta, pos_tauler_i, pos_tauler_j;
    char pila;
    if (influencia) {
        char magia;
        int jugador_a_cedir;
        char cedir_influ = demana_jugada_amb_influencia(joc, magia, jugador_a_cedir, jugador, num_jugadors);
        if (cedir_influ == 's')
            joc.enviar_seguidors_de(magia, jugador, jugador_a_cedir);
    }
    demana_jugada(joc, pos_carta, pos_tauler_i, pos_tauler_j, pila, jugador);

    joc.fer_jugada(pos_carta, pos_tauler_i, pos_tauler_j, pila, jugador);
}

void torn_de(int& i, Joc& joc, const int num_jugadors, char& opcio) {
    // Pre: joc i num jugadors correcte
    // Post: torn del jugador 
    entrar_opcio(opcio);
    if (opcio == 'I') {
        jugada(joc, i, true, num_jugadors);
        i++;
    }
    else if (opcio == 'J') {
        jugada(joc, i, false, num_jugadors);
        i++;
    }
    else if (opcio == 'P') {
        joc.mostrar_piles();
    }
    else if (opcio == 'F') {
        cout << "PARTIDA ABANDONADA" << endl;
    }
    else {
        cout << "OPCIO NO DEFINIDA" << endl;
    }
}

char partida(Joc& joc, const int num_jugadors) {
    // Pre: --;
    // Post: per cada jugador hi ha un torn per escollir una opció del menu fins que s'entri l'opcio FI, retorna l'ultima opcio entrada
    char opcio = 'I';
    int jug = 0, jug_final = 0;
    while (!joc.partida_finalitzada() and opcio != FI) {
        jug = 0;
        while (jug < num_jugadors and opcio != FI) {
            joc.mostrar_joc(jug);
            mostrar_menu();
            torn_de(jug, joc, num_jugadors, opcio);
            if (joc.partida_finalitzada()) jug_final = jug;
        }
    }
    jug = 0;
    while (jug < jug_final - jug + 1 and opcio != FI) {
        joc.mostrar_joc(jug);
        mostrar_menu();  
        torn_de(jug, joc, num_jugadors, opcio);
    }
    return opcio;
}

int main() {
    Joc joc(entrar_llavor());
    
    int num_jugadors = entrada_jugadors(joc);
    joc.preparar();

    int opcio = partida(joc, num_jugadors);
    if (opcio != FI) {
        joc.calcula_punts_decepcio();
        joc.mostrar_resultat();
    }
}