#include "Fajl.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lavirint.h"

/*
Modul koji sadrži funkciju za upis lavirinta u fajl.
Autor: Lana Mirkov
Poslednja izmena: 2.8.2025.
*/

void Fajl::upisiUFajl(std::string izlazniFajl, Lavirint lavirint) {
	// ako fajl ne postoji, kreiraj ga
	if (izlazniFajl.empty()) {
		std::cerr << "Greska: Ime izlaznog fajla ne sme biti prazno." << std::endl;
		return;
	}

	std::ofstream file(izlazniFajl);  //  otvaranje fajla za upis
	if (!file.is_open()) {
		std::cerr << "Greska prilikom otvaranja fajla: " << izlazniFajl << std::endl;   
		return;
	}

	for (unsigned int i = 0; i < lavirint.getBrojRedova(); i++) {
		for (unsigned int j = 0; j < lavirint.getBrojKolona(); j++) {
			Polje** matrica = lavirint.getMatrica();

			if (matrica[i][j].getTip() == 'R') {
				file << "R"; // Robot
			}
			else if (matrica[i][j].getTip() == 'M') {
				file << "M"; // Minotaur
			}
			else if (matrica[i][j].getTip() == 'P') {
				file << "P"; // Magicni predmet
			}
			else if (matrica[i][j].getTip() == 'U') {
				file << "U"; // Ulaz
			}
			else if (matrica[i][j].getTip() == 'I') {
				file << "I"; // Izlaz
			}
			else if (matrica[i][j].getTip() == '#') {
				file << "#"; // Zid
			}
			else {
				file << " "; // Prazno polje
			}
		}
		file << std::endl; // novi red nakon svakog reda lavirinta
	}

	file << std::endl;
	std::cout << "Lavirint je upisan u fajl: " << izlazniFajl << std::endl;


	file.close();
}