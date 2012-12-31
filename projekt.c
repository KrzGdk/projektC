#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct miasto{
    char nazwa[40];
};

struct miasto* tworzTabMiast(int*);
int** tworzMacierz(int);
void wypelnijMacierz(int**,struct miasto*,int);

int main(void){
    int liczbaMiast, i, j;
    struct miasto* miasta;
    int** macierz;

    miasta=tworzTabMiast(&liczbaMiast);
    macierz=tworzMacierz(liczbaMiast);
	wypelnijMacierz(macierz,miasta,liczbaMiast);

    for(i=0;i<liczbaMiast;i++){
		for(j=0;j<liczbaMiast;j++){
			printf("%d ", macierz[i][j]);
		}
		printf("\n");
	}

    free(miasta);
    free(macierz);
	return 0;
}

void wypelnijMacierz(int** macierz,struct miasto* miasta,int liczbaMiast){
	char temp[40], odl[5], nazwa[35];
	int i, j, cyfr, odlInt;
	FILE *miejscowosci;
	if((miejscowosci=fopen("miejscowosci_v2.dat", "r"))==NULL){
		printf("Blad przy otwieraniu pliku\n");
		exit(EXIT_FAILURE);
	}
	
	fgets(temp,40,miejscowosci);
	while(!feof(miejscowosci)){       
        for(i=0;i<liczbaMiast;i++){
			if(strcmp(temp,miasta[i].nazwa)==0){
				fgets(temp,40,miejscowosci);
				break;
			}
        }
		while(isdigit(temp[0]) && !feof(miejscowosci)){
			for(cyfr=0;cyfr<5;cyfr++){
				if(!isdigit(temp[cyfr])) break;    /* liczy cyfry */
			}
			strncpy(odl,temp,cyfr);
			odl[cyfr]='\0';
			strcpy(nazwa,temp+cyfr+1);
			for(j=0;j<liczbaMiast;j++){
				if(strcmp(nazwa,miasta[j].nazwa)==0) break;
			}
			odlInt=atoi(odl);
			macierz[i][j]=odlInt;
			fgets(temp,40,miejscowosci);
			}

    }

}

int** tworzMacierz(int liczbaMiast){
    int i;
    int** macierz;
    if((macierz=(int**) calloc(liczbaMiast,sizeof(int*)))==NULL){
        printf("Blad przydzialu pamieci\n");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<liczbaMiast;i++){
        macierz[i]=(int *) calloc(liczbaMiast,sizeof(int));
        if(macierz[i]==NULL){
            printf("Blad przydzialu pamieci\n");
            exit(EXIT_FAILURE);
        }
    }
    return macierz;
}

struct miasto* tworzTabMiast(int* liczbaMiast){
    char c;
	int liczbaLinii=0;
	int i=0, linia=0;
	char temp[50];
	struct miasto* tab;

	FILE *miejscowosci;
	if((miejscowosci=fopen("miejscowosci_v2.dat", "r"))==NULL){
		printf("Blad przy otwieraniu pliku\n");
		exit(EXIT_FAILURE);
	}
    c=fgetc(miejscowosci);
    while(c!=EOF){
        if(c=='\n')liczbaLinii++;
        c=getc(miejscowosci);
    }
    rewind(miejscowosci);
    while(linia<=liczbaLinii){
        fgets(temp,40,miejscowosci);
        if(isdigit(temp[0])) i--;
        i++;
        linia++;
    }

    *liczbaMiast=i;

    if((tab=(struct miasto*) malloc(*liczbaMiast*sizeof(struct miasto)))==NULL){
        printf("Blad przydzialu pamieci\n");
        exit(EXIT_FAILURE);
    }
    printf("%d\b\b  \b\b",*liczbaMiast);
    rewind(miejscowosci);
    i=0;
    linia=0;
    while(linia<liczbaLinii){
        fgets(tab[i].nazwa,40,miejscowosci);
        if(isdigit(tab[i].nazwa[0])) i--;
        i++;
        linia++;
    }
	fclose(miejscowosci);
	return tab;
}



