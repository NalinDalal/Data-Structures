// Clean, single implementation of a doubly linked list and demo
#include <iostream>

class Node {
public:
    int data;
    Node* next;
    Node* prev;
    Node(int v) : data(v), next(nullptr), prev(nullptr) {}
};

void insertAtHead(Node*& head, int val) {
    Node* n = new Node(val);
    n->next = head;
    if (head) head->prev = n;
    head = n;
}

void insertAtTail(Node*& head, int val) {
    if (!head) { insertAtHead(head, val); return; }
    Node* temp = head;
    while (temp->next) temp = temp->next;
    Node* n = new Node(val);
    temp->next = n;
    n->prev = temp;
}

void display(const Node* head) {
    const Node* temp = head;
    while (temp) {
        std::cout << temp->data;
        if (temp->next) std::cout << " <-> ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

void deleteAtHead(Node*& head) {
    if (!head) return;
    Node* todelete = head;
    head = head->next;
    if (head) head->prev = nullptr;
    delete todelete;
}

void deletion(Node*& head, int pos) {
    if (!head || pos <= 0) return;
    if (pos == 1) { deleteAtHead(head); return; }
    Node* temp = head;
    int count = 1;
    while (temp && count < pos) { temp = temp->next; ++count; }
    if (!temp) return; // position out of range
    if (temp->prev) temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    delete temp;
}

void clearList(Node*& head) {
    Node* cur = head;
    while (cur) {
        Node* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head = nullptr;
}

int main() {
    Node* head = nullptr;

    insertAtTail(head, 1);
    insertAtTail(head, 2);
    insertAtTail(head, 3);
    insertAtTail(head, 4);
    insertAtTail(head, 5);

    std::cout << "Initial list:\n";
    display(head);

    insertAtTail(head, 6);
    std::cout << "After inserting 6 at tail:\n";
    display(head);

    deletion(head, 5);
    std::cout << "After deleting position 5:\n";
    display(head);

    deleteAtHead(head);
    std::cout << "After deleting head:\n";
    display(head);

    clearList(head);
    return 0;
}