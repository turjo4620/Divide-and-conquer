/*
 * Problem: Maximum Triplet Sum (Divide and Conquer)
 * Description: Find the maximum sum of three consecutive numbers in an array.
 * Constraints:
 * 1. Must use Divide and Conquer.
 * 2. NO LOOPS allowed in the algorithm.
 * 3. Time complexity must be O(n).
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// The Divide and Conquer algorithm (No loops!)
long long maxTripletSum(const vector<long long>& arr, int low, int high) {
    // 1. Base Case 1: Less than 3 elements
    // We cannot form a triplet, return a very small number (-infinity)
    if (high - low + 1 < 3) {
        return -1e18; // Standard way to represent negative infinity for long long
    }

    // 2. Base Case 2: Exactly 3 elements
    // Just return their sum directly!
    if (high - low + 1 == 3) {
        return arr[low] + arr[low + 1] + arr[low + 2];
    }

    // 3. Divide
    int mid = low + (high - low) / 2;

    // 4. Conquer Left and Right
    long long max_left = maxTripletSum(arr, low, mid);
    long long max_right = maxTripletSum(arr, mid + 1, high);

    // 5. Combine (The Boundary Check)
    // We manually check the only two possible triplets that cross the 'mid' line.

    long long cross1 = -1e18;
    // Check Triplet 1: [mid-1, mid, mid+1]
    if (mid - 1 >= low && mid + 1 <= high) {
        cross1 = arr[mid - 1] + arr[mid] + arr[mid + 1];
    }

    long long cross2 = -1e18;
    // Check Triplet 2: [mid, mid+1, mid+2]
    if (mid >= low && mid + 2 <= high) {
        cross2 = arr[mid] + arr[mid + 1] + arr[mid + 2];
    }

    // Return the absolute maximum out of all 4 possibilities
    return max({max_left, max_right, cross1, cross2});
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<long long> arr(n);

        // Loop is allowed ONLY for reading input as per the problem description
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        if (n < 3) {
            // Edge case where input size is too small for a triplet
            cout << "0\n"; 
        } else {
            long long result = maxTripletSum(arr, 0, n - 1);
            cout << result << "\n";
        }
    }

    return 0;
}
