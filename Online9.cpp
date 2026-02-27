/*
 * Problem: Find the Odd Occurring Element in Logarithmic Time
 * Description: Given an array where every element appears in pairs except one,
 * find the uniquely odd-occurring element in O(log n) time.
 */

#include <iostream>
#include <vector>

using namespace std;

// The Divide and Conquer function (O(log n) Binary Search)
int findOddOccurringElement(const vector<int>& arr) {
    int low = 0;
    int high = arr.size() - 1;

    // Binary search loop
    while (low < high) {
        int mid = low + (high - low) / 2;

        // Force mid to always be an EVEN index.
        // This ensures we always point to the start of a pair 
        // if we are on the left side of the anomaly.
        if (mid % 2 != 0) {
            mid--;
        }

        // Compare mid with the element immediately to its right
        if (arr[mid] == arr[mid + 1]) {
            // The pair is intact (EVEN index matches ODD index).
            // This means the anomaly is further to the right.
            low = mid + 2; 
        } else {
            // The pair is broken. 
            // The anomaly is either at 'mid' or to the left of it.
            high = mid; 
        }
    }

    // When low == high, we have pinpointed the exact odd element
    return arr[low];
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        int result = findOddOccurringElement(arr);
        cout << result << "\n";
    }

    return 0;
}
