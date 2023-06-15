#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


struct PlayerLocation{
    int x;
    int y;
    int score;

    PlayerLocation(int x=0,int y=0)
    {
        this->x = x;
        this->y = y;
        this->score =0;
    }

    void operator=(PlayerLocation & other){
        this->x=other.x;
        this->y =other.y;
        this->score = other.score;
    }
};

struct GameInfo{
    PlayerLocation Players[3];
    int boardsize;
    bool ** Treasures;
    sf::RenderWindow* GameWindow;
    int PassValue;

    GameInfo(){
        
    }
    GameInfo(RenderWindow &window,bool ** Treasures,int size){
        this->GameWindow = &window;
        this->Treasures=Treasures;
        boardsize =size;
    }

    GameInfo(GameInfo & other){
        this->GameWindow = (other.GameWindow);
        this->boardsize = other.boardsize;
        this->Treasures = other.Treasures;
        for(int i =0;i<3;i++)
            this->Players[i] = other.Players[i];
        this->PassValue = other.PassValue;
    }

    bool operator==(GameInfo & other){
        for(int i =0;i< 3;i++){
            if(Players[i].x != Players[i].x || Players[i].y != Players[i].y)
                return false;
        }
        return false;
    }
    void operator=(GameInfo & other){
        this->GameWindow = (other.GameWindow);
        this->boardsize = other.boardsize;
        this->Treasures = other.Treasures;
        for(int i =0;i<3;i++)
            this->Players[i] = other.Players[i];
        this->PassValue = other.PassValue;
    }
};

template<typename t>
struct Node{

    t data;
    Node<t> * next;

    Node(){
        next =NULL;
    }
};

template<typename t>
class Queue{
private:
    Node<t> * first;
public:
    Queue(){
        first = NULL;
    }
    void Enqueue(t toInsert){
        if(first==NULL){
            first = new Node<t>;
            first->data = toInsert;
            return;
        }
    }

    t Dequeue(){
        t temp=first->data;
        if(first!=NULL){
            Node<t> * prev = first;
            first = first->next;
            delete first;
        }
        return temp;
    }

    bool isEmpty(){
        if(first == NULL)
            return true;
        return false;
    }
};