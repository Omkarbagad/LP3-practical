#include<iostream>
#include<vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

void swap(vector<int>& arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(vector<int>& arr, int p, int r) {
    int x = arr[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (arr[j] <= x) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, r);
    return i + 1;
}

void quickSort(vector<int>& arr, int p, int r) {
    if (p < r) {
        int q = partition(arr, p, r);
        quickSort(arr, p, q - 1);
        quickSort(arr, q + 1, r);
    }
}

int randomPartition(vector<int>& arr, int p, int r) {
    int i = p + rand() % (r - p + 1);
    swap(arr, i, r);
    return partition(arr, p, r);
}

void randomizedQuickSort(vector<int>& arr, int p, int r) {
    if (p < r) {
        int q = randomPartition(arr, p, r);
        randomizedQuickSort(arr, p, q - 1);
        randomizedQuickSort(arr, q + 1, r);
    }
}

int main() {
    srand(time(0));
    cout << "Enter the list of numbers (space-separated): ";
    string input;
    getline(cin, input);
    istringstream inputStream(input);
    vector<int> arr;
    int number;
    while (inputStream >> number) {
        arr.push_back(number);
    }
    randomizedQuickSort(arr, 0, arr.size() - 1);
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
