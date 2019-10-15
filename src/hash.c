//
// Created by Hubert on 13.04.2019.
//

#include "hash.h"
#include "specifications.h"
#include <stdio.h>
#include <string.h>
hashtable* new_hashtable() {
    hashtable* tab = (hashtable*)malloc(sizeof(hashtable));
    if (!tab)
        return NULL;

    for (int i = 0; i < P; i++)
        tab->tab[i] = NULL;

    return tab;
}


int hash_word(const char* s, int p) {
    int w = 0;
    int x = 1;

    for (int i = 0; s[i]; i++) {
        w += ((s[i] + N_OF_LETTERS) * x) % p;
        w %= p;

        x *= N_OF_LETTERS;
        x %= p;
    }

    return w;
}

bool add_hash(hashtable* tab, int hash, City* v) {
    if(!tab->tab[hash]) {
        tab->tab[hash] = new_list(v);
        if (!tab->tab[hash]) {
            return false;
        }
    }
    else {
        if(!add_elem(tab->tab[hash], v)) {
            return false;
        }

    }

    return true;
}

bool add_city(hashtable* tab, const char* s, City* v) {
    int hash = hash_word(s, P);

    return add_hash(tab, hash, v);
}

City* get_city_id(hashtable* tab, const char* s) {
    int hash = hash_word(s, P);

    list* l = tab->tab[hash];
    l = first_elem(l);

    while (l) {
        if (strcmp(l->city->city_name, s) == 0)
            return l->city;
        l = l->next;
    }

    return NULL;
}

void free_cities(hashtable* tab) {
    for (int i = 0; i < P; i++) {
        list* l = tab->tab[i];

        while (l) {
            City* c = l->city;
            road_list* rl = c->roads;

            while (rl && rl->prev_road)
                rl = rl->prev_road;
            while (rl) {
                road_list* rl_pom = rl->next_road;
                free(remove_road(rl->road->city1, rl->road->city2));
                rl = rl_pom;
            }

            free(c->city_name);
            free(c);

            l = l->next;
        }

        free_list(tab->tab[i]);
    }

    free(tab->tab);
}
