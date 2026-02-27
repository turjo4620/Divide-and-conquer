/*
 * Problem: LeetCode 53 - Maximum Subarray (Divide & Conquer Solution)
 * Description: Given an integer array nums, find the subarray with the 
 * largest sum, and return its sum.
 * Follow up: If you have figured out the O(n) solution, try coding another 
 * solution using the divide and conquer approach, which is more subtle.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        return findMaxSum(nums, 0, nums.size() - 1);
    }

private:
    int findMaxSum(const vector<int>& nums, int low, int high) {
        if (low == high) return nums[low]; // Base case: 1 element

        int mid = low + (high - low) / 2;

        // Recursively find max in left and right halves
        int left_max = findMaxSum(nums, low, mid);
        int right_max = findMaxSum(nums, mid + 1, high);

        // Find max crossing the boundary
        int cross_max = findMaxCrossing(nums, low, mid, high);

        return max({left_max, right_max, cross_max});
    }

    int findMaxCrossing(const vector<int>& nums, int low, int mid, int high) {
        // Expand to the left from mid
        int left_sum = -1e9, current_sum = 0;
        for (int i = mid; i >= low; i--) {
            current_sum += nums[i];
            left_sum = max(left_sum, current_sum);
        }

        // Expand to the right from mid + 1
        int right_sum = -1e9; current_sum = 0;
        for (int i = mid + 1; i <= high; i++) {
            current_sum += nums[i];
            right_sum = max(right_sum, current_sum);
        }

        // Combine them
        return left_sum + right_sum;
    }
};
