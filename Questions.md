# Questions

## Golang

1. defer & panic
   Q: what is the output?

   ```go
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
   ```

   A:

   ```
   4th line
   3rd line
   fuck panic
   2nd line
   1st line
   panic: fuck

   defer operation is pushed to stack,first in last out

   ```

2. range
   Q: output?

   ```go
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
   		m[stu.Name] = &stu
   	}

   /*
   	for i := 0; i < len(stus); i++{
   		m[stus[i].Name] = &stus[i]
   	}
   */
   	for k,v := range m{
   		fmt.Println("name:",k)
   		fmt.Println("status",v.Name,v.Age)
   	}
   }

   ```

   A: 

   ```
   name: zhou
   status diaosi 99
   name: diaosi
   status diaosi 99

   When ranging over a slice, two values are returned for each iteration. The first is the index, and the second is a copy of the element at that index.
   导致map里的student指针指向copy element的地址，copy element地址没变，所以引用的值是一样的，
   ```

3. goroutine and loop
   A: output what?

   ```go
   func Practice3() {
   	runtime.GOMAXPROCS(1) //use no more than one logic cpu
   	wg := sync.WaitGroup{}
   	wg.Add(20)
   	for i := 0; i < 10; i++ {
   		go func() {
   			fmt.Println("i: ", i)
   			wg.Done()
   		}()
   		if i == 9 {
   			fmt.Println("loop1 over")
   		}
   	}
   	for i := 10; i < 20; i++ {
   		//fmt.Println(i)
   		go func() {
   			fmt.Println("i: ", i)
   			wg.Done()
   		}()
   		if i == 19 {
   			fmt.Println("loop2 over")
   		}
   	}
   	wg.Wait()
   }
   ```

   A: 

   ```
   loop1 over
   loop2 over
   i:  20
   i:  10
   i:  10
   i:  10
   i:  10
   i:  10
   i:  10
   i:  10
   i:  10
   i:  10
   i:  10
   i:  20
   i:  20
   i:  20
   i:  20
   i:  20
   i:  20
   i:  20
   i:  20
   i:  20

   because the goroutines will probably not begin executing until after the loop;
   it comes especially when runtime logic cpu is one
   ```

   The proper ways to write that closure loop are these two:

   ```go
   for val := range values {
   	go func(val interface{}) {
   		fmt.Println(val)
   	}(val)
   }
   for i := range valslice {
   	val := valslice[i]
   	go func() {
   		fmt.Println(val)
   	}()
   }
   ```

    

