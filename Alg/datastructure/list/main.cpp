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
        virtual  ~BiList(){
            Node*itr = head;
            while (itr != nullptr){
                auto next = itr->next;
                cout << "delete " << itr->val << endl;
                delete itr;
                itr = nullptr;
                itr = next;

            }
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

        void del_first_of(int x){
            Node * itr = head;
            while(itr != nullptr){
                if(itr->val == x){
                    break;
                }
                itr = itr->next;
            }
            if(itr == nullptr){
                return;
            }

            Node * preNode = itr->prev;
            if(preNode != nullptr){
                preNode->next = itr->next;
            }
            Node * nextNode = itr->next;
            if(nextNode != nullptr){
                nextNode->prev = preNode;
            }
            delete itr;
            itr = nullptr;
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
    list.push_front(5);
    list.push_front(4);
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    list.del_first_of(4);
    list.print();
    return 0;
}
