package main

type ListNode struct {
	Val  int
	Next *ListNode
}

type List struct {
	Head *ListNode
	Num int
}

func CreateList() *List{
	list := &List{nil,0}
	return list
}

func (list *List) PushBack(val int){

	if list.Head == nil{
		list.Head = &ListNode{val,nil}
	}

	prev := list.Head
	ptr := list.Head
	//find the empty node
	for ptr != nil{
		prev = ptr
		ptr = ptr.Next
	}
	prev.Next = &ListNode{val,nil}


}

func main(){


}
