// 324CA Ciorceanu Andrei Razvan
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <limits.h>
#include<time.h>

#include <iostream>
#include <fstream>
#include <queue>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;
// declarare vectori de parcurgere matricea de caractere
int vertical_i[2];
int vertical_j[2];
int orizontal_i[2];
int orizontal_j[2];


int main() {
	// deschidere fisiere de citire/afisare
	ifstream fin;
	ofstream fout;
	fin.open("poduri.in");
	fout.open("poduri.out");
	// declarare si citire variabile
	int i, j, k;
	int M, N;
	int X, Y;
	fin >> N >> M;
	fin >> X >> Y;
	// declarare matricea de caractere si matricea
	// pentru drum minim
	char caractere[N][M];
	int drum[N][M];
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			drum[i][j] = 0;
		}
	}
	// pozitia de start
	drum[X - 1][Y - 1] = 1;
	int min = INT_MAX;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			// citire caractere si in locul in care avem punct
			// punem -1, nu putem trece
			fin >> caractere[i][j];
			if(caractere[i][j] == '.') {
				drum[i][j] = -1;
			}
		}
	}
	// initializare vectori de parcurgere
	vertical_i[0] = 1;
	vertical_i[1] = -1;
	vertical_j[0] = 0;
	vertical_j[1] = 0;
	orizontal_i[0] = 0;
	orizontal_i[1] = 0;
	orizontal_j[0] = 1;
	orizontal_j[1] = -1;
	// cream coada pentru a aplica alg lui Lee
	queue<pair<int, int>> coada;
	coada.push({X - 1, Y - 1});
	while (!coada.empty()) {
		// punem perechile prin care trecem in coada
		pair<int, int> aux;
		aux = coada.front();
		coada.pop();
		// analizam tip-urile de poduri peste care dam
		// in fiecare celula
		if (caractere[aux.first][aux.second] == 'O') {
			for (k = 0; k < 2; k++) {
				// luam toate posibilitatile de deplasare si
				// punem conditiile de deplasare prin matricea de caractere
				if ((aux.first + orizontal_i[k]) >= 0 && (aux.second + orizontal_j[k]) >= 0
					&& (aux.first + orizontal_i[k]) <= (N - 1)
					&& (aux.second + orizontal_j[k]) <= (M - 1)
					&& drum[aux.first + orizontal_i[k]][aux.second + orizontal_j[k]] != -1
					&& drum[aux.first + orizontal_i[k]][aux.second + orizontal_j[k]] < 1) {
					drum[aux.first + orizontal_i[k]][aux.second +
						orizontal_j[k]] = drum[aux.first][aux.second] + 1;
				// daca celula in care ne deplasam este valida o adaugam in coada
					coada.push({aux.first + orizontal_i[k], aux.second + orizontal_j[k]});
				}
			}
		}
		// punem aceleasi conditii ca la cazul cu podul orizontal
		// folosim vectorii de deplasare verticali
		if (caractere[aux.first][aux.second] == 'V') {
			for (k = 0; k < 2; k++) {
				if ((aux.first + vertical_i[k]) >= 0 && (aux.second + vertical_j[k]) >= 0
					&& (aux.first + vertical_i[k]) <= (N - 1)
					&& (aux.second + vertical_j[k]) <= (M - 1)
					&& drum[aux.first + vertical_i[k]][aux.second + vertical_j[k]] != -1
					&& drum[aux.first + vertical_i[k]][aux.second + vertical_j[k]] < 1) {
					drum[aux.first + vertical_i[k]][aux.second +
						vertical_j[k]] = drum[aux.first][aux.second] + 1;
					coada.push({aux.first + vertical_i[k], aux.second + vertical_j[k]});
				}
			}
		}
		// aceleasi conditii doar ca podul dublu
		// intruneste ambele cazuri de la orizontal si vertical
		if (caractere[aux.first][aux.second] == 'D') {
			for (k = 0; k < 2; k++) {
				if ((aux.first + orizontal_i[k]) >= 0 && (aux.second + orizontal_j[k]) >= 0
					&& (aux.first + orizontal_i[k]) <= (N - 1)
					&& (aux.second + orizontal_j[k]) <=(M - 1)
					&& drum[aux.first + orizontal_i[k]][aux.second + orizontal_j[k]] != -1
					&& drum[aux.first + orizontal_i[k]][aux.second + orizontal_j[k]] < 1) {
					drum[aux.first + orizontal_i[k]][aux.second +
						orizontal_j[k]] = drum[aux.first][aux.second] + 1;
					coada.push({aux.first + orizontal_i[k], aux.second + orizontal_j[k]});
				}
			}
			for (k = 0; k < 2; k++) {
				if ((aux.first + vertical_i[k]) >= 0 && (aux.second + vertical_j[k]) >= 0
					&& (aux.first + vertical_i[k]) <= (N - 1)
					&& (aux.second + vertical_j[k]) <= (M - 1)
					&& drum[aux.first + vertical_i[k]][aux.second + vertical_j[k]] != -1
					&& drum[aux.first + vertical_i[k]][aux.second + vertical_j[k]] < 1) {
					drum[aux.first + vertical_i[k]][aux.second +
						vertical_j[k]] = drum[aux.first][aux.second] + 1;
					coada.push({aux.first + vertical_i[k], aux.second + vertical_j[k]});
				}
			}
		}
	}
	// in cazul in care Gigel ajunge pe prima coloane din matricea
	// noastra de caractere,verificam cazurile in care acesta poate
	// ajunge pe mal,daca poate ajunge pe mal,daca exista un pod
	// de tipul orizontal/dublu, daca a ajuns pe un drum minim
	// si care este posibilitatea cea mai buna sa ajunga pe mal
	for (i = 1; i < N - 1; i++) {
		if (drum[i][0] < min) {
			if (drum[i][0] != -1) {
				if (drum[i][0] != 0) {
					if (caractere[i][0] == 'O' || caractere[i][0] == 'D') {
						min = drum[i][0];
					}
				}
			}
		}
	}
	// verificam separat cazurile in care gigel ajunge in
	// colturile matricei noastre de caractere si daca poate
	// ajunge in acele celule
	if (drum[0][0] < min) {
		if (drum[0][0] != 0) {
			if (drum[0][0] != -1) {
				if (caractere[0][0] != '.') {
					min = drum[0][0];
				}
			}
		}
	}
	if(drum[N - 1][0] < min) {
		if(drum[N - 1][0] != 0) {
			if(drum[N - 1][0] != -1) {
				if(caractere[N - 1][0] != '.') {
					min = drum[N - 1][0];
				}
			}
		}
	}
	// daca gigel ajunge pe prima linie verificam analog cazurile
	// de iesire din matrice,schimbam doar tipurile de poduri
	// pe care poate trece astfel incat sa ajunga pe mal
	for (i = 1; i < M - 1; i++) {
		if (drum[0][i] < min) {
			if (drum[0][i] != -1) {
				if (drum[0][i] != 0) {
					if (caractere[i][0] == 'D' || caractere[i][0] == 'V') {
						min = drum[0][i];
					}
				}
			}
		}
	}

	if (drum[0][M - 1] < min) {
		if (drum[0][M - 1] != 0) {
			if (drum[0][M - 1] != -1) {
				if (caractere[0][M - 1] != '.') {
					min = drum[0][M - 1];
				}
			}
		}
	}
	// aceleasi cazuri pentru ultima coloana din matricea de caractere
	for (i = 1; i < N - 1; i++) {
		if (drum[i][M - 1] < min) {
			if (drum[i][M - 1] != -1) {
				if (drum[i][M - 1] != 0) {
					if (caractere[i][M - 1] == 'D' || caractere[i][M - 1] == 'O') {
						min = drum[i][M - 1];
					}
				}
			}
		}
	}
	// aceleasi cazuri pentru ultima linie din matricea de caractere
	if (drum[N - 1][M - 1] < min) {
		if (drum[N - 1][M - 1] != 0) {
			if (drum[N - 1][M - 1] != -1) {
				if (caractere[N - 1][M - 1] != '.') {
					min = drum[N - 1][M - 1];
				}
			}
		}
	}
	// ultima linie
	for (i = 1; i < M - 1; i++) {
		if (drum[N - 1][i] < min) {
			if (drum[N - 1][i] != -1) {
				if (drum[N - 1][i] != 0) {
					if (caractere[N - 1][i] == 'D' || caractere[N - 1][i] == 'V') {
						min = drum[N - 1][i];
					}
				}
			}
		}
	}
	// daca a ajuns pe mal afisam minimul
	if (min != INT_MAX) {
	fout << min;
	// inchidem fisierele de citire/afisare
	fin.close();
	fout.close();
	return 0;
	}
	// daca minimul nu a fost modificat inseamna
	// ca nu poate ajunge pe mal,afisam -1
	fout << "-1\n";
	fin.close();
	fout.close();
	return 0;
}
