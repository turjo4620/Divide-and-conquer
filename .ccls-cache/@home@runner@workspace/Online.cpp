/*
 * Problem: Find the First Monotonic Triplet
 * * Description:
 * You are given an array of integers. A monotonic triplet is a sequence of three 
 * consecutive elements that are either strictly increasing or strictly decreasing. 
 * That is, for a subarray of three consecutive elements (a_i, a_{i+1}, a_{i+2}), 
 * it is monotonic if:
 * * (a_i < a_{i+1} < a_{i+2})   OR   (a_i > a_{i+1} > a_{i+2})
 * * Your task is to use a divide and conquer strategy to find the first index 'i' 
 * of such a monotonic triplet in the array. If no such triplet exists, return -1.
 * * Input:
 * - First line: an integer n (3 <= n <= 10^5) — the number of elements in the array.
 * - Second line: n space-separated integers — the array elements.
 * * Output:
 * - A single integer — the first index i (0-based) such that (a_i, a_{i+1}, a_{i+2}) 
 * forms a monotonic triplet. If there is no such index, output -1.
 */

#include <iostream>
#include <vector>

using namespace std;

// Helper function to check if a triplet starting at index i is monotonic
// It checks if (arr[i], arr[i+1], arr[i+2]) is strictly increasing or decreasing
bool isMonotonic(const vector<int>& arr, int i) {
    // Safety check to prevent out-of-bounds access
    if (i < 0 || i + 2 >= arr.size()) {
        return false; 
    }

    bool strictly_increasing = (arr[i] < arr[i+1]) && (arr[i+1] < arr[i+2]);
    bool strictly_decreasing = (arr[i] > arr[i+1]) && (arr[i+1] > arr[i+2]);

    return strictly_increasing || strictly_decreasing;
}

// The Divide and Conquer function
int findFirstTriplet(const vector<int>& arr, int low, int high) {
    // 1. Base Case: If the current chunk has fewer than 3 elements, 
    // a triplet is impossible.
    if (high - low + 1 < 3) {
        return -1;
    }

    // Find the middle index to divide the array
    int mid = low + (high - low) / 2;

    // 2. Conquer the Left: Recursively check the left half [low to mid]
    int left_result = findFirstTriplet(arr, low, mid);

    // If we found a valid triplet on the left, we return immediately 
    // because we want the FIRST occurrence in the array.
    if (left_result != -1) {
        return left_result;
    }

    // 3. Check the Boundary (The Seam)
    // We check the two possible triplets that cross the 'mid' point.
    // They must fit completely inside our current [low, high] bounds.

    // Crossing Triplet A: starts at mid - 1 (indices: mid-1, mid, mid+1)
    if (mid - 1 >= low && mid + 1 <= high) {
        if (isMonotonic(arr, mid - 1)) {
            return mid - 1;
        }
    }

    // Crossing Triplet B: starts exactly at mid (indices: mid, mid+1, mid+2)
    if (mid >= low && mid + 2 <= high) {
        if (isMonotonic(arr, mid)) {
            return mid;
        }
    }

    // 4. Conquer the Right: If left and boundary failed, check the right half
    // [mid + 1 to high]
    return findFirstTriplet(arr, mid + 1, high);
}

int main() {
    // Fast I/O for competitive programming/online judges
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Call the function on the entire array (from index 0 to n-1)
    int first_index = findFirstTriplet(arr, 0, n - 1);

    cout << first_index << "\n";

    return 0;
}
