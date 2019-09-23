#ifdef __CONTROLER_H__
#define __CONTROLER_H__

#define MAX_PLAYERS 10
typedef struct _player {
    int isRegistered; 
    char name[100];
    int sock_fd;
} player;

typedef struct _playCtrl
{
    int playerIndex;
    player p[MAX_PLAYERS];
} playCtrl;

#endif
