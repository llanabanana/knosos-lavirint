#include "GeneratorLavirinta.h"
#include <queue>
#include <algorithm>
#include <random>
#include <ctime>
#include <chrono> 
#include <vector>

/*
Modul koji sadrzi definicije funkcija koje generisu lavirint
Autor: Lana Mirkov
Poslednja izmena: 3.8.2025.
*/

Polje** GeneratorLavirinta::generisi(unsigned int brojRedova, unsigned int brojKolona, unsigned int brojPredmeta,
    Polje& ulaz, Polje& izlaz, Robot& robot, Minotaur& minotaur, std::vector<std::pair<int,int>>& ivice) {
    /*
    Ova funkcija generise lavirint sa zadatim brojem redova, kolona i predmeta.
    Parametri:
    - brojRedova: Broj redova lavirinta.
    - brojKolona: Broj kolona lavirinta.
    - brojPredmeta: Broj magicnih predmeta u lavirintu.
    - ulaz: Polje koje predstavlja ulaz u lavirint.
    - izlaz: Polje koje predstavlja izlaz iz lavirinta.
    - robot: Robot koji se nalazi u lavirintu.
    - minotaur: Minotaur koji se nalazi u lavirintu.
    */

	std::default_random_engine rng(static_cast<unsigned int>(time(0)));  // Inicijalizacija generatora slučajnih brojeva sa trenutnim vremenom
	auto start = std::chrono::high_resolution_clock::now();  // Merenje vremena generisanja lavirinta

	// Initializacija matrice
    Polje** matrica = new Polje * [brojRedova];
    for (unsigned int i = 0; i < brojRedova; i++) {
        matrica[i] = new Polje[brojKolona];
        for (unsigned int j = 0; j < brojKolona; j++) {
            matrica[i][j].setTip(' ');
        }
    }

    // Postavljamo ivice
    for (unsigned int i = 0; i < brojRedova; i++) {
        for (unsigned int j = 0; j < brojKolona; j++) {
            if (i == 0 || i == brojRedova - 1 || j == 0 || j == brojKolona - 1) {
                matrica[i][j] = Polje(i, j, '#');
				ivice.push_back(std::make_pair(i, j));  // Čuvamo ivice lavirinta
            }
            else {
                matrica[i][j] = Polje(i, j, ' ');
            }
        }
    }
    std::uniform_int_distribution<int> distX(1, brojKolona - 2);
    std::uniform_int_distribution<int> distY(1, brojRedova - 2);
    // Ulaz
	int xU = distX(rng);  // Generisanje slučajnog X koordinata za ulaz
    ulaz = Polje(0, xU, 'U');
    matrica[0][xU] = ulaz;

	// Robot se postavlja ispod ulaza
    robot.setKoordinate(1, xU);
    matrica[1][xU].setTip('R');

    // Izlaz
	int xI = distX(rng);  // Generisanje slučajnog X koordinata za izlaz
    izlaz = Polje(brojRedova - 1, xI, 'I');
    matrica[brojRedova - 1][xI] = izlaz;
	



	std::vector<std::pair<int, int>> emptyCells;  // Vektor za preostala prazna polja
    for (int i = 1; i < (int)brojRedova - 1; ++i) {
        for (int j = 1; j < (int)brojKolona - 1; ++j) {
			emptyCells.emplace_back(i, j);  // Dodajemo sve prazne ćelije osim ivica
        }
    }
	std::shuffle(emptyCells.begin(), emptyCells.end(), rng);  // Mešanje praznih ćelija da bi se postigla slučajnost

	// Minotaur se postavlja na neku praznu ćeliju
    for (auto& cell : emptyCells) {
        int y = cell.first;
        int x = cell.second;
        if (matrica[y][x].getTip() == ' ') {
            minotaur.setKoordinate(y, x);
            matrica[y][x].setTip('M');
            break;
        }
    }

    // Predmeti
    int predmetCount = 0;
    for (auto& cell : emptyCells) {
        int y = cell.first;
        int x = cell.second;
        if (matrica[y][x].getTip() == ' ') {
            matrica[y][x].setTip('P');
			if (++predmetCount == (int)brojPredmeta) break;  // Provera da li je postavljen dovoljan broj predmeta
        }
    }

    // Zidovi
	unsigned int ukupnoZidova = (brojRedova * brojKolona) / 3;  // Određivanje maks broja zidova
    std::vector<std::pair<int, int>> wallCandidates;
    for (auto& cell : emptyCells) {
        int y = cell.first;
        int x = cell.second;
        if (matrica[y][x].getTip() == ' ') {
			wallCandidates.emplace_back(y, x);  // Dodajemo sve prazne ćelije kao kandidate za zidove
        }
    }

	std::shuffle(wallCandidates.begin(), wallCandidates.end(), rng);  // Mešanje kandidata za zidove da bi se postigla slučajnost

    std::vector<std::pair<int, int>> postavljeniZidovi;
    unsigned int postavljeno = 0;
    for (auto& cell : wallCandidates) {
		if (postavljeno >= ukupnoZidova) break;  // Proveravamo da li je dostignut maksimalan broj zidova
        int y = cell.first;
        int x = cell.second;
		matrica[y][x].setTip('#');  // Postavljamo zid
        postavljeniZidovi.emplace_back(y, x);
        postavljeno++;
    }

	// Postavimo prazno polje iznad izlaza, da bi se moglo proći
    matrica[brojRedova - 2][xI].setTip(' ');

    // Validacija
    while (!matricaJeValidna(matrica, brojRedova, brojKolona, ulaz, izlaz)) {
        /*
		Sve dok ne postoji put od ulaza do izlaza, uklanjamo zidove jedan po jedan
		Nakohn svake iteracije proveravamo da li je matrica validna.
        */
        if (postavljeniZidovi.empty()) break;
        auto cell = postavljeniZidovi.back();
        int y = cell.first;
        int x = cell.second;
        postavljeniZidovi.pop_back();
        matrica[y][x].setTip(' ');
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Generisanje lavirinta zavrseno za " << duration.count() << " ms." << std::endl;
    return matrica;
}


bool GeneratorLavirinta::floodFill(Polje** matrica, unsigned int brojRedova, unsigned int brojKolona, int row, int col, std::vector<std::vector<bool>>& visited, char target) {
    /*
	Algoritam za pretragu lavirinta koristeći BFS (Breadth-First Search).
	Parametri:
	- matrica: Lavirint koji se pretražuje.
	- brojRedova: Broj redova u lavirintu.
	- brojKolona: Broj kolona u lavirintu.
	- row: Trenutni red u lavirintu.
	- col: Trenutna kolona u lavirintu.
	- visited: Vektor vektora boolova koji prati posećena polja.
	- target: Ciljni tip polja koje tražimo (npr. 'I' za izlaz).
    */
    std::queue<std::pair<int, int>> q;
    q.push({ row, col });
    visited[row][col] = true;

    std::vector<std::pair<int, int>> directions = { {-1,0}, {1,0}, {0,-1}, {0,1} };

    while (!q.empty()) {
        auto curRow = q.front().first;
        auto curCol = q.front().second;
        q.pop();
        if (matrica[curRow][curCol].getTip() == target) return true;

        for (auto& dir : directions) {
            int dr = dir.first;
            int dc = dir.second;
            int newRow = curRow + dr;
            int newCol = curCol + dc;
            if (newRow >= 0 && newRow < (int)brojRedova && newCol >= 0 && newCol < (int)brojKolona &&
                !visited[newRow][newCol] &&
                matrica[newRow][newCol].getTip() != '#' &&
                matrica[newRow][newCol].getTip() != 'M') {
                visited[newRow][newCol] = true;
                q.push({ newRow, newCol });
            }
        }
    }
    return false;
}


bool GeneratorLavirinta::matricaJeValidna(Polje** matrica, unsigned int brojRedova, unsigned int brojKolona, Polje ulaz, Polje izlaz) {
	/*
	Funkcija proverava da li postoji put od ulaza do izlaza u lavirintu.
	Parametri:
	- matrica: Lavirint koji se pretražuje.
	- brojRedova: Broj redova u lavirintu.
	- brojKolona: Broj kolona u lavirintu.
	- ulaz: Polje koje predstavlja ulaz u lavirint.
	- izlaz: Polje koje predstavlja izlaz iz lavirinta.
	Vraća true ako postoji put, inače false.
	*/
	std::vector<std::vector<bool>> visited(brojRedova, std::vector<bool>(brojKolona, false));  // Inicijalizacija matrice posećenih polja
    return floodFill(matrica, brojRedova, brojKolona, ulaz.getX(), ulaz.getY(), visited, 'I');
}