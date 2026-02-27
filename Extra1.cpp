/*
 * Problem: Find the First Monotonic Triplet
 *
 * Description:
 * You are given an array of integers. A monotonic triplet is a sequence of three 
 * consecutive elements that are either strictly increasing or strictly decreasing. 
 * That is, for a subarray of three consecutive elements (a_i, a_{i+1}, a_{i+2}), 
 * it is monotonic if:
 *   (a_i < a_{i+1} < a_{i+2})   OR   (a_i > a_{i+1} > a_{i+2})
 *
 * Task:
 * Use a divide-and-conquer strategy to find the first index 'i' of such a monotonic 
 * triplet in the array. If no such triplet exists, return -1. Additionally, store 
 * the triplet in a vector and print it along with whether it is increasing or decreasing.
 *
 * Input:
 * - First line: an integer n (3 <= n <= 10^5) — the number of elements in the array.
 * - Second line: n space-separated integers — the array elements.
 *
 * Output:
 * - First, print the index i of the first monotonic triplet (0-based). 
 * - Then print the three elements of the triplet.
 * - Finally, print whether it is "Increasing" or "Decreasing".
 */

#include <iostream>
#include <vector>

using namespace std;

// Helper function: checks if the triplet starting at index i is strictly increasing or decreasing
bool isMonotonic(const vector<int>& arr, int i) {
    if (i < 0 || i + 2 >= arr.size()) return false; // Out-of-bounds safety
    bool increasing = (arr[i] < arr[i+1]) && (arr[i+1] < arr[i+2]);
    bool decreasing = (arr[i] > arr[i+1]) && (arr[i+1] > arr[i+2]);
    return increasing || decreasing;
}

// Divide-and-Conquer function to find the first monotonic triplet
int findFirstTriplet(const vector<int>& arr, int low, int high, vector<int>& triplet) {
    // Base case: fewer than 3 elements → no triplet possible
    if (high - low + 1 < 3) return -1;

    int mid = low + (high - low) / 2;

    // Step 1: Check the left half recursively
    int left_result = findFirstTriplet(arr, low, mid, triplet);
    if (left_result != -1) return left_result; // If found, return immediately

    // Step 2: Check the boundary (triplets crossing mid)
    // Triplet A: starts at mid-1
    if (mid - 1 >= low && mid + 1 <= high) {
        if (isMonotonic(arr, mid - 1)) {
            triplet = {arr[mid-1], arr[mid], arr[mid+1]};
            return mid - 1;
        }
    }
    // Triplet B: starts at mid
    if (mid >= low && mid + 2 <= high) {
        if (isMonotonic(arr, mid)) {
            triplet = {arr[mid], arr[mid+1], arr[mid+2]};
            return mid;
        }
    }

    // Step 3: Check the right half recursively
    return findFirstTriplet(arr, mid + 1, high, triplet);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];

    vector<int> triplet; // To store the first monotonic triplet
    int first_index = findFirstTriplet(arr, 0, n - 1, triplet);

    if (first_index != -1) {
        cout << "First monotonic triplet index: " << first_index << "\n";
        cout << "Triplet: ";
        for (int x : triplet) cout << x << " ";
        cout << "\n";

        if (triplet[0] < triplet[1] && triplet[1] < triplet[2]) cout << "Increasing\n";
        else cout << "Decreasing\n";
    } else {
        cout << "No monotonic triplet found\n";
    }

    return 0;
}