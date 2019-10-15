#include "specifications.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

size_t int_length(int d) {
    int length = (d < 0) ? 1 : 0;
    d = abs(d);

    while (d > 0) {
        length++;
        d /= 10;
    }

    return length;
}

char* int_to_string(int d) {
    int length = int_length(d);
    char* string = (char*)malloc(length * sizeof(char) + 1);
    if (!string)
        return NULL;

    string[length] = '\0';

    if (d < 0) {
        string[0] = '-';
        d = abs(d);
    }

    while (d != 0) {
        string[length-1] = d % 10 + '0';
        d /= 10;
        length--;
    }

    return string;
}

City* newCity(const char* city, unsigned city_id) {
    City* c = (City*)malloc(sizeof(City));
    if (!c)
        return NULL;

    c->roads = NULL;
    size_t n = strlen(city);
    c->city_name = (char*)malloc(n * sizeof(char) + 1);

    for (size_t i = 0; i < n; i++)
        c->city_name[i] = city[i];

    c->city_name[n] = '\0';

    c->city_id = city_id;
    return c;
}

road_list* newRoadList(Road* r) {
    road_list* rl = (road_list*)malloc(sizeof(road_list));
    if (!rl)
        return NULL;

    rl->road = r;
    rl->prev_road = NULL;
    rl->next_road = NULL;

    return rl;
}

void free_road_list(road_list* rl) {
    if (!rl)
        return;

    rl->prev_road = NULL;
    rl->next_road = NULL;
    free(rl);
}

bool newRoad(City* city1, City* city2, unsigned length, int repairYear) {
    Road* r = (Road*)malloc(sizeof(Road));

    if (!r)
        return false;

    r->length = length;
    r->city1 = city1;
    r->city2 = city2;
    r->repairYear = repairYear;

    road_list* rl1 = city1->roads;
    road_list* rl2 = city2->roads;
    road_list* new_rl1 = newRoadList(r);
    road_list* new_rl2 = newRoadList(r);

    if (!new_rl1 || !new_rl2) {
        free_road_list(new_rl1);
        free_road_list(new_rl2);
        return false;
    }

    if (!rl1) {
        //rl1 = new_rl;
        city1->roads = new_rl1;
    }
    else {
        new_rl1->next_road = rl1;
        rl1->prev_road = new_rl1;
        city1->roads = new_rl1;
    }

    if (!rl2) {
       // rl2 = new_rl;
       city2->roads = new_rl2;
    }
    else {
        new_rl2->next_road = rl2;
        rl2->prev_road = new_rl2;
        city2->roads = new_rl2;
    }

    return true;
}

bool areConnected(City* city1, City* city2) {
    if (!city1 || !city2)
        return false;

    road_list* rl = city1->roads;

    while (rl) {
        Road* r = rl->road;

        if (r->city1 == city2 || r->city2 == city2)
            return true;

        rl = rl->next_road;
    }

    return false;
}

Road* getRoad(City* city1, City* city2) {
    road_list* rl = city1->roads;

    while(rl) {
        if (rl->road->city1 == city2 || rl->road->city2 == city2)
            return rl->road;

        rl = rl->next_road;
    }

    return NULL;
}

void changeRepairYear(City* city1, City* city2, int repairYear) {
    Road* road = getRoad(city1, city2);
    road->repairYear = repairYear;
}

road_list* get_road_list(City* c1, City* c2) {
    road_list* rl = c1->roads;

    while (rl) {
        if(rl->road->city1 == c2 || rl->road->city2 == c2)
            return rl;

        rl = rl->next_road;
    }

    return NULL;
}

road_list* first_road_list(road_list* rl) {
    if (!rl)
        return NULL;

    while (rl->prev_road)
        rl = rl->prev_road;

    return rl;
}

Road* remove_road(City* c1, City* c2) {
    Road* road = getRoad(c1, c2);


    road_list* rl1 = get_road_list(c1, c2);
    road_list* rl2 = get_road_list(c2, c1);

    if (rl1->prev_road) {
        rl1->prev_road->next_road = rl1->next_road;
        c1->roads = rl1->prev_road;
    }
    if (rl1->next_road) {
        rl1->next_road->prev_road = rl1->prev_road;
        c1->roads = rl1->next_road;
    }

    if (rl2->prev_road) {
        rl2->prev_road->next_road = rl2->next_road;
        c2->roads = rl2->prev_road;
    }
    if (rl2->next_road) {
        rl2->next_road->prev_road = rl2->prev_road;
        c2->roads = rl2->next_road;
    }

    if (!rl1->next_road && !rl1->prev_road)
        c1->roads = NULL;
    if (!rl2->next_road && !rl2->prev_road)
        c2->roads = NULL;

    c1->roads = first_road_list(c1->roads);
    c2->roads = first_road_list(c2->roads);

    free_road_list(rl1);
    free_road_list(rl2);

    return road;
}