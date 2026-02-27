/*
 * Problem: Online - 7 (C1/C2) Divide and Conquer - Count Inversions
 * * Description:
 * Inversions in an array indicate how far (or close) the array is from being
 * sorted. For an array of integers, an inversion is defined as a pair of 
 * indices (i, j) such that:
 * - i < j
 * - array[i] > array[j]
 * * Goal: 
 * Write an algorithm to count the total number of inversions in a given array 
 * using a divide-and-conquer approach.
 * * Examples:
 * Input: 1 4 2 3 5  =>  Output: 2  (Pairs: (4,2), (4,3))
 * Input: 2 4 1 3 5  =>  Output: 3  (Pairs: (2,1), (4,1), (4,3))
 * * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 */

#include <iostream>
#include <vector>
using namespace std;

// Helper function that merges two sorted halves and counts the "cross inversions"
long long mergeAndCount(vector<int>& arr, int left, int mid, int right) {
    // Temporary array to hold the merged result
    vector<int> temp(right - left + 1);

    int i = left;      // Pointer for the left half
    int j = mid + 1;   // Pointer for the right half
    int k = 0;         // Pointer for the temp array

    long long invCount = 0;

    // Merge the two halves while looking for inversions
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            // Left element is smaller or equal. Everything is in order.
            temp[k++] = arr[i++];
        } else {
            // Right element is smaller! We found an inversion.
            temp[k++] = arr[j++];

            // THE CRUCIAL STEP:
            // Since the left half is already sorted, if arr[i] > arr[j], 
            // then EVERY element remaining in the left half is ALSO > arr[j].
            // We count all of them at once by checking how many elements 
            // are left between index 'i' and 'mid'.
            invCount += (mid - i + 1);
        }
    }

    // Copy any remaining elements from the left half
    while (i <= mid)
        temp[k++] = arr[i++];

    // Copy any remaining elements from the right half
    while (j <= right)
        temp[k++] = arr[j++];

    // Copy the sorted temp array back into the original array
    for (int p = 0; p < temp.size(); p++)
        arr[left + p] = temp[p];

    return invCount;
}

// The core Divide and Conquer function (Modified Merge Sort)
long long mergeSortAndCount(vector<int>& arr, int left, int right) {
    long long invCount = 0;

    // Base case: If the array segment has 1 or 0 elements, it has 0 inversions.
    if (left < right) {
        int mid = left + (right - left) / 2;

        // 1. Divide & Conquer the Left Half
        invCount += mergeSortAndCount(arr, left, mid);

        // 2. Divide & Conquer the Right Half
        invCount += mergeSortAndCount(arr, mid + 1, right);

        // 3. Combine: Merge the two halves and count inversions that cross the middle
        invCount += mergeAndCount(arr, left, mid, right);
    }

    return invCount;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        // Start the algorithm on the full array
        cout << mergeSortAndCount(arr, 0, n - 1) << "\n";
    }

    return 0;
}
