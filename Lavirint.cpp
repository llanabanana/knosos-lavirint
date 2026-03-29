#include "Lavirint.h"
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <chrono>
#include <random>   
#include <algorithm>
#include <ctime>
#include <iostream>
#include "GeneratorLavirinta.h"

using std::vector;
using std::cout;
using std::endl;
/*
Modul Lavirint sadrzi sve informacije o lavirintu, kao i metode za rad sa lavirintom.
Autor: Lana Mirkov
Poslednja izmena: 25.7.2025.
*/
Lavirint::Lavirint() {
	matrica = nullptr;
	brojRedova = 0;
	brojKolona = 0;
	brojPredmeta = 0;
	ulaz = Polje();
	izlaz = Polje();
	robot = Robot();
	minotaur = Minotaur();
	ivice = vector<std::pair<int, int>>();  // Inicijalizacija ivica kao praznog vektora

}

Lavirint::Lavirint(unsigned int brojRedova, unsigned int brojKolona, unsigned int brojPredmeta) {
	this->brojRedova = brojRedova;
	this->brojKolona = brojKolona;
	this->brojPredmeta = brojPredmeta;

	matrica = GeneratorLavirinta::generisi(brojRedova, brojKolona, brojPredmeta, ulaz, izlaz, robot, minotaur, ivice);
	

	
}

Lavirint::~Lavirint() {
	for (unsigned int i = 0; i < brojRedova; i++) {
		delete[] matrica[i];
	}
	delete[] matrica;
	matrica = nullptr;
}

unsigned int Lavirint::getBrojRedova() {
	return brojRedova;
}

unsigned int Lavirint::getBrojKolona() {
	return brojKolona;
}

unsigned int Lavirint::getBrojPredmeta() {
	return brojPredmeta;
}
vector<std::pair<int, int>> Lavirint::getIvice() const {
	return ivice;
}
void Lavirint::setIvice(const vector<std::pair<int, int>>& ivice) {
	this->ivice = ivice;
}
Polje** Lavirint::getMatrica() {
	return matrica;
}



void Lavirint::setBrojRedova(unsigned int brojRedova) {
	this->brojRedova = brojRedova;
}

void Lavirint::setBrojKolona(unsigned int brojKolona) {
	this->brojKolona = brojKolona;
}

void Lavirint::setBrojPredmeta(unsigned int brojPredmeta) {
	this->brojPredmeta = brojPredmeta;
}
void Lavirint::setUlaz(Polje ulaz) {
	this->ulaz = ulaz;
}

void Lavirint::setIzlaz(Polje izlaz) {
	this->izlaz = izlaz;
}

void Lavirint::setRobot(Robot robot) {
	this->robot = robot;
}

void Lavirint::setMinotaur(Minotaur minotaur) {
	this->minotaur = minotaur;
}


void Lavirint::setPraznoPolje(int x, int y) {
	matrica[x][y] = Polje(x, y, ' ');
}

Polje Lavirint::getUlaz() {
	return ulaz;
}

Polje Lavirint::getIzlaz() {
	return izlaz;
}

Robot& Lavirint::getRobot() {
	return robot;
}

Minotaur Lavirint::getMinotaur() {
	return minotaur;
}



void Lavirint::setRobotKoordinate(int x, int y) {
	robot.smanjiTrajanjeSvihEfekata();  // Smanjujemo trajanje svih efekata robota pre nego što ga pomerimo
	robot.setKoordinate(x, y);
	matrica[x][y].setTip('R');
}

void Lavirint::setMinotaurKoordinate(int x, int y) {
	minotaur.setKoordinate(x, y);
	matrica[x][y].setTip('M');
}

std::pair<int, int> Lavirint::getRobotKoordinate() {
	return robot.getKoordinate();
}

std::pair<int, int> Lavirint::getMinotaurKoordinate() {
	return minotaur.getKoordinate();
}



void Lavirint::prikaziLavirint() {
	// Funkcija koja prikazuje lavirint u konzoli
	cout << "Lavirint: " << endl;
	for (unsigned int i = 0; i < brojRedova; i++) {
		for (unsigned int j = 0; j < brojKolona; j++) {
			matrica[i][j].prikaziPolje();
		}
		cout << endl;
	}
}

void Lavirint::prikaziMaglaLavirint() {
	// Funkcija koja prikazuje lavirint u konzoli, ali sa maglom
	cout << "Lavirint (sa maglom): " << endl;
	std::pair<int, int> robotCoords = getRobotKoordinate();
	int robotX = robotCoords.first;
	int robotY = robotCoords.second;

	for (unsigned int i = 0; i < brojRedova; i++) {
		for (unsigned int j = 0; j < brojKolona; j++) {
			unsigned int distance = std::max(abs(robotX - (int)i), abs(robotY - (int)j));

			if (distance <= 3) {
				matrica[i][j].prikaziPolje();
			}

		}
		cout << endl;
	}
}


std::pair<int, int> Lavirint::pronadjiNovoPolje(int x, int y, const char& c) {
	//Funkcija koja nakon sto se unese smer, na osnovu trenutnog polja odrejuje gde robot treba dalje da se krece
	if (c == 'w') {
		x--;
	}
	else if (c == 's') {
		x++;
	}
	else if (c == 'a') {
		y--;
	}
	else if (c == 'd') {
		y++;
	}
	else
	{
		cout << "Uneli ste nepostojeci smer!" << endl;
		return std::make_pair(-1, -1);
	}
	return std::make_pair(x, y);
}


Polje* Lavirint::operator[](unsigned int index) {
	if (index < 0 || index >= brojRedova) {
		throw std::out_of_range("Indeks reda van opsega");
	}
	return matrica[index];
}
