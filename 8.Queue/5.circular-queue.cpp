#include <iostream>
using namespace std;

#define SIZE 5

class CircularQueue {
private:
  int arr[SIZE];
  int front, rear;

public:
  CircularQueue() {
    front = -1;
    rear = -1;
  }

  bool isFull() { return ((rear + 1) % SIZE == front); }

  bool isEmpty() { return (front == -1); }

  void enqueue(int x) {
    if (isFull()) {
      cout << "[❌] Queue Overflow\n";
      return;
    }

    if (isEmpty()) {
      front = rear = 0;
    } else {
      rear = (rear + 1) % SIZE;
    }

    arr[rear] = x;
    cout << "[✅] Enqueued: " << x << endl;
    printState();
  }

  void dequeue() {
    if (isEmpty()) {
      cout << "[❌] Queue Underflow\n";
      return;
    }

    cout << "[🗑️ ] Dequeued: " << arr[front] << endl;

    if (front == rear) {
      front = rear = -1;
    } else {
      front = (front + 1) % SIZE;
    }

    printState();
  }

  void printState() {
    if (isEmpty()) {
      cout << "🔄 Queue is currently empty.\n\n";
      return;
    }

    cout << "📦 Circular Queue: ";
    int i = front;
    while (true) {
      if (i == front && i == rear)
        cout << "[" << arr[i] << " (F/R)] ";
      else if (i == front)
        cout << "[" << arr[i] << " (F)] ";
      else if (i == rear)
        cout << "[" << arr[i] << " (R)] ";
      else
        cout << "[" << arr[i] << "] ";

      if (i == rear)
        break;
      i = (i + 1) % SIZE;
    }
    cout << "\n\n";
  }
};

int main() {
  CircularQueue q;

  q.enqueue(10);
  q.enqueue(20);
  q.enqueue(30);
  q.enqueue(40);
  q.enqueue(50); // Should show overflow

  q.dequeue();
  q.dequeue();

  q.enqueue(60);
  q.enqueue(70);

  q.dequeue();
  q.enqueue(80);

  q.printState();

  return 0;
}
