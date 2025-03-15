#include <iostream>

class pile{
private:
    int cards[5];
    int next = 0;
public:
    int pop(){
        if(!isEmpty()){
            return cards[--next];
        } else {
            std::cout << "deck is currently empty\n"; //make into exception
            return -1;
        }
    }
    void push(int inVal){
        if(!isFull()){
            cards[index++] = inVal;
        } else {
            std::cout << "deck is currently full\n"; //make into exception
            return -1;
        }
    }
    bool isEmpty(){
        return next == 0;
    }
    bool isFull(){
        return next == 5;
    }
    int count(){
        return index;
    }
}
