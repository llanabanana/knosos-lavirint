#pragma once
#include "Polje.h"
#include <iostream>

/*
Klasa koja predstavlja minotaura u lavirintu.
Autor: Lana Mirkov
Poslednja izmena: 25.2.2025.
*/

class Minotaur {
private:
	std::pair<int, int> koordinate;
	bool unisten = false;  // ukoliko je minotaur unisten macem
public:
	Minotaur();
	Minotaur(int x, int y);
	~Minotaur();

	void setKoordinate(int x, int y);
	std::pair<int, int> getKoordinate() const;

	bool isUnisten() const;
	void setUnisten(bool status);

	// Proverava da li je robot pored minotaura i vraca koordinate robota ako jeste
	std::pair <bool, std::pair<int, int>> robotJePored(std::pair<int, int> robotKoord, std::pair<int, int> minotaur);


};