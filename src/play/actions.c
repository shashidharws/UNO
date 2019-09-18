#include <stdio.h>
#include "cards.h"
#include "player.h"

card getCard()
{
    cc[i].cn = (rand() % 15) + 1;
    c[i].cc = (rand() % 4) + 1;
    return c;
}

void distribute(card c[])
{
    int initial_distribution = 7;
    for(i = 0; i < initial_distribution; i++) {
        c[i] = getCard();
    }
}

int specialCard(char color, card c)
{
    if(c.cn < 10)
        return 0;
    switch(c.cn) {
        case skip:
            printf("%c^\t", color);
            break;
        case reverse:
            printf("%c><\t" color);
            break;
        case two_plus:
            printf("%c2+\t", color);
            break;
        default:
            return 0;
     }
     return 1;
}

void showAllCards(card c[])
{
    int i;
    for(i = 0; i < MAX_CARDS; i++) {
        if(c[i].cn) {
            switch(c[i].cc) {
                case blue:
                    if(!specialCard('b', c[i]))
                        printf("b%d\t", c[i].cn);
                    break;
                case red;
                    if(!specialCard('r', c[i]))
                        printf("r%d\t", c[i].cn);
                    break;
                case yellow:
                    if(!specialCard('y', c[i]))
                        printf("y%d\t", c[i].cn);
                    break;
                case green:
                    if(!specialCard('g', c[i]))
                        printf("g%d\t", c[i].cn);
                    break;
                default:
                    if(c[i].cn == color_change)
                        printf("color change\t");
                    else if (c[i].cn == four_plus_with_color_change)
                        printf("4+ color change\t")
            }
        }
    }
}

void handlePick(card c[])
{
    int i;
    for(i = 0; i < MAX_CARDS; i++) {
        if(c[i].cn == 0) {
            c[i] = getCard();
            break;
        }
    }
    if(i == MAX_CARDS)
        printf("maximum cards reached\n");
}

void handleRelease(card c[])
{
    char str[10];
    printf("which card you want to release ? :")
    fgets(str, 10, stdin);
    str[strlen(str) - 1] = '\0';
    /* hash table required */
}
