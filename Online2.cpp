/*
 * Problem: Maximum Difference (Divide and Conquer)
 * Description: Given an array A, find the max difference A[j] - A[i] 
 * such that j > i and A[j] > A[i].
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A structure to hold the results of each recursive call
struct SubarrayInfo {
    long long min_val;
    long long max_val;
    long long max_diff;
};

// The Divide and Conquer function
SubarrayInfo findMaxDifference(const vector<long long>& arr, int low, int high) {
    // 1. Base Case: If the chunk is just one element
    // A single element has no difference. We return it as both min and max.
    // We set max_diff to -1 to indicate no valid pair exists yet.
    if (low == high) {
        return {arr[low], arr[low], -1};
    }

    // Find the middle to divide the array
    int mid = low + (high - low) / 2;

    // 2. Conquer Left and Right
    SubarrayInfo left = findMaxDifference(arr, low, mid);
    SubarrayInfo right = findMaxDifference(arr, mid + 1, high);

    // 3. Calculate the Crossing Boundary difference
    // The best cross difference is the biggest number on the right minus the smallest on the left
    long long cross_diff = right.max_val - left.min_val;

    // 4. Combine: Figure out the stats for our current combined chunk
    SubarrayInfo current;
    current.min_val = min(left.min_val, right.min_val);
    current.max_val = max(left.max_val, right.max_val);

    // The maximum difference is the best of the three possibilities
    current.max_diff = max({left.max_diff, right.max_diff, cross_diff});

    return current;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Call the function on the entire array
    SubarrayInfo result = findMaxDifference(arr, 0, n - 1);

    // If the array is strictly decreasing, no valid A[j] > A[i] pair exists.
    // The problem implies outputting the difference, but if max_diff is <= 0, 
    // it means no "larger element after smaller" was found. We output -1.
    if (result.max_diff > 0) {
        cout << result.max_diff << "\n";
    } else {
        cout << -1 << "\n"; 
    }

    return 0;
}
