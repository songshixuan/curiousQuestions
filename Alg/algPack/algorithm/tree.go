package algorithm


type TreeNode struct {
	Val int
	Left *TreeNode
	Right *TreeNode
}


var Root *TreeNode = nil

func Insert(n **TreeNode, v int){
	if *n == nil{
		*n = &TreeNode{v,nil,nil}
	}
	

}