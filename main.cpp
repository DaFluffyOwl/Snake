#ifdef _WIN32
#include <windows.h>
#else
#error "OS not supported"
#endif
#include <stdio.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

int HEIGHT = 20, WIDTH = 40;
class Snake{
    public:
    bool L = 0, R = 0, U = 0, D = 0;
    const char head = '@', tail = 'o';
    int length = 1;
    vector<int> SnakeXY = {WIDTH/2, HEIGHT/2};
    vector<int> TailX = {0};
    vector<int> TailY = {0};
    void KeyB(){
        char key;
        if (_kbhit()){
            key = char(_getch());
            L = 0; R = 0; U = 0; D = 0;
            switch ( key ){
                case 'w':
                {
                    U = 1;
                    break;
                }
                case 's':
                {
                    D = 1;
                    break;
                }
                case 'a':
                {
                    L = 1;
                    break;
                }
                case 'd':
                {
                    R = 1;
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
    
}snake;
class Screen{
    #ifdef _WIN32
    public:
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    void gotoxy(short x, short y){
        //Set the Curson Position of the console 
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(hStdOut, coord);
    }
    void hideCursor(){
        // Hides the Console's Cursor
        info.dwSize = 100;
        info.bVisible = false;
        SetConsoleCursorInfo(hStdOut, &info);
    }
    template<typename T>
    void Draw(short x, short y, T c, int color){
        gotoxy(x, y);
        SetConsoleTextAttribute(hStdOut, color);
        cout << c;
    }
    #endif
}screen;

class Food{
    public:
    vector<int> FoodXY = { };
    void GenerateFood(){
        srand(time(NULL));
        WIDTH--;
        HEIGHT--;
        int RandX = rand() % WIDTH + 1;
        int RandY =  rand() % HEIGHT + 1;
        FoodXY = { RandX , RandY };
        for(auto c: snake.TailX){
            if(FoodXY[0] == snake.TailX[c] && FoodXY[1] == snake.TailY[c]){
                GenerateFood();
            }
        }
        WIDTH++;
        HEIGHT++;
    }
}food;

int main(){
    bool gameOver = false;
    food.GenerateFood();
    snake.TailX.reserve(HEIGHT*WIDTH);
    snake.TailY.reserve(HEIGHT*WIDTH);
    while(!gameOver){
        screen.hideCursor();
        snake.KeyB();
        for(int i = 0; i <= WIDTH; i++){
            for(int j = 0; j <= HEIGHT; j++){
                if(j == 0 || j == HEIGHT){
                    screen.Draw(i, j, '#', 15);
                }
                else if(i == 0 || i == WIDTH){
                    screen.Draw(i, j, '#', 15);
                }
            }
        }
        if(snake.SnakeXY[0] == 0 || snake.SnakeXY[0] == WIDTH || snake.SnakeXY[1] == 0 || snake.SnakeXY[1] == HEIGHT){
            gameOver = true;
        }
        if(snake.U == 1){
            snake.SnakeXY[1]--;
        }
        else if(snake.D == 1){
            snake.SnakeXY[1]++;
        }
        else if(snake.L == 1){
            snake.SnakeXY[0]--;
        }
        else if(snake.R == 1){
            snake.SnakeXY[0]++;
        }
        int tempX = snake.SnakeXY[0];
        int tempY = snake.SnakeXY[1];
        if(snake.SnakeXY[0] == food.FoodXY[0] && snake.SnakeXY[1] == food.FoodXY[1]){
            snake.length++;
            screen.Draw(food.FoodXY[0], food.FoodXY[1], ' ', 30);
            food.GenerateFood();
        }
        screen.Draw(snake.SnakeXY[0], snake.SnakeXY[1], snake.head, 10);
        screen.Draw(food.FoodXY[0], food.FoodXY[1], 'F', 12);
        Sleep(100);
        if(snake.length < 1){
            screen.Draw(tempX, tempY, ' ', 0);
        }
        else{
            //Draw Tail
            for(int c = 0; c < snake.length; c++){
                screen.Draw(snake.TailX[c], snake.TailY[c], ' ', 0);
                if(c > 0 && snake.SnakeXY[0] == snake.TailX[c] && snake.SnakeXY[1] == snake.TailY[c]){
                    gameOver = true;
                }
            }
            screen.Draw(tempX, tempY, ' ', 0);
            int prevX = snake.TailX[0];
            int prevY = snake.TailY[0];
            int prev2X, prev2Y;
            snake.TailX[0] = snake.SnakeXY[0];
            snake.TailY[0] = snake.SnakeXY[1];
            for(int i = 1; i <= snake.length; i++){
                prev2X = snake.TailX[i];
                prev2Y = snake.TailY[i];
                snake.TailX[i] = prevX;
                snake.TailY[i] = prevY;
                prevX = prev2X;
                prevY = prev2Y;
            }
            for(int c = 0; c < snake.length; c++){
                screen.Draw(snake.TailX[c], snake.TailY[c], snake.tail, 2);
            }
            if(snake.length == HEIGHT * WIDTH - 1){
                screen.Draw(WIDTH/2-5, HEIGHT/2, "YOU WIN!", 32);
                getch();
            }
        }
        screen.gotoxy(0, HEIGHT + 1);
        printf("Score: %i", snake.length);
    }
    screen.Draw(WIDTH/2-5, HEIGHT/2, "Game Over!", 11);
    screen.gotoxy(WIDTH/2-5, HEIGHT/2 - 1);
    printf("Score: %i", snake.length);
    Sleep(200);
    getch();
}
