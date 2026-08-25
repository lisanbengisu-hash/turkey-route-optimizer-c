#include "tsp.h"
#include "dijkstra.h"
#include"config.h"
#define MAX_MASK (1 << MAX_STOPS)


static int dp[MAX_MASK][MAX_STOPS];
static int parent[MAX_MASK][MAX_STOPS];


void buildDistK(
    graph* g,
    int stopk[],
    int k,
    int distk[][MAX_STOPS]
)
{
    int dist[CITY_COUNT];
    int prev[CITY_COUNT];

    for (int i = 0; i < k; i++)
    {
        dijkstra(g, stopk[i], dist, prev);

        for (int j = 0; j < k; j++)
        {
            distk[i][j] = dist[stopk[j]];
        }
    }
}


int TSPPath(
    int distk[][MAX_STOPS],
    int k,
    int order[],
    int* lenOut
)
{
    int full = (1 << k) - 1;

    for (int mask = 0; mask <= full; mask++)
    {
        for (int i = 0; i < k; i++)
        {
            dp[mask][i] = INF;
            parent[mask][i] = -1;
        }
    }

    dp[1 << 0][0] = 0;

    for (int mask = 0; mask <= full; mask++)
    {
        for (int u = 0; u < k; u++)
        {
            if (!(mask & (1 << u)))
                continue;

            if (dp[mask][u] >= INF)
                continue;

            for (int v = 0; v < k; v++)
            {
                if (mask & (1 << v))
                    continue;

                if (distk[u][v] >= INF)
                    continue;

                int nmask = mask | (1 << v);
                int cand = dp[mask][u] + distk[u][v];

                if (cand < dp[nmask][v])
                {
                    dp[nmask][v] = cand;
                    parent[nmask][v] = u;
                }
            }
        }
    }

    int end = k - 1;
    int best = dp[full][end];

    if (best >= INF)
        return INF;

    int len = 0;
    int mask = full;
    int cur = end;

    while (cur != -1)
    {
        order[len++] = cur;

        if (cur == 0)
            break;

        int p = parent[mask][cur];

        mask ^= (1 << cur);
        cur = p;
    }

    for (int i = 0, j = len - 1; i < j; i++, j--)
    {
        int tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }

    *lenOut = len;

    return best;
}