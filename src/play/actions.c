#include <stdio.h>
#include "cards.h"
#include "player.h"

void distribute(cards c[])
{
    int initial_distribution = 7;
    for(i = 0; i < initial_distribution; i++) {
        cc[i].cn = rand() % 15;
        c[i].cc = rand() % 4;

    }
}
