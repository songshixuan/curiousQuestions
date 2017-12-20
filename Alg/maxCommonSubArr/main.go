package main

import (
	"fmt"
)

func findLength(A []int, B []int) int {
	iMaxF := func(a, b int) int {
		if a > b {
			return a
		} else {
			return b
		}
	}
	max := 0
	m := len(A)                 //
	n := len(B)                 //
	dp := make([][]int, 0, m+1) //a[m][n] m is lines; n is rows
	for i := 0; i < n+1; i++ {
		dp = append(dp, make([]int, n+1))
	}

	for i := 0; i < m+1; i++ {
		for j := 0; j < n+1; j++ {
			if i == 0 || j == 0 {
				//fmt.Println(i, j)
				dp[i][j] = 0
			} else {
				if A[i-1] == B[j-1] {
					dp[i][j] = iMaxF(dp[i-1][j-1], dp[i-1][j-1]) + 1
					max = iMaxF(dp[i][j], max)
				} else {

				}
			}

		}
	}
	return max
}

func main() {
	var a1 = []int{1, 2, 3, 4, 5}
	var a2 = []int{5, 4, 12, 1, 2}
	fmt.Println(findLength(a1, a2))
}
