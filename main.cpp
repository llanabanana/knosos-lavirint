// knosos_sv23_2023.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Igra.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Koriscenje: ./knosos redovi kolone predmeti" << endl;
        return 1;
    }

    int r = stoi(argv[1]);
    int k = stoi(argv[2]);
    int p = stoi(argv[3]);

    if (r < 15 || k < 15 || p < 3 || p>r+k) {
        cerr << "Dimenzije min 15x15 i min 3 predmeta" << endl;
        return 1;
    }
    Igra igra(r, k, p);
    igra.pokreni();

	
    return 0;
}
