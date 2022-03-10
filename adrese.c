#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define _CRT_SECURE_NO_WARNINGS
// functie care combina 2 persoane in cazul in care au aceeasi adresa de email
void combinePersons(int indexp1, int indexp2, char** names,
	int* emailNumbers, char*** emails, int n) {
	char* finalName;
	int finalEmailNumber = 0;
	char** finalEmails = NULL;

	// se alege numele cel mai mic (alfabetic)
	if (strcmp(names[indexp1], names[indexp2]) < 0) {
		finalName = (char*)malloc((strlen(names[indexp1]) + 1) * sizeof(char));
		strcpy(finalName, names[indexp1]);
	} else {
		finalName = (char*)malloc((strlen(names[indexp2]) + 1) * sizeof(char));
		strcpy(finalName, names[indexp2]);
	}

	// punem toate emailurile pentru persoana p1
	finalEmails = (char**)malloc(emailNumbers[indexp1] * sizeof(char*));
	for (int i = 0; i < emailNumbers[indexp1]; i++) {
		finalEmails[finalEmailNumber] = (char*)
		malloc((strlen(emails[indexp1][i]) + 1) * sizeof(char));
		strcpy(finalEmails[finalEmailNumber], emails[indexp1][i]);
		finalEmailNumber++;
	}
	// se aleg doar emailurile distincte pentru persoana p2
	for (int i = 0; i < emailNumbers[indexp2]; i++) {
		int emailExistent = 0;
		for (int j = 0; j < finalEmailNumber; j++) {
			if (strcmp(emails[indexp2][i], finalEmails[j]) == 0) {
				emailExistent = 1;
				break;
			}
		}
		if (!emailExistent) {
			finalEmails = (char**)realloc(finalEmails,
				(finalEmailNumber + 1) * sizeof(char*));
			finalEmails[finalEmailNumber] = (char*)
			malloc((strlen(emails[indexp2][i]) + 1) * sizeof(char));
			strcpy(finalEmails[finalEmailNumber], emails[indexp2][i]);
			finalEmailNumber++;
		}
	}
	// eliberam memoria pentru indexp1 si indexp2
	free(names[indexp1]);
	free(names[indexp2]);
	for (int i = 0; i < emailNumbers[indexp1]; i++) {
		free(emails[indexp1][i]);
	}
	free(emails[indexp1]);

	for (int i = 0; i < emailNumbers[indexp2]; i++) {
		free(emails[indexp2][i]);
	}
	free(emails[indexp2]);

	// punem persoana noua pe pozitia indexp1
	// si o stergem pe cea de pe pozitia indexp2
	names[indexp1] = finalName;
	emails[indexp1] = finalEmails;
	emailNumbers[indexp1] = finalEmailNumber;
	for (int i = indexp2; i < n - 1; i++) {
		names[i] = names[i + 1];
		emails[i] = emails[i + 1];
		emailNumbers[i] = emailNumbers[i + 1];
	}
}

void emailuri_v1() {
	FILE* inFile, * outFile;
	char buffer[51];
	int n;
	char** names;
	int* emailNumbers;
	char*** emails;
	// deschidere fisiere
	inFile = fopen("adrese.in", "r");
	outFile = fopen("adrese.out", "w");

	if (inFile == NULL || outFile == NULL) {
		printf("Eroare: deschide fisier");
		return;
	}
	// citire date din fisier
	fscanf(inFile, "%d", &n);
	// citire numar de persoane si alocare memorie
	// pentru vectorii de nume,emailuri
	// vector de nume,repr ca sir de caractere
	names = (char**)malloc(n * sizeof(char*));
	// vector cu nr de mailuri pt fiecare persoana
	emailNumbers = (int*)malloc(n * sizeof(int));
	// vector in care tinem pointer la lista de emailuri
	// emailurile fiind un pointer la un sir de caractere
	emails = (char***)malloc(n * sizeof(char**));
	// pentru cele n persoane citim,numele si nr de emailuri
	// dupa care citim si atatea emailuri cat am citit nr
	for (int i = 0; i < n; i++) {
		fscanf(inFile, "%s %d", &buffer, &emailNumbers[i]);
		names[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(names[i], buffer);
		emails[i] = (char**)malloc(emailNumbers[i] * sizeof(char*));
		for (int j = 0; j < emailNumbers[i]; j++) {
			fscanf(inFile, "%s", &buffer);
			emails[i][j] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(emails[i][j], buffer);
		}
	}
	// comparam toate persoanele pentru a vedea daca au fost combinate
	// daca au emailuri comune,si facem acest lucru prin functia combinePersons
	for (int i = 0; i < n; i++) {
	// se ia pe rand fiecare persoana
		for (int j = 0; j < emailNumbers[i]; j++) {
		// se ia pe rand fiecare e-mail al persoanei
			for (int ii = i + 1; ii < n; ii++) {
			// se iau pe rand celelalte persoane
				int persoanaAFostCombinata = 0;
				for (int jj = 0; jj < emailNumbers[ii]; jj++) {
				// se iau pe rand e-mailurile celeilalte persoane
					if (strcmp(emails[i][j], emails[ii][jj]) == 0) {
					// daca este acelasi e-mail
						combinePersons(i, ii, names, emailNumbers, emails, n);
						n--;
						persoanaAFostCombinata = 1;
						break;
					}
				}
				if (persoanaAFostCombinata) {
					continue;
				}
			}
		}
	}
	// sortare persoane in ordinea precizata in enunt
	// mai intai dupa nr de emailuri apoi lexicografic
	int auxNrEmails;
	char* auxNume;
	char** auxEmails;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (emailNumbers[i] > emailNumbers[j] ||
				(emailNumbers[i] == emailNumbers[j] && strcmp(names[i], names[j]) > 0)) {
			// schimbare intre ele
				auxNrEmails = emailNumbers[i];
				emailNumbers[i] = emailNumbers[j];
				emailNumbers[j] = auxNrEmails;
				auxNume = names[i];
				names[i] = names[j];
				names[j] = auxNume;
				auxEmails = emails[i];
				emails[i] = emails[j];
				emails[j] = auxEmails;
			}
		}
	}
	// sortare emailuri pentru fiecare persoana
	// in odrinea precizata in enunt,adica lexicografic
	char* auxEmail;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < emailNumbers[i]; j++) {
			for (int k = j + 1; k < emailNumbers[i]; k++) {
				if (strcmp(emails[i][j], emails[i][k]) > 0) {
					auxEmail = emails[i][j];
					emails[i][j] = emails[i][k];
					emails[i][k] = auxEmail;
				}
			}
		}
	}
	// scriere in fisier
	fprintf(outFile, "%d\n", n);
	for (int i = 0; i < n; i++) {
		fprintf(outFile, "%s %d\n", names[i], emailNumbers[i]);
		for (int j = 0; j < emailNumbers[i]; j++) {
			fprintf(outFile, "%s\n", emails[i][j]);
		}
	}
	// inchidere fisiere
	fclose(outFile);
	fclose(inFile);
}
int main() {
	emailuri_v1();

	return 0;
}
