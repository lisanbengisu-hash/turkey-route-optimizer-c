#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include "data.h"


#include <stdio.h>

int readStops(int stopk[], int* k)
{
    printf("durak sayisi(2-%d): ", MAX_STOPS);

    if (scanf("%d", k) != 1 || *k < 2 || *k > MAX_STOPS)
    {
        printf("gecerli bir k giriniz!!!!!\n");
        return 0;
    }

    for (int i = 0; i < *k; i++)
    {
        int p;

        printf("\n%d.plaka: ", i + 1);

        if (scanf("%d", &p) != 1 || p < 1 || p > CITY_COUNT)
        {
            printf("hata lutfen gecerli bir plaka giriniz!!!!!\n");
            return 0;
        }

        stopk[i] = p - 1;
    }

    return 1;
}