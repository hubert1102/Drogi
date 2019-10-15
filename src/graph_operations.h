/** @file
 * Biblioteka definująca opreacje szukania optymalnej drogi w grafie.
 */

#ifndef DROGI_GRAPH_H
#define DROGI_GRAPH_H

#include "list.h"
#include "hash.h"
#include "specifications.h"
#include "priority_queue.h"
/** @brief Znajduje optmalną drogę pomiędzy dwoma miastami.
 *  Znajduje optymalną drogę pomiędzi miastami @p c_pocz i @p c_kon.
 *  Optymalna droga nie może przechodzić przez miasta zawarte w @p route.
 *  Wyznacza w @p previous_cities dla każdego miasta miasto poprzedzajace je w
 *  najlepszej drodze do niego z miasta początkowego. Dla każdego miasta
 *  @p only_one_path trzyma informację czy do danego miasta istnieje tylko
 *  jedna optymalna droga z miasta początkowego. Jeżeli nie uda się zaalokować
 *  pamięci, to wszysktie dane pozostaną bez zmian.
 * @param [in] c_pocz       - Wskaźnik na strukturę reprezentującą
 * miasto początkowe;
 * @param [in] c_kon        - Wskaźnik na strukturę reprezentującą
 * miasto końcowe;
 * @param [in] n_of_cities  - Maksymalna liczba miast;
 * @param [in] route        - Droga, przez którą nie może przechodzić
 * szukana droga;
 * @param [in, out] previous_city- Tablica wypełniona @p NULL,
 * która będzie wypełniona w trakcie działania funkcji;
 * @param [in, out] only_one_path- Tablica zawierająca tylko wartości @p false,
 * która będzie wypełniona w trakcie działania funkcji
 */
void shortest_path(City *c_pocz, City *c_kon, size_t n_of_cities,
                   list *route, City **previous_city, bool *only_one_path);

/** @brief Znajduje optymalną drogę pomiędzy dwoma miastami.
 * Znajduje optymalną drogę pomiędzy @p city1 i @p city2 nieprzechodzącą
 * przez żadne miasto z @p route. Zapisuję tą drogę jako ciąg miast do
 * @p l.
 * @param [in, out] l             - Wskaźnik na listę dwukierunkową zawierającą
 * miasto początkowe;
 * @param [in] route         - Droga przedstawiona jako ciąg miast;
 * @param [in] city1         - Wskaźnik na strukturę reprezentującą
 * miasto początkowe;
 * @param [in] city2         - Wskaźnik na strukturę reprezentującą
 * miasto końcowe;
 * @param [in] n_of_cities   - Maksymalna ilość miast.
 * @return Zwraca @p true jeżeli usało się jednoznacznie znaleźć optymalną drogę.
 * Zwraca false w przeciwnym wypadku lub gdy nie uda się zaalokować pamięci.
 */
bool find_path(list* l, list* route, City* city1, City* city2,
               size_t n_of_cities);

#endif //DROGI_GRAPH_H
