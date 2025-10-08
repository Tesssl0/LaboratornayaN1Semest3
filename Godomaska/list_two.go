package main

import "fmt"

type DoublyNode struct {
	node string
	next *DoublyNode
	prev *DoublyNode
}

type ForwardListTwo struct {
	head *DoublyNode
	tail *DoublyNode
}

func NewDoublyList() *ForwardListTwo {
	return &ForwardListTwo{head: nil, tail: nil}
}

func addNodeHeadTwo(flist *ForwardListTwo, num string) {
	newNode := &DoublyNode{node: num, next: flist.head, prev: nil}
	if flist.head != nil {
		flist.head.prev = newNode
	}
	flist.head = newNode
	if flist.tail == nil {
		flist.tail = newNode
	}
}

func addNodeTailTwo(flist *ForwardListTwo, num string) {
	newNode := &DoublyNode{node: num, next: nil, prev: flist.tail}
	if flist.tail != nil {
		flist.tail.next = newNode
	}
	flist.tail = newNode
	if flist.head == nil {
		flist.head = newNode
	}
}

func addNodeAfterTwo(flist *ForwardListTwo, target *DoublyNode, num string) {
	if target != nil {
		newNode := &DoublyNode{node: num, next: target.next, prev: target}
		if target.next != nil {
			target.next.prev = newNode
		} else {
			flist.tail = newNode
		}
		target.next = newNode
	}
}

func addNodeBeforeTwo(flist *ForwardListTwo, target *DoublyNode, num string) {
	if target != nil {
		newNode := &DoublyNode{node: num, next: target, prev: target.prev}
		if target.prev != nil {
			target.prev.next = newNode
		} else {
			flist.head = newNode
		}
		target.prev = newNode
	}
}

func deleteNodeHeadTwo(flist *ForwardListTwo) {
	if flist.head != nil {
		toDelete := flist.head
		flist.head = flist.head.next
		if flist.head != nil {
			flist.head.prev = nil
		} else {
			flist.tail = nil
		}
		toDelete.next = nil
		toDelete.prev = nil
	}
}

func deleteNodeTailTwo(flist *ForwardListTwo) {
	if flist.tail != nil {
		toDelete := flist.tail
		flist.tail = flist.tail.prev
		if flist.tail != nil {
			flist.tail.next = nil
		} else {
			flist.head = nil
		}
		toDelete.next = nil
		toDelete.prev = nil
	}
}

func deleteNodeAfterTwo(flist *ForwardListTwo, target *DoublyNode) {
	if target != nil && target.next != nil {
		toDelete := target.next
		target.next = toDelete.next
		if toDelete.next != nil {
			toDelete.next.prev = target
		} else {
			flist.tail = target
		}
		toDelete.next = nil
		toDelete.prev = nil
	}
}

func deleteNodeBeforeTwo(flist *ForwardListTwo, target *DoublyNode) {
	if target != nil && target.prev != nil {
		toDelete := target.prev
		target.prev = toDelete.prev
		if toDelete.prev != nil {
			toDelete.prev.next = target
		} else {
			flist.head = target
		}
		toDelete.next = nil
		toDelete.prev = nil
	}
}

func deleteNodeIndexTwo(flist *ForwardListTwo, num string) bool {
	if flist.head == nil {
		return false
	}
	cur := flist.head
	for cur != nil {
		if cur.node == num {
			if cur.prev != nil {
				cur.prev.next = cur.next
			} else {
				flist.head = cur.next
			}
			if cur.next != nil {
				cur.next.prev = cur.prev
			} else {
				flist.tail = cur.prev
			}
			return true
		}
		cur = cur.next
	}
	return false
}

func findNodeIndexTwo(flist *ForwardListTwo, num string) bool {
	cur := flist.head
	for cur != nil {
		if cur.node == num {
			return true
		}
		cur = cur.next
	}
	return false
}

func printListTwo(flist ForwardListTwo) {
	fmt.Print("Список: ")
	cur := flist.head
	for cur != nil {
		fmt.Print(cur.node, " ")
		cur = cur.next
	}
	fmt.Println()
}

func countNodesTwo(flist ForwardListTwo) int {
	cnt := 0
	cur := flist.head
	for cur != nil {
		cnt++
		cur = cur.next
	}
	return cnt
}

func getNodeByIndexTwo(flist ForwardListTwo, index int) *DoublyNode {
	if index < 0 {
		return nil
	}
	cur := flist.head
	i := 0
	for cur != nil {
		if i == index {
			return cur
		}
		cur = cur.next
		i++
	}
	return nil
}
