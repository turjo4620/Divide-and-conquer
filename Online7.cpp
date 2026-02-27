/*
 * Problem: Find Peak Element
 * Description: Given an integer array, find any peak element in it. 
 * A peak element is an element that is greater than or equal to its neighbors.
 * * Boundary Conditions:
 * - A[i-1] <= A[i] >= A[i+1] for internal elements
 * - A[i] >= A[i+1] if i = 0 (Left edge)
 * - A[i-1] <= A[i] if i = n-1 (Right edge)
 * * Constraint: MUST be O(log n) time complexity.
 */

#include <iostream>
#include <vector>

using namespace std;

// The Divide and Conquer function (Binary Search logic)
int findPeakElement(const vector<int>& arr, int low, int high, int n) {
    // 1. Find the middle element
    int mid = low + (high - low) / 2;

    // 2. Check if mid is a peak
    // We use boolean flags to safely handle the edges of the array
    bool greater_than_left = (mid == 0 || arr[mid] >= arr[mid - 1]);
    bool greater_than_right = (mid == n - 1 || arr[mid] >= arr[mid + 1]);

    if (greater_than_left && greater_than_right) {
        // We found a peak! Return the element itself (not the index)
        return arr[mid];
    }

    // 3. If the element to the right is strictly greater, 
    // there MUST be a peak on the right half. Go right.
    if (mid < n - 1 && arr[mid] < arr[mid + 1]) {
        return findPeakElement(arr, mid + 1, high, n);
    }

    // 4. Otherwise, the element to the left must be greater, 
    // so there MUST be a peak on the left half. Go left.
    return findPeakElement(arr, low, mid - 1, n);
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // Read the size of the array
    if (cin >> n) {
        // Edge case: if array is empty
        if (n == 0) return 0;

        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        // Call the O(log n) function and print the result
        int peak = findPeakElement(arr, 0, n - 1, n);
        cout << peak << "\n";
    }

    return 0;
}
