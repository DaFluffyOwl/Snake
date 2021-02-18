#ifdef _WIN32
#include <windows.h>
#else
#error "OS not supported"
#endif
#include <stdio.h>
#include <iostream>
#include <array>
#include <conio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

<<<<<<< Updated upstream
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
=======
int HEIGHT = 20, WIDTH = 40;
class Snake{
    public:
    bool L = 0, R = 0, U = 0, D = 0;
    char head = '@', tail = 'o';
    int length = 0;
    vector<int> SnakeXY = {WIDTH/2, HEIGHT/2};
    vector<int> TailX = { };
    vector<int> TailY = { };
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
>>>>>>> Stashed changes
    }
    void Draw(short x, short y, char a){
        gotoxy(x, y);
        cout << a;
    }
<<<<<<< Updated upstream
    void AppendSnake(){
        snakeLength++;
    }
}snake;

=======
    template<typename T>
    void Draw(short x, short y, T c){
        gotoxy(x, y);
        cout << c;
    }
    #endif
}screen;
>>>>>>> Stashed changes

class Food{
    public:
    vector<int> FoodXY = { };
    void GenerateFood(){
        srand(time(NULL));
        FoodXY = {rand() % WIDTH + 1, rand() % HEIGHT + 1};
        if(FoodXY[0] == 0){
            FoodXY[0]++;
        }
        if(FoodXY[1] == 0){
            FoodXY[1]++;
        }
        screen.Draw(FoodXY[0], FoodXY[1], 'F');
    }
}food;

int main(){
<<<<<<< Updated upstream
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
=======
    bool gameOver = false;
    food.GenerateFood();
    while(!gameOver){
        screen.hideCursor();
        snake.KeyB();
        for(int i = 0; i <= WIDTH; i++){
            for(int j = 0; j <= HEIGHT; j++){
                if(j == 0 || j == HEIGHT){
                    screen.gotoxy(i, j);
                    cout << "#";
                }
                else if(i == 0 || i == WIDTH){
                    screen.gotoxy(i, j);
>>>>>>> Stashed changes
                    cout << "#";
                }
            }
        }
<<<<<<< Updated upstream
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
=======
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
            screen.Draw(food.FoodXY[0], food.FoodXY[1], ' ');
            food.GenerateFood();
        }
        screen.Draw(snake.SnakeXY[0], snake.SnakeXY[1], snake.head);
        Sleep(100);
        if(snake.length < 1){
            screen.Draw(tempX, tempY, ' ');
        }
        else{
            //Draw Tail
            screen.Draw(tempX, tempY, ' ');
        }
        screen.Draw(WIDTH + 1, HEIGHT + 1, food.FoodXY[0]);
        screen.Draw(WIDTH + 1, HEIGHT + 2, food.FoodXY[1]);
        screen.Draw(WIDTH + 1, HEIGHT + 3, snake.SnakeXY[0]);
        screen.Draw(WIDTH + 1, HEIGHT + 4, snake.SnakeXY[1]);
    }

    screen.Draw(WIDTH/2-5, HEIGHT/2, "Game Over!");
    screen.gotoxy(WIDTH/2-5, HEIGHT/2 - 1);
    printf("Score: %i", snake.length);
    getch();
>>>>>>> Stashed changes
}
