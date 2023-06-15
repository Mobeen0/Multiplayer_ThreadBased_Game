/*
Assignment #2
Course: Operating Systems

Name : Muhammad Mobeen
Roll Num : 21i-0444
Section : C

*/

#include <SFML/Graphics.hpp>
#include<iostream>
#include<time.h>
#include<pthread.h>
#include<unistd.h>
#include "utility.h"
#include<string>
using namespace std;
using namespace sf;


int getBoardSize(){
    int RollNum = 0444;
    int randomNum,lastDigit=4,N;
    	srand(unsigned (time(0)));
   	randomNum= rand()%90 + 10;
    
    	randomNum*=4;
    	N = RollNum/randomNum;
    
   	N = N%25;
    
    	if(N<10)
    		N+=15;
    
    return N;
}
void DrawGrid(RenderWindow&,int,bool **,PlayerLocation[]); // CREATED PlayerLocation in Utility.h myself
bool ** initValues(int size){
    bool ** retVal= new bool *[size];
    for(int i =0;i<size;i++){
        retVal[i] = new bool[size];
    }

    for(int r=0;r<size;r++)
        for(int c=0;c<size;c++)
            retVal[r][c] = false;

    int x,y;
    srand(unsigned(time(0)));
    for(int i =0;i<7;i++){ // creating initial treasure blocks
        x= rand()%size;
        y= rand()%size;
        if(retVal[x][y] || (x==0 && y==0))
            i--;
        else
            retVal[x][y] = true;
    }

return retVal;
}
void UpdateTreasure(bool ** &Treasures,int size,PlayerLocation Players[]){
    int count =0;
    int x,y;
    for(int r=0;r<size;r++){
        for(int c=0;c<size;c++){
            if(Treasures[r][c])
                count++;
        }
    }

    while(count!=7){
        do{
            x = rand()%size;
            y = rand()%size;
        }while(!(Treasures[y][x]) && (Players[0].x!=x &&Players[0].y!=y)
        &&(Players[1].x!=x && Players[1].y!=y) && 
        (Players[2].x!=x && Players[2].y!=y));
        Treasures[y][x]=true;
        count++;
    }

}

void PollThreadResults(GameInfo first,GameInfo second,GameInfo third,GameInfo& gameInfo){


    if(first == second)
        gameInfo = third;
    if(first == third)
        gameInfo = second;
    if(second == third)
        gameInfo = first;
    
    // results polled only the updated value is stored in gameINfo
}

void * Player1Thread(void * Args){ // PLAYER 1 MOVEMENT

    GameInfo * gameInfo = (GameInfo*)Args; // GAMEInfo is user defined in Utility.h


        if(gameInfo->PassValue==71){ // LEFT KEY PRESSED
            if(gameInfo->Players[0].x != 0){
                gameInfo->Players[0].x -=1;
            }
        }
        if(gameInfo->PassValue==72){ // RIGHT KEY
            if(gameInfo->Players[0].x != gameInfo->boardsize-1)
                gameInfo->Players[0].x +=1;
        }
        if(gameInfo->PassValue==73){ // UP KEY
            if(gameInfo->Players[0].y != 0)
                gameInfo->Players[0].y -=1;
        }
        if(gameInfo->PassValue==74){ // DOWN KEY
            if(gameInfo->Players[0].y != gameInfo->boardsize-1)
                gameInfo->Players[0].y +=1;
        }
        if(gameInfo->Treasures[gameInfo->Players[0].y][gameInfo->Players[0].x]){ // treasure exists
            gameInfo->Treasures[gameInfo->Players[0].y][gameInfo->Players[0].x] = false;
            gameInfo->Players[0].score+=1;
            UpdateTreasure(gameInfo->Treasures,gameInfo->boardsize,gameInfo->Players);
        }

    //cout << "Returning status = 1" << endl; 
pthread_exit((void*)gameInfo);


return NULL;
}

void * Player2Thread(void * Args){ // PLAYER 2 MOVEMENT


    GameInfo * gameInfo = (GameInfo*)Args;


        if(gameInfo->PassValue==0){ // A KEY PRESSED
            if(gameInfo->Players[1].x != 0)
                gameInfo->Players[1].x -=1;
        }
        if(gameInfo->PassValue==3){ // D KEY
            if(gameInfo->Players[1].x != gameInfo->boardsize-1)
                gameInfo->Players[1].x +=1;
        }
        if(gameInfo->PassValue==22){ // W KEY
            if(gameInfo->Players[1].y != 0)
                gameInfo->Players[1].y -=1;
        }
        if(gameInfo->PassValue==18){ // S KEY
            if(gameInfo->Players[1].y != gameInfo->boardsize-1)
                gameInfo->Players[1].y +=1;
        }
        if(gameInfo->Treasures[gameInfo->Players[1].y][gameInfo->Players[1].x]){ // treasure exists
            gameInfo->Treasures[gameInfo->Players[1].y][gameInfo->Players[1].x] = false;
            gameInfo->Players[1].score+=1;
            UpdateTreasure(gameInfo->Treasures,gameInfo->boardsize,gameInfo->Players);
        }
        //cout << "Returning status = 2" << endl; 

pthread_exit((void*)gameInfo);

return NULL;
}

void * Player3Thread(void * Args){ // PLAYER 3 MOVEMENT

GameInfo * gameInfo = (GameInfo*)Args;


    if(gameInfo->PassValue==9){ // J KEY PRESSED
        if(gameInfo->Players[2].x != 0)
            gameInfo->Players[2].x -=1;
    }
    if(gameInfo->PassValue==11){ // L KEY
        if(gameInfo->Players[2].x != gameInfo->boardsize-1)
            gameInfo->Players[2].x +=1;
    }
    if(gameInfo->PassValue==8){ // I KEY
        if(gameInfo->Players[2].y != 0)
            gameInfo->Players[2].y -=1;
    }
    if(gameInfo->PassValue==10){ // K KEY
        if(gameInfo->Players[2].y != gameInfo->boardsize-1)
            gameInfo->Players[2].y +=1;
    }
    if(gameInfo->Treasures[gameInfo->Players[2].y][gameInfo->Players[2].x]){ // treasure exists
        gameInfo->Treasures[gameInfo->Players[2].y][gameInfo->Players[2].x] = false;
        gameInfo->Players[2].score+=1;
        UpdateTreasure(gameInfo->Treasures,gameInfo->boardsize,gameInfo->Players);
    }
    //cout << "Returning status = 3" << endl; 
pthread_exit((void*)gameInfo);

return NULL;
}


void RunGame(){



    pthread_t Player1,Player2,Player3;
    void * Arguments;
    void * retVal1; void* retVal2; void* retVal3;
    int size = getBoardSize();
    bool ** Treasure=initValues(size);
    cout << "Size = " << size << endl;

    RenderWindow window(VideoMode(1280, 900), "i21-0444 Game Window");
    GameInfo gameInfo(window,Treasure,size); // CREATED DATA TYPE IN Utility.h MYSELF

    //Queue<GameInfo> myq;
    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();


            if(event.type==Event:: KeyPressed){
                
                gameInfo.PassValue = event.key.code;
                Arguments = (void*)&gameInfo;
                pthread_create(&Player1,NULL,Player1Thread,Arguments);
                pthread_create(&Player2,NULL,Player2Thread,Arguments);
                pthread_create(&Player3,NULL,Player3Thread,Arguments); // THREADS RUN SIMULTANEOUSLY 
                pthread_join(Player1,&retVal1);
                //myq.Enqueue(*((GameInfo*) retVal1));
                pthread_join(Player2,&retVal2);
                //myq.Enqueue(*((GameInfo*) retVal2));
                pthread_join(Player3,&retVal3);
                //myq.Enqueue(*((GameInfo*) retVal3)); // QUEUE implementation but got rid of it
                //gameInfo = *((GameInfo*) Arguments); // Only the the updated value gotten
                PollThreadResults(*((GameInfo*) retVal1),*((GameInfo*) retVal2),*((GameInfo*) retVal3),gameInfo); // polling results
            }
        }

        DrawGrid(window,size,Treasure,gameInfo.Players);
    }


    for(int i =0;i<size;i++){
        delete[] Treasure[i];
    }
    delete[] Treasure;

}

void setContents(string & str,PlayerLocation Players[]){
    str="";
    str+="* Player 1: ";
    str+= to_string(Players[0].score);
    str+='\n';
    str+="* Player 2: ";
    str+= to_string(Players[1].score);
    str+='\n';
    str+="* Player 3: ";
    str+= to_string(Players[2].score);

}

int main()
{

    RunGame();

    return 0;
}

void DrawGrid(RenderWindow& window,int size, bool ** treasure,PlayerLocation players[]){

    int startx,starty;
    float perSquarex,perSquarey;
    RectangleShape Square(Vector2f(30.0f,30.0f));

    startx=-40;
    starty=-180;
    perSquarex=float(1200)/size;
    perSquarey=float(700)/size;
    Square.setSize(Vector2f(perSquarex,perSquarey));
    Square.setFillColor(Color::White);
    Square.setOutlineColor(Color::Black);

    Texture logo,Background,Coin,fences;
    Sprite sprite1,sprite2;

    logo.loadFromFile("UtilityImages/Logo.png");
    Background.loadFromFile("UtilityImages/Background.jpeg");
    Coin.loadFromFile("UtilityImages/goldTreasure.jpeg");
    fences.loadFromFile("UtilityImages/border.jpeg");

    sprite1.setTexture(logo);
    sprite2.setTexture(Background);
    sprite1.setScale(0.2,0.2);
    sprite1.setPosition(Vector2f(600.0f,20.0f));
    sprite2.setScale(1,1.25);



    Texture p1,p2,p3;
    Sprite Player1,Player2,Player3;
    p1.loadFromFile("UtilityImages/Player1.png");
    p2.loadFromFile("UtilityImages/Player2.png");
    p3.loadFromFile("UtilityImages/Player3.png");
    Player1.setTexture(p1);Player2.setTexture(p2);Player3.setTexture(p3); // adding textures
    Player1.setScale(0.1,0.1);Player2.setScale(0.25,0.2);Player3.setScale(0.25,0.2); // setting scales
    Player1.setPosition(Vector2f(float(-startx + (players[0].x * perSquarex)), float(-starty -13 + (players[0].y * perSquarey)))); // offsetting y a little
    Player2.setPosition(Vector2f(float(-startx +10 +(players[1].x * perSquarex)), float(-starty-4 + (players[1].y * perSquarey)))); // offsetting x and y a little
    Player3.setPosition(Vector2f(float(-startx +(players[2].x * perSquarex)), float(-starty -4 + (players[2].y * perSquarey))));

    Font font;
    font.loadFromFile("Font/Aller_Bd.ttf");
    Text ScoreBoard;string content;
    ScoreBoard.setFont(font);
    setContents(content,players);
    ScoreBoard.setCharacterSize(24);
    ScoreBoard.setStyle(Text::Bold);
    ScoreBoard.setString(content);

    window.clear();
    window.draw(sprite2);
    window.draw(sprite1);
    Square.setOutlineThickness(3);
    Square.setOutlineColor(Color::Black);
    for(int r =0;r<size;r++){ // DRAWING THE GAME BOARD
        for(int c=0;c<size;c++){
            if(treasure[r][c]){
                Square.setTexture(&Coin);
            }
            else
                Square.setTexture(NULL);
            Square.setOrigin(startx-(c*perSquarex),starty);
            window.draw(Square);
        }
        starty = starty-perSquarey;
    }
    window.draw(Player1);
    window.draw(Player2);
    window.draw(Player3);
    window.draw(ScoreBoard);
    window.display();
}
