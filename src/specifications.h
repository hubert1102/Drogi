/** @file
 * Biblioteka implementująca podstawowe struktury i operacje na miastach
 * i drogach.
 */


#ifndef DROGI_SPECIFICATIONS_H
#define DROGI_SPECIFICATIONS_H

#include <stdbool.h>
#include <stddef.h>

struct City;
/** @brief Typ danych przechowujący inforamcje o mieście.
 * @var City::city_id - Numer Id miasta.
 * @var City::city_name - Wskaźnik na napis będący nazwą miasta.
 * @var City::road_list - Wskaźnik na element listy zawierającej
 * odcinki wychodzące z tego miasta.
 */
typedef struct City City;

struct Road;
/** @brief Typ danych przechowujący dane o odcinku drogi
 * @var Road::length - Długość odcinka drogi.
 * @var Road::repair - Ostatni czas remontu lub budowy odcinka drogi.
 * @var Road::city1  - Miasto, z którego wychodzi ten odcinek.
 * @bar Road::city2  - Drugie miasto, którego wychodzi ten odcinek.
 */
typedef struct Road Road;

struct road_list;
/** @brief Typ danych przechowujący listę odcinków
 * drogi wychodzących z jednego miasta.
 * @var road_list::road - Wskaźnik na odcinek drogi.
 * @var road_list::next_road - Wskaźnik na następny element listy.
 * @var road_list::prev_road - Wskaźnik na poprzedni element listy.
 */
typedef struct road_list road_list;


struct Road {
    unsigned length;
    int repairYear;
    City* city1;
    City* city2;
};

struct road_list {
    Road* road;
    road_list* next_road;
    road_list* prev_road;
};

struct City {
    unsigned city_id;
    char* city_name;
    road_list* roads;
};

/** @brief Zwraca liczbę cyfr liczby @p d, dodaje jeden jeżeli jest ujemna.
 *
 * @param [in] d     - Liczba całkowita.
 * @return  Liczba cyfr @p d, powiększona o jeden, jeżeli jest ujemna.
 */
size_t int_length(int d);

/** @brief Zamienia liczbę całkowitą na napis.
 *  Alokuje pamięc na napis reprezentujący liczbę @p d.
 * @param [in] d     - Liczba całkowita.
 * @return Napis reprezentujący @p d. Zwraca NULL jeżeli alokacja się
 * nie powiodła.
 */
char* int_to_string(int d);

/** @brief Zwraca wskaźnik na odcinek drogi pomiędzy dwoma miastami @p city1 i @p city2..
 * @param [in] city1     - Wskaźnik na strukturę reprezentującą miasto.
 * @param [in] city2     - Wskaźnik na strukturę reprezentującą miasto.
 * @return Zwraca wskaźnik na odcinek drogi pomiędzy p city1 i @p city2. Jeżeli nie
 * istnieje taki odcinek, to zwraca @p NULL.
 */
Road* getRoad(City* city1, City* city2);

/** @brief Znajduje miejsce w liście, które trzyma odcinek drogi pomiędzy @p city1
 * a @p city2.
 *
 * @param [in] city1    - Wskaźnik na strukturę reprezentującą miasto.
 * @param [in] city2    - Wskaźnik na strukturę reprezentującą miasto.
 * @return Zwraca miejsce w liście odcinków wychodzących z @p city1,
 * które zawera odcinek drogi pomiędzy @p city1 a @p city2.
 */
road_list* get_road_list(City* city1, City* city2);

/** @brief Usuwa odcinek drogi pomiędzy @p c1 i @p c2.
 *  Usuwa odcinek drogi pomiędzu @p c1 i @p c2 z list wychodzących odcinków dróg
 *  obu miast. Nic nie robi, jeżeli nie istnieje taki odcinek.
 * @param [in] city1    - Wskaźnik na strukturę reprezentującą miasto.
 * @param [in] city2    - Wskaźnik na strukturę reprezentującą miasto.
 * @return Zwraca wskaźnik na usunięty odcinek drogi, lub NULL, jeżeli ten odcinek
 * nie istniał.
 */
Road* remove_road(City* c1, City* c2);

/**@brief Sprawdza, czy istnieje odcinek drogi pomiędzy miastami @p city1 i @p city2.
 *
 * @param [in] city1    - Wskaźnik na strukturę reprezentującą miasto.
 * @param [in] city2    - Wskaźnik na strukturę reprezentującą miasto.
 * @return Zwraca @p true, jeżeli istnieje odcinek drogi łączącej oba miasta,
 * @p false w przeciwnym wypadku.
 */
bool areConnected(City* city1, City* city2);

/** @Brief Tworzy nowy element typu @c road_list, zawierający odcienk
 * drogi @p road.
 * @param [in] road     - Odcinek drogi.
 * @return Zwraca wskaźnik na nowo utworzony element. Jeżeli alokacja
 * pamięci się nie powiodła, to zwraca NULL.
 */
road_list* newRoadList(Road* road);

/** @brief Usuwa z pamięci listę odcinków drogi.
 * Usuwa i zwalnia pamięć z całej listy odcinków dróg oraz samych
 * odcinków dróg zawartych w tej liście.
 * @param [in, out] rl  - Lista odcinków dróg.
 */
void free_road_list(road_list* rl);

/** @brief Tworzy struktuę opisującą nowe miasto.
 *
 * @param [in] city     - Nazwa miasta.
 * @param [in] city_id  - Id miasta.
 * @return Zwraca @p true jeżeli udało się stworzyć miasto. Zwraca @p false
 * jeżeli nie udało się zaalokować pamięci.
 */
City* newCity(const char* city, unsigned city_id);

/** @brief Dodaje odcinek drogi pomiędzy miastami @p city1 i @ city2 o długości
 * @p length i roku budowy @p repairYear.
 * @param [in] city1        - Wskaźnik na strukturę reprezentującą miasto.
 * @param [in] city1        - Wskaźnik na strukturę reprezentującą miasto.
 * @param [in] length       - Długość odcinka drogi.
 * @param [in] repairYear   - Rok budowy odcinka drogi.
 * @return Zwraca @p true jeżeli udało się dodać i stworzyć odcinek. Zwraca @p false
 * jeżeli nie udało się zaalokować pamięci.
 */
bool newRoad(City* city1, City* city2, unsigned length, int repairYear);

/** @Brief Zmienia czas remontu odcinka drogi pomiędzy @p city1 a @p city2
 * na @p repairYear.
 *
 * @param [in] city1        - Wskaźnik na strukturę reprezentującą miasto.
 * @param [in] city2        - Wskaźnik na strukturę reprezentującą miasto.
 * @param [in] repairYear   - Rok remontu odcinka drogi.
 */
void changeRepairYear(City* city1, City* city2, int repairYear);

#endif //DROGI_SPECIFICATIONS_H
