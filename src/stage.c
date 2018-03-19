#include "stage.h"

int snakeFacing, snakeLength, stageWidth, stageHeight, freeBlockCount, gameOver;
int *snakeX, *snakeY;
char *snakeStage;

int isGameOver() {
    return gameOver;
}

char *getBlockByXY(int X, int Y) {
    if ((snakeStage == NULL) || (X < 0) || (X >= stageWidth + 2) || (Y < 0) || (Y >= stageHeight + 2)) return NULL;
    else return snakeStage + Y * (stageWidth + 2) + X;
}

void initStage(int W, int H) {
    finalizeStage();
    gameOver = 0;
    /* init stage */
    stageWidth = W; stageHeight = H;
    snakeStage = (char *)malloc(sizeof(char) * (stageWidth + 2) * (stageHeight + 2));
    int x, y;
    for (y = 0; y < stageHeight + 2; y++) {
        for (x = 0; x < stageWidth + 2; x++) {
            if ((x == 0) || (x == stageWidth + 1) || (y == 0) || (y == stageHeight + 1)) {
                *getBlockByXY(x, y) = CHAR_WALL;
            } else {
                *getBlockByXY(x, y) = CHAR_SPACE;
            }
        }
    }
    
    /* init snake */
    snakeX = (int *)malloc(sizeof(int) * stageWidth * stageHeight);
    snakeY = (int *)malloc(sizeof(int) * stageWidth * stageHeight);
    *getBlockByXY(1, stageHeight / 2) = *getBlockByXY(2, stageHeight / 2) = CHAR_SNAKE_BODY;
    *getBlockByXY(3, stageHeight / 2) = CHAR_SNAKE_HEAD;
    snakeX[0] = 1; snakeX[1] = 2; snakeX[2] = 3;
    snakeY[0] = snakeY[1] = snakeY[2] = stageHeight / 2;
    snakeLength = 3; snakeFacing = SR;
    freeBlockCount = stageWidth * stageHeight - snakeLength;
    
    /* init fruit */
    putFruit();
}

void finalizeStage() {
    gameOver = 1;
    free(snakeStage);
    free(snakeX);
    free(snakeY);
}

void changeDirection(int direction) {
    if ((direction + 2) % 4 == snakeFacing) return;
    snakeFacing = direction;
}

int putFruit() {
    if (freeBlockCount <= 0) return false;
    srand((unsigned)time(NULL));
    int index = rand() % (freeBlockCount - 1 + 1) + 1, count = 0;
    int x, y;
    for (x = 1; x <= stageWidth; x++) {
        for (y = 1; y <= stageHeight; y++) {
            if (*getBlockByXY(x, y) == CHAR_SPACE) {
                count++;
                if (count == index) {
                    *getBlockByXY(x, y) = CHAR_FRUIT;
                }
            }
        }
    }
    return true;
}

void snakeMove() {
    snakeMoveXY((int)sin(snakeFacing * M_PI_2), (int)cos(snakeFacing * M_PI_2));
}

void snakeMoveXY(int dx, int dy) {
    *getBlockByXY(snakeX[0], snakeY[0]) = CHAR_SPACE;
    switch (*getBlockByXY(snakeX[snakeLength - 1] + dx, snakeY[snakeLength - 1] + dy)) {
        case CHAR_WALL:
        case CHAR_SNAKE_BODY:
            *getBlockByXY(snakeX[snakeLength - 1], snakeY[snakeLength - 1]) = CHAR_SNAKE_BODY;
            *getBlockByXY(snakeX[snakeLength - 1] + dx, snakeY[snakeLength - 1] + dy) = CHAR_SNAKE_HEAD;
            gameOver = 1;
            /* call of func gameover; */
            mvprintw(stageHeight + 3, 1, "Game Over");
            break;
        case CHAR_FRUIT:
            *getBlockByXY(snakeX[0], snakeY[0]) = CHAR_SNAKE_BODY;
            *getBlockByXY(snakeX[snakeLength - 1], snakeY[snakeLength - 1]) = CHAR_SNAKE_BODY;
            snakeX[snakeLength] = snakeX[snakeLength - 1] + dx;
            snakeY[snakeLength] = snakeY[snakeLength - 1] + dy;
            *getBlockByXY(snakeX[snakeLength], snakeY[snakeLength]) = CHAR_SNAKE_HEAD;
            snakeLength++;
            freeBlockCount--;
            if (!putFruit()) {
                gameOver = 1;
                /* call of func gamewin; */
                mvprintw(stageHeight + 3, 1, "You win");
            }
            break;
        case CHAR_SPACE:
            *getBlockByXY(snakeX[snakeLength - 1], snakeY[snakeLength - 1]) = CHAR_SNAKE_BODY;
            int i;
            for (i = 0; i < snakeLength - 1; i++) {
                snakeX[i] = snakeX[i + 1];
                snakeY[i] = snakeY[i + 1];
            }
            snakeX[snakeLength - 1] = snakeX[snakeLength - 1] + dx;
            snakeY[snakeLength - 1] = snakeY[snakeLength - 1] + dy;
            *getBlockByXY(snakeX[snakeLength - 1], snakeY[snakeLength - 1]) = CHAR_SNAKE_HEAD;
            break;
        default:
            abort(); /* fatal error detected */
            break;
    }
}

void printStage() {
    if (snakeStage == NULL) return;
    int i;
    for (i = 0; i < (stageWidth + 2) * (stageHeight + 2); i++) {
        addch(*(snakeStage + i));
        if ((i + 1) % (stageWidth + 2) == 0) {
            addch('\n');
        }
    }
}
