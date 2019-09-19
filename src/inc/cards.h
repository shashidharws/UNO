#ifndef __CARDS_H__
#define __CARDS_H__

typedef enum {
    blue,
    red,
    green,
    yellow
} cardColor;

typedef enum {
    skip = 10,
    reverse,
    two_plus,
    color_change,
    four_plus_with_color_change,
} specialCards;


typedef struct _card {
    cardColor cc;
    int cn;
} card;

#endif
