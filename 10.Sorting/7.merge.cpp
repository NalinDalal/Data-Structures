#include <iostream>
#include <vector>

void merge(std::vector<int>& data, int first, int mid, int last) {
    int leftSize = mid - first + 1;
    int rightSize = last - mid;

    std::vector<int> leftArray(leftSize);
    std::vector<int> rightArray(rightSize);

    for (int i = 0; i < leftSize; ++i) {
        leftArray[i] = data[first + i];
    }

    for (int j = 0; j < rightSize; ++j) {
        rightArray[j] = data[mid + 1 + j];
    }

    int i = 0, j = 0, k = first;

    while (i < leftSize && j < rightSize) {
        if (leftArray[i] <= rightArray[j]) {
            data[k] = leftArray[i];
            ++i;
        } else {
            data[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    while (i < leftSize) {
        data[k] = leftArray[i];
        ++i;
        ++k;
    }

    while (j < rightSize) {
        data[k] = rightArray[j];
        ++j;
        ++k;
    }
}

void mergesort(std::vector<int>& data, int first, int last) {
    if (first < last) {
        int mid = (first + last) / 2;
        mergesort(data, first, mid);
        mergesort(data, mid + 1, last);
        merge(data, first, mid, last);
    }
}

int main() {
    std::vector<int> data = {38, 27, 43, 3, 9, 82, 10};

    mergesort(data, 0, data.size() - 1);

    std::cout << "Sorted array: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}