#include <iostream>

struct Node {
  int data;
  Node *next;

  Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
public:
  Node *head;

  LinkedList() : head(nullptr) {}

  // Function to add a new node to the end of the list
  void append(int value) {
    Node *newNode = new Node(value);
    if (!head) {
      head = newNode;
    } else {
      Node *temp = head;
      while (temp->next) {
        temp = temp->next;
      }
      temp->next = newNode;
    }
  }

  // Function to print the linked list
  void display() {
    Node *temp = head;
    while (temp) {
      std::cout << temp->data << " ";
      temp = temp->next;
    }
    std::cout << std::endl;
  }

public:
  // Merge function to merge two sorted linked lists
  Node *merge(Node *left, Node *right) {
    Node *result = nullptr;

    // Base cases
    if (!left)
      return right;
    if (!right)
      return left;

    // Recursive cases
    if (left->data <= right->data) {
      result = left;
      result->next = merge(left->next, right);
    } else {
      result = right;
      result->next = merge(left, right->next);
    }

    return result;
  }

  // Merge Sort function for linked list
  Node *mergeSort(Node *head) {
    // Base case: If the list is empty or has only one element, return it
    if (!head || !head->next) {
      return head;
    }

    // Split the linked list into two halves
    Node *slow = head;
    Node *fast = head->next;

    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }

    Node *right = slow->next;
    slow->next = nullptr;

    // Recursively sort the two halves
    Node *leftSorted = mergeSort(head);
    Node *rightSorted = mergeSort(right);

    // Merge the sorted halves
    return merge(leftSorted, rightSorted);
  }

  // Function to perform Merge Sort on the linked list
  void performMergeSort() { head = mergeSort(head); }
};

int main() {
  // Example usage
  LinkedList list;
  list.append(12);
  list.append(11);
  list.append(13);
  list.append(5);
  list.append(6);
  list.append(7);

  std::cout << "Original linked list: ";
  list.display();

  list.performMergeSort();

  std::cout << "Linked list after Merge Sort: ";
  list.display();

  return 0;
}
