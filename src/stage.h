#ifndef stage_h
#define stage_h

#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CHAR_SNAKE_BODY 'X'
#define CHAR_SNAKE_HEAD 'H'
#define CHAR_WALL '*'
#define CHAR_FRUIT '$'
#define CHAR_SPACE ' '

#define SD 0   /* down */
#define SR 1   /* right */
#define ST 2   /* top */
#define SL 3   /* left */

#ifndef M_PI_2
#define M_PI_2      1.57079632679489661923132169163975144   /* pi/2           */
#endif

int isGameOver(void);
char *getBlockByXY(int X, int Y);
void initStage(int W, int H);
void finalizeStage(void);
void changeDirection(int direction);
int putFruit(void);
void snakeMove(void);
void snakeMoveXY(int dx, int dy);
void printStage(void);

#endif /* stage_h */
