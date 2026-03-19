#include <iostream> // include the iostream library so we can use cout
using namespace std; // put all the items from std into scope 
// so we don't have to use the scope resolution operator like std::cout

// create constants for the minimum and maximum TODO find these
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList { // create a class named DoublyLinkedList
private: // these class members cannot be accessed outside the class
    struct Node { // create a struct named Node; this will be each node in the list
        int data; // create a member variable of node named data that stores an integer
        // this int is the data value stored in the list; the other struct members are pointers
        // that create the structure of the list

        Node* prev; // create a pointer to a Node, named prev, which will store a pointer to the previous list item
        Node* next; // create a pointer to a Node, named next, which will store a pointer to the next list item
        
        // Node constructor with parameters to set the data and the previous and next pointers
        Node(int val, Node* p = nullptr, Node* n = nullptr) { // default pointer values are nullptr, which need to be the values when we start the list with just one node
            data = val; // assign the value of the first argument to the data member variable of the Node
            prev = p; // assign the value of the 2nd argument if there is one to the Node's prev pointer
            next = n; // assign the value of the 3rd argment if there is one to the Node's next pointer
        } // end of the constructor
    }; // end of the class definition

    Node* head; // create a pointer to a Node, named head; this will be the head pointer for the beginning of the list
    Node* tail; // create a pointer to a Node, named tail; this will be the tail pointer for the end of the list

public: // the following members of the DLL class are accessible outside of the class
    DoublyLinkedList() { head = nullptr; tail = nullptr; } // default constructor; will be called when no arguments are provided

    void insert_after(int value, int position) { // public member function to insert a new item into the list with the value and position from the arguments provided by caller
        if (position < 0) { // they have to enter a position at least 0 because that's the first item
            cout << "Position must be >= 0." << endl; // show an error message
            return; // just end the function because the argument was invalid
        } // end of input validation function

        Node* newNode = new Node(value); // dynanmically allocate memory for a Node with the value given by the argument
        if (!head) { // if head == nullptr, that means the list is empty
            head = tail = newNode; // this is the first and only item, so both head and tail should point to it
            return; // end the function
        } // end of checking for empty list

        Node* temp = head; // create a temp pointer and start it with the same address and head
        for (int i = 0; i < position && temp; ++i) // traverse the list until we either reach the given position or the end of the list
            temp = temp->next; // move to the next node
        // this loop takes us to the position in the list where we need to insert the new node

        if (!temp) { // this is true if the for loop kept going to the tail pointer and we didn't yet get to the specified position
            // i.e. they put in a position >= the size of the list
            cout << "Position exceeds list size. Node not inserted.\n"; // display error message
            delete newNode; // deallocate the memory because we aren't going to insert this node
            return; // end the function
        } // end of checking for position being a too-high number

        // if we've reached this line, we are at the correct position to insert the new node in the list
        newNode->next = temp->next; // assign the new node's next pointer to point to the node after the node we're inserting after
        newNode->prev = temp; // assign the new node's prev pointer to point to the node we're inserting after
        if (temp->next) // if the item we're inserting after is NOT the last item in the list...
            temp->next->prev = newNode; // ... then make the node we're inserting after point to the new node
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}