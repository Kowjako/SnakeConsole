#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <fstream>
using namespace std;
bool endgame, walls;
const int kolorconsoli = system( "color 30" );
int x,y, fruitX, fruitY, score, start_time, width, height;
int tailX[100], tailY[100];
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
void Ustawienia() {
    srand(time(NULL));
    endgame = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitX = rand() % width-1;
    fruitY = rand() % height-1;
    score = 0;
}
void Rysowanie() {
    system("cls");
    for(int i=0;i<=width;i++) cout<<"-";
    cout<<endl;
    for(int i=1;i<height;i++) {
        for(int j=0; j< width; j++) {
            if(j==0 || j==width - 1) cout<<"|";
            if(i==y && j==x) cout<<"0"; else
                if(i==fruitY && j==fruitX) cout<<"x";
            else  {

                bool print = false;
                 for(int k=0;k<score;k++) {
                   if(tailX[k]==j && tailY[k]==i) {
                    print = true;
                    cout<<"-";
                   }
                }
                if(!print)
                cout<<" ";
            }
        }
        cout<<endl;
    }
    for(int i=0;i<=width;i++) cout<<"-";
    cout<<endl;
    cout<<"Score = "<<score<<endl;
    cout<<"Time = "<<(clock() - start_time)/1000<<endl;
}
void Wejscie() {
    if(_kbhit()) {
        switch(_getch()) {
        case 'a':
            if (dir != RIGHT || score == 0)dir = LEFT; break;
        case 'd':
            if (dir != LEFT || score == 0) dir = RIGHT; break;
        case 'w':
            if (dir != DOWN || score == 0) dir = UP; break;
        case 's':
            if (dir != UP || score == 0) dir = DOWN; break;
        case 'q':
            dir = STOP; break;
        case 'x':
            endgame = true ; break;
        }
    }
}
void Logika() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X,prev2Y;
    for(int i=1;i<=score;i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir) {
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
    }
    switch(walls) {
        case false: {
            if(x==width-1) x=0; else if(x==-1) x=width-1;
            if(y==height) y=0; else if(y==0) y=height-1;
            break;
        }
        case true: {
            if(x==width || x==0 || y==height || y==0)
            endgame = true;
            break;
        }
    }
    if(x==fruitX && y==fruitY) {
        score++;
        srand(time(NULL));
        fruitX = rand() % width-1;
        fruitY = rand() % height-1;
    }
}
void WriteStats() {
    string Name;
    cout<<"Write your name"<<endl;
    cin>>Name;
    ofstream out;
    out.open("D:\\stats.txt",ios::app);
    if(out.is_open()) {
        out<<score<<" "<<Name<<endl;
    }
}
void BestScore() {
    string line;
    int i =0;
    ifstream in("D:\\stats.txt");
    int bestscore = 0;
    if(in.is_open()) {
        while(getline(in, line)) {
            i=(int)line[0];
            if(i>bestscore) bestscore = i;
        }
    }
    in.close();
    cout<<"BestScore = "<<bestscore-48<<endl;
}
int main()
{
    cout<<"Witam, wkrotce zagrasz w Snake'a"<<endl;;
    cout<<"Wybierz opcje"<<endl;

    cout<<"1 - Nowa gra"<<endl;
    cout<<"2 - Lepszy wynik"<<endl;
    int opcja;
    cin>>opcja;
    system("cls");
    switch(opcja) {
        case 1:
    cout<<"Size X Y"<<endl;
    cin>>width>>height;
    cout<<"walls 1, no walls 0"<<endl;
    cin>>walls;
    start_time = clock();
    Ustawienia();
    while(!endgame) {
        Rysowanie();
        Wejscie();
        Logika();
        Sleep(150);
    }
    cout<<"Result add"<<endl;
    WriteStats();
    system("cls");
        break;
        case 2: BestScore();
        break;
    }
    return 0;
}
