#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node *next;
} *head;

/*********** Creating Circular-List from Array **********/
Node* createList(int *A, int n){
    Node *first = new Node;
    Node *last = first;
    Node *newNode;

    first->data = A[0];
    first->next = NULL;
    for(int i=1; i<n; i++){
        //Create a new node
        newNode = new Node;
        newNode->data = A[i];
        newNode->next = NULL;

        //inserting into the list with the 'last' pointer
        last->next = newNode;
        last = newNode;
    }
    last->next = first;
    return first;
}

/********* Display Circular-List *********/
void displayCirList(Node *&head){
    Node *p = head;
    do{
        cout<<p->data;
        if(p->next) cout<<" -> ";
        p = p->next;
    } while(p != head);
}


int main(){
    int A[] = {2,4,6,7,8,10};
    int n = sizeof(A)/sizeof(A[0]);

    Node *head = createList(A,n);
    displayCirList(head);
    

}