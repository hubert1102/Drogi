/** @file
 * Biblioteka definiująca listę dwukierunkową i operacje na niej.
 */
#ifndef DROGI_LIST_H
#define DROGI_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include "specifications.h"

struct list;


/**
 * @brief Typ danych reprezentujący element listy dwukierunkowej.
 */
typedef struct list {
    City* city; /**< wskaźnik na strukturę reprezentującą miasto.*/
    struct list* next; /**< Wskaźnik na następny element listy dwukierunkowej*/
    struct list* prev; /**< Wskaźnik na poprzedni element listy dwukierunkowej*/
} list;



/** @brief Tworzy nową listę dwukierunkową.
 *
 * Tworzy nową lisę dwukierunkową, której pierwszym elementem jest
 * wskaźnik na miasto.
 * @param [in] city     - wskaźnik na miasto.
 * @return Wskaźnik na utworzoną jednoelementową strukturę lub NULL,
 * gdy nie udało się zaalokować pamięci.
 */
list* new_list(City* city);

/** @brief Zwraca wskaźnik na pierwszy element listy.
 *
 * @param [in, out] l     - wskaźnik na listę.
 * @return Wskaźnik na pierwszy element listy lub NULL,
 * gdy lista nie zawierała żadnego elementu.
 */
list* first_elem(list* l);
/** @brief Zwraca wskaźnik na ostatni element listy
 *
 * @Param [in, out] l     - wskaźnik na listę.
 * @return Wskaźnik na ostatni element listy lub NULL,
 * gdy lista nie zawierała żadnego elementu.
 */
list* last_elem(list* l);

/** @brief Złącza dwie listy.
 * Jeżeli @p l jest ostatnim elementem listy dwukierunkowej, to dołącza
 * na jej koniec listę zawierającą @p lx. Jeżeli @p l nie jest ostatnim elementem listy,
 * to lista zawierająca @p lx zostaje dołączona pomiędzy @p l a następnym elementem
 * tej listy.
 *
 * @param [in, out] l     - wskaźnik na element listy dwukierunkowej;
 * @param [in] lx         - wskaźnik na element listy dwukierunkowej.
 */
void add_list(list* l, list* lx);

/** @brief Dodaje wskaźnik na miasto do listy.
 * Dodaje wskaźnik na strukturę przechowującą miasto do
 * listy zawierającej @p l. Wskaźnik zostaje dodany bezpośrednio za
 * @p l.
 * @param [in, out] l     - wskaźnik na element listy dwukierunkowej;
 * @param [in] city       - wskaźnik na strukturę reprezentującą miasto.
 * @return Zwraca @p true jeśli element został dodany. Zwraca @p false
 * jeżeli nie udało się zaalokować pamięci.
 */
bool add_elem(list* l, City* city);

/** @brief Dodaje wskaźnik na miasto na początek listy.
 * Dodaje wskaźnik na strukturę przechowującą miasto na początek
 * listy zawierającej @p l.
 * @param [in, out] l     - wskaźnik na element listy dwukierunkowej;
 * @param [in] city        - wskaźnik na strukturę reprezentującą miasto.
 * @return Zwraca @p true jeśli element został dodany. Zwraca @p false
 * jeżeli nie udało się zaalokować pamięci.
 */
bool add_to_beginning(list* l, City* city);

/** @brief Znajduje wskaźnik na strukturę reprezentującą miasto w liście.
 * @param [in] l     - wskaźnik na element listy dwukierunkowej.
 * @param [in] city        - wskaźnik na strukturę reprezentującą miasto.
 * @return Zwraca wskaźnik na element w liście zawierającej l, który
 * zawiera wskaźnik na strukturę reprezentującą miasto. Zwraca @p NULL
 * jeżeli lista nie zawiera takiego elementu.
 */
list* find_city(list* l, City* c);
/** @brief Spawdza czy lista zawiera wskaźnik na strukturę reprezentującą
 * miasto.
 * @param [in] l     - wskaźnik na element listy dwukierunkowej;
 * @param [in] city  - wskaźnik na strukturę reprezentującą miasto.
 * @return Zwraca @p true, jeżeli lista zawiera podany wskaźnik, @p false w
 * przeciwnym wypadku.
 */
bool exists(list* l, City* c);

/** @brief Porównuje dwie drogi do siebie.
 * Porównuje dwa ciągi kolejnych miast do siebie pod względem długości oraz
 * lat ostatnich remontów. Każde dwa kolejne elementy listy są połączone drogą.
 * @param[in] path1        - wskaźnik na element listy dwukierunkowej;
 * @param[in] path2        - wskaźnik na element listy dwukierunkowej.
 * @return Zwraca @p 0 jeżeli drogi są tej samej długości i najstarszy
 * odcinek jest w obu równie stary. Zwraca liczbę dodatnią, jeżeli pierwsza droga
 * jest krótsza od drugiej lub, w przypadku równych długości, najstarszy odcinek drogi
 * zawarty w pierwszej drodze jest młodszy od najstarszego odcinka drogi zawartego w
 * drugiej drodze. Zwraca liczę ujemną wprzeciwnym wypaku.
 */
int compare_paths(list* path1, list* path2);

/** @brief Uzupełnia jedną drogę o dodatkowe odcinki.
 * Uzupełnia drogę route o drogę zawartą w @p l. Pewne dwa kolejne miasta w
 * route są odpowiednio pierwszym i ostatnim elementem listy @p l i to
 * w ich miejsce wstawiana jest lista @p l.
 * @param [in, out] route   - wskaźnik na element listy dwukierunkowej;
 * @param [in] l            - wskaźnik na element listy dwukierunkowej.
 */
void fill_gap(list* route, list* l);

/** @brief Znajduje długośc drogi.
 * Znajduje długośc drogi reprezentowanej jako ciąg kolejnych jej miast w
 * liście @p route.
 * są odpowiednio pierwszym i ostatnim elementem listy @p l i to w ich miejsce
 * wstawiana jest lista @p l.
 * @param [in, out] route   - wskaźnik na element listy dwukierunkowej;
 * @return Zwraca długość drogi przedstawionej w @p route. Zwraca @p 0 jeżeli
 * taka droga nie istnieje.
 */
unsigned route_length(list* l);

/** @brief Znajduje najstarszy odcinek drogi w drodze.
 * Znajduje najstarszy odcinek drogi w drodze reprezentowanej jako ciąg
 * kolejnych miast, przez które ta droga przechodzi.
 * są odpowiednio pierwszym i ostatnim elementem listy @p l i to w ich miejsce
 * wstawiana jest lista @p l.
 * @param [in, out] route   - wskaźnik na element listy dwukierunkowej;
 * @return Zwraca rok ostatniego remontu lub budowy najstarszego odcinka drogi
 * przedstawionej w @p route. Zwraca @p 0 jeżeli taka droga nie istnieje.
 */
int route_repair(list* l);

/** @brief Wydłuża jedną drogę o dodatkowe odcinki.
 * Wydłuża drogę route o drogę extension. Droga extenion zostaje doklejona
 * na koniec listy l.
 * wstawiana jest lista l.
 * @param [in, out] route   - wskaźnik na element listy dwukierunkowej;
 * @param [in] extension    - wskaźnik na element listy dwukierunkowej.
 * @return Zwraca wskaźnik na wydłużoną listę.
 */
list* extend_path(list* route, list* extension);
/** @brief Sprawdza czy droga zawiera odcinek drogi.
 * @param [in] route            - wskaźnik na element listy dwukierunkowej;
 * @param [in] city1            - wskaźnik na strukturę reprezentującą miasto;
 * @param [in] city2            - wskaźnik na strukturę reprezentującą miasto.
 * @return Zwraca @p true, jeżeli droga zawiera odcinek drogi, @p false w
 * przeciwnym wypadku.
 */
bool containsRoad(list* route, City* city1, City* city2);

/** @brief Dodaje napis na podane miejsce do tablicy.
 * Wstawia napis @p string w napis @p description w taki sposób, że słowo
 * @p string zaczyna się w słowie @ description na indeksie @p index.
 * @param [in, out] description   - wskaźnik na tworzący się
 * napis opisu drogi krajowej;
 * @param [in] string             - wskaźnik na niepusty napis.
 * @param [in] index              - wskaźnik na liczbę całkowitą
 * z zakresu @p description.
 */
void add_at_index(char* description, const char* string, size_t *index);

/** @brief Zwraca liczbę całkowitą liczbę znaków potrzebnych do
 * opisania drogi krajowej.
 * @param [in] route   - wskaźnik na listę reprezentującą drogę.
 * @return Zwraca nieujemną liczbę całkowitą, która jest dokładną ilością znaków,
 * jaką będzie zawierać opis drogi przedstawionej w @p route.
 */
size_t describeRoute_length(list* route);

/** @brief Zwraca wskaźnik na napis opisujący drogę krajową.
 *
 * Zwraca wskaźnik na napis, który zawiera informacje o drodze krajowej. Alokuje
 * pamięć na ten napis. Informacje są podawane w tej samej kolejności, co miasta
 * w route.
 * Informacje wypisywane są w formacie:
 * numer drogi krajowej;nazwa miasta;długość odcinka drogi;rok budowy lub
 * ostatniego remontu;nazwa miasta;długość odcinka drogi;rok budowy lub
 * ostatniego remontu;nazwa miasta;…;nazwa miasta.
 * @param [in] route   - wskaźnik na element listy dwukierunkowej;
 * @param [in] routeId - nieujemna liczba reprezentująca numer drogi krajowej.
 * @return Zwraca wskaźnik na napis opisujący drogę krajową.
 */
char* describeRoute(list* route, unsigned routeId);

/** @brief Usuwa listę i zwalnia zaalokowaną dla niej pamięć.
 * Nie robi nic, jeżeli lista była już pusta.
 * @param [in] list   - wskaźnik na element listy dwukierunkowej.
 */
void free_list(list* l);

/** @Brief Usuwa i zwalnia z pamięci tablicę list dwukierunkowych, ustawia
 * @p l na @p NULL.
 *
 * @param [in, out] l   - tablica list dwukierunkowych.
 */
void free_routes(list** l);
#endif //DROGI_LIST_H
