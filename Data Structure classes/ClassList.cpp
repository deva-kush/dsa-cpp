#include<iostream>
using namespace std;

class Node{
public:
    int data;
    Node *next;

public:
    Node(int val){
        data = val;
        next = nullptr;
    }

    ~Node(){
        // Keep Node destructor trivial: do NOT delete `next` here.
        // Deleting the whole list should be done iteratively in List::~List()
        // to avoid deep recursive deletion (stack overflow / recursive terminate).
    }
};

class List{
public:
    Node *head;
    Node *tail;
public:
    List(){ head = nullptr; tail = nullptr;}
    ~List(){
        // Iteratively delete nodes to avoid recursion.
        Node* curr = head;
        while(curr){
            Node* nxt = curr->next;
            curr->next = nullptr;
            delete curr;
            curr = nxt;
        }
        head = nullptr;
        tail = nullptr;
    }

    void push_front(int val){
        Node *newNode = new Node(val);

        if(head == nullptr){
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
    }

    void push_back(int val){
        Node *newNode = new Node(val);

        if(head == nullptr){
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void displayList(){
        if(!head){
            cout << "No List exists";
            return;
        }
        Node *p = head;
        while(p){
            cout << p->data;
            if(p->next) cout << "->";
            p = p->next;
        }
        cout << "\n";
    }

    void insert(int val, int pos){
        Node* newNode = new Node(val);

        Node* p = head;
        for(int i=0; i<pos-1; i++){
            if(!p){
                cout << "Invalid index";
                return;
            }
            p = p->next;
        }

        newNode->next = p->next;
        p->next = newNode;
    }

    int pop_front(){
        if(!head){
            cout <<"List is empty";
            return 0;
        }
        Node *temp = head;
        head = head->next;
        int x = temp->data;
        temp->next = NULL;
        delete temp;
        return x;
    }

    int pop_back(){
        if(!head){
            cout <<"List is empty!";
            return 0;
        }

        Node *temp = head;
        int x = temp->data;

        while(temp->next->next){
            temp = temp->next;
        }
        temp->next = NULL;
        delete tail;
        tail = temp;
        return x;
    }

    int itrSearch(int key){
        Node *temp = head;
        int idx = 0;
        while(temp){
            if(temp->data == key)
                return idx;
            
                temp = temp->next;
                idx++;
        }

        return -1;
    }

    int helper(Node *temp, int key) {

        if(temp == NULL){
            return -1;
        }

        if(temp->data == key)
            return 0;
        int idx = helper(temp->next, key);

        if(idx == -1)
            return -1;
        
        return idx + 1;
    }

    int recSearch(int key){
        return helper(head, key);
    }

    int getSize(){
        int sz = 0;
        Node *temp = head;
        while(temp){
            temp = temp->next;
            sz++;
        }

        return sz;
    }
    void removeLastNth(int n){
        int size = getSize();
        Node *prev = head;

        for(int i=1; i<(size-n); i++){
            prev = prev->next;
        }
        prev->next = prev->next->next;
    }

    bool isCycle(Node *head){
        Node *slow = head;
        Node *fast = head;

        while(fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;

            if(slow == fast){
                cout << "Cycle exists!";
                return true;
            } 
        }

        cout <<"Cycle doesn't exists!";
        return false;
    }

    void removeCycle(Node* head){
        Node* slow = head;
        Node* fast = head;
        bool isCycle = false;
        
        while(fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;

            if(slow == fast){
                cout <<"Cycle exists!";
                isCycle = true;
                break;
            }
        }

        if(!isCycle){
            cout << "No cycle exists idiot!";
            return;
        }

        slow = head;

        if(slow == head) {
            while(fast->next != slow){
                fast = fast->next;
            }
            fast->next = NULL;

        } else {
            Node* prev = fast;
            while(slow != fast){
                slow = slow->next;
                prev = fast;
                fast = fast->next;
            }
            prev->next = NULL;
        }
    }

    
};

Node* splitAtMid(Node* head){
        Node* slow = head;
        Node* fast = head;
        Node* prev = NULL;

        while(fast != NULL && fast->next != NULL){
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        if(prev)
            prev->next = NULL;
        
        return slow;
}

Node* merge(Node *left, Node* right){
    List ans;
    Node* i = left;
    Node* j = right;

    while(i && j){
        if(i->data <= j->data){
            ans.push_back(i->data);
            i = i->next;
        } else {
            ans.push_back(j->data);
            j = j->next;
        }
    }

    while(i){
        ans.push_back(i->data);
        i = i->next;
    }

    while(j){
        ans.push_back(j->data);
        j = j->next;
    }
    // Transfer ownership of the created nodes out of the local `ans` list.
    // If we return `ans.head` directly, `ans`'s destructor will run
    // when it goes out of scope and delete those nodes, leaving a
    // dangling pointer and causing double-delete / recursive terminate.
    Node* result = ans.head;
    ans.head = nullptr; // prevent destructor from deleting nodes
    ans.tail = nullptr;
    return result;
}

Node* mergeSort(Node* head){
    if(!head || !(head->next))
        return head;

    Node* rightHead = splitAtMid(head);

    Node* left = mergeSort(head);
    Node* right = mergeSort(rightHead);
    return merge(left, right);
}

int main(){
    List l1, l2;

    for(int i = 1; i<3; i++){
        
        l1.push_back(2*i);
        l1.push_back(3*i);
    }

    l1.head = mergeSort(l1.head);
    l1.displayList();
    
}
// l1.push_back(2);
// l1.push_back(4);
// l1.push_back(6);
// l1.push_back(8);
// l1.push_back(10);
// l1.displayList();

// l2.push_front(15);
// l2.push_front(12);
// l2.push_front(9);
// l2.push_front(6);
// l2.push_front(3);
// l2.displayList();

// l1.insert(20,3);
// l1.displayList();

// cout << l1.pop_front();
// cout <<l1.pop_back();
// cout <<l1.itrSearch(4);
// cout << l1.recSearch(4);
// l1.removeLastNth(2);