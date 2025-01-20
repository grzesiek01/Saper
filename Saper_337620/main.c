#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include<time.h>
#include "plik.h"
#include "plansza.h"

int main(int argc, char **argv){
    int poziom = 0;
    int x = 0;
    int y = 0;
    int ilosc_min = 0;
    char nazwa[20];
    char tryb[1];
    char rozmiar[8];
    printf("Witaj przyjacielu!\nPodaj swoja nazwe(max 20 znakow bez spacji):\n");
    int flag = 0;
    int c = 0;
    int flag2 = 0;
    int flag3 = 0;
    int flag4 = 0;
    flag = 0;
    while(flag == 0){//sprawdzenie czy nazwa podana przez uzytkownika jest poprawna
        gets(nazwa);
        flag2 = 0;
        c = 0;
        while(nazwa[c] != 0){
            if(nazwa[c] == ' '){
                flag2 = 1;
            }
            c++;
        }
        if(flag2 == 0){
            flag = 1;
        }
        else{
            printf("Bledna nazwa\n");
        }
    }
    printf("Wybierz poziom trudnosci:\n");
    printf("1 - latwy (9x9 10 min)\n");
    printf("2 - sredni (16x16 40 min)\n");
    printf("3 - trudny (16x30 99 min)\n");
    printf("4 - dowolny (Twoj wynik nie bedzie punktowany)\n");
    flag = 0;
    while(flag == 0){//sprawdzenie czy poziom jest dobry
        flag3 = 0;
        while(flag3 == 0){
            gets(tryb);
            if(tryb[0] == 49 || tryb[0] == 50 || tryb[0] == 51 || tryb[0] == 52){
                poziom = tryb[0] - 48;
                flag3 = 1;
            }
            else{
                printf("Bledny poziom\n");
            }   
        }
        switch(poziom){//ustawienie poziomu trudnosci
            case 1:
                x = 9;
                y = 9;
                ilosc_min = 10;
                flag = 1;
                break;
            case 2:
                x = 16;
                y = 16;
                ilosc_min = 40;
                flag = 1;
                break;
            case 3:
                x = 16;
                y = 30;
                ilosc_min = 99;
                flag = 1;
                break;
            case 4:
                flag2 = 0;
                while(flag2 == 0){ 
                    printf("Podaj wymiary i ilosc min (uwaga ilosc min nie moze przekraczac polowy pol)\n");
                    flag3 = 0;
                    while(flag3 == 0){//sprawdzenie czy wymiary sa dobre
                        gets(rozmiar);
                        c = 0;
                        flag4 = 0;
                        x = 0;
                        y = 0;
                        ilosc_min = 0; 
                        while(flag4 == 0){
                            while(rozmiar[c] != ' ' && rozmiar[c] != 0){
                                if((rozmiar[c]-48)>=0 && (rozmiar[c]-48)<10){
                                    x = x*10 + rozmiar[c]-48;
                                    c++;
                                }
                                else{
                                    c++;
                                    flag4 = 1;
                                }
                            }
                            c++;
                            while(rozmiar[c] != ' ' && rozmiar[c] != 0){
                                if((rozmiar[c]-48)>=0 && (rozmiar[c]-48)<10){
                                    y = y*10 + rozmiar[c]-48;
                                    c++;
                                }
                                else{
                                    c++;
                                    flag4 = 1;
                                }
                            }
                            c++;
                            while(rozmiar[c] != 0){
                                if((rozmiar[c]-48)>=0 && (rozmiar[c]-48)<10){
                                    ilosc_min = ilosc_min*10 + rozmiar[c]-48;
                                    c++;
                                }
                                else{
                                    c++;
                                    flag4 = 1;
                                }
                            }
                            if(flag4 == 0){
                                flag4 = 2;
                            }
                        }
                        if(flag4 == 2){
                            flag3 = 1;
                        }
                        else{
                            printf("Bledne dane\n");
                        }
                    }
                    if(ilosc_min > x*y/2 || x<3 || y<3 || ilosc_min<1 || x>99 || y>99){
                        printf("Nie mozna utworzyc takiej planszy\n");
                    }
                    else{
                        poziom = 0;
                        flag = 1; 
                        flag2 = 1;
                    }
                }
                break;
            default:
                printf("Nieprawidowe wprowadzenie\n"); 
                break;
        }
    }
    pole_t **plansza = genruj_plansze(x,y);//generowanie planszy
    graj(x,y,ilosc_min,poziom,nazwa,plansza);//gra
    return 0;
}
