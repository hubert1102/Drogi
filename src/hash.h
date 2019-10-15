/** @file
 * Biblioteka definiująca haszmapęm której kluczami są nazwy miast,
 * a wartościami wskaźniki na struktury reprezentujące dane miasta.
 */
#ifndef DROGI_HASH_H
#define DROGI_HASH_H

#include "list.h"

#define P 10007

#define N_OF_LETTERS 300

/** @brief Typ danych przechowujący hashmapę.
 * Kluczem są nazwy miast, a wartościami struktury miast odpowiadające
 * tym miastom.
 */
typedef struct hashtable {
    list* tab[P]; /**< Tablica zawierająca listy oblicznonych haszy.*/
} hashtable;

/** @brief Tworzy nową haszmapę.
 *  @return Zwraca wskaźnik na haszmapę lub NULL, gdy nie udało się
 *  zaaklokować pamięci.
 */
hashtable* new_hashtable();

/** @brief Liczy hasza dla podaego słowa.
 * Liczy hasza słowa @p s dla bazy haszowania @p p.
 * @param [in] s        - wskaźnik na słowo;
 * @param [in] p        - liczba całkowita będąca bazą haszowania.
 * @return Zwraca hasza słowa @p s w bazie @p p.
 */
int hash_word(const char* s, int p);

/** @brief Dodaje wartość do tablicy.
 * Dodaje wartość @p city do haszmapy @p tab z kluczem @p hash.
 * @param [in, out] tab      - wskaźnik na haszmapę;
 * @param [in] hash          - liczba będąca kluczem @p city;
 * @param [in] city          - wskaźnik na strukturę reprezentującą miasto.
 * @return Zwraca @p true jeżeli wartość została dodana do haszmapy. Zwraca
 * @p false w przeciwnym wypadku: nie udało się zaalokować pamięci.
 */
bool add_hash(hashtable* tab, int hash, City* city);

/** @brief Dodaje miasto do haszmapy.
 * @param[in, out] tab       - wskaźnik na haszmapę;
 * @param[in] s              - wskaźnik na napis reprezentujący nazwę miasta;
 * @param[in] city           - wskaźnik na strukturę reprezentującą miasto.
 *  @return Zwraca @p true jeżeli miasto zostało dodane do haszmapy lub
 *  @p false jeżeli nie udało się zaalokować pamięci.
 */
bool add_city(hashtable* tab, const char* s, City* city);

/** @brief Znajduje wartość w haszmapie dla podanego klucza..
 * @param [in] tab            - wskaźnik na haszmapę;
 * @param [in] s              - wskaźnik na napis reprezentujący nazwę miasta.
 * @return Jeżeli miasto zostało wcześniej dodane do haszmapy to zwraca
 * wskaźnik na strukturę reprezentującą miasto o podanej nazwie. Zwraca
 * @p NULL w przeciwnym wypadku.
 */
City* get_city_id(hashtable* tab, const char* s);
/** @brief Usuwa haszmapę.
 *  Zwalnia z pamięci wszystkie wartości i klucze zawarte w haszmapie.
 *  Nie robi nic jeżeli @p tab miało wartość @p NULL.
 * @param [in]tab       - wskaźnik na haszmapę;
 */
void free_cities(hashtable* tab);

#endif //DROGI_HASH_H
