#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "plik.h"

int compare(const void* a, const void* b){//funkcja compare do quicksorta
    return ((struct wynik*)b)->punkty- ((struct wynik*)a)->punkty;
}

void wpisanie_do_pliku(wynik_t rezultat){//funkcja czyta plik z wynikami, wpisuje wyniki do tablicy sortuje ja i wypisuje 5 najlepszych wynikow(uwzgledniajac wlasnie osiagniety), na koniec dopisuje ostatni wynik 
    FILE *f;
    f = fopen("wyniki.txt","r+");
    if(f == NULL){
        printf("Blad\n");
    }
    char wiersz[BUFSIZE];
    wynik_t wynik_tmp;
    wynik_t* wyniki = malloc(sizeof(wynik_t));
    int c = 0;
    while(fgets( wiersz, BUFSIZE, f ) != NULL){
        int c1 = 0;
        int wynik = 0;
        char* nazwa = malloc(sizeof(char)*20);
        while(nazwa[c1] != 0){
            nazwa[c1] = 0;
            c1++;
        }
        c1 = 0;
        while(wiersz[c1] != ' '){
            nazwa[c1] = wiersz[c1];
            c1++;
        }
        c1++;
        while(wiersz[c1] != '\n'){
            wynik = wynik * 10 + (wiersz[c1]-48);
            c1++;
        }
        wynik_tmp.nazwa = nazwa;
        wynik_tmp.punkty = wynik;
        wyniki = realloc(wyniki,sizeof(wynik_t)*(c+2));
        wyniki[c] = wynik_tmp;
        c++;
    }
    wyniki = realloc(wyniki,sizeof(wynik_t)*c);
    wyniki[c] = rezultat;
    qsort(wyniki, c+1 , sizeof(wynik_t),compare);
    printf("Top 5 najlepszych wynikow:\n");
    for(int i = 0; i < 5; i++){
        printf("%d: %s %d\n",i+1, wyniki[i].nazwa, wyniki[i].punkty);
    }
    fprintf(f,"%s %d", rezultat.nazwa, rezultat.punkty);
    fprintf(f,"\n");
    fclose(f);
}