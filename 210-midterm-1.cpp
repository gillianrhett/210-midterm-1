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
// these are member functions we can call to work with a DLL object
    DoublyLinkedList() { head = nullptr; tail = nullptr; } // default constructor; will be called when no arguments are provided

    void insert_after(int value, int position) { // public member function to insert a new item into the list
        // does not return a value, needs 2 arguments that are the data value to store and the index of the node we want to insert the new node AFTER
        // which means if the list isn't empty, then this function can't add a node to the front
        if (position < 0) { // they have to enter a position at least 0 because that's the first item
            cout << "Position must be >= 0." << endl; // show an error message
            return; // just end the function because the argument was invalid
        } // end of input validation function

        Node* newNode = new Node(value); // dynanmically allocate memory for a Node with the value given by the argument
        if (!head) { // if head == nullptr, that means the list is empty
            head = tail = newNode; // this is the first and only item, so both head and tail should point to it
            return; // end the function
        } // end of checking for empty list

        Node* temp = head; // create a temporary pointer and start it pointing to the first node in the list
        for (int i = 0; i < position && temp; ++i) // traverse the list until we either reach the given position or the end of the list
            temp = temp->next; // move to the next node
        // this loop takes us to the position in the list where we need to insert the new node
        // if position is 0 then i < position is never true and temp still points to the first item, so the new node will become the second item

        if (!temp) { // this is true if the for loop kept going to the end of the list and we didn't yet get to the specified position
            // i.e. they put in a position > the size of the list
            cout << "Position exceeds list size. Node not inserted.\n"; // display error message
            delete newNode; // deallocate the memory because we aren't going to insert this node after all
            return; // end the function
        } // end of checking for position being a too-high number

        // if we've reached this line, we are at the correct position to insert the new node in the list
        newNode->next = temp->next; // assign the new node's next pointer to point forward to the node after the node we're inserting after
        newNode->prev = temp; // assign the new node's prev pointer to point backward to the node we're inserting after
        if (temp->next) // if the node we're inserting after is NOT the last item in the list...
            temp->next->prev = newNode; // ...the node after the one we're inserting after will have its prev pointer point backward to the new node
        else // else the node we're inserting after IS the last one, therefore the new node becomes the new last one
            tail = newNode; // make tail point to the new last node
        temp->next = newNode; // make the node we're inserting after point forward to the new node
    }

    void delete_val(int value) { // function to delete the first node found with the given value
        // does not return a value
        if (!head) return; // if the list is empty, just end the function

        Node* temp = head; // create a temporary pointer and start it pointing to the first node in the list
        
        while (temp && temp->data != value) 
        // traverse the list until either we reach the first instance of the given value or the end of the list
            temp = temp->next; // the above conditions haven't yet been met so move on to the next node

        if (!temp) return; // if we reached the end of the list without finding the given value, end the function

        if (temp->prev) // if the item with the given value is not the first (its prev pointer isn't nullptr)...
            temp->prev->next = temp->next; // ... then make the item before it point forward to the item after it
        else // else the item with the given value is the first node in the list...
            head = temp->next; // ... then make head point to the second node in the list
        // it's OK to change these because the temp pointer is saving the address of the node we're removing

        if (temp->next) // if the node we're removing is not at the end of the list...
            temp->next->prev = temp->prev; // ...then make the node before it point to the node after it
        else // else the node we're removing IS at the end...
            tail = temp->prev; // ...then make tail point to the second-to-last node

        delete temp; // now that we've changed the pointers, deallocate the memory for the node we're removing
    } // end of the function, so we don't need to assign nullptr to temp because it's going out of scope and getting deleted anyway

    void delete_pos(int pos) { // delete the node at the given position (NOT index; the first item is position 1)
        // does not return a value
        if (!head) { // if the head pointer is nullptr, the list is empty
            cout << "List is empty." << endl; // message lets user know there is nothing to delete
            return; // end the function
        } // end of checking for empty list
    
        if (pos == 1) { // if we want to delete the first item
            pop_front(); // call the function that deletes the first item
            return; // end this function
        } // end of checking whether it's the first item
    
        Node* temp = head; // make a temp pointer and point it at the first node
    
        for (int i = 1; i < pos; i++){ // traverse the list
            if (!temp) { // if we got to the end
                cout << "Position doesn't exist." << endl; // tell user we reached the end and didn't find the position they wanted
                return; // end the function
            } // done checking whether we are at the end of the list
            else // else we are not at the end of the list
                temp = temp->next; // advance to the next node
        } // end of loop to traverse the list
        if (!temp) { // if we reached the end of the list on the last loop iteration
            cout << "Position doesn't exist." << endl; // tell user we reached the end etc. as above
            return; // end the function
        } // done checking for whether the position argument is valid
    
        if (!temp->next) { // if the item to delete is at the end
            pop_back(); // function that deletes the last node
            return; // end this function
        } // done checking whether the item to remove is the last one
    
        Node* tempPrev = temp->prev; // make a temp pointer for saving the prev pointer to the node before the one we're removing
        tempPrev->next = temp->next; // make the node before the one we're removing point forward to the node after the one we're removing
        temp->next->prev = tempPrev; // make the node after the one we're removing point backward to the node before the one we're removing
        delete temp; // now that all the pointers have bypassed the node we're removing, deallocate its memory
    } // end of delete function

    void push_back(int v) { // function to append a node to the end
        // doesn't return a value, takes argument of the value the new node should store
        Node* newNode = new Node(v); // allocate memory for a node with the given value
        if (!tail) // if the list is empty...
            head = tail = newNode; // ...head and tail both point to this new node, which is the only list item
        else { // the list isn't empty
            tail->next = newNode; // make the last item point forward to the new node
            newNode->prev = tail; // make the new node point backward to what was the last item
            tail = newNode; // make the tail pointer point to the new node, which is now the last item
        } // end of checking whether list is empty
    } // end of push_back function
    
    void push_front(int v) { // function for prepending a node to the beginning
        // doesn't return a value, takes arg of the value the new node will store
        Node* newNode = new Node(v); // allocate memory for a new node storing the given value
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

    // TESTING
    DoublyLinkedList list;
    list.print();
    list.insert_after(1, 0);
    list.insert_after(2, 0);
    list.insert_after(3, 0);
    list.print();
    
    return 0;
}