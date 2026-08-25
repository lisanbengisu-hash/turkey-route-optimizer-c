#pragma once


typedef struct edge
{
    int to;
    int km;
    struct edge* next;
} edge;

typedef struct graph
{
    int citycount;
    edge** adjenlist;
} graph;
graph* creategraph(int citycount);
void addedge(int to, int km, int from, graph* g);
void freeedgelist(edge* head);
void freegraph(graph* g);
