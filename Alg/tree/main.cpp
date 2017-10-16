#include <iostream>
using namespace std;

struct Node{
    int val;
    Node* l;
    Node* r;
    Node* p;
    Node(int v,Node* left=nullptr,Node* right=nullptr,Node* parent=nullptr):l(left),r(right),p(parent),val(v){

    }
};

struct Tree{

    Tree():root(nullptr){

    }
    virtual ~Tree(){

    }

    void insert(int val){
        Node* newNode = new Node(val);
        Node* p = nullptr;
        Node* x = root;
        while(x != nullptr){
            p = x;
            if(val < x->val){
                x = x->l;
            }else{
                x = x->r;
            }

        }
        newNode->p = p;
        if (p == nullptr){
            cout << "root = " << newNode->val << endl;
            root = newNode;
        }else if(val < p->val){
            p->l = newNode;
        }else{
            p->r = newNode;
        }

    }

    void inorder_traverse(Node *x){
        if(x != nullptr){
            inorder_traverse(x->l);
            cout << x->val << endl;
            inorder_traverse(x->r);
        }
    }

    Node* tree_min(Node* x){
        Node* p = nullptr;
        while(x != nullptr){
            p = x;
            x = x->l;
        }
        return p;
    }

    Node* tree_max(Node* x){
        Node* p = nullptr;
        while(x != nullptr){
            p = x;
            x = x->r;
        }
        return p;
    }

    void del(Node* x){

    }

    Node*  prev(){

    }

    Node* next(Node* x){
        //if has right sub tree
        if(x->r != nullptr){
            return tree_min(x->r);
        }else{
            Node* p = x->p;
            while(p != nullptr && x == p->r){
                x = p;
                p = x->p;
            }
            return p;
        }
    }

    Node *find(Node* n,int x){
        Node* ptr = n;
        while(ptr != nullptr && ptr->val != x){
            if(x < ptr->val){
                ptr = ptr->l;
            }else{
                ptr = ptr->r;
            }
        }
        return ptr;
    }

    Node* root;
};



void testcase1(){
    Tree t;
    t.insert(6);
    t.insert(3);
    t.insert(9);
    t.inorder_traverse(t.root);

}


void testcase2(){
    Tree t;
    t.insert(12);
    t.insert(6);
    t.insert(4);
    t.insert(11);
    t.inorder_traverse(t.root);

    Node* n = t.next(t.root);
    if(n != nullptr){
        cout << n->val << endl;
    }else{
        cout << "next is none" << endl;
    }
}


void testcaseFind(){
    Tree t;
    t.insert(12);
    t.insert(6);
    t.insert(4);
    t.insert(11);

    t.inorder_traverse(t.root);
    int k = 11;
    Node* n = t.find(t.root,k);
    if(n != nullptr){
        cout << "found " << k << endl;
        auto next = t.next(n);
        if(next != nullptr){
            cout << k << "'s next is" << next->val <<endl;
        }
    }else{
        cout << "did't find " << k  << endl;
    }

    k = 99;
    n = t.find(t.root,k);
    if(n != nullptr){
        cout << "found " << k << endl;
    }else{
        cout << "did't find " << k  << endl;
    }


}





int main(){
//    testcase2();
    testcaseFind();

    return 0;
}
