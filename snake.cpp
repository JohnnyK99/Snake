#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>

int boardSize;

using namespace std;

struct field{
    int x;
    int y;
};

void clearScreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

field getDot(){
    field tmp;
    tmp.x = rand()%(boardSize-2);
    tmp.y = rand()%(boardSize-2);
    return tmp;
}

bool contains(vector<field> vector, field field){
    for(int i = 0; i<vector.size(); i++){
        if(vector.at(i).x == field.x && vector.at(i).y == field.y){
            return true;
        }
    }
    return false;
}

void show(vector<field> vector, field dot, int score){
    clearScreen();

    char tab[boardSize-2][boardSize-2];
    for(int i = 0; i<boardSize-2; i++){
        for(int j = 0; j<boardSize-2; j++){
            tab[i][j] = ' ';
        }
    }

    tab[dot.x][dot.y] = '*';

    for(int i = 0; i<vector.size(); i++){
        tab[vector.at(i).x][vector.at(i).y] = 'O';
    }

    for(int i = 0; i<boardSize; i++){
        cout<<"X ";
    }
    cout<<endl;
    for(int i = 0; i<boardSize-2; i++){
        cout<<"X ";
        for(int j = 0; j<boardSize-2; j++){
            cout<<tab[i][j]<<" ";
        }
        cout<<"X ";
        cout<<endl;
    }
    for(int i = 0; i<boardSize; i++){
        cout<<"X ";
    }
    cout<<endl<<"SCORE: "<<score<<endl;
}

void move(vector<field> *vector, int direction, field *dot, int *score, bool *end){
    field tmp = vector->back();

    switch(direction){
        case -2: {
            tmp.x++;
            break;
        }
        case -1: {
            tmp.y++;
            break;
        }
        case 1: {
            tmp.y--;
            break;
        }
        case 2:{
            tmp.x--;
            break;
        }
        default:{

        }
    }

    if(tmp.y != 0 && (tmp.y % (boardSize-2) == 0 || tmp.y == -1)){
        *end = true;
    }

    if(tmp.x != 0 && (tmp.x % (boardSize-2) == 0 || tmp.x == -1)){
        *end = true;
    }

    if(contains(*vector, tmp)){
        *end = true;
    }
    else{
        vector->push_back(tmp);
    }

    if(vector->back().x == dot->x && vector->back().y == dot->y ){
        dot->x = -1;
        (*score)++;
    }
    else{
        vector->erase(vector->begin());
    }

}

int main() {

    cout<<"Enter board size: ";
    cin>>boardSize;

    system("cls");

    int difficulty;
    cout<<"Choose difficulty: \n1  Easy\n2  Medium\n3  Hard\n";
    cin>>difficulty;

    difficulty = ((4-difficulty)*100);

    vector<field> snake;
    int tmp, dir = -1, score = 0;
    bool end = false;
    field dot = getDot();

    snake.push_back(field{boardSize/2,boardSize/2});

    srand(time(NULL));

    while(1) {
        show(snake, dot, score);
        Sleep(difficulty);
        if (kbhit()) {
            tmp = _getch();
        }
        switch (tmp) {
            case 119: {
                tmp = 2;
                break;
            }
            case 115: {
                tmp = -2;
                break;
            }
            case 97: {
                tmp = 1;
                break;
            }
            case 100: {
                tmp = -1;
                break;
            }
            default: {
                tmp = dir * -1;
            }
        }

        if (tmp != dir * -1)
            dir = tmp;

        move(&snake, dir, &dot, &score, &end);

        if (end) {
            cout << "YOU LOST\n";
            return 0;
        }
        if (dot.x == -1)
            dot = getDot();
    }

}

