package main

import (
	"fmt"
	"math/rand"
	"time"
)

var depositC = make(chan int)
var balanceC = make(chan int)
var withdrawC = make(chan int)

func withdraw(amount int) {
	withdrawC <- amount
}

func deposit(amount int) {
	depositC <- amount
}
func check() {
	b := <-balanceC
	fmt.Println(b)
}
func teller(start int) {
	var balance int = start
	for {
		select {
		case amount := <-depositC:
			balance += amount
		case amount := <-withdrawC:
			if balance-amount < 0 {
				break
			}
			balance -= amount
		case balanceC <- balance:

		}
	}
}

func testMultiWithdraw() {
	for {

		withdraw(rand.Intn(100))

		check()
		duration := int(time.Microsecond) * rand.Intn(60)
		d := time.Duration(duration)
		time.Sleep(d)
	}
}

func testMultiDeposit() {
	for {

		deposit(rand.Intn(100))

		check()
		duration := int(time.Microsecond) * rand.Intn(60)
		d := time.Duration(duration)
		time.Sleep(d)
	}
}

func main() {
	rand.Seed(int64(time.Now().Second()))

	go testMultiDeposit()
	go testMultiWithdraw()
	teller(0)

}
