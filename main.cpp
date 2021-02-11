#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <iostream>
#include <array>
#include <conio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

const int WIDTH = 40, HEIGHT = 20;
bool GameOver = false;
int snakeLength = 0;
int SnakePosX[WIDTH * HEIGHT] = {WIDTH/2};
int SnakePosY[WIDTH * HEIGHT] = {HEIGHT/2};
enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
Direction dir = STOP;
const int delay = 100;
class Snake{
    public:
    int snakeLength = 1;
    void hidecursor(){
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);
    }       
    void gotoxy(short x, short y){
        #ifdef _WIN32
        COORD coord = {x, y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #endif
    }
    void Draw(short x, short y, char a){
        gotoxy(x, y);
        cout << a;
    }
    void AppendSnake(){
        snakeLength++;
    }
}snake;


int main(){
    srand(time(NULL));
    snake.Draw(SnakePosX[0], SnakePosY[0], '@');
    int FoodXY[2] = {rand() % WIDTH, rand() % HEIGHT};
    snake.Draw(FoodXY[0], FoodXY[1], 'F');
    while(!GameOver){
        if(_kbhit()){
        switch (getch()){
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        default:
            break;
            }   
        }
        switch(dir){
            case UP:
                SnakePosY[0]--;
                break;
            case DOWN:
                SnakePosY[0]++;
                break;
            case LEFT:
                SnakePosX[0]--;
                break;
            case RIGHT:
                SnakePosX[0]++;
                break;
        }
        snake.hidecursor();
        for(int i = 0; i <= WIDTH; i++){
            for(int j = 0; j <= HEIGHT; j++){
                if(i == 0 || i == WIDTH){
                    snake.gotoxy(i, j);
                    cout << "#";
                }
                if(j == 0 || j == HEIGHT){
                    snake.gotoxy(i, j);
                    cout << "#";
                }
            }
        }
        snake.Draw(SnakePosX[0], SnakePosY[0], '@');
        Sleep(delay);
        snake.Draw(SnakePosX[0], SnakePosY[0], ' ');
        if(SnakePosX[0] == FoodXY[0] && SnakePosY[0] == FoodXY[1]){
            snake.AppendSnake();
            snake.Draw(FoodXY[0], FoodXY[1], ' ');
            srand(time(NULL));
            int FoodXY[2] = {10, 10};
        }
        if(SnakePosX[0] == 0 || SnakePosX[0] == WIDTH || SnakePosY[0] == 0 || SnakePosY[0] == HEIGHT){
            GameOver = true;
        }
        snake.Draw(FoodXY[0], FoodXY[1], 'F');
        snake.gotoxy(WIDTH+3, HEIGHT+3);
        cout << FoodXY[0] << " " << FoodXY[1] << endl;
        cout << SnakePosX[0] << " " << SnakePosY[0];
    }
    snake.gotoxy(WIDTH/2, HEIGHT/2);
    cout << "GAME OVER!";
    snake.gotoxy(WIDTH, HEIGHT);
    cout << endl;
    system("pause");
}
