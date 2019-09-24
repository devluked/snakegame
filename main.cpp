//Snake game
//Luke Duggan
//September 24th, 2019

#include <iostream>
#include <ncurses.h>
#include <cstdlib>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x,y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

int tailX[100], tailY[100];
int ntail = 0;

void setup()
{
    
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    
    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fruitX = rand() % width + 1;
    fruitY = rand() % height + 1;
    score = 0;
}

void draw()
{
    clear();
    
    for (int i = 0; i < width+2; i++)
        mvprintw(0, i, "#");
    
    for (int i = 0; i < height+2; i++)
    {
        for (int j = 0; j < width+2; j++)
        {
            if (i == 0 | i == 21)
                mvprintw(i, j, "#");
            else if (j == 0 | j == 21)
                mvprintw(i, j, "#");
            else if (i == y && j == x)
                mvprintw(i, j, "O");
            else if (i == fruitY && j == fruitX)
                mvprintw(i, j, "F");
            else
                for (int k = 0; k < ntail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                        mvprintw(i, j, "o");
                }
        }
    }
 
    mvprintw(23, 0, "Score: %d",score);
    refresh();
}
void input()
{
    keypad(stdscr, TRUE);
    halfdelay(1);
    
    int c = getch();
    
    switch(c)
    {
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case 113:
            gameOver = true;
            break;
    }
}
void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    
    for (int i = 1; i < ntail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    switch(dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    
    if (x>width || x < 1 || y < 1 || y > height)
        gameOver = true;
    
    for (int i = 0; i < ntail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score++;
        fruitX = (rand() % width) + 1;
        fruitY = (rand() % height) + 1;
        ntail++;
    }
}

int main()
{
    setup();
    while(!gameOver)
    {
        draw();
        input();
        logic();
    }
    
    getch();
    endwin();
    
    return 0;
}
