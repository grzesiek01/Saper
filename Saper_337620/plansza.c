#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "plansza.h"
#include "plik.h"

pole_t **genruj_plansze(int x, int y){//funkcja tworzy pusta plansze o podanych wymiarach
    pole_t **plansza = malloc(sizeof(pole_t*)*y);
    for(int i = 0; i < y; i++){
        plansza[i] = malloc(sizeof(pole_t)*x);
        for(int j = 0; j < x; j++){
            plansza[i][j].czy_mina = 0;
            plansza[i][j].czy_odkryte = 0;
            plansza[i][j].wartosc = 0;
            plansza[i][j].odkrycie = 0;
        }
    }
    return plansza;
}

pole_t **generuj_miny(int x, int y, int x_czyste, int y_czyste, int ilosc, pole_t **plansza){//funkcja losuje ustawienie min na planszy, nie moze ustawic miny na polu wybranym przez gracza jako pierwszym
    int wygenerowane = 0;
    srand(time(NULL));
    while(wygenerowane < ilosc){
	    int x_los = rand() % x;
	    int y_los = rand() % y;
        if(plansza[y_los][x_los].czy_mina == 0 && x_los != x_czyste && y_los != y_czyste){
            plansza[y_los][x_los].czy_mina = 1;
            wygenerowane++;
        }
    }
    return plansza;
}

pole_t **ustaw_wartosci(int x, int y, pole_t **plansza){//funkcja na podstawie wygenerowanych min ustawia wartosi pol na ilosc sasiadujacych min
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if(plansza[i][j].czy_mina == 1){
                plansza[i][j].wartosc = -1;
            }
            else{
                int licznik = 0;
                for(int k = -1; k <= 1; k++){
                    for(int l = -1; l <= 1; l++){
                        if(i+k >= 0 && i+k < y && j+l >= 0 && j+l < x){
                            if(plansza[i+k][j+l].czy_mina == 1){
                                licznik++;
                            }
                        }
                    }
                }
                plansza[i][j].wartosc = licznik;
            }
        }
    }
    return plansza;
}

void pisz_plansze(int x, int y, int wynik, pole_t **plansza){//funkcja wypisuje aktualny stan planszy
    printf("Twoj wynik: %d \n  ", wynik);
    for(int k = 0; k < x; k++){
        if(k<9){
            printf(" %d ",k+1);
        }
        else{
            printf("%d ",k+1);
        }
    }
    printf("\n");
    for(int i = 0; i < y; i++){
        if(i>8){
            printf("%d",i+1);
        }
        else{
            printf("%d ",i+1);
        }
        for(int j = 0; j < x; j++){
            if(plansza[i][j].czy_odkryte == 0){
                printf("[ ]");
            }
            else if(plansza[i][j].odkrycie == -2){
                printf("[f]");
            }
            else{
                printf("[%d]",plansza[i][j].odkrycie);
            }
        }
        printf("\n");
    }
}

void odkrywanie(int x, int y, int* odkrycia, int x_podane, int y_podane, pole_t **plansza){//funkcja odkrywa wszystkie pola nie sasiadujace z mina i sasiadujace do nich
    if(plansza[x_podane][y_podane].czy_odkryte == 0){
        plansza[x_podane][y_podane].czy_odkryte = 1;
        plansza[x_podane][y_podane].odkrycie = plansza[x_podane][y_podane].wartosc;
        (*odkrycia)++;
    }
    for(int k = -1; k <= 1; k++){
        for(int l = -1; l <= 1; l++){
            if(x_podane+k >= 0 && x_podane+k < x && y_podane+l >= 0 && y_podane+l < y && plansza[x_podane+k][y_podane+l].czy_odkryte == 0){
                if(plansza[x_podane+k][y_podane+l].wartosc == 0){
                    odkrywanie(x,y,odkrycia,x_podane+k,y_podane+l,plansza);
                }
                else{
                    if(plansza[x_podane+k][y_podane+l].czy_odkryte == 0){
                        plansza[x_podane+k][y_podane+l].czy_odkryte = 1;
                        plansza[x_podane+k][y_podane+l].odkrycie = plansza[x_podane+k][y_podane+l].wartosc;
                        (*odkrycia)++;
                    }
                }
            }
        }
    }
}

int graj(int x, int y, int ilosc, int poziom, char* nazwa, pole_t **plansza){// funkcja odpowiadajaca za gre, czyta kolejne ruchy i wykonuje akcje
    int flag = 0;
    int flag2 = 0;
    int flag3 = 0;
    int flag4 = 0;
    int odkryte = 0;
    pisz_plansze(x,y,odkryte*poziom,plansza);
    int wybrane_x = 0;
    int wybrane_y = 0;
    char rodzaj;
    char wpis[7];
    char wpis1[7];
    int c = 0;
    printf("Twoj pierwszy ruch:\n");
    flag3 = 0;
    while(flag3 == 0){
        gets(wpis);
        flag4 = 0;
        while(flag4 == 0){
            c = 2;
            if(wpis[0] == 'r'){
                if(wpis[1] == ' '){
                    while(wpis[c] != ' ' && wpis[c] != 0){
                        if((wpis[c]-48)>=0 && (wpis[c]-48)<10){
                            wybrane_x = wybrane_x*10 + (wpis[c]-48);
                            c++;
                        }
                        else{
                            c++;
                            printf("Tu1\n");
                            flag4 = 1;
                        }
                    }
                    c++;
                    while(wpis[c] != 0){
                        if((wpis[c]-48)>=0 && (wpis[c]-48)<10){
                            wybrane_y = wybrane_y*10 + (wpis[c]-48);
                            c++;
                        }
                        else{
                            printf("Tu2\n");
                            c++;
                            flag4 = 1;
                        }
                    }
                }
                else{
                    printf("Tu4\n");
                	flag4 = 1;
                }
            }
            else{
                printf("Tu3\n");
                flag4 = 1;
            }
            if(flag4 == 0){
                flag4 = 2;
            }
        }
        if(flag4 == 2 && wybrane_x-1 < x && wybrane_y-1 < y){
            flag3 =1;
        }
        else{
            printf("Bledny ruch\n");
        }
    }
    printf("\033[2J");
    generuj_miny(x,y,wybrane_x-1,wybrane_y-1,ilosc,plansza);
    ustaw_wartosci(x,y,plansza);
    int dodaj = 0;
    if(plansza[wybrane_x-1][wybrane_y-1].wartosc == 0){
        odkrywanie(x,y,&dodaj,wybrane_x-1,wybrane_y-1,plansza);
        odkryte+=dodaj;
    }
    else{
        plansza[wybrane_x-1][wybrane_y-1].czy_odkryte = 1;
        odkryte++;
        plansza[wybrane_x-1][wybrane_y-1].odkrycie = plansza[wybrane_x-1][wybrane_y-1].wartosc;
    }
    pisz_plansze(x,y,odkryte*poziom,plansza);
    if(odkryte == x*y-ilosc){
        printf("Wygrales/as\n");
    }
    while(flag == 0){
        flag2=0;
        printf("\033[2J");
        pisz_plansze(x,y,odkryte*poziom,plansza);
        while(flag2==0){
            printf("Twoj ruch:\n");
            flag3 = 0;
            while(flag3 == 0){
                gets(wpis1);
                flag4 = 0;
                wybrane_x = 0;
                wybrane_y = 0;
                while(flag4 == 0){
                    c = 2;
                    if(wpis1[0] == 'r' || wpis1[0] == 'f'){
                        rodzaj = wpis1[0];
                        if(wpis1[1] == ' '){
                            while(wpis1[c] != ' ' && wpis1[c] != 0){
                                if((wpis1[c]-48)>=0 && (wpis1[c]-48)<10){
                                    wybrane_x = wybrane_x*10 + (wpis1[c]-48);
                                    c++;
                                }
                                else{
                                    c++;
                                    flag4 = 1;
                                }
                            }
                            c++;
                            while(wpis1[c] != 0){
                                if((wpis1[c]-48)>=0 && (wpis1[c]-48)<10){
                                    wybrane_y = wybrane_y*10 + (wpis1[c]-48);
                                    c++;
                                    }
                                else{
                                    c++;
                                    flag4 = 1;
                                }
                            }
                        }
                        else{
                            flag4 = 1;
                        }
                    }
                    else{
                        flag4 = 1;
                    }
                    if(flag4 == 0){
                        flag4 = 2;
                    }
                }
                if(flag4 == 2 && wybrane_x-1 < x && wybrane_y-1 < y){
                    flag3 =1;
                }
                else{
                    printf("Bledny ruch\n");
                }
            }
            if(wybrane_x >= 0 && wybrane_x <= y && wybrane_y >= 0 && wybrane_y <= x){
                if(rodzaj == 'r' && (plansza[wybrane_x-1][wybrane_y-1].czy_odkryte == 0 || (plansza[wybrane_x-1][wybrane_y-1].czy_odkryte == 1 && plansza[wybrane_x-1][wybrane_y-1].odkrycie == -2 ))){
                    if(plansza[wybrane_x-1][wybrane_y-1].wartosc != -1){
                        if(plansza[wybrane_x-1][wybrane_y-1].wartosc != 0){
                            plansza[wybrane_x-1][wybrane_y-1].czy_odkryte = 1;
                            odkryte++;
                            plansza[wybrane_x-1][wybrane_y-1].odkrycie = plansza[wybrane_x-1][wybrane_y-1].wartosc;
                            flag2=1;
                            printf("\033[2J");
             	        }
                        else{
                            dodaj = 0;
                            odkrywanie(x,y,&dodaj,wybrane_x-1,wybrane_y-1,plansza);
                            odkryte+=dodaj;
                            flag2=1;
                            printf("\033[2J");
                        }
                    }
                    else{
                        printf("\033[2J");
                        printf("Przegrales/as\nTwoj wynik: %d\n",odkryte*poziom);
                        wynik_t rezultat = {nazwa,odkryte*poziom};
                        wpisanie_do_pliku(rezultat);
                        flag2=1;
                        flag=1;
                    }
                }    
                else if(rodzaj == 'f'){
                    if(plansza[wybrane_x-1][wybrane_y-1].czy_odkryte == 0){
                        plansza[wybrane_x-1][wybrane_y-1].czy_odkryte = 1;
                        plansza[wybrane_x-1][wybrane_y-1].odkrycie = -2;
                        flag2=1;
                        printf("\033[2J");
                    }
                    else{
                        if(plansza[wybrane_x-1][wybrane_y-1].odkrycie == -2){
                            plansza[wybrane_x-1][wybrane_y-1].czy_odkryte = 0;
                            plansza[wybrane_x-1][wybrane_y-1].odkrycie = 0;
                            flag2=1;
                            printf("\033[2J");
                        }
                    }
                }
                else{
                    printf("Nie mozesz wykonac tego ruchu\n");
                }
            }
            else{
                printf("Bledny ruch\n");
            }
        }
        if(odkryte == x*y-ilosc){
            flag = 1;
            printf("\033[2J");
            printf("Wygrales/as\nTwoj wynik: %d\n",odkryte*poziom);
            wynik_t rezultat = {nazwa,odkryte*poziom};
            wpisanie_do_pliku(rezultat);
        }
    }
    return odkryte*poziom;
}
