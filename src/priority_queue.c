#include "priority_queue.h"
#include "specifications.h"

bool is_empty(priority_queue* q) {
    if (q->tree[1].last_repair == 0)
        return true;

    return false;
}

void free_priority_queue(priority_queue* q) {
    if (q) {
        free(q->tree);
        free(q);
    }
}
path_priority empty_route() {
    path_priority route;

    route.city = NULL;
    route.city_id = 0;
    route.last_repair = 0;
    route.total_length = 0;

    return route;
}

path_priority make_path(City* city, int repair, unsigned length) {
    path_priority route;

    route.city = city;
    route.city_id = city->city_id;
    route.last_repair = repair;
    route.total_length = length;

    return route;
}

path_priority get_city_priority(priority_queue* q, City* city) {
    return q->tree[city->city_id + q->size];
}

int compare_priority(path_priority pp1, path_priority pp2) {
    if (pp1.last_repair == 0)
        return -1;

    if (pp2.last_repair == 0)
        return 1;

    if (pp1.total_length != pp2.total_length)
        return pp2.total_length - pp1.total_length;

    if (pp1.last_repair != pp2.last_repair)
        return pp1.last_repair - pp2.last_repair;

    return 0;
}

priority_queue* make_priority_queue(size_t size) {
    size_t k = 1;
    while (k < size) k *= 2;

    priority_queue* q = (priority_queue*)malloc(sizeof(priority_queue));
    if (!q)
        return NULL;

    q->tree = (path_priority*)malloc(2 * k * sizeof(path_priority));
    if (!q->tree) {
        free(q);
        return NULL;
    }
    q->size = k;

    for (size_t i = 0; i < 2 * k; i++)
        q->tree[i] = empty_route();

    return q;
}

void add(priority_queue* q, path_priority route) {
    size_t x = route.city_id + q->size;

    if (compare_priority(q->tree[x], route) <= 0)
        q->tree[x] = route;
    else
        return;

    x /= 2;

    while (x != 0) {
        if(compare_priority(q->tree[x], route) < 0)
            q->tree[x] = route;

        x /= 2;
    }
}

path_priority pop(priority_queue* q) {
    path_priority route = q->tree[1];

    size_t x = route.city_id + q->size;
    q->tree[x] = empty_route();
    x /= 2;

    while (x != 0) {
        q->tree[x] = empty_route();

        if (compare_priority(q->tree[2 * x], q->tree[2 * x + 1]) < 0)
            q->tree[x] = q->tree[2 * x + 1];
        else
            q->tree[x] = q->tree[2 * x];



        x /= 2;
    }

    return route;
}