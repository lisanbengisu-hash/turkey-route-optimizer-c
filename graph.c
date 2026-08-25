#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

graph* creategraph(int citycount)
{
    graph* g = malloc(sizeof(graph));

    if (g == NULL) {
        printf("Bellek ayrilamadi!\n");
        return NULL;
    }

    edge** adjenlist = malloc(citycount * sizeof(edge*));

    if (adjenlist == NULL) {
        printf("Bellek ayrilamadi!\n");
        free(g);
        return NULL;
    }

    g->citycount = citycount;
    g->adjenlist = adjenlist;

    for (int i = 0; i < citycount; i++)
    {
        adjenlist[i] = NULL;
    }

    return g;
}

void addedge(int to, int km, int from, graph* g)
{
    edge* e1 = malloc(sizeof(edge));
    e1->km = km;
    e1->to = to;
    e1->next = g->adjenlist[from];
    g->adjenlist[from] = e1;

    edge* e2 = malloc(sizeof(edge));
    e2->km = km;
    e2->to = from;
    e2->next = g->adjenlist[to];
    g->adjenlist[to] = e2;



}

void freeedgelist(edge* head)
{
    edge* curr = head;
    while (curr != NULL)
    {
        edge* next = curr->next;
        free(curr);
        curr = next;
    }
}
void freegraph(graph* g)
{
    int i = 0;
    while (i < g->citycount)
    {
        freeedgelist(g->adjenlist[i]);
        g->adjenlist[i] = NULL;
        i++;
    }
    free(g->adjenlist);
    g->adjenlist = NULL;
    free(g);
}