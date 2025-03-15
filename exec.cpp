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
    };
    void push(int inVal){
        if(!isFull()){
            cards[index++] = inVal;
        } else {
            std::cout << "deck is currently full\n"; //make into exception
            return;
        }
    };
    bool isEmpty(){
        return next == 0;
    };
    bool isFull(){
        return next == 5;
    };
    int count(){
        return index;
    };
};

class deck{
    private:
        struct card {
            int value = 0;
            struct card *next = nullptr;
            card(int inVal){
                value = inVal;
            }
        };
        card *head;

    public:
        deck(){
            head = nullptr;
        };
        ~deck(){
            card *temp = nullptr;
            while(head != nullptr){
                temp = head;
                while(temp != nullptr){
                    temp = temp->next;
                }
                temp->next = nullptr;
                delete temp;
            }
            delete head;
        };
        bool isEmpty(){
            return head == nullptr;
        }
        void push(int inVal){
            card *temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = new card(inVal);
        };
        int pop(){
            if(isEmpty()){
                std::cout << "deck is currently empty\n"; //make into exception
                return -1;
            }
            int retVal = head->value;
            card *temp = head;
            head = head->next;
            delete temp;
            return retVal;
        };
        int peek(){
            if(isEmpty()){
                std::cout << "deck is currently empty\n"; //make into exception
                return -1;
            }
            return head->value;
        };
        int count(){
            int retVal = 0;
            card *temp = head;
            while(temp != nullptr){
                retVal++;
            }
            return retVal;
        };
};

int main(){
    bool style;
    std::cout << "What style of play would you prefer:\n\t0: rounds\n\t1: all out\n";
    std::cin >> style;
    int numberOfRounds = -1;
    if(style){
        std::cout << "How many rounds do you want to play?\n";
        std::cin >> numberOfRounds;
        while(numberOfRounds <= 0){
            std::cout << "Number of rounds must be a positive, non-zero number\n";    
            std::cin >> numberOfRounds;
        }
    }
    // initilialize & declare all variables to be used
    deck myDeck;
    pile myPile;
    deck pcDeck;
    pile pcPile;

    // play function
    for(int i = numberOfRounds; i != 0; i--){
        
    }
}
