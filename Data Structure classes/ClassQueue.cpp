#include<iostream>
using namespace std;

class Queue {
    int* arr;
    int capacity;
    int size;
    int front, rear;

public:
    Queue(int capacity) {
        this->capacity = capacity;
        arr = new int[capacity];
        size = 0;
        front = 0;
        rear = -1;
    }

    void push(int data){
        if(size == capacity){
            cout << "Queue is Full\n";
            return;
        }

        rear = (rear + 1) % capacity;
        arr[rear] = data;
        size++;
        
    }

    void pop(){
        if(empty()) {
            cout << "Queue is empty!";
            return;
        }

        front = (front + 1) % capacity;
        size--;
    }

    int atfront(){
        if(empty()) {
            cout << "Queue is empty!";
            return -1;
        }
        return arr[front];
    }

    bool empty(){
        return size == 0;
    }
};

int main(){
    Queue q(4);
    q.push(2);
    q.push(4);
    q.push(6);
    q.push(8);

    cout << q.atfront() << endl;
    q.pop();
    cout << q.atfront() << endl;
    q.push(5);
    cout << q.atfront() << endl;
    return 0;
}