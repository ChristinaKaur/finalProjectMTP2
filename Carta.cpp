#include <iostream>
#include <string>
#include "Carta.h"

using namespace std;

const char Carta::MAGIA[MAX_MAGIA] = {'b', 'o', 'p', 'r', 't', 'v'};
const char Carta::GERMANDAT[MAX_GERMANDAT] = {'c', 'g', 's'};

// CONSTRUCTORS I DESTRUCTOR 
Carta::Carta() {
	// Pre: --; Post: Carta buida
	a_magia = 'M';
	a_influencia = 0;
	a_germandat = 'G';
}

Carta::Carta(char magia, int influencia, char germandat){
	// Pre: --; Post: carta amb dades correctes
	a_magia = magia;
	a_influencia = influencia;
	a_germandat = germandat;
}

// CONSULTORS 
void Carta::mostrar(const bool revers) const
{
	// Pre: carta no buida; 
	// Post: mostra per pantalla tot el contingut de la carta actual en format [mIg] si revers és fals, en cas contrari només la [m]  
	if (!revers) {
		if (buida()) cout << "[   ]";
		else {
			cout << "[" << a_magia;
			if (buida()) cout << " ";
			else cout << a_influencia;
			cout << a_germandat << "]";
		}
	}
	else {
		if (buida()) cout << "[ ]";
		else cout << "[" << a_magia << "]";
	}
}

bool Carta::comparar(const Carta& c) const {
	// Pre: carta i c no buides; 
	// Post: retorna cert si s'ha convençut un seguidor
	return (a_magia == c.a_magia or a_germandat == c.a_germandat) and !((*this) == c);
}

bool Carta::buida() const {
	// Pre: --;
	// Post: retorna cert si la carta està buida, fals en cas contrari
	Carta nova;
	return nova == (*this);
}

char Carta::magia() const {
	// Pre: -- 
	// Post: retorna magia de la carta actual
	return a_magia;
}

char Carta::germandat() const {
	// Pre: -- 
	// Post: retorna germandat de la carta actual
	return a_germandat;
}

int Carta::influencia() const {
	// Pre: -- 
	// Post: retorna influencia de la carta actual
	return a_influencia;
}

bool Carta::operator ==(const Carta& c) const {
	// Pre: -- ; Post: cert si c és igual a la carta actual, fals altrament
	return a_magia == c.a_magia and a_influencia == c.a_influencia and a_germandat == c.a_germandat;
}

bool Carta::operator >(const Carta& c) const {
	// Pre: -- ; Post: cert si c és inferior a la carta actual, fals altrament
	return (a_magia > c.a_magia) or (a_magia == c.a_magia and a_influencia > c.a_influencia) or (a_magia == c.a_magia and a_influencia == c.a_influencia and a_germandat > c.a_germandat);
}

bool Carta::operator >=(const Carta& c) const {
	// Pre: -- ; Post: cert si c és inferior o igual a la carta actual, fals altrament
	return ((*this) == c or (*this) > c);
}

ostream& operator<<(ostream& o, const Carta& c) {
	// Pre: es pot escriure a o; 
	// Post: s’ha escrit la informació de c a o
	c.mostrar(false);
	return o;
}