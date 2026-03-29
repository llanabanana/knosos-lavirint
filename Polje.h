#pragma once

#include <iostream>
#include <string>
#include <vector>

/*
Klasa koja predstavlja jedno polje u lavirintu(matrici).
Autor: Lana Mirkov
Poslednja izmena: 20.2.2025.
*/

class Polje {
private:
	int x;
	int y;
	char tip;  // ' ' - prazno polje, '#' - zid, 'P' - predmet, 'R' - robot, 'M' - minotaur, 'U' - ulaz, 'I' - izlaz
public:
	Polje();
	Polje(int x, int y, char tip);
	~Polje();

	int getX();
	int getY();
	char getTip();

	void setX(int x);
	void setY(int y);
	void setTip(char tip);

	void prikaziPolje();

	Polje& operator=(const Polje& p);
	Polje& operator=(char noviTip);

};