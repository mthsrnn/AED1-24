/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int falta[numsSize], i, j;

    for (int i = 0; i < numsSize; i++) {
        falta[i] = target - nums[i];
    }

    for (i = 0; i < numsSize; i++) {
        for (j = i; j < numsSize; j++) {
            if (i != j && nums[i] == falta[j]) {
                *returnSize = 2;
                int* indices =(int*) malloc(sizeof(int) * 2);
                indices[0] = i;
                indices[1] = j;
                return indices;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

