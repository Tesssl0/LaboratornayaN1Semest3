package main

import "fmt"

type linkedList struct {
	node string
	next *linkedList
}

type ForwardList struct {
	head *linkedList
}

func NewForwardList() *ForwardList {
	return &ForwardList{head: nil}
}

func addNodeHead(flist *ForwardList, num string) {
	newNode := &linkedList{node: num, next: flist.head}
	flist.head = newNode
}

func addNodeTail(flist *ForwardList, num string) {
	newNode := &linkedList{node: num, next: nil}
	if flist.head == nil {
		flist.head = newNode
	} else {
		cur := flist.head
		for cur.next != nil {
			cur = cur.next
		}
		cur.next = newNode
	}
}

func addNodeAfter(flist *ForwardList, target *linkedList, num string) {
	if target != nil {
		newNode := &linkedList{node: num, next: target.next}
		target.next = newNode
	}
}

func addNodeBefore(flist *ForwardList, target *linkedList, num string) {
	if target != nil {
		if target == flist.head {
			addNodeHead(flist, num)
		} else {
			cur := flist.head
			for cur != nil && cur.next != target {
				cur = cur.next
			}
			if cur != nil && cur.next == target {
				newNode := &linkedList{node: num, next: target}
				cur.next = newNode
			}
		}
	}
}

func deleteNodeHead(flist *ForwardList) {
	if flist.head != nil {
		temp := flist.head
		flist.head = flist.head.next
		temp.next = nil
	}
}

func deleteNodeTail(flist *ForwardList) {
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
}

func deleteNodeAfter(flist *ForwardList, target *linkedList) {
	if target != nil && target.next != nil {
		toDelete := target.next
		target.next = toDelete.next
		toDelete.next = nil
	}
}

func deleteNodeBefore(flist *ForwardList, target *linkedList) {
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
