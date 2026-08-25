#pragma once
#include "graph.h"
#include"config.h"

int loadcities(
    const char* citiesFile,
    char cityNames[CITY_COUNT][NAME_LEN]
);
int loadroads(
    const char* roadsFile,
    graph* g
);