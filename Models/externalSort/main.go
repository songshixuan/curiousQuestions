package main

import (
	"bufio"
	"fmt"
	"github.com/Workiva/go-datastructures/fibheap"
	"log"
	"os"
	"strconv"
	"sync"
)

const (
	POSTFIX_ORDER = "_ORDERD"
)

type Heap struct {
	HeapArray []int
	HeapSiz   int
}

func createHeap(arr []int, siz int) *Heap {
	heapArr := make([]int, siz+1)
	for i := 1; i <= siz; i++ {
		heapArr[i] = arr[i-1]
	}
	return &Heap{heapArr, siz}
}

/**
 */
func heapTest() {
	var arr = []int{87, 25, 4, 6, 7, 99, 53}
	h := createHeap(arr, len(arr))
	h.BuildHeap()
	h.HeapSort()
	fmt.Println(h.HeapArray, "size: ", h.HeapSiz)
}

func (h *Heap) minHeap(n int) {

	for n <= h.HeapSiz {
		fmt.Println("minheap")
		min := h.HeapArray[n]
		minN := n
		leftC := 2 * n
		rightC := 2*n + 1
		if leftC <= h.HeapSiz && h.HeapArray[leftC] < min {
			minN = leftC
			min = h.HeapArray[minN]
		}
		if rightC <= h.HeapSiz && h.HeapArray[rightC] < min {
			minN = rightC
			min = h.HeapArray[minN]
		}
		if n != minN {
			h.HeapArray[n], h.HeapArray[minN] = h.HeapArray[minN], h.HeapArray[n]
			n = minN
		} else {
			break
		}
	}

}

func (h *Heap) BuildHeap() {
	for i := h.HeapSiz / 2; i >= 1; i-- {
		h.minHeap(i)
	}
}

func (h *Heap) HeapSort() {
	for i := h.HeapSiz; i > 1; i-- {
		fmt.Println("swap")
		h.HeapArray[i], h.HeapArray[1] = h.HeapArray[1], h.HeapArray[i]
		fmt.Println(h.HeapArray)
		h.HeapSiz--
		h.minHeap(1)
	}
}

func (h *Heap) GetAndAdd(num int) (int, error) {
	ret := h.HeapArray[1]
	if h.HeapSiz > 0 {

		h.HeapSiz--
	} else {
		return ret, fmt.Errorf("empty")
	}
	h.HeapArray[1] = num
	h.HeapSiz++
	h.minHeap(1)
	return ret, nil
}

func (h *Heap) Pop() (int, error) {
	if h.HeapSiz <= 0 {
		fmt.Println("pop error")
		return 0, fmt.Errorf("empty")
	} else {
		fmt.Println("pop", h.HeapArray[1])
		h.HeapSiz--
		return h.HeapArray[1], nil
	}
}

func (h *Heap) Push(n int) {
	h.HeapSiz++
	if len(h.HeapArray) <= h.HeapSiz {
		old := h.HeapArray
		h.HeapArray = make([]int, 10*h.HeapSiz)
		for i, v := range old {
			h.HeapArray[i] = v
		}
	}
	h.HeapArray[1] = n
	h.minHeap(1)
}

const (
	FILE_PREFIX     = "dataFile"
	FILE_POSTFIX    = ".~tmp"
	ORDERED_POSTFIX = ".~otmp"
)

func quickSortWrapper(n int) []string {

	//newName := filename+ POSTFIX_ORDER

	var ordered = make([]string, n)
	var wg sync.WaitGroup
	for i := 0; i < n; i++ {
		go func(name string, index int) {
			wg.Add(1)
			var arr []int
			arr = make([]int, 0)
			fmt.Println("read", name)
			file, err := os.Open(name)
			if err != nil {
				log.Fatal(err)
			}
			defer file.Close()

			scanner := bufio.NewScanner(file)

			for scanner.Scan() {
				//fmt.Println(scanner.Text())
				iNum, _ := strconv.Atoi(scanner.Text())
				arr = append(arr, iNum)
			}

			if err := scanner.Err(); err != nil {
				log.Fatal(err)
			}

			quickSort(arr, 0, len(arr)-1)

			orderedFname := fmt.Sprintf("%s%d%s", FILE_PREFIX, index, ORDERED_POSTFIX)
			ordered[index] = orderedFname
			fmt.Println("create " + orderedFname)
			wf, err := os.Create(orderedFname)
			if err != nil {
				fmt.Printf("error creating file: %v", err)
				return
			}
			for _, v := range arr {
				wf.WriteString(fmt.Sprintf("%d\n", v))

			}

			defer wf.Close()
			defer wg.Done()

		}(fmt.Sprintf("%s%d%s", FILE_PREFIX, i, FILE_POSTFIX), i)
	}
	wg.Wait()
	return ordered
}

func Partition(arr []int, l, r int) int {
	left := l - 1
	pivot := arr[r]
	for ; l < r; l++ {
		if arr[l] <= pivot {
			left++
			arr[left], arr[l] = arr[l], arr[left]
		}
	}
	left += 1
	arr[left], arr[r] = arr[r], arr[left]
	return left
}

func quickSort(arr []int, l, r int) {
	if l < r {
		p := Partition(arr, l, r)
		quickSort(arr, l, p-1)
		quickSort(arr, p+1, r)
	}

}

/*
merge seperated result into one file
*/
func mergeResults(files []string, maxHeapHiz int) {

	var filechannelMap = make(map[string]chan int)
	for _, v := range files {
		filechannelMap[v] = make(chan int)
		go func(f string, C chan int) {
			file, err := os.Open(f)
			if err != nil {
				log.Fatal(err)
			}
			defer file.Close()

			scanner := bufio.NewScanner(file)

			for scanner.Scan() {
				//fmt.Println(scanner.Text())
				iNum, _ := strconv.Atoi(scanner.Text())
				C <- iNum
			}
			close(C)

		}(v, filechannelMap[v])
	}

	final := "results.txt"
	wf, err := os.Create(final)
	defer wf.Close()
	if err != nil {
		fmt.Printf("error creating file: %v", err)
		return
	}
	heap := fibheap.NewFloatFibHeap()

	for _, v := range files {
		heap.Enqueue(float64(<-filechannelMap[v]))
	}

	for heap.Size() > 0 {
		min, _ := heap.DequeueMin()
		wf.WriteString(fmt.Sprintf("%v\n", min.Priority))
		fName := files[int(min.Priority)%100]
		v, ok := <-filechannelMap[fName]
		if ok {
			heap.Enqueue(float64(v))
		}

	}

}

func main() {
	orederedFiles := quickSortWrapper(100)

	mergeResults(orederedFiles, 100)

}
