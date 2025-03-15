#include <iostream>

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
