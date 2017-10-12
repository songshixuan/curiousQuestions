#include <iostream>
using namespace std;

struct Node{
    Node(int x,Node* p = nullptr,Node *n = nullptr):val(x),next(n),prev(p){

    }
    Node* prev;
    Node* next;
    int val;
};

class BiList{
    public:
        BiList():head(nullptr){

        }
        void push_front(int x){
            cout << "push_front " <<x <<endl;
            Node * n  = new Node(x);
            n->next = head;
            if(head != nullptr){
                head->prev = n;

            }
            head = n;
            n->prev = nullptr;
        }


        void print(){
            Node * itr = head;
            while(itr != nullptr){
                cout << itr->val << ";";
                itr = itr->next;
            }
        }

    private:
        Node *head;

};



int main(){
    BiList list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    list.print();
    return 0;
}
