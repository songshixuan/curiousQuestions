package main

import (
	"fmt"
)

func mergesort(arr []int, i int, j int) {
	if i < j {
		mid := (i + j) / 2
		mergesort(arr, i, mid)
		mergesort(arr, mid+1, j)
		merge(arr, i, mid, j)
	}
}

func merge(arr []int, i int, mid int, j int) {
	start := i
	lBeg := i
	lEnd := mid
	rBeg := mid + 1
	rEnd := j
	arrTemp := make([]int, len(arr))
	for lBeg <= lEnd && rBeg <= rEnd {
		if arr[lBeg] <= arr[rBeg] {
			arrTemp[i] = arr[lBeg]
			lBeg++
		} else {
			arrTemp[i] = arr[rBeg]
			rBeg++
		}
		i++
	}
	for lBeg <= lEnd {
		arrTemp[i] = arr[lBeg]
		lBeg++
		i++
	}
	for rBeg <= rEnd {
		arrTemp[i] = arr[rBeg]
		rBeg++
		i++
	}
	//copy back
	for start <= j {
		arr[start] = arrTemp[start]
		start++
	}

}

func quickSort(arr []int, i, j int) {
	if i < j {

		p := partition(arr, i, j)
		quickSort(arr, i, p-1)
		quickSort(arr, p+1, j)
	}

}

func partition(arr []int, i, j int) int {
	pivot := arr[j]
	l := i - 1
	index := i
	for ; index < j; index++ {
		if arr[index] < pivot {
			l++
			arr[l], arr[index] = arr[index], arr[l]
		}
	}
	l++
	arr[l], arr[j] = arr[j], arr[l]
	return l
}

func main() {
	var a = []int{1, 3, 5, 6, 4, 2, 99, 54, 23}

	quickSort(a, 0, len(a)-1)

	fmt.Println(a)
}
