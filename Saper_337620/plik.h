#define BUFSIZE 256

typedef struct wynik{
    char* nazwa;//nazwa gracza
    int punkty;//punkty gracza
}wynik_t;

int compare(const void* a, const void* b);

void wpisanie_do_pliku(wynik_t rezultat);
