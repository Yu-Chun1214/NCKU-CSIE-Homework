#include<iostream>
#include<vector>
#include<time.h>

using namespace std;

class tile{
    int x,y;
    int count;
public:
    tile(int px, int py){
        x = px;
        y = py;
        count = 0;
    }
    int X(){return x;}
    int Y(){return y;}
    int Count(){return count;}
    int operator ++(int);
};

int tile::operator++(int){
    ++count;
    return count;
}

class Bug{
private:
    int x,y;
    int steps;
    int imove[8];
    int jmove[8];
    int Random();

public:
// constructor
    Bug(int Ox,int Oy){
        x = Ox;
        y = Oy;
        steps = 0;
        imove[0] = imove[6] = imove[7] = -1;
        imove[1] = imove[5] = 0;
        imove[2] = imove[3] = imove[4] = 1;

        jmove[0] = jmove[1] = jmove[2] = 1;
        jmove[3] = jmove[7] = 0;
        jmove[4] = jmove[5] = jmove[6] = -1;
    }
public:
    // return value which is private menber
    int XPosition();
    int YPosition();
    
    void Walk(vector<tile *>&square);
};

class Game{
private:
    vector<vector<tile> >Tiles;
    int Rows,Cols;

public:
    // constructor
    Game(int m,int n){
        Cols = m;
        Rows = n;
        vector<tile> row;
        for(int i = 0; i < Rows; ++i){
            row.clear();
            for(int j = 0;j < Cols; j++){
                tile temp(j,i);
                row.push_back(temp);
            }
            Tiles.push_back(row); 
        }
    }
    bool IsOver();
    void Print();
    void Play(Bug bug);
};

void Game::Play(Bug bug){
    int px = bug.XPosition(),py = bug.YPosition();
    Tiles[px][py]++;
    vector<tile *> square;
    int count;
    if(px > Cols || py > Rows || px < 0 || py < 0){
        printf("The position of bug is illegal");
        return;
    }
    for(count = 0;count < 50000 && !IsOver();count++){
        px = bug.XPosition();
        py = bug.YPosition();
        square.clear();
        for(int i = px - 1; i <= px + 1; ++i){
            for(int j = py - 1; j <= py + 1; ++j){
                if(i >= 0 && i < Cols && j >= 0 && j < Rows){
                    square.push_back(&Tiles[j][i]);
                }
            }
        }
        bug.Walk(square);
    }
    cout<<"Total moves: "<<count<<endl;
}

void Game::Print(){
    for(int i = 0; i < Tiles.size(); i++){
        for(int j = 0; j < Tiles[i].size(); j++){
            printf("%6d",Tiles[i][j].Count());
        }
        printf("\n");
    }
}

bool Game::IsOver(){
    for(int i = 0; i < Tiles.size(); i++){
        for(int j = 0; j < Tiles[i].size(); j++){
            if(Tiles[i][j].Count() == 0)
                return false;
        }
    }
    return true;
}

int Bug::Random(){
    return rand()%8;
}

int Bug::XPosition(){
    return x;
}

int Bug::YPosition(){
    return y;
}

void Bug::Walk(vector<tile *>&square){
    int k = 0,movex,movey;
    do{
        k = Random();
        movex = x + imove[k];
        movey = y + jmove[k];
        for(int i = 0; i < square.size(); i++){
            if(square[i]->X() == movex && square[i]->Y() == movey){
                (*square[i])++;
                x = movex;
                y = movey;
                return;
            }
        }
    }while(true);
}

int main(){
    srand(time(NULL));
    cout<<"Experiment 1 :"<<endl;
    Bug bug1(10,10);
    Game game1(15,15);
    game1.Play(bug1);
    game1.Print();
    ///////////////////////////////////////////////////
    cout<<"Experiment 2 :"<<endl;
    Bug bug2(1,1);
    Game game2(19,39);
    game2.Play(bug2);
    game2.Print();
}