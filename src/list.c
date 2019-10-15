//
// Created by Hubert on 13.04.2019.
//

#include "list.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_ROUTES 1000
list* new_list(City* city) {
    list* l = (list*)malloc(sizeof(list));
    if (!l)
        return NULL;

    l->next = NULL;
    l->prev = NULL;
    l->city = city;

    return l;
}

list* first_elem(list* l) {
    if (!l)
        return NULL;

    while (l->prev)
        l = l->prev;


    return l;
}
list* last_elem(list* l) {
    if (!l)
        return l;

    while (l->next)
        l = l->next;

    return l;
}

void add_list(list* l, list* lx) {
    list* lpom = l->next;
    list* lxp = first_elem(lx);
    list* lxk = last_elem(lx);

    l->next = lxp;
    lxp->prev = l;

    if (lpom) {
        lpom->prev = lxk;
        lxk->next = lpom;
    }
}

bool add_elem(list* l, City* city) {
    list* s = new_list(city);
    if (!s)
        return false;

    l = last_elem(l);
    add_list(l, s);
    return true;
}

bool add_to_beginning(list* l, City* city) {
    l = first_elem(l);
    list* pom = new_list(city);
        if (!pom)
            return false;

    pom->next = l;
    l->prev = pom;

    return true;
}

list* find_city(list* l, City* c) {
    l = first_elem(l);

    while (l) {
        if (l->city == c)
            return l;

        l = l->next;
    }

    return NULL;
}
bool exists(list* l, City* c) {
    if (find_city(l, c))
        return true;

    return false;
}

unsigned route_length(list* l) {
    unsigned length = 0;

    while (l->next) {
        Road* road = getRoad(l->city, l->next->city);
        if (!road)
            return 0;

        length += road->length;

        l = l->next;
    }

    return length;
}

int route_repair(list* l) {
    int repair = INT_MAX;

    while (l->next) {
        Road* road = getRoad(l->city, l->next->city);
        if (!road)
            return 0;

        repair = (repair > road->repairYear) ? road->repairYear : repair;

        l = l->next;
    }

    return repair;
}

int compare_paths(list* l1, list* l2) {
    unsigned length1 = route_length(l1), length2 = route_length(l2);
    int min_repair1 = route_repair(l1), min_repair2 = route_repair(l2);

    if (length1 == 0)
        return -1;

    if (length2 == 0)
        return 1;

    if (length1 != length2)
        return length2 - length1;

    return min_repair1 - min_repair2;
}

bool containsRoad(list* l, City* c1, City* c2) {
    if (!l)
        return false;

    l = first_elem(l);
    while (l->next) {
        if (l->city == c1 && l->next->city == c2)
            return true;

        l = l->next;
    }

    return false;
}
void fill_gap(list* route, list* l) {
    route = first_elem(route);
    l = first_elem(l);

    while (route->city != l->city)
        route = route->next;

    l = l->next;
    list* l_pom1 = route->next;
    free(l->prev);
    l->prev = route;
    route->next = l;

    list* l_pom2 = last_elem(l);
    l_pom1->prev = last_elem(l)->prev;
    last_elem(l)->prev->next = l_pom1;
    free(l_pom2);
}

list* extend_path(list* route, list* extension) {
    route = last_elem(route);
    extension = first_elem(extension);
    route = route->prev;
    free(route->next);

    route->next = extension;
    extension->prev = route;

    return first_elem(route);
}

void add_at_index(char* description, const char* string, size_t *index) {
    size_t pom = *index;
    for (; string[*index - pom]; (*index)++)
        description[*index] = string[*index - pom];
}

size_t describeRoute_length(list* route) {
    size_t length = 0;
    length += strlen(route->city->city_name);

    while (route->next) {
        Road* road = getRoad(route->city, route->next->city);
        length += int_length(road->repairYear) + 1;
        length += int_length(road->length) + 1;
        length += strlen(route->next->city->city_name) + 1;
        route = route->next;
    }

    return length + 1;
}
char* describeRoute(list* route, unsigned routeId) {
    route = first_elem(route);
    size_t routeId_length = int_length(routeId);
    size_t length = describeRoute_length(route) + routeId_length + 1;
    size_t *index = (size_t*)malloc(sizeof(size_t));
    if (!index)
        return NULL;

    *index = 0;

    char* description = (char*)malloc(length * sizeof(char));
    if (!description) {
        free(index);
        return NULL;
    }
    description[length-1] = '\0';
    const char* city_name = route->city->city_name;

    char* rId = int_to_string(routeId);

    add_at_index(description, rId, index);
    description[*index] = ';';
    (*index)++;
    free(rId);
    add_at_index(description, city_name, index);
    description[*index] = ';';
    (*index)++;
    char* repair;
    char* len;

    while (route->next) {
        Road* road = getRoad(route->city, route->next->city);

        len = int_to_string(road->length);
        if (!len) {
            free(description);
            free(index);
            return NULL;
        }
        add_at_index(description, len, index);
        description[*index] = ';';
        (*index)++;
        free(len);

        repair = int_to_string(road->repairYear);
        if (!repair) {
            free(description);
            free(index);
            return NULL;
        }
        add_at_index(description, repair, index);
        description[*index] = ';';
        (*index)++;
        free(repair);

        city_name = route->next->city->city_name;
        add_at_index(description, city_name, index);
        if (route->next->next)
                description[*index] = ';';
        (*index)++;

        route = route->next;
    }

    free(index);

    return description;
}

void free_list(list* l) {
    l = first_elem(l);

    while (l) {
        list* l_next = l->next;
        l->next = NULL;
        free(l);
        l = l_next;
    }
}

void free_routes(list** l) {
    for (size_t i = 0; i < MAX_ROUTES; i++) {
        free_list(l[i]);
    }
    free(l);
}