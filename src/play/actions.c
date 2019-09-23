#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cards.h"
#include "player.h"

static card getCard()
{
    card c;
    c.cn = (rand() % 15) + 1;
    if(c.cn < color_change)
        c.cc = (rand() % 4) + 1;
    return c;
}

void distribute(card c[])
{
    int i;
    int initial_distribution = 7;
    for(i = 0; i < initial_distribution; i++) {
        c[i] = getCard();
    }
}

static int specialCard(char color, card c)
{
    if(c.cn < 10)
        return 0;
    switch(c.cn) {
        case skip:
            printf("%c^\t", color);
            break;
        case reverse:
            printf("%c><\t", color);
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
                case red:
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
                        printf("c_c\t");
                    else if (c[i].cn == four_plus_with_color_change)
                        printf("4+_cc\t");
            }
        }
    }
}

static int releaseCard(card c[], card rel_c)
{
    int i;
    for(i = 0; i < MAX_CARDS; i++) {
        if(c[i].cn && (c[i].cn == rel_c.cn && c[i].cc == rel_c.cc)) {
            c[i].cn = 0;
            break;
        }
    }
    if(i == MAX_CARDS) {
        printf("Invalid card: ");
        return -1;
    }
    return 0;
}

static int releaseSpecialCard(card c[], char *cType)
{
    card rel_c = {0, 0};
    if(!strcmp("c_c", cType))
        rel_c.cn = color_change;
    else if(!strcmp("4+_cc", cType))
        rel_c.cn = four_plus_with_color_change;
    return releaseCard(c, rel_c);
}

static int specialColorCardRelease(char *cType, card *c)
{
    if(isdigit(cType))
        return 0;
    if(cType[0] == '^')
        c->cn = skip;
    else if(!strcmp("><", cType))
        c->cn = reverse;
    else if(!strcmp("2+", cType))
        c->cn = two_plus;
    else {
        printf("Invalid Type :");
        c->cn = 0;
    }
    return 1;
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

int handleRelease(card c[])
{
    char str[10];
    card rel_c;
    printf("which card you want to release ? :");
    fgets(str, 10, stdin);
    str[strlen(str) - 1] = '\0';
    switch(str[0]) {
        case 'b':
            rel_c.cc = blue;
            if(!specialColorCardRelease(&str[1], &rel_c)) {
                rel_c.cn = atoi(&str[1]);
            }
            /* No break */
        case 'y':
            rel_c.cc = blue;
            if(!specialColorCardRelease(&str[1], &rel_c)) {
                rel_c.cn = atoi(&str[1]);
            }
            /* No break */
        case 'g':
            rel_c.cc = blue;
            if(!specialColorCardRelease(&str[1], &rel_c)) {
                rel_c.cn = atoi(&str[1]);
            }
            /* No break */
        case 'r':
            rel_c.cc = blue;
            if(!specialColorCardRelease(&str[1], &rel_c)) {
                rel_c.cn = atoi(&str[1]);
            }
            /* Applies to all */
            return releaseCard(c, rel_c);
        default:
            return releaseSpecialCard(c, str);
    }
    return 0;
}
