package main

import (
	"fmt"
	"sync"
)

var resource int = 0
var resMut sync.Mutex
var resCond *sync.Cond

func produceNoCond() {
	for {
		resMut.Lock()
		resource++
		resMut.Unlock()
	}
}

func consumeNoCond() {
	for {
		fmt.Println("I am checking...")
		resMut.Lock()
		for resource > 0 {
			//fmt.Println("consume", resource)
			resource--
		}
		resMut.Unlock()
	}

}

func produceWithCond(mut *sync.Mutex, cond *sync.Cond) {
	for {
		resMut.Lock()
		resource++
		resMut.Unlock()
		cond.Signal()
	}
}
func consumeWithCond(mut *sync.Mutex, cond *sync.Cond) {
	for {
		mut.Lock()
		for resource <= 0 {
			cond.Wait()
		}
		fmt.Println("consume", resource)
		for resource > 0 {
			resource--

		}
		mut.Unlock()
	}
}

func CondTest() {
	var mut sync.Mutex
	cond := sync.NewCond(&mut)
	go produceWithCond(&mut, cond)
	go produceWithCond(&mut, cond)
	consumeWithCond(&mut, cond)

}

func noCondTest() {
	go produceNoCond()
	go produceNoCond()
	consumeNoCond()
}
