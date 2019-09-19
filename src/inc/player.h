#ifndef __PLAYER_H__
#define __PLAYER_H__

#define MAX_CARDS 30

typedef struct _player
{
    int isUno;
    int nCards;
    card c[MAX_CARDS];
    char name[100];
} player;

#endif
