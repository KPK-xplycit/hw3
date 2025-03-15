#include <iostream>
#include <ctime>

class pile{
private:
    int cards[5];
    int next = 0;
public:
    int pop(){
        if(!isEmpty()){
            return cards[--next];
        } else {
            std::cout << "pile is currently empty\n"; //make into exception
            return -1;
        }
    };
    void push(int inVal){
        if(!isFull()){
            cards[next++] = inVal;
        } else {
            std::cout << "pile is currently full\n"; //make into exception
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
        return next;
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
            card *temp;
            while(head != nullptr){
                temp = head;
                head = head->next;
                delete temp;
            }
        };
        bool isEmpty(){
            return head == nullptr;
        }
        void push(int inVal){
        if (head == nullptr) {
            head = new card(inVal);
            return;
        }
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
    std::srand(std::time(nullptr));
    bool style;
    std::cout << "What style of play would you prefer:\n\t0: rounds\n\t1: all out\n";
    std::cin >> style;
    int numberOfRounds = -1;
    if(!style){
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
    int deckBuilder[54]= {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,14,14};
    int i = 54;
    int k;
    while(i!=0){
        k = std::rand() % 54;
        while(deckBuilder[k]!=0){
            myDeck.push(deckBuilder[k]);
            i--;
            deckBuilder[k] = 0;
        }
        k = std::rand() % 54;
        while(deckBuilder[k]!=0){
            pcDeck.push(deckBuilder[k]);
            i--;
            deckBuilder[k] = 0;
        }
    }

    // play function
    for(int i = numberOfRounds; i != 0; i--){
        int choice;
        std::cout << "Your current card is " << myDeck.peek() << "\n\t1: Play current card\n\t2: Place current card on pile and play a new random card\n\t3: Pull from pile and play both that card and current card\n";
        std::cin >> choice;
        while((1 > choice || choice > 3) || (choice == 2 && myPile.isFull()) || (choice == 3 && myPile.isEmpty())){
            if(1 > choice || choice > 3){
                std::cout<< "Your choice must be between 1 and 3\n";
                std::cin >> choice;
            } else if(choice == 2 && myPile.count() == 5) {
                std::cout << "Your pile is full: chose 1 or 3";
                std::cin >> choice;
            } else {
                std::cout << "Your pile is empty: chose 1 or 2";
                std::cin >> choice;
            }
        }
        // pc making choice
        int pcPileCard = 0;
        int pcDeckCard = 0;
        if(pcDeck.peek() <= 5 && pcPile.count() != 5) {
            pcPile.push(pcDeck.pop());
            pcPileCard = pcDeck.pop();
        } else if(pcDeck.peek() <= 11 && pcPile.count() != 0){
            pcDeckCard = pcDeck.pop();
            pcPileCard = pcPile.pop();
        } else {
            pcPileCard = pcDeck.pop();
        }
        int pcScore = pcPileCard + pcDeckCard;
        
        int myDeckCard = 0;
        int myPileCard = 0;
        switch(choice){
        case 1: // current card
            myDeckCard = myDeck.pop();
            break;
        case 2: // pile current card
            myPile.push(myDeck.pop());
            myPileCard = myDeck.pop();
            break;
        case 3: // pull pile card
            myDeckCard = myDeck.pop();
            myPileCard = myPile.pop();
        }
        int myScore = myPileCard + myDeckCard;
        // Tell what computer did and what cards were played overall
        
        
        if(myScore>pcScore){
            std::cout << "Congrats you won this round\n\tYou have gained: ";
            if(pcDeckCard > 0){
                std::cout << pcDeckCard << ", ";
                myDeck.push(pcDeckCard);
            }
            if(pcPileCard > 0){
                std::cout << pcPileCard;
                myDeck.push(pcPileCard);
            }
        } else {
            std::cout << "Dang, you lost this round\n\tThe computer has gained: ";
            if(myDeckCard > 0){
                std::cout << myDeckCard << ", ";
                pcDeck.push(myDeckCard);
            }
            if(myPileCard > 0){
                std::cout << myPileCard;
                pcDeck.push(myPileCard);
            }
        }
        std::cout << std::endl;
    }
}
