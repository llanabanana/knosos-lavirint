#include "MagicniPredmet.h"
#include <iostream>
#include <string>
#include <vector>

/*
Modul imlementira funkije koje rade sa magicnim predmetima u igri.
Autor: Lana Mirkov
Poslednja izmena: 5.5.2025.
*/

MagicniPredmet::MagicniPredmet(const std::string& name) : naziv(name) {}

MagicniPredmet::MagicniPredmet() : naziv(getRandomPredmet()) {}

MagicniPredmet::~MagicniPredmet() {}

std::string MagicniPredmet::getRandomPredmet() {
	std::vector<std::string> predmeti = { "Magla", "Mac", "Stit", "Cekic" };
	return predmeti[rand() % predmeti.size()];
}

Magla::Magla() : MagicniPredmet("Magla") {}
//Magla smanjuje vidljivost robota na matircu 3x3
void Magla::primeniEfekat(Robot& robot) {
	robot.dodajEfekat("Magla");
	std::cout << "Magla je aktivirana tokom naredna 3 poteza!" << std::endl;
}

Mac::Mac() : MagicniPredmet("Mac") {}
// Mac unistava minotaura ako poksusa da napadne robota
void Mac::primeniEfekat(Robot& robot) {
	robot.dodajEfekat("Mac");
	std::cout << "Mac je aktiviran tokom naredna 3 poteza!" << std::endl;
}

Stit::Stit() : MagicniPredmet("Stit") {}
// Stit omogucava robotu da se odbrani od napada minotaura
void Stit::primeniEfekat(Robot& robot) {
	robot.dodajEfekat("Stit");
	std::cout << "Stit je aktiviran tokom naredna 3 poteza!" << std::endl;
}

Cekic::Cekic() : MagicniPredmet("Cekic") {}
// Cekic omogucava robotu da unisti zid ako stane na njegovu koordinatu
void Cekic::primeniEfekat(Robot& robot) {
	robot.dodajEfekat("Cekic");
	std::cout << "Cekic je aktiviran tokom naredna 3 poteza!" << std::endl;
}

