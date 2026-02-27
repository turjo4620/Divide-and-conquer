/*
 * Problem: Find the Majority Element (Divide and Conquer)
 * Description: Given an array of n integers, find the element that occurs 
 * more than n/2 times. Assume a majority element always exists.
 */

#include <iostream>
#include <vector>

using namespace std;

// Helper function to count how many times a 'target' appears in arr[low...high]
int countOccurrences(const vector<int>& arr, int low, int high, int target) {
    int count = 0;
    for (int i = low; i <= high; ++i) {
        if (arr[i] == target) {
            count++;
        }
    }
    return count;
}

// The Divide and Conquer function
int findMajorityElement(const vector<int>& arr, int low, int high) {
    // 1. Base Case: If the chunk is just one element, it is the majority.
    if (low == high) {
        return arr[low];
    }

    // 2. Divide: Find the middle index
    int mid = low + (high - low) / 2;

    // 3. Conquer: Recursively find the majority in the left and right halves
    int left_candidate = findMajorityElement(arr, low, mid);
    int right_candidate = findMajorityElement(arr, mid + 1, high);

    // 4. Combine:
    // If both halves agree on the majority element, return it.
    if (left_candidate == right_candidate) {
        return left_candidate;
    }

    // If they disagree, count the occurrences of each candidate in the CURRENT chunk
    int left_count = countOccurrences(arr, low, high, left_candidate);
    int right_count = countOccurrences(arr, low, high, right_candidate);

    // Return the candidate that appears more often
    if (left_count > right_count) {
        return left_candidate;
    } else {
        return right_candidate;
    }
}

int main() {
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // Keep reading input (useful if testing multiple test cases, or simply handles the first)
    if (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }

        // Call the recursive function from index 0 to n-1
        int majority = findMajorityElement(arr, 0, n - 1);

        cout << majority << "\n";
    }

    return 0;
}
