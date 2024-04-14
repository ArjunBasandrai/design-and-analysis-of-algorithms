#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct {
    int left_idx;
    int right_idx;
    int sum;
} response;

response max_cross_sum(int* nums, int low, int mid, int high) {
    int left_sum = -INT_MAX, sum = 0, right_sum = -INT_MAX;
    int left_idx = 0, right_idx = 0;
    for (int i = mid; i >= low; i--) {
        sum += nums[i];
        if (sum > left_sum) {
            left_sum = sum;
            left_idx = i;
        }
    }
    sum = 0;
    for (int i = mid + 1; i <= high; i++) {
        sum += nums[i];
        if (sum > right_sum) {
            right_sum = sum;
            right_idx = i;
        }
    }
    return (response){left_idx, right_idx, left_sum + right_sum};
}

response max_sum(int* nums, int low, int high) {
    if (high == low) return (response){low, high, nums[low]};
    else {
        int mid = floor((low + high) / 2);
        response left = max_sum(nums, 0, mid);
        response right = max_sum(nums, mid+1, high);
        response cross = max_cross_sum(nums, low, mid, high);
        if (left.sum >= right.sum && left.sum >= cross.sum) {
            return left;
        } else if (right.sum >= left.sum && right.sum >= cross.sum) {
            return right;
        }
        return cross;
    }
}

void max_sub_array(int* nums, int numsSize) {
    response res;
    if (numsSize == 1) res = (response){0,0,nums[0]};
    else res = max_sum(nums, 0, numsSize-1);
    printf("Maximum subarray sum: %d for elements: ", res.sum);
    for (int i = res.left_idx; i <= res.right_idx; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main() {
    int nums[] = {-2,1,-3,4,-1,2,1,-5,4};
    int numsSize = 9;
    max_sub_array(nums, numsSize);
    return 0;
}