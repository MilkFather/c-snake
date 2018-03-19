#include <stdio.h>
#include <curses.h>
#include <pthread.h>
#include "stage.h"

void * automove() {
    printStage();
    while (!isGameOver()) {
        system("sleep 0.2");
        erase();
        snakeMove();
        move(0, 0);
        printStage();
        refresh();
    }
    return NULL;
}

int main(int argc, const char * argv[]) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    
    initStage(20, 10);
    refresh();

    pthread_t autothread;
    pthread_create(&autothread, NULL, automove, NULL);
    pthread_detach(autothread);
    
    while(!isGameOver()) {
        switch (getch()) {
            case KEY_LEFT:
                changeDirection(SL);
                break;
            case KEY_RIGHT:
                changeDirection(SR);
                break;
            case KEY_UP:
                changeDirection(ST);
                break;
            case KEY_DOWN:
                changeDirection(SD);
                break;
        }
    }

    finalizeStage();
    
    getch();
    endwin();
    return 0;
}
