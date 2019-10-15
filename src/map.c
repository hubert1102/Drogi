//
// Created by Hubert on 13.04.2019.
//

#include "map.h"
#include "list.h"
#include "priority_queue.h"
#include "hash.h"
#include "graph_operations.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_ROUTES 1000

struct Map {
    list* routes[MAX_ROUTES];

    hashtable* city_id;

    int n_of_cities;
};

Map* newMap() {
    Map* m = (Map*)malloc(sizeof(Map));
    if (!m)
        return NULL;

    m->n_of_cities = 0;
    m->city_id = new_hashtable();
    if (!m->city_id) {
        free(m);
        return NULL;
    }

    for (int i = 0; i < MAX_ROUTES; i++)
        m->routes[i] = NULL;

    return m;
}

bool valid_city(const char* city) {
    for (int i = 0; city[i]; i++) {
        if ((city[i] >= 0 && city[i] < 32) || city[i] == ';')
            return false;
    }

    if (city[0] != '\0')
        return true;
    else
        return false;
}

bool valid_newRoute(Map* map, const char* city1, const char* city2) {

    if (!valid_city(city1) || !valid_city(city2))
        return false;

    City* c1 = get_city_id(map->city_id, city1);
    City* c2 = get_city_id(map->city_id, city2);

    if (!c1 || !c2)
        return false;

    if (c1 == c2)
        return false;

    return true;

}

bool valid_addRoad(Map *map, const char *city1, const char *city2,
                   unsigned length, int builtYear) {
    if (strcmp(city1, city2) == 0)
        return false;

    if (!valid_city(city1) || !valid_city(city2))
        return false;

    if (length <= 0)
        return false;

    if (builtYear == 0)
        return false;

    City* c1 = get_city_id(map->city_id, city1);
    City* c2 = get_city_id(map->city_id, city2);

    if (!c1 || !c2)
        return true;

    if (areConnected(c1, c2))
        return false;
    return true;
}

bool addRoad(Map *map, const char *city1, const char *city2,
             unsigned length, int builtYear) {

    if (!valid_addRoad(map, city1, city2, length, builtYear))
        return false;

    if (!get_city_id(map->city_id, city1)) {
        City* c1 = newCity(city1, map->n_of_cities);

        if (!add_city(map->city_id, c1->city_name, c1))
            return false;
        map->n_of_cities++;
    }

    if (!get_city_id(map->city_id, city2)) {
        City* c1 = newCity(city2, map->n_of_cities);

        if (!add_city(map->city_id, city2, c1))
            return false;
        map->n_of_cities++;
    }

    City* c1 = get_city_id(map->city_id, city1);
    City* c2 = get_city_id(map->city_id, city2);

    newRoad(c1, c2, length, builtYear);

    return true;
}

bool repairRoad(Map *map, const char *city1, const char *city2, int repairYear) {
    if (!valid_city(city1) || !valid_city(city2))
        return false;

    City* c1 = get_city_id(map->city_id, city1);
    City* c2 = get_city_id(map->city_id, city2);

    if (!c1 || !c2)
        return false;

    if (!areConnected(c1, c2))
        return false;

    Road* road = getRoad(c1, c2);
    if (road->repairYear > repairYear)
        return false;

    changeRepairYear(c1, c2, repairYear);
    changeRepairYear(c2, c1, repairYear);

    return true;

}

bool newRoute(Map *map, unsigned routeId,
              const char *city1, const char *city2) {
    if (!valid_newRoute(map, city1, city2))
        return false;

    City* c1 = get_city_id(map->city_id, city1);
    City* c2 = get_city_id(map->city_id, city2);

    list* route = new_list(c2);
    if (!route)
        return false;

    if (!find_path(route, map->routes[routeId], c1, c2, map->n_of_cities)) {
        free_list(route);
        return false;
    }

    map->routes[routeId] = route;

    return true;
}

bool extendRoute(Map *map, unsigned routeId, const char *city) {
    City* c = get_city_id(map->city_id, city);
    if (!c || !map->routes[routeId])
        return false;

    list* route_pocz = first_elem(map->routes[routeId]);
    list* route_kon = last_elem(map->routes[routeId]);

    list* extend_kon = new_list(c);
    list* extend_pocz = new_list(route_pocz->city);

    if (!extend_pocz || !extend_kon) {
        if (extend_kon)
            free(extend_kon);
        if(extend_pocz)
            free(extend_pocz);
        return false;
    }

    find_path(extend_kon, map->routes[routeId],
              route_kon->city, c, map->n_of_cities);
    find_path(extend_pocz, map->routes[routeId],
              c, route_pocz->city, map->n_of_cities);

    extend_pocz = first_elem(extend_pocz);
    extend_kon = first_elem(extend_kon);

    if (compare_paths(extend_kon, extend_pocz) > 0) {
        map->routes[routeId] = extend_path(route_pocz, extend_kon);
        free_list(extend_pocz);
        return true;
    }
    if (compare_paths(extend_kon, extend_pocz) < 0) {
        map->routes[routeId] = extend_path(extend_pocz, route_pocz);
        free_list(extend_kon);
        return true;
    }

    return false;
}

bool removeRoad(Map *map, const char *city1, const char *city2) {
    City* c1 = get_city_id(map->city_id, city1);
    City* c2 = get_city_id(map->city_id, city2);
    if (!areConnected(c1, c2))
        return false;

    list** extensions = (list**)malloc(MAX_ROUTES * sizeof(list));
    if (!extensions)
        return false;

    Road* road = remove_road(c1, c2);
    for (int i = 0; i < MAX_ROUTES; i++)
        extensions[i] = NULL;

    for (int i = 0; i < MAX_ROUTES; i++) {
        if (containsRoad(map->routes[i], c1, c2)) {
            extensions[i] = new_list(c2);
            if (!extensions[i]) {
                free_routes(extensions);
                addRoad(map, c1->city_name, c2->city_name,
                        road->length, road->repairYear);
                return false;
            }
            if (!find_path(extensions[i], map->routes[i],
                      c1, c2, map->n_of_cities)) {
                free_routes(extensions);
                addRoad(map, c1->city_name, c2->city_name,
                        road->length, road->repairYear);
                return false;
            }
        }
        if (containsRoad(map->routes[i], c2, c1)) {
            extensions[i] = new_list(c1);
            if (!extensions[i]) {
                free_routes(extensions);
                addRoad(map, c1->city_name, c2->city_name,
                        road->length, road->repairYear);
                return false;
            }
            if (!find_path(extensions[i], map->routes[i],
                           c2, c1, map->n_of_cities)) {
                free_routes(extensions);
                addRoad(map, c1->city_name, c2->city_name,
                        road->length, road->repairYear);
                return false;
            }
        }
    }

    for (int i = 0; i < MAX_ROUTES; i++) {
        extensions[i] = first_elem(extensions[i]);

        if ((containsRoad(map->routes[i], c1, c2) ||
             containsRoad(map->routes[i], c2, c1)) &&
             !extensions[i])  {
            free_routes(extensions);
            addRoad(map, c1->city_name, c2->city_name,
                    road->length, road->repairYear);
            return false;
        }
    }

    for (int i = 0; i < MAX_ROUTES; i++) {
        if (containsRoad(map->routes[i], c1, c2) ||
            containsRoad(map->routes[i], c2, c1)) {
            fill_gap(map->routes[i], extensions[i]);
        }
    }

    free(extensions);
    free(road);
    return true;
}

char const* getRouteDescription(Map *map, unsigned routeId) {
    if (routeId >= MAX_ROUTES || !map->routes[routeId]) {
        char* description = (char*)malloc(sizeof(char));
        if (!description)
            return NULL;

        description[0] = '\0';
        return description;
    }

    const char* description = describeRoute(map->routes[routeId], routeId);

    return description;
}

void deleteMap(Map *map) {
    for (int i = 0; i < MAX_ROUTES; i++)
        free_list(map->routes[i]);

    free_cities(map->city_id);
    free(map);
}

