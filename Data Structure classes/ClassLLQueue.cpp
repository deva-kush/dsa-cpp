#include<iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int data){
        this->data = data;
        this->next = nullptr;
    }
};

class Queue {
    Node* head;
    Node* tail;
public:
    Queue(): head(nullptr), tail(nullptr){}
    ~Queue() {
        // Clean up all nodes
        while(head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    void push(int val) {
        Node* newNode = new Node(val);
        if(!head){
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    void pop() {
        if (empty()) {
            cout << "Queue is empty\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        if (!head) {
            tail = nullptr;  // Queue is now empty
        }
        delete temp;
    }
    int front() {
        if (empty()) {
            cout << "Queue is empty\n";
            return -1;  // Or throw an exception if preferred
        }
        return head->data;
    }
    bool empty() {
        return head == nullptr;
    }
};


int main(){
    Queue q;

    q.push(2);
    q.push(4);
    q.push(6);

    while(!q.empty()) {
        cout << q.front() << endl;
        q.pop();
    }
    return 0;
}