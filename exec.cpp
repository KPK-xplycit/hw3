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
                temp = temp->next;
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
    int k = std::rand() % 54;
    while(i!=0){
        while(deckBuilder[k] == 0){
            k = std::rand() % 54;
        }
        while(deckBuilder[k]!=0){
            myDeck.push(deckBuilder[k]);
            i--;
            deckBuilder[k] = 0;
        }
        while(deckBuilder[k] == 0){
            k = std::rand() % 54;
        }
        while(deckBuilder[k]!=0){
            pcDeck.push(deckBuilder[k]);
            i--;
            deckBuilder[k] = 0;
        }
    }

    // play function
    for(int i = numberOfRounds; i != 0; i--){
        int myDeckCount = myDeck.count();
        int myPileCount = myPile.count();
        int pcDeckCount = pcDeck.count();
        int pcPileCount = pcPile.count();
        int choice;
        std::cout << "\t\tYou currently have " << myDeckCount << " cards in your deck\n";
        std::cout << "\t\tYou currently have " << myPileCount << " cards in your pile\n";
        std::cout << "\t\tThe computer currently has " << pcDeckCount << " cards in its deck\n";
        std::cout << "\t\tThe computer currently has " << pcPileCount << " cards in its pile\n";
        if(myDeckCount != 0){
            std::cout << "Your current card is " << myDeck.peek() << "\n\t1: Play current card\n\t2: Place current card on pile and play a new random card\n\t3: Pull from pile and play both that card and current card\n";
            std::cin >> choice;
            while((1 > choice || choice > 3) || (choice == 2 && myPile.isFull()) || (choice == 3 && myPile.isEmpty())){
                if(1 > choice || choice > 3){
                    std::cout<< "Your choice must be between 1 and 3\n";
                    std::cin >> choice;
                } else if(choice == 2 && myPile.count() == 5) {
                    std::cout << "Your pile is full: chose 1 or 3\n";
                    std::cin >> choice;
                } else {
                    std::cout << "Your pile is empty: chose 1 or 2\n";
                    std::cin >> choice;
                }
            }
        } else {
            std::cout << "-\tYou have no cards in your deck currently\n-\tYou must play from your side pile\n";
        }
        // pc making choice
        int pcCard1 = 0;
        int pcCard2 = 0;
        if(pcDeckCount != 0) {
            if(pcDeck.peek() <= 5 && pcPile.count() != 5) {
                std::cout << "The computer puts the card it peeked at in its pile and plays the next card in its deck\n";
                pcPile.push(pcDeck.pop());
                pcCard1 = pcDeck.pop();
            } else if(pcDeck.peek() <= 11 && pcPile.count() != 0){
                std::cout << "The computer pulls a card from its pile, playing both the card from the deck and the card from the pile\n";
                pcCard1 = pcDeck.pop();
                pcCard2 = pcPile.pop();
            } else {
                std::cout << "The computer plays the card from its deck\n";
                pcCard1 = pcDeck.pop();
            }
        } else {
            std::cout << "The computer is out of cards in its deck and is forced to play the card from its pile";
            pcCard1 = pcPile.pop();
        }
        int pcScore = pcCard1 + pcCard2;
        // player making choice
        int myCard1 = 0;
        int myCard2 = 0;
        if(myDeckCount != 0){
            switch(choice){
                case 1: // current card
                    myCard1 = myDeck.pop();
                    break;
                case 2: // pile current card
                    myPile.push(myDeck.pop());
                    myCard1 = myDeck.pop();
                    break;
                case 3: // pull pile card
                    myCard1 = myDeck.pop();
                    myCard2 = myPile.pop();
                    break;
            }
        } else {
            myCard1 = myPile.pop();
        }
        int myScore = myCard1 + myCard2;
        // Telling who played what
        std::cout << "You play: ";
        if(myCard1 > 0) {
            std::cout << myCard1;
        }
        if(myCard2 > 0) {
            std::cout << " & " << myCard2;
        }
        std::cout << std::endl << "The computer plays: ";
        if(pcCard1 > 0) {
            std::cout << pcCard1;
        }
        if(pcCard2 > 0) {
            std::cout << " & " << pcCard2;
        }
        std::cout << std::endl;

        if(myScore>pcScore){
            // Adding cards that the player played back to deck
            if(myCard1 > 0){
                myDeck.push(myCard1);
            }
            if(myCard2 > 0){
                myDeck.push(myCard2);
            }
            std::cout << "\tCongrats you won this round\n\tYou have gained: ";
            if(pcCard1 > 0){
                std::cout << pcCard1;
                myDeck.push(pcCard1);
            }
            if(pcCard2 > 0){
                std::cout << " & " << pcCard2;
                myDeck.push(pcCard2);
            }
        } else {
            // Adding cards that the computer played back to deck
            if(pcCard1 > 0){
                pcDeck.push(pcCard1);
            }
            if(pcCard2 > 0){
                pcDeck.push(pcCard2);
            }
            std::cout << "\tDang, you lost this round\n\tThe computer has gained: ";
            if(myCard1 > 0){
                std::cout << myCard1;
                pcDeck.push(myCard1);
            }
            if(myCard2 > 0){
                std::cout << " & " << myCard2;
                pcDeck.push(myCard2);
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        // Win/loss condition for empty deck & pile
        if(pcDeck.count() + pcPile.count() == 0){
            std::cout << "The computer has ran out of cards!\n\tYou win!\n";
            return 1;
        }
        if(myDeck.count() + myPile.count() == 0){
            std::cout << "You have ran out of cards!\n\tYou lose!\n";
            return 1;
        }
    }
    // Win decision for rounds choice:
    if(myDeck.count() + myPile.count() < pcDeck.count() + pcPile.count()) {
        std::cout << "After " << numberOfRounds << " rounds, you have lost:\n\t";
        std::cout << "Your total cards: " << myDeck.count() + myPile.count() << "\n\t";
        std::cout << "Computer\'s total cards: " << pcDeck.count() + pcPile.count();
    } else if (myDeck.count() + myPile.count() > pcDeck.count() + pcPile.count()) {
        std::cout << "After " << numberOfRounds << " rounds, you have won:\n\t";
        std::cout << "Your total cards: " << myDeck.count() + myPile.count() << "\n\t";
        std::cout << "Computer\'s total cards: " << pcDeck.count() + pcPile.count();
    } else {
        std::cout << "After " << numberOfRounds << " rounds, you have tied:\n\t";
        std::cout << "Your total cards: " << myDeck.count() + myPile.count() << "\n\t";
        std::cout << "Computer\'s total cards: " << pcDeck.count() + pcPile.count();
    }
    std::cout << std::endl;
}
