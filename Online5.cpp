/*
 * Problem: Online - 7 (B1/B2) Divide and Conquer - Unique Elements
 * Description: You are given a sorted (non-decreasing) array of integers, 
 * which may contain duplicate elements. Your task is to find the number of 
 * unique elements in the array using a divide and conquer approach.
 * * Examples:
 * Input: 1 2 2 2 3 5  => Output: 4
 * Input: 4 5 6 7 8    => Output: 5
 */

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// The Divide and Conquer function
int countUniqueElements(const vector<int>& arr, int low, int high) {
    // 1. Safety check
    if (low > high) {
        return 0;
    }

    // 2. Base Case & Optimization: 
    // Because the array is sorted, if the first element of our current chunk 
    // is equal to the last element, ALL elements in this chunk are identical.
    // Thus, there is exactly 1 unique element in this entire chunk.
    // (This also naturally handles the case where low == high)
    if (arr[low] == arr[high]) {
        return 1;
    }

    // 3. Divide: Find the middle index
    int mid = low + (high - low) / 2;

    // 4. Conquer: Count unique elements in the left and right halves
    int left_count = countUniqueElements(arr, low, mid);
    int right_count = countUniqueElements(arr, mid + 1, high);

    // 5. Combine: 
    int total_unique = left_count + right_count;

    // The Boundary Check: 
    // If the element at the end of the left half is the same as the element 
    // at the start of the right half, we have counted that element twice 
    // (once in left_count, once in right_count). We must subtract 1.
    if (arr[mid] == arr[mid + 1]) {
        total_unique -= 1;
    }

    return total_unique;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Read the whole line of input since the problem doesn't explicitly 
    // give us 'n' first in the example inputs provided.
    string line;
    if (getline(cin, line)) {
        stringstream ss(line);
        vector<int> arr;
        int num;
        while (ss >> num) {
            arr.push_back(num);
        }

        if (!arr.empty()) {
            int unique_count = countUniqueElements(arr, 0, arr.size() - 1);
            cout << unique_count << "\n";
        }
    }

    return 0;
}
