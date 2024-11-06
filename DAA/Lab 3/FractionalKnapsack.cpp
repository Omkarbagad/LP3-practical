#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

class Item {
public:
    int weight;
    int value;
    
    Item(int weight, int value) : weight(weight), value(value) {}
};

// Comparator function to sort items by value/weight ratio in descending order
bool compare(Item item1, Item item2) {
    double ratio1 = (double)item1.value / item1.weight;
    double ratio2 = (double)item2.value / item2.weight;
    return ratio1 > ratio2;
}

double getMaxValue(vector<Item>& items, int capacity) {
    // Sort items by value-to-weight ratio in descending order
    sort(items.begin(), items.end(), compare);
    
    double totalValue = 0.0;
    int currentWeight = 0;
    
    for (const auto& item : items) {
        if (currentWeight + item.weight <= capacity) {
            // If we can take the whole item, take it
            currentWeight += item.weight;
            totalValue += item.value;
        } else {
            // If we can't take the whole item, take a fraction of it
            int remainingCapacity = capacity - currentWeight;
            totalValue += ((double)item.value / item.weight) * remainingCapacity;
            break;
        }
    }
    
    return totalValue;
}

int main() {
    vector<Item> items = {
        Item(10, 60),
        Item(20, 100),
        Item(30, 120)
    };
    int capacity = 50;
    
    double maxValue = getMaxValue(items, capacity);
    cout << "Maximum value in Knapsack = " << fixed << setprecision(2) << maxValue << endl;

    return 0;
}
