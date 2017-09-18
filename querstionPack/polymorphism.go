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