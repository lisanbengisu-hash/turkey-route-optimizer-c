#define _CRT_SECURE_NO_WARNINGS

#include "data.h"

#include <stdio.h>
#include <string.h>


int loadcities(
    const char* citiesFile,
    char cityNames[CITY_COUNT][NAME_LEN]
)
{
    FILE* f = fopen(citiesFile, "r");

    if (f == NULL)
    {
        printf("Cities dosyasi acilamadi.\n");
        return 0;
    }

    for (int i = 0; i < CITY_COUNT; i++)
    {
        cityNames[i][0] = '\0';
    }

    int plaka;
    char name[NAME_LEN];

    while (fscanf(f, "%d %31s", &plaka, name) == 2)
    {
        if (plaka < 1 || plaka > CITY_COUNT)
        {
            continue;
        }

        strcpy(cityNames[plaka - 1], name);
    }

    fclose(f);

    return 1;
}


int loadroads(
    const char* roadsFile,
    graph* g
)
{
    FILE* f = fopen(roadsFile, "r");

    if (f == NULL)
    {
        printf("Roads dosyasi acilamadi.\n");
        return 0;
    }

    int p1;
    int p2;
    int km;

    while (fscanf(f, "%d %d %d", &p1, &p2, &km) == 3)
    {
        if (
            p1 < 1 || p1 > CITY_COUNT ||
            p2 < 1 || p2 > CITY_COUNT ||
            km <= 0
            )
        {
            continue;
        }

        int from = p1 - 1;
        int to = p2 - 1;

        addedge(to, km, from, g);
    }

    fclose(f);

    return 1;
}