#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#include "graph.h"
#include "tsp.h"
#include "data.h"
#include "ui.h"
#include"route.h"
#include "config.h"

char cityNames[CITY_COUNT][NAME_LEN];
int main(void)
	{
		if (!loadcities("cities.txt", cityNames)) {
			printf("cities yuklenemedi!\n");
			return 1;
		}

		graph* g = creategraph(CITY_COUNT);
		if (g == NULL) return 1;

		if (!loadroads("roads.txt", g)) {
			printf("roads yuklenemedi!\n");
			freegraph(g);
			return 1;
		}

		int k;
		int stopk[MAX_STOPS];
		if (!readStops(stopk, &k)) {
			freegraph(g);
			return 1;
		}

		int distk[MAX_STOPS][MAX_STOPS];
		buildDistK(g, stopk, k, distk);

		int order[MAX_STOPS];
		int len;
		int best = TSPPath(distk, k, order, &len);

		if (best >= INF) {
			printf("Rota bulunamadi!!!!\n");
			freegraph(g);
			return 1;
		}
		if (!printFullRouteOneLine(g, stopk, order, len, cityNames)) {
			freegraph(g);
			return 1;
		}

		freegraph(g);
		return 0;
	}












