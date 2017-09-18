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

   Q: output what?

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

4. anonymous field & dynamic binding & receiver

   Q: what is the output?

   ```go
   type People struct {

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
   }

   func (t *Teacher) ShowB()  {
   	fmt.Println("Teacher show B")
   }


   func Question4() {
   	t := Teacher{}
   	t.ShowA()
   }

   ```

   A:

   ```
   people show A
   people show B
   ```

   showA() is people's method, no dynamic binding here!

   Q:  this time teacher has showA for its own,what is the output?

   ```go
   type People struct {

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

   }

   func (t *Teacher) ShowB()  {
   	fmt.Println("Teacher show B")
   }


   func Question4() {
   	t := Teacher{}
   	t.ShowA()
   }



   func (t *Teacher) ShowA(){
   	fmt.Println("Teacher show A")
   }
   ```

   A:

   ```
   Teacher show A
   ```

   Q: 1. this time, teacher doesn't have showA its own but has two inner field has ShowA  2. how about teacher has showA its own?

   ```go
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
   	t := Teacher{}
   	t.ShowA()
   }

   ```

   A:

    first A: ERROR:ambiguous selector t.ShowA
   second A: teacher showA

5. The proper way to achieve Polymorphism
   using interface:

   ```go
   package Quesion

   import "fmt"

   //base class
   type HasHobby interface {
   	MyHobby() string
   }



   type Dog struct {

   }

   type Dick struct {

   }

   //implement Hobby
   func (d *Dog) MyHobby() string {
   	return "whow!"
   }

   func (d *Dick) MyHobby() string  {
   	return "fuck"
   }

   func PolyTest1() {
   	var hasHobby HasHobby = &Dog{}
   	fmt.Println(hasHobby.MyHobby())
   	hasHobby = &Dick{}
   	fmt.Println(hasHobby.MyHobby())

   }
   ```

   ​

6. ​

   ​


