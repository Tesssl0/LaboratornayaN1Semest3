package main

import "fmt"

type linkedList struct {
	node string
	next *linkedList
}

type ForwardList struct {
	head *linkedList
}

type Position int

const (
	HEAD Position = iota
	TAIL
	AFTER
	BEFORE
)

func NewForwardList() *ForwardList {
	return &ForwardList{head: nil}
}

func addNode(flist *ForwardList, target *linkedList, num string, pos Position) {
	newNode := &linkedList{node: num, next: nil}

	switch pos {
	case HEAD:
		newNode.next = flist.head
		flist.head = newNode
	case TAIL:
		if flist.head == nil {
			flist.head = newNode
		} else {
			cur := flist.head
			for cur.next != nil {
				cur = cur.next
			}
			cur.next = newNode
		}
	case AFTER:
		if target != nil {
			newNode.next = target.next
			target.next = newNode
		}
	case BEFORE:
		if target != nil {
			if target == flist.head {
				newNode.next = flist.head
				flist.head = newNode
			} else {
				cur := flist.head
				for cur != nil && cur.next != target {
					cur = cur.next
				}
				if cur != nil && cur.next == target {
					newNode.next = target
					cur.next = newNode
				}
			}
		}
	}
}

func deleteNode(flist *ForwardList, target *linkedList, num string, pos Position) {
	var toDelete *linkedList

	switch pos {
	case HEAD:
		if flist.head != nil {
			temp := flist.head
			flist.head = flist.head.next
			temp.next = nil
		}
	case TAIL:
		if flist.head == nil {
			return
		}
		if flist.head.next == nil {
			flist.head = nil
			return
		}
		cur := flist.head
		for cur.next != nil && cur.next.next != nil {
			cur = cur.next
		}
		cur.next = nil
	case AFTER:
		if target != nil && target.next != nil {
			toDelete = target.next
			target.next = toDelete.next
			toDelete.next = nil
		}
	case BEFORE:
		if target != nil {
			if target == flist.head {
				return
			}
			prev := (*linkedList)(nil)
			cur := flist.head
			for cur != nil && cur != target {
				prev = cur
				cur = cur.next
			}
			if prev != nil {
				// find prev's prev
				if prev == flist.head {
					flist.head = target
				} else {
					pp := flist.head
					for pp.next != prev {
						pp = pp.next
					}
					pp.next = target
				}
			}
		}
	}
}

func deleteNodeIndex(flist *ForwardList, num string) bool {
	if flist.head == nil {
		return false
	}
	if flist.head.node == num {
		flist.head = flist.head.next
		return true
	}
	cur := flist.head
	for cur.next != nil {
		if cur.next.node == num {
			toDelete := cur.next
			cur.next = toDelete.next
			toDelete.next = nil
			return true
		}
		cur = cur.next
	}
	return false
}

func findNodeIndex(flist *ForwardList, num string) bool {
	cur := flist.head
	for cur != nil {
		if cur.node == num {
			return true
		}
		cur = cur.next
	}
	return false
}

func printList(flist ForwardList) {
	fmt.Print("spisok: ")
	cur := flist.head
	for cur != nil {
		fmt.Print(cur.node, " ")
		cur = cur.next
	}
	fmt.Println()
}

func countNodes(flist ForwardList) int {
	cnt := 0
	cur := flist.head
	for cur != nil {
		cnt++
		cur = cur.next
	}
	return cnt
}

func getNodeByIndex(flist ForwardList, index int) *linkedList {
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
