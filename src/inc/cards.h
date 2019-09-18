#ifndef __CARDS_H__
#define __CARDS_H__

typdef enum {
    blue,
    red,
    green,
    yellow
} cardColor;

typdef enum {
    skip = 10,
    reverse,
    two_plus,
    color_change,
    four_plus_with_color_change,
} specialCards;


typdef struct _card {
    int cc;
    int cn;
} card;

#endif
