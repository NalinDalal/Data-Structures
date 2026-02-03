#include <iostream>

using namespace std;

// Node structure for doubly linked list
struct Node {
    int data;
    Node* prev;
    Node* next;
};

// Doubly Linked List class
class DoublyLinkedList {
private:
    Node* head;

public:
    // Constructor
    DoublyLinkedList() : head(nullptr) {}

    // Function to insert a new element at the end of the list
    void insert(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->prev = nullptr;
        newNode->next = nullptr;

        if (head == nullptr) {
            // If the list is empty, set the new node as the head
            head = newNode;
        } else {
            // Traverse to the end of the list and insert the new node
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }

        cout << "Element " << value << " inserted successfully." << endl;
    }

    // Function to traverse and print the elements of the list
    void traverse() {
        Node* temp = head;
        cout << "List elements: ";
        while (temp != nullptr) {
            cout << temp->data << " <=>";
            temp = temp->next;
        }
        cout << endl;
    }

    // Function to delete a specific element from the list
    void deleteElement(int value) {
        Node* temp = head;
        while (temp != nullptr && temp->data != value) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Element not found in the list." << endl;
        } else {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            } else {
                // If the element to be deleted is the head
                head = temp->next;
            }

            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }

            delete temp;
            cout << "Element " << value << " deleted successfully." << endl;
        }
    }
};

int main() {
    DoublyLinkedList dll;
    int choice, value;

    do {
        cout << "\n1. Insert\n2. Traverse\n3. Delete\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the element to insert: ";
                cin >> value;
                dll.insert(value);
                break;

            case 2:
                dll.traverse();
                break;

            case 3:
                cout << "Enter the element to delete: ";
                cin >> value;
                dll.deleteElement(value);
                break;

            case 4:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}