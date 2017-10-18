package main

import (
	"fmt"
	"sync"
)

var glob int = 0
var wg sync.WaitGroup
var incMu sync.Mutex

func tryunlock(i int) {
	defer wg.Done()
	fmt.Println("try Unlock", i)
	incMu.Unlock()

}

func mutIncr(i int) {
	defer wg.Done()
	fmt.Println("increase", i)
	loc := glob
	for j := 0; j < i; j++ {
		incMu.Lock()
		loc = glob
		loc++
		glob = loc
		incMu.Unlock()
	}
}

func incr(i int) {
	defer wg.Done()
	fmt.Println("increase", i)
	loc := glob
	for j := 0; j < i; j++ {
		//fmt.Println("execute")
		loc = glob
		loc++
		glob = loc
	}
}

func mutexTest() {

	wg.Add(2)
	go mutIncr(100000)
	go mutIncr(100000)
	wg.Wait()
	fmt.Println("glob=", glob)

}

func main() {
	CondTest()
}
