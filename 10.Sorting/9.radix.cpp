#include <iostream>
#include <queue>
#include <vector>

template <typename T>
class Queue {
private:
    std::queue<T> q;

public:
    void enqueue(T value) {
        q.push(value);
    }

    T dequeue() {
        T front = q.front();
        q.pop();
        return front;
    }

    bool empty() const {
        return q.empty();
    }
};

void radixsort(long data[], int n) {
    const int radix = 10;
    const int digits = 10; // the maximum number of digits for a long
    Queue<long> queues[radix]; // array of queues

    for (int d = 0, factor = 1; d < digits; factor *= radix, d++) {
        for (int j = 0; j < n; j++) {
            queues[(data[j] / factor) % radix].enqueue(data[j]);
        }

        for (int j = 0, k = 0; j < radix; j++) {
            while (!queues[j].empty()) {
                data[k++] = queues[j].dequeue();
            }
        }
    }
}

int main() {
    // Example usage
    const int size = 8;
    long arr[size] = {170, 45, 75, 90, 802, 24, 2, 66};

    std::cout << "Original array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    radixsort(arr, size);

    std::cout << "\nSorted array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}