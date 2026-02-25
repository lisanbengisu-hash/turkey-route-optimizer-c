#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <limits.h>
#define INF (INT_MAX/4)
#define CITY_COUNT 81
#define NAME_LEN 32
#define MAX_STOPS 15
#define MAX_MASK (1 << MAX_STOPS)

 int dp[MAX_MASK][MAX_STOPS];
 int parent[MAX_MASK][MAX_STOPS];



char cityNames[CITY_COUNT][NAME_LEN];

typedef struct edge
{
	int to;
	int km;
	struct edge* next;
}edge;
typedef struct graph
{
	int citycount;
	edge** adjenlist;
}graph;
graph* creategraph(int citycount)
{
	graph* g = malloc(sizeof(graph));
	if (g == NULL) {
		printf("Bellek ayrilamadi!\n");
		return NULL;
	}
		edge** adjenlist = malloc(citycount * (sizeof(edge*)));
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
	g->adjenlist=NULL;
	free(g);
}
int loadcities(char* cities, char cityname[CITY_COUNT][NAME_LEN])
{
	FILE* f = fopen(cities, "r");
	if (f == NULL)
	{
		printf("dosya acilamadi");
		return 0;
	}
	for (int i = 0; i < CITY_COUNT; i++)
	{
		cityname[i][0] = '\0';
	}
	int plaka;
	char name[NAME_LEN];
	while (fscanf(f, "%d %31s", &plaka, name) == 2)
	{
		if (plaka<1 || plaka>CITY_COUNT)
			continue;
		strcpy(cityname[plaka - 1], name);
	}
	fclose(f);
	return 1;
}
int loadroads( graph* g)
{
	FILE* f = fopen("roads.txt", "r");
	if (f == NULL)
	{
		printf("dosyaacilamadi");
		return 0;
	}
	int p1;
	int p2;
	int km;
	while (fscanf(f, "%d %d %d", &p1, &p2, &km) == 3)
	{
		if (p1<1 || p1>CITY_COUNT || p2<1 || p2>CITY_COUNT || km <= 0)
			continue;
		int from = p1 - 1;
		int to = p2 - 1;
		addedge(to, km, from, g);
	}
	fclose(f);
	return 1;
}
int mindistance(int dist[], int visited[],graph*g)
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
int printFullRouteOneLine(graph* g, int stopk[], int order[], int len)
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
			printf("HATA!!!!");
			return 0;
		}
		totalreal += dist[B];
		int seg[CITY_COUNT];
		int seglen = 0;
		if (!(buildpatharray(A, B, prev, seg, &seglen)))
		{
			printf("hataa!!");
			return 0;
		}
		int startidx = (i == 0) ? 0 : 1;
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
		if (t != fulllen - 1) printf(" -> ");

	}
	printf("\nToplam mesafe: %d km\n", totalreal);
	return 1;
}
int readStops(int stopk[], int* k)
{
	printf("durak sayisi(2-%d): ", MAX_STOPS);
	if (scanf("%d", k) != 1 || *k < 2 || *k > MAX_STOPS) {
		printf("gecerli bir k giriniz!!!!!\n");
		return 0;
	}

	for (int i = 0; i < *k; i++) {
		int p;
		printf("\n%d.plaka: ", i + 1);
		if (scanf("%d", &p) != 1 || p < 1 || p > CITY_COUNT) {
			printf("hata lutfen gecerli bir plaka giriniz!!!!!\n");
			return 0;
		}
		stopk[i] = p - 1;
	}
	return 1;
}
void buildDistK(graph* g, int stopk[], int k, int distk[][MAX_STOPS])
{
	int dist[CITY_COUNT];
	int prev[CITY_COUNT];

	for (int i = 0; i < k; i++) {
		dijkstra(g, stopk[i], dist, prev);
		for (int j = 0; j < k; j++) {
			distk[i][j] = dist[stopk[j]];
		}
	}
}
int TSPPath(int distk[][MAX_STOPS], int k, int order[], int* lenOut)
{
	int full = (1 << k) - 1;

	for (int mask = 0; mask <= full; mask++) {
		for (int i = 0; i < k; i++) {
			dp[mask][i] = INF;
			parent[mask][i] = -1;
		}
	}

	dp[1 << 0][0] = 0;

	for (int mask = 0; mask <= full; mask++) {
		for (int u = 0; u < k; u++) {
			if (!(mask & (1 << u))) continue;
			if (dp[mask][u] >= INF) continue;

			for (int v = 0; v < k; v++) {
				if (mask & (1 << v)) continue;
				if (distk[u][v] >= INF) continue;

				int nmask = mask | (1 << v);
				int cand = dp[mask][u] + distk[u][v];

				if (cand < dp[nmask][v]) {
					dp[nmask][v] = cand;
					parent[nmask][v] = u;
				}
			}
		}
	}

	int end = k - 1;
	int best = dp[full][end];
	if (best >= INF) return INF;

	
	int len = 0;
	int mask = full;
	int cur = end;

	while (cur != -1) {
		order[len++] = cur;
		if (cur == 0) break;
		int p = parent[mask][cur];
		mask ^= (1 << cur);
		cur = p;
	}

	
	for (int i = 0, j = len - 1; i < j; i++, j--) {
		int tmp = order[i];
		order[i] = order[j];
		order[j] = tmp;
	}

	*lenOut = len;
	return best;
}

	int main(void)
	{
		if (!loadcities("cities.txt", cityNames)) {
			printf("cities yuklenemedi!\n");
			return 1;
		}

		graph* g = creategraph(CITY_COUNT);
		if (g == NULL) return 1;

		if (!loadroads(g)) {
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
		if (!printFullRouteOneLine(g, stopk, order, len)) {
			freegraph(g);
			return 1;
		}

		freegraph(g);
		return 0;
	}












