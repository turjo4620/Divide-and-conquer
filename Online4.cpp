/*
 * Problem: Online - 7 (A1/A2) Divide and Conquer - Adjacent Inverted Pairs
 * * Description:
 * You are given a string 's' consisting of lowercase letters. An adjacent inverted 
 * pair is defined as a pair of consecutive characters (s[i], s[i+1]) such that 
 * s[i] > s[i+1]. Your task is to count the total number of adjacent inverted 
 * pairs in the string.
 * * You must solve this problem using a divide-and-conquer approach.
 * * Examples:
 * 1. Input: "abcfrx"
 * Output: 0
 * * 2. Input: "abdcbabxawer"
 * Output: 5
 * Explanation: The pairs are "dc", "cb", "ba", "xa", and "we".
 */

#include <iostream>
#include <string>

using namespace std;

// The Divide and Conquer function
int countAdjacentInvertedPairs(const string& s, int low, int high) {
    // 1. Base Case: If the string chunk has 1 or 0 characters, there are 0 pairs.
    if (low >= high) {
        return 0;
    }

    // 2. Divide: Find the middle index
    int mid = low + (high - low) / 2;

    // 3. Conquer: Recursively count in the left and right halves
    int left_count = countAdjacentInvertedPairs(s, low, mid);
    int right_count = countAdjacentInvertedPairs(s, mid + 1, high);

    // 4. Combine (The Boundary Check):
    // Check if the character exactly at 'mid' is strictly greater than 
    // the one at 'mid + 1'
    int boundary_count = 0;
    if (s[mid] > s[mid + 1]) {
        boundary_count = 1;
    }

    // Return the total sum of pairs found
    return left_count + right_count + boundary_count;
}

int main() {
    // Fast I/O for competitive programming/online judges
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (cin >> s) {
        // Call the function from the first index (0) to the last index (length - 1)
        int total_pairs = countAdjacentInvertedPairs(s, 0, s.length() - 1);
        cout << total_pairs << "\n";
    }

    return 0;
}
