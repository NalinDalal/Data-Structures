#include <iostream>

using namespace std;

// Node structure for linked list
struct Node {
    int data;
    Node* next;

    // Constructor to initialize data and next pointer
    Node(int value) : data(value), next(nullptr) {}
};

// Function to merge two sorted linked lists
Node* mergeSortedLists(Node* list1, Node* list2) {
    // Dummy node to simplify code
    Node* dummy = new Node(-1);
    Node* current = dummy;

    // Traverse both lists until one of them becomes empty
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->data < list2->data) {
            // Append smaller node from list1
            current->next = list1;
            list1 = list1->next;
        } else {
            // Append smaller node from list2
            current->next = list2;
            list2 = list2->next;
        }
        // Move to the next node in the merged list
        current = current->next;
    }

    // If one of the lists is not empty, append the remaining nodes
    if (list1 != nullptr) {
        current->next = list1;
    } else {
        current->next = list2;
    }

    // Return the merged list starting from the next of the dummy node
    return dummy->next;
}

// Function to print the elements of a linked list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Creating two sorted linked lists
    Node* list1 = new Node(1);
    list1->next = new Node(3);
    list1->next->next = new Node(5);

    Node* list2 = new Node(2);
    list2->next = new Node(4);
    list2->next->next = new Node(6);

    // Merging the two sorted lists
    Node* mergedList = mergeSortedLists(list1, list2);

    // Printing the merged list
    cout << "Merged List: ";
    printList(mergedList);

    return 0;
}

