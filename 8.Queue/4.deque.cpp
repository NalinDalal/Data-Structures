#include <iostream>
using namespace std;

#define SIZE 10

class Deque {
private:
  int arr[SIZE];
  int front;
  int rear;

public:
  Deque() {
    front = -1;
    rear = -1;
  }

  bool isFull() {
    return ((front == 0 && rear == SIZE - 1) || (front == rear + 1));
  }

  bool isEmpty() { return (front == -1); }

  void pushFront(int x) {
    if (isFull()) {
      cout << "[❌] Deque is Full\n";
      return;
    }

    if (isEmpty()) {
      front = rear = 0;
    } else if (front == 0) {
      front = SIZE - 1;
    } else {
      front--;
    }

    arr[front] = x;
    cout << "[✅] Inserted at Front: " << x << endl;
    printState();
  }

  void pushRear(int x) {
    if (isFull()) {
      cout << "[❌] Deque is Full\n";
      return;
    }

    if (isEmpty()) {
      front = rear = 0;
    } else if (rear == SIZE - 1) {
      rear = 0;
    } else {
      rear++;
    }

    arr[rear] = x;
    cout << "[✅] Inserted at Rear: " << x << endl;
    printState();
  }

  void popFront() {
    if (isEmpty()) {
      cout << "[❌] Deque is Empty\n";
      return;
    }

    cout << "[🗑️ ] Deleted Front: " << arr[front] << endl;

    if (front == rear) {
      front = rear = -1;
    } else if (front == SIZE - 1) {
      front = 0;
    } else {
      front++;
    }

    printState();
  }

  void popRear() {
    if (isEmpty()) {
      cout << "[❌] Deque is Empty\n";
      return;
    }

    cout << "[🗑️ ] Deleted Rear: " << arr[rear] << endl;

    if (front == rear) {
      front = rear = -1;
    } else if (rear == 0) {
      rear = SIZE - 1;
    } else {
      rear--;
    }

    printState();
  }

  void printState() {
    if (isEmpty()) {
      cout << "🔄 Deque is currently empty.\n";
      return;
    }

    cout << "📦 Deque: ";
    int i = front;
    while (true) {
      if (i == front && i == rear)
        cout << "[" << arr[i] << " (F/R)] ";
      else if (i == front)
                cout << "[" << arr[[48;52;178;1768;2848ti] << " (F)] ";
            else if (i == rear)
                cout << "[" << arr[i] << " (R)] ";
            else
                cout << "[" << arr[i] << "] ";

            if (i == rear) break;
            i = (i + 1) % SIZE;
    }
    cout << "\n\n";
  }
};

int main() {
  Deque dq;

  dq.pushRear(10);
  dq.pushRear(20);
  dq.pushFront(5);
  dq.pushFront(2);

  dq.popRear();
  dq.popFront();

  dq.pushRear(30);
  dq.pushRear(40);
  dq.pushRear(50);
  dq.pushRear(60);
  dq.pushRear(70);
  dq.pushRear(80);
  dq.pushRear(90); // Should fill the deque

  dq.pushRear(100); // Should show full

  dq.popFront();
  dq.popRear();

  return 0;
}
