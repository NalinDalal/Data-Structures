#include <iostream>

using namespace std;

// Node structure for circular linked list
struct Node {
    int data;
    Node* next;

    // Constructor to initialize data and next pointer
    Node(int value) : data(value), next(nullptr) {}
};

// Circular Linked List class
class CircularLinkedList {
private:
    Node* head;

public:
    // Constructor
    CircularLinkedList() : head(nullptr) {}

    // Function to insert a new element at the end of the list
    void insert(int value) {
        Node* newNode = new Node(value);

        // If the list is empty, set the new node as the head and make it circular
        if (head == nullptr) {
            head = newNode;
            newNode->next = head;
        } else {
            // Traverse to the end of the list and insert the new node
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }

        cout << "Element " << value << " inserted successfully." << endl;
    }

    // Function to traverse and print the elements of the list
    void traverse() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    // Function to search for an element in the list
    bool search(int value) {
        if (head == nullptr) {
            cout << "List is empty. Element not found." << endl;
            return false;
        }

        Node* temp = head;
        do {
            if (temp->data == value) {
                cout << "Element " << value << " found in the list." << endl;
                return true;
            }
            temp = temp->next;
        } while (temp != head);

        cout << "Element " << value << " not found in the list." << endl;
        return false;
    }

    // Function to delete a specific element from the list
    void deleteElement(int value) {
        if (head == nullptr) {
            cout << "List is empty. Deletion failed." << endl;
            return;
        }

        Node* temp = head;
        Node* prev = nullptr;

        // Traverse the list to find the node to be deleted
        do {
            if (temp->data == value) {
                // If the node to be deleted is the head
                if (temp == head) {
                    Node* lastNode = head;
                    while (lastNode->next != head) {
                        lastNode = lastNode->next;
                    }
                    head = head->next;
                    lastNode->next = head;
                } else {
                    prev->next = temp->next;
                }

                delete temp;
                cout << "Element " << value << " deleted successfully." << endl;
                return;
            }

            prev = temp;
            temp = temp->next;
        } while (temp != head);

        cout << "Element " << value << " not found. Deletion failed." << endl;
    }
};

int main() {
    CircularLinkedList cll;
    int choice, value;

    do {
        cout << "\n1. Insert\n2. Traverse\n3. Search\n4. Delete\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the element to insert: ";
                cin >> value;
                cll.insert(value);
                break;

            case 2:
                cll.traverse();
                break;

            case 3:
                cout << "Enter the element to search: ";
                cin >> value;
                cll.search(value);
                break;

            case 4:
                cout << "Enter the element to delete: ";
                cin >> value;
                cll.deleteElement(value);
                break;

            case 5:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    cout<<"Hello World"<<endl;
    return 0;
}
