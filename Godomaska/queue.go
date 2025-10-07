package main

import "fmt"

type Queue struct {
	arr      []string
	capacity int
	front    int
	size     int
	silent   bool
}

func NewQueue(cap int, silent bool) *Queue {
	if cap <= 0 {
		cap = 100
	}
	return &Queue{
		arr:      make([]string, cap),
		capacity: cap,
		front:    0,
		size:     0,
		silent:   silent,
	}
}

func (q *Queue) Enqueue(value string) {
	if q.size == q.capacity {
		newCap := q.capacity * 2
		newArr := make([]string, newCap)
		for i := 0; i < q.size; i++ {
			newArr[i] = q.arr[(q.front+i)%q.capacity]
		}
		q.arr = newArr
		q.capacity = newCap
		q.front = 0
	}
	pos := (q.front + q.size) % q.capacity
	q.arr[pos] = value
	q.size++
	if !q.silent {
		fmt.Println("Элемент", value, "добавлен в очередь")
	}
}

func (q *Queue) Dequeue() (string, bool) {
	if q.size == 0 {
		if !q.silent {
			fmt.Println("Очередь пуста!")
		}
		return "", false
	}
	val := q.arr[q.front]
	q.arr[q.front] = ""
	q.front = (q.front + 1) % q.capacity
	q.size--
	if !q.silent {
		fmt.Println("Элемент", val, "удалён из очереди")
	}
	return val, true
}

func (q *Queue) Front() (string, bool) {
	if q.size == 0 {
		if !q.silent {
			fmt.Println("Очередь пуста!")
		}
		return "", false
	}
	return q.arr[q.front], true
}

func (q *Queue) IsEmpty() bool {
	return q.size == 0
}

func (q *Queue) GetSize() int {
	return q.size
}

func (q *Queue) Print() {
	if q.size == 0 {
		fmt.Println("(пустая очередь)")
		return
	}
	fmt.Print("(первый -> последний): ")
	for i := 0; i < q.size; i++ {
		fmt.Print(q.arr[(q.front+i)%q.capacity], " ")
	}
	fmt.Println()
}
