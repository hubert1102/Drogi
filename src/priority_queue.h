/** @file
 * Biblioteka implementująca kolejkę priorytetową i operacje na niej.
 */

#ifndef DROGI_PRIORITY_H
#define DROGI_PRIORITY_H

#include <stdlib.h>
#include <stdio.h>
#include "specifications.h"
/** @brief Typ danych wyznaczający priorytet danej drogi.
 */
typedef struct path_priority {
    int last_repair; ///< Rok remontu lub budowy najstarszego odcinka drogi
    unsigned total_length; ///< Długość całej drogi
    size_t city_id; ///< Numer Id ostatniego miasta na drodze
    City* city; ///< Wskaźnik na strukturę reprezentującą ostatnie miasto
    ///< na drodze
} path_priority;

/** @brief Typ danych reprezentujący kolejkę priorytetową.
 * Typ danych reprezentującą kolejkę priorytetową. Elementy kolejki są
 * typu @c path_priority.
 */
typedef struct priority_queue {
    size_t size; ///< Maksymalna pojemność kolejki
    path_priority* tree; ///< Struktura reprezentująca kolejkę priorytetową
} priority_queue;

/** @brief Porównuje priorytet dwóch dróg.
 * Porównuje dwie drogi pod względem całkowitej długości. Jeżeli są \
 * rownej długości, to porónuje po najstarszym odcinku drogi w obu drogach.
 * @param [in] pp1      - Struktura opisująca drogę.
 * @param [in] pp2      - Struktura opisująca drogę.
 * @return Zwraca @p 0 jeżeli drogi @p pp1 i @p pp2 są równej długości i ich
 * najstarsze odcinki są z tego samego roku. Zwraca wartość dodatnią, jeżeli
 * droga reprezentowana  prez @p pp1 jest krótsza od tej w @p pp2 lub, w przypadku
 * równych długości, najstarszy odcinek w @p pp1 jest młodszy niż w @p pp2.
 * W pozostałych przypadkach zwraca liczbę ujemną.
 */
int compare_priority(path_priority pp1, path_priority pp2);

/** @brief usuwa kolejkę priorytetową.
 * Usuwa kolejkę priorytetową @p q i zwalnia zaalokowaną przez nią pamięć.
 * Ustawia wartość @p q na @p NULL.
 *
 * @param [in, out] q   - Wskaźnik na kolejkę priorytetową.
 */
void free_priority_queue(priority_queue* q);

/** @brief Struktura oznaczjąca drogę nieprzechodzącą przez żadne miasto.
 * Struktura opisująca drogę nieprzechodzącą przez żadne miasto. Ma priorytet
 * niższy od dowolnej niepustej drogi.
 * @return Zwraca struktuę oznaczjącą drogę nieprzechodzącą przez żadne miasto.
 */
path_priority empty_route();
/** @brief Znajduje w kolejce priorytetowej strukturę
 * reprezentującą drogę do danego miasta.
 * Znajduje w kolejce  @p q strukturę reprezentującą optymalną
 * drogę do miasta @p city.
 *
 * @param [in] q        - Wskaźnik na kolejkę priorytetową.
 * @param [in] city     - Wskaźnik na strukturę reprezentującą miasto.
 * @return Zwraca strukturę reprezentującą optymalną
 * drogę do miasta @p city. Jeżeli taka struktura nie istnieje to zwraca
 * strukturę oznaczającą drogę nieprzechodzącą przez żadne miasto.
 */
path_priority get_city_priority(priority_queue* q, City* city);

/** Sprawdza czy kolejka jest pusta.
 *  Sprawdza czy kolejka priorytetowa @p q jest pusta.
 * @param [in] q        - Wskaźnik na kolejkę priorytetową;
 * @return Zwraca @p true jeżeli kolejka jest pusta,
 * @p false w przeciwnym wypadku.
 */
bool is_empty(priority_queue* q);

/** @brief Tworzy struktuę reprezentującą drogę do danego miasta.
 *  Tworzy strukturę reprezentującą drogę do miasta @p city. Jest ona długości
 *  @p length i najstarszy odcinek drogi w niech pchodzi z roku @p repair.
 * @param city          - Wskaźnik na strukturę reprezentującą miasto;
 * @param repair        - Rok budowy lub remontu najstarszego odcinka drogi.
 * @param length        - Długość drogi w km.
 * @return Zwraca struktuę reprezentującą drogę do @p city o całkowitej długości
 * @p length i zwierającą najstarszy odcinek długości @p repair.
 */
path_priority make_path(City *city, int repair, unsigned length);

/** @brief Tworzy kolejkę priorytetową.
 * Tworzy kolejkę priorytetową, która może pomieścić @p size elementów.
 * @param [in] size     - Maksymalny rozmiar kolejki priorytetowej.
 * @return Zwraca wskaźnik na kolejkę priorytetową. Zwraca NULL jeżeli nie
 * uda się zaalokować pamięci.
 */
priority_queue* make_priority_queue(size_t size);

/** @brief Dodaje element do kolejki.
 *  Dodaje @p route do kolejki @p q. Jeżeli w @p q istniała już droga o mniejszym
 *  priorytecie do tego samego miasta, do którego prowadzi @p route, to ją zastępuje.
 *  Jeżeli w @p q istniała już droga o większym priorytecie do tego samego miasta,
 *  do którego prowadzi @p route, to nic nie robi.
 * @param [in, out]         - Wskaźnik na kolejkę priorytetową.
 * @param route             - Struktura opisująca drogę.
 */
void add(priority_queue* q, path_priority route);

/** @brief Pobiera i usuwa element o największym priorytecie z kolejki.
 * Pobiera element o największym priorytecie z kolejki @p q i go z niej
 * usuwa.
 * @param [in, out] q       - Wskaźnik na kolejkę priorytetową.
 * @return Zwraca strukturę opisującą drogę o największym priorytecie.
 */
path_priority pop(priority_queue* q);

#endif