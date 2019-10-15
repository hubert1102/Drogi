//
// Created by Hubert on 14.04.2019.
//

#include "graph_operations.h"
#include "math.h"
#include "limits.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void shortest_path(City *c_pocz, City *c_kon, size_t n_of_cities,
                   list *route, City **previous_city, bool *only_one_path) {
    priority_queue* q = make_priority_queue(n_of_cities);
    if (!q)
        return;

    bool* odw = (bool*)malloc(n_of_cities * sizeof(bool));
    if (!odw) {
        free_priority_queue(q);
        return;
    }

    for (size_t i = 0; i < n_of_cities; i++)
        odw[i] = false;

    path_priority pp = make_path(c_pocz, INT_MAX, 0);
    add(q, pp);

    while (!is_empty(q) && pp.city != c_kon) {
        pp = pop(q);
        City* c = pp.city;
        road_list* rl = c->roads;
        odw[c->city_id] = true;
        while (rl) {
            Road* road = rl->road;
            City* nextCity = (road->city1 == c) ? road->city2 : road->city1;
            size_t nextCity_id = nextCity->city_id;

            if (!odw[nextCity_id] && (!exists(route, nextCity) || nextCity == c_kon)) {
                int repair = MIN(pp.last_repair, road->repairYear);
                path_priority pom = make_path(nextCity, repair, pp.total_length + road->length);
                path_priority pom2 = get_city_priority(q, nextCity);

                if (compare_priority(pom, pom2) == 0) {
                    only_one_path[nextCity_id] = false;
                }
                else {
                    only_one_path[nextCity_id] = true;

                    if (compare_priority(pom, pom2) > 0)
                        previous_city[nextCity_id] = c;
                }

                add(q, pom);
            }

            rl = rl->next_road;
        }
    }
    free(odw);
    free_priority_queue(q);
}

bool find_path(list* l, list* route, City* c1, City* c2,
               size_t n_of_cities) {
    bool* only_one_path = (bool*)malloc(n_of_cities * sizeof(bool));
    if (!only_one_path)
        return false;

    City** previous_city = (City**)malloc(n_of_cities * sizeof(City*));
    if (!previous_city) {
        free(only_one_path);
        return false;
    }


    for (size_t i = 0; i < n_of_cities; i++) {
        only_one_path[i] = false;
        previous_city[i] = NULL;
    }

    shortest_path(c1, c2, n_of_cities, route, previous_city, only_one_path);
    City* c = c2;

    if (!only_one_path[c->city_id]) {
        free(only_one_path);
        free(previous_city);
        return false;
    }

    while (c != c1) {
        if (!only_one_path[c->city_id]) {
            free(only_one_path);
            free(previous_city);
            return false;
        }

        c = previous_city[c->city_id];
    }

    c = previous_city[c2->city_id];

    while (c != c1) {
        if (!add_to_beginning(l, c)) {
            free_list(l);
            l = NULL;
            break;
        }

        c = previous_city[c->city_id];
    }

    if (l) {
        if (!add_to_beginning(l, c1)) {
            free_list(l);
            l = NULL;
        }
    }
    free(only_one_path);
    free(previous_city);
    return true;
}