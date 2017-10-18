package main

import (
	"fmt"
	"sync"
)

var resource int = 0
var resMut sync.Mutex

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

func noCondTest() {
	go produceNoCond()
	go produceNoCond()
	consumeNoCond()
}
