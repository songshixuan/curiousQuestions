package Quesion

import (
	"fmt"
	"runtime"
	"sync"
	"reflect"
	"go/types"
)

func Practice1()  {
	defer func(){fmt.Println("1st line")
	}()
	defer func(){fmt.Println("2nd line")}()
	defer func(){fmt.Println("3rd line")
		//panic("fuck")
		fmt.Println("fuck panic")}()

	defer func() {
		fmt.Println("4th line")
		panic("fuck")
	} ()

}

type student struct {
	Name string
	Age 	int
}

func Practice2() {
	m := make(map[string]*student)
	stus := []student{
		{Name:"zhou",Age:25},
		{Name:"diaosi",Age:99},
	}
	//range return index and copy of element
	for _,stu := range stus{
		fmt.Println("in loop" ,&stu.Name)
		m[stu.Name] = &stu
	}


	for i := 0; i < len(stus); i++{
		m[stus[i].Name] = &stus[i]
	}



	for k,v := range m{
		fmt.Println(k)
		fmt.Println(v.Name)
		fmt.Println(v.Age)
	}
}



func Practice3(){
	runtime.GOMAXPROCS(100)
	wg := sync.WaitGroup{}
	wg.Add(20)
	for i := 0; i < 10; i++{
		fmt.Println(i)
		j := i
		go func() {
			fmt.Println("i: " ,j)
			fmt.Println("fuck i: " ,j,"fuck i again",j)
			fmt.Println("fuck i: " ,j,"fuck i again",j)
			wg.Done()
		}()
	}
	for i := 0; i < 10; i++{
		//fmt.Println(i)
		go func() {
			fmt.Println("i: " ,i)
			wg.Done()
		}()
	}
	//wg.Wait()
}




//q4
type People struct {

}

type Animal struct {

}

func (a *Animal) ShowA()  {
	fmt.Println("Fuck u!!!")
}

func (p *People) ShowA() {
	fmt.Println("people show A")
	p.ShowB()
}
func (p *People) ShowB(){
	fmt.Println("people show B")
}

type Teacher struct {
	People
	Animal
}

func (t *Teacher) ShowB()  {
	fmt.Println("Teacher show B")
}


func Question4() {
	//t := Teacher{}
	//t.ShowA()
}


/*
func (t *Teacher) ShowA(){
	fmt.Println("Teacher show A")
}
*/
//end of q4


func Question5(){
	runtime.GOMAXPROCS(1)
	int_chan := make(chan int,1)
	string_chan := make(chan string,1)
	int_chan <- 1
	string_chan <- "hello"
	select {
	case v1 := <- int_chan:
		fmt.Println(v1)
	case v2 := <- string_chan:
		fmt.Println(v2)
	}
}

func Question7() {
	s := make([]int,5)
	s = append(s,1,2,3)
	fmt.Println(s)
}

type UserAges struct {
	ages map[string]int
	sync.Mutex
}

func (ua *UserAges) Add(name string,age int){
	ua.Lock()
	defer ua.Unlock()
	ua.ages[name] = age
}

func (ua *UserAges) Get(name string)int{
	if age,ok := ua.ages[name];ok{
		return age
	}
	return -1
}

func Question8(){
	ua := UserAges{}
	ua.ages = make(map[string]int)
	ua.Add("Liuda",88)
	fmt.Println(ua.Get("Liuda"))

}


type Pig interface {
	Show()
}

type Poppy struct {

}

func (p *Poppy) Show(){

}

func live() Pig{
	var pp *Poppy
	return pp
}

func Question11(){
	if live() == nil{
		fmt.Println("AAAAA")
	}else{
		fmt.Printf("%T %v",live(),live())
		fmt.Println(reflect.TypeOf(live()))
		fmt.Println(reflect.ValueOf(live()))
		fmt.Println("BBBBB")
	}


}