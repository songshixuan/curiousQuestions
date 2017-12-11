package main

import (
	"fmt"
)

/*
Given an array consisting of n integers, find the contiguous subarray of given length k that has the maximum average value.
And you need to output the maximum average value.
1 <= k <= n <= 30,000.
*/
func findMaxAverage(arr []int, k int) float64 {

}

func main() {
	var arr = []int{4433, -7832, -5068, 4009, 2830, 6544, -6119, -7126, -780, -4254, -8249, -9168, 9492, 402, 5789, 6808, 8953, 5810, -7353, 7933, 4766, 5182, -3230, -1989, 5786, 6922, -4646, 4415, -9906, 807, -6373, 3370, 2604, 8751, -9173, -2668, -6876, 9500, 3465, -1900, 4134, -1758, -1453, -5201, -9825, 4469, -1999, -1108, 1836, 3923, 6796, -5252, 9863, -5997, -3251, 9596, -3404, -540, 2826, -1737, 3341, -3623, -9885, 2603, -5782, 8174, 2710, 6504, -412859}

	fmt.Println("max k average", findMaxAverage(arr, 59), len(arr))
}
