typedef struct pole{
    int czy_mina;//wartosc 0 jesli na polu nie ma miny, wartosc 1 jesli jest
    int czy_odkryte;//wartosc 0 jesli pole nie zostalo odkryte przez gracza
    int wartosc;//wartosc -1 jesli na polu jest mina lub ilosc min dookola
    int odkrycie;//wartosc -2 jesli wyswietlona ma byc flaga lub wartosc liczbowa min dookola
}pole_t;

pole_t **genruj_plansze(int x, int y);

pole_t **generuj_miny(int x, int y, int x_czyste, int y_czyste, int ilosc, pole_t **plansza);

pole_t **ustaw_wartosci(int x, int y, pole_t **plansza);

void pisz_plansze(int x, int y, int wynik, pole_t **plansza);

void odkrywanie(int x, int y, int* odkrycia, int x_podane, int y_podane, pole_t **plansza);

int graj(int x, int y, int ilosc, int poziom, char* nazwa, pole_t **plansza);
