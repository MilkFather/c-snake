# c-snake

This is a simple implementation of the "Snake" game in C.

[TOC]

## Compilation

To compile the program, pull the source code and run
```text
gcc -lpthread -lcurses main.c stage.h stage.c
```

Currently the ```pthread.h``` and the ```curses.h``` libraries are only available on Unix, Linux and macOS. Support on Windows may be added in the future.

## Game Controls

The game will start immediately when you open the application. Symbols are shown as the table below:

| Symbol     | Meaning     |
| :------------- | :------------- |
| H       | The head of the snake       |
| X       | The body of the snake       |
| *       | The wall                    |
| $       | The fruit                   |

Use the ```Up```, ```Down```, ```Left``` and ```Right``` arrows to control the facing of the snake.

Eat fruits to make the snake grow, but be careful not to let the snake bump into the wall or itself. If you manage to make the snake fill every inch of the available ground, you will win the game.

After winning or losing, press any key to exit. Relaunch the program to play again.

## Licence

This project is published under the GNU General Public License v3.0.
