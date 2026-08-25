#include "dijkstra.h"
#include"config.h"


static int mindistance(int dist[], int visited[], graph* g)
{
	int min = INF;
	int idx = -1;

	for (int i = 0; i < g->citycount; i++)
	{
		if (!visited[i] && dist[i] < min)
		{
			min = dist[i];
			idx = i;
		}
	}

	return idx;
}
void dijkstra(graph* g, int start, int dis[], int prev[])
{
	int n = g->citycount;
	int visited[CITY_COUNT];
	for (int i = 0; i < n; i++)
	{
		dis[i] = INF;
		prev[i] = -1;
		visited[i] = 0;
	}
	dis[start] = 0;
	for (int step = 0; step < n; step++)
	{
		int u = mindistance(dis, visited, g);
		if (u == -1)
			break;
		visited[u] = 1;
		edge* curr = g->adjenlist[u];
		while (curr != NULL)
		{
			int v = curr->to;
			int w = curr->km;
			if (visited[v] == 0 && dis[u] + w < dis[v])
			{
				dis[v] = dis[u] + w;
				prev[v] = u;

			}
			curr = curr->next;
		}
	}
}
int buildpatharray(int start, int target, int prev[], int outpath[], int* outlen)
{
	int temp[CITY_COUNT];
	int count = 0;
	int curr = target;
	while (curr != -1)
	{
		temp[count++] = curr;
		if (curr == start)
			break;
		curr = prev[curr];
	}
	if (count == 0 || temp[count - 1] != start) {
		return 0;
	}
	*outlen = 0;
	for (int i = count - 1; i >= 0; i--)
	{
		outpath[(*outlen)++] = temp[i];

	}
	return 1;
}
