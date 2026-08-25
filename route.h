#pragma once

#include "graph.h"
#include "data.h"
#include "config.h"

int printFullRouteOneLine(
    graph* g,
    int stopk[],
    int order[],
    int len,
    char cityNames[CITY_COUNT][NAME_LEN]
);