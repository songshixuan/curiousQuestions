package main

import (
	"fmt"
	"runtime"
	"sync"
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




