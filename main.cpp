#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

class Snake{
    public:
    
}snake;
class Screen{
    public:
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    void gotoxy(short x, short y){
        //Set the Curson Position of the console 
        COORD coord = {x, y};
        SetConsoleCursorPosition(hStdOut, coord);
    }
    void hideCursor(){
        // Hides the Console's Cursor
        info.dwSize = 100;
        info.bVisible = false;
        SetConsoleCursorInfo(hStdOut, &info);
    }
}screen;

int main(){
    bool gameOver = false;
    while(!gameOver){
        screen.hideCursor();
        screen.gotoxy(10, 10);
    }
}
