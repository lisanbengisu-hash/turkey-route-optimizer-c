#pragma once

#include "graph.h"
#include"config.h"

void buildDistK(
    graph* g,
    int stopk[],
    int k,
    int distk[][MAX_STOPS]
);

int TSPPath(
    int distk[][MAX_STOPS],
    int k,
    int order[],
    int* lenOut
);