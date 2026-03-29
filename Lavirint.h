#pragma once
#include "Polje.h"
#include "Robot.h"
#include <iostream>
#include <queue>
#include <vector>
#include "Minotaur.h"

/*
Klasa koja predstavlja lavirint.
Autor: Lana Mirkov
Poslednja izmena: 2.8.2025.
*/

class Lavirint
{
private:
	Polje** matrica;  // matrica predstavlja sam lavirint
	unsigned int brojRedova;
	unsigned int brojKolona;
	unsigned int brojPredmeta;
	Polje ulaz;
	Polje izlaz;
	Robot robot;
	Minotaur minotaur;
	std::vector<std::pair<int, int>>  ivice;  // vektor koji sadrzi koordinate ivica lavirinta
public:
	Lavirint();
	Lavirint(unsigned int brojRedova, unsigned int brojKolona, unsigned int brojPredmeta);
	~Lavirint();

	//getteri i setteri za broj redova, kolona i predmeta
	unsigned int getBrojRedova();
	unsigned int getBrojKolona();
	unsigned int getBrojPredmeta();
	void setBrojRedova(unsigned int brojRedova);
	void setBrojKolona(unsigned int brojKolona);
	void setBrojPredmeta(unsigned int brojPredmeta);
	std::vector<std::pair<int, int>> getIvice() const;
	void setIvice(const std::vector<std::pair<int, int>>& ivice);
	//getteri i setteri za ulaz, izlaz, robota i minotaura
	Polje getUlaz();
	Polje getIzlaz();
	Robot& getRobot();
	Minotaur getMinotaur();
	void setUlaz(Polje ulaz);
	void setIzlaz(Polje izlaz);
	void setRobot(Robot robot);
	void setMinotaur(Minotaur minotaur);
	void setPraznoPolje(int x, int y);

	std::pair<int, int> getRobotKoordinate();
	void setRobotKoordinate(int x, int y);
	std::pair<int, int> getMinotaurKoordinate();
	void setMinotaurKoordinate(int x, int y);
	
	// samo get za matricu, setuje se u GeneratorLavirinta
	Polje** getMatrica();

	
	
	// Nakon unosa sa tastature, odredjuje koje je novo polje
	std::pair<int, int> pronadjiNovoPolje(int x, int y, const char& c);

	void prikaziLavirint();
	void prikaziMaglaLavirint();

	Polje* operator[](unsigned int index); // Vraca pokazivac na niz polja u redu index
	


};