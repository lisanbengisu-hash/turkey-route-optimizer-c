#pragma once
#include "graph.h"

void dijkstra(graph* g, int start, int dis[], int prev[]);

int buildpatharray(int start, int target, int prev[], int outpath[], int* outlen);
