#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define _CRT_SECURE_NO_WARNINGS
// vector in care tinem sumele distincte si nr lor
// o variabila pentru a afla suma maxima posibila
// care se poate obtine cu acele piese
int sumeDistincte[1000];
int lungimeSumeDistincte;
int maxLungimeSumeDistincte = 0;
int* pieseMaxLungimeSumeDistincte = NULL;

int sume_distincte_consecutive() {
	int max = 0;
	int count = 1;
	// ordonam sumele distince in ordine crescatoare
	for (int i = 0; i < lungimeSumeDistincte; i++) {
  		for (int j = i + 1; j < lungimeSumeDistincte; j++) {
  			if (sumeDistincte[i] > sumeDistincte[j]) {
  				// interschimbare
				int aux = sumeDistincte[i];
				sumeDistincte[i] = sumeDistincte[j];
				sumeDistincte[j] = aux;
			}
		}
	}
	// vedem cate sume consecutive avem,daca diferenta
	// lor este 1, si le numaram in variabila count
	for (int i = 1; i < lungimeSumeDistincte; i++) {
    	if (sumeDistincte[i] == sumeDistincte[i - 1] + 1) {
      	count++;
    	} else {
       		if (count > max) {
         		max = count;
       		}
       		count = 1;
    	}
    }
    // comparam count cu un max initializat initial cu 0 si daca
    // avem astfel de sume distincte updatam max si il returnam
    if (count > max) {
     	max = count;
     }
	return max;
}

void lego_back_sum(int t, int* v, int l, int* numereSuma, int lungimeNS,
	int curentPos, int currentSum) {
	if (currentSum != 0) {
		int sumaMaiExista = 0;
		for (int i = 0; i < lungimeSumeDistincte; i++) {
		// vedem daca suma a mai fost sau nu
			if (sumeDistincte[i] == currentSum) {
				sumaMaiExista = 1;
				break;
			}
		}
		if (!sumaMaiExista) {
			// if(l==4 && v[0]==2 && v[1]==5 && v[2]==11 && v[3] == 15) {
			// cout << currentSum << "=";
			// for (int i = 0; i < lungimeNS; i++) {
			// 	cout << numereSuma[i]<<"+";
			// }
			// cout << endl;
			// adaugam suma in vectorul de sume
			// incrementnam nr de sume distincte
			sumeDistincte[lungimeSumeDistincte] = currentSum;
			lungimeSumeDistincte++;
			// }
		}
	}
	// daca am folisit t piese cat se cerea in enunt
	if (lungimeNS == t) {
		return;
	}
	// cate piese mai putem folosi
	for (int i = curentPos; i < l; i++) {
		numereSuma[lungimeNS] = v[i];
		// continuam cu gasirea sumelor
		lego_back_sum(t, v, l, numereSuma, lungimeNS + 1, i, currentSum+ v[i]);
	}
}

void lego_back(int n, int k, int t, int* v, int l, int curentVal) {
	if (l == n) {  // aici obtin toate multimile posibile
		// pentru fiecare trebuie sa calculez toate
		// numerele distincte care se pot calcula cu ele
		lungimeSumeDistincte = 0;
		int* numereSuma = (int*)malloc(t * sizeof(int));
		/*cout << "Pentru multimea: ";
		for (int i = 0; i < n; i++) {
			printf("%d ", v[i]);
		}
		cout << endl;*/
		lego_back_sum(t, v, l, numereSuma, 0, 0, 0);
		int sume_consecutive = sume_distincte_consecutive();
		if (maxLungimeSumeDistincte < sume_consecutive) {
			// updatam nr de sume consecutive
			maxLungimeSumeDistincte = sume_consecutive;
			if (pieseMaxLungimeSumeDistincte != NULL) {
				free(pieseMaxLungimeSumeDistincte);
			}
			pieseMaxLungimeSumeDistincte = (int*)malloc(n * sizeof(int));
			memcpy(pieseMaxLungimeSumeDistincte, v, l * sizeof(int));
		}
		free(numereSuma);
		return;
	}
	for (int i = curentVal; i <= k; i++) {
		v[l] = i;
		lego_back(n, k, t, v, l + 1, i + 1);
	}
}

void lego_v1() {
	FILE* inFile, * outFile;
	// deschidere fisiere
	inFile = fopen("lego.in", "r");
	outFile = fopen("lego.out", "w");
	// citire date din fisire
	// k dimensiune maxima
	// n nr de piese selectate
	// t nr max de piese care pot fi folosite
	int k, n, t;
	fscanf(inFile, "%d %d %d", &k, &n, &t);
	int* v = (int*)malloc(n * sizeof(int));
	// conditie din cerinta ca prima piesa sa fie mereu 1
	v[0] = 1;
	// apelare backtracking de gasire sume
	lego_back(n, k, t, v, 1, 1);
	/*cout << maxLungimeSumeDistincte << endl;
	for (int i = 0; i < n; i++) {
		cout << pieseMaxLungimeSumeDistincte[i] << " ";
	}*/
	// afisare in fisier
	fprintf(outFile, "%d\n", maxLungimeSumeDistincte);
	for (int i = 0; i < n; i++) {
		fprintf(outFile, "%d", pieseMaxLungimeSumeDistincte[i]);
		if (i != n - 1) {
			fprintf(outFile, " ");
		}
	}
	free(v);
	// inchidere fisiere
	fclose(outFile);
	fclose(inFile);
}

int main() {
	lego_v1();
	return 0;
}
