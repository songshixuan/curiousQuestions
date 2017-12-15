package main

import (
	"fmt"
)

/*
Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]
*/

func findDuplicates(nums []int) []int {

	fAbs := func(v int) int {
		if v > 0 {
			return v
		} else {
			return 0 - v
		}
	}

	index := 0
	res := make([]int, 0, len(nums))
	for _, v := range nums {
		index = fAbs(v) - 1
		if nums[index] < 0 {
			res = append(res, fAbs(v))
		}
		nums[index] = 0 - nums[index]
	}
	return res
}

func main() {
	var nums = []int{4, 3, 2, 7, 8, 2, 3, 1}
	res := findDuplicates(nums)
	fmt.Println(res)
}
