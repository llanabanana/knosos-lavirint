#include "Polje.h"
#include <iostream>
using std::cout;

/*
Modul sadrži funkcije za rad sa poljima lavirinta.
Autor: Lana Mirkov
Poslednja izmena: 22.2.2025.
*/

Polje::Polje() {
	x = 0;
	y = 0;
	tip = ' ';
}

Polje::Polje(int x, int y, char tip) {
	this->x = x;
	this->y = y;
	this->tip = tip;
}

Polje::~Polje() {
}

int Polje::getX() {
	return x;
}

int Polje::getY() {
	return y;
}

char Polje::getTip() {
	return tip;
}

void Polje::setX(int x) {
	this->x = x;
}

void Polje::setY(int y) {
	this->y = y;
}

void Polje::setTip(char tip) {
	if (tip == ' ' || tip == '#' || tip == 'P' || tip == 'R' || tip == 'M' || tip == 'U' || tip == 'I') {
		this->tip = tip;
	}
	else {
		//  Ako je tip polja nevažeći, baciti izuzetak
		throw std::invalid_argument("Nedozvoljen tip polja");
	}
}

void Polje::prikaziPolje() {
	cout << tip;
}

Polje& Polje::operator=(const Polje& p) {
	/*
	Preklopljeni operator dodele koji izjednacava polje sa drugim poljem.
	Parametri: 		p - polje koje se dodeljuje (referenca na objekat tipa Polje)
	Vraća: 		*this - referenca na izmenjeni objekat
	*/
	x = p.x;
	y = p.y;
	tip = p.tip;

	return *this;
}

Polje& Polje::operator=(char noviTip) {
	/*
	Preklopljeni operator dodele koji izjednacava tip polja sa novim tipom.
	Parametri: 		noviTip -  tip polja koji se dodeljuje(char)
	Vraća: 		*this - referenca na izmenjeni objekat
	*/
	if (noviTip == ' ' || noviTip == '#' || noviTip == 'P' || noviTip == 'R' || noviTip == 'M' || noviTip == 'U' || noviTip == 'I') {
		tip = noviTip;
	}
	else {
		throw std::invalid_argument("Nedozvoljen tip polja");
	}
	return *this;
}

