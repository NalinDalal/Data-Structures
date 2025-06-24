#include <iostream>
using namespace std;

#define SIZE 100

struct Node {
  int data;
  int priority;
};

class PriorityQueue {
private:
  Node arr[SIZE];
  int n;

public:
  PriorityQueue() { n = 0; }

  // Insert based on priority
  void enqueue(int data, int priority) {
    if (n == SIZE) {
      cout << "[❌] Queue is full\n";
      return;
    }

    arr[n].data = data;
    arr[n].priority = priority;
    n++;

    // Sort after insert based on priority (descending)
    for (int i = n - 1; i > 0; i--) {
      if (arr[i].priority > arr[i - 1].priority) {
        swap(arr[i], arr[i - 1]);
      } else {
        break;
      }
    }

    cout << "[✅] Enqueued: " << data << " (Priority: " << priority << ")\n";
    display();
  }

  // Remove element with highest priority
  void dequeue() {
    if (n == 0) {
      cout << "[❌] Queue is empty\n";
      return;
    }

    cout << "[🗑️ ] Dequeued: " << arr[0].data
         << " (Priority: " << arr[0].priority << ")\n";
    for (int i = 1; i < n; i++) {
      arr[i - 1] = arr[i];
    }
    n--;

    display();
  }

  void display() {
    if (n == 0) {
      cout << "🔄 Queue is empty.\n\n";
      return;
    }

    cout << "📦 Priority Queue State:\n";
    for (int i = 0; i < n; i++) {
      cout << "[" << arr[i].data << " (P=" << arr[i].priority << ")] ";
    }
    cout << "\n\n";
  }
};

int main() {
  PriorityQueue pq;

  pq.enqueue(10, 2);
  pq.enqueue(30, 4);
  pq.enqueue(20, 3);
  pq.enqueue(40, 1);

  pq.dequeue();
  pq.enqueue(50, 5);
  pq.dequeue();

  return 0;
}
