
#include "route.h"
#include "dijkstra.h"
#include "data.h"
#include "config.h"
#include <stdio.h>



int printFullRouteOneLine(
    graph* g,
    int stopk[],
    int order[],
    int len,
    char cityNames[CITY_COUNT][NAME_LEN]
)
{
    int dist[CITY_COUNT];
    int prev[CITY_COUNT];

    int fullpath[5000];
    int fulllen = 0;
    int totalreal = 0;

    int i = 0;

    while (i < len - 1)
    {
        int A = stopk[order[i]];
        int B = stopk[order[i + 1]];

        dijkstra(g, A, dist, prev);

        if (dist[B] >= INF)
        {
            printf("HATA!!!!\n");
            return 0;
        }

        totalreal += dist[B];

        int seg[CITY_COUNT];
        int seglen = 0;

        if (!buildpatharray(A, B, prev, seg, &seglen))
        {
            printf("HATA!!!!\n");
            return 0;
        }

        int startidx;

        if (i == 0)
        {
            startidx = 0;
        }
        else
        {
            startidx = 1;
        }

        for (int t = startidx; t < seglen; t++)
        {
            fullpath[fulllen++] = seg[t];
        }

        i++;
    }

    printf("\nROTA\n");

    for (int t = 0; t < fulllen; t++)
    {
        printf("%s (%d)", cityNames[fullpath[t]], fullpath[t] + 1);

        if (t != fulllen - 1)
        {
            printf(" -> ");
        }
    }

    printf("\nToplam mesafe: %d km\n", totalreal);

    return 1;
}