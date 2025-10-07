package main

import "fmt"

type Stack struct {
	Arr      []string
	Capacity int
	Top      int
	Silent   bool
}

func NewStack(cap int, silent bool) *Stack {
	if cap <= 0 {
		cap = 100
	}
	return &Stack{
		Arr:      make([]string, cap),
		Capacity: cap,
		Top:      -1,
		Silent:   silent,
	}
}

func (s *Stack) Push(value string) {
	if s.Top >= s.Capacity-1 {
		newCap := s.Capacity * 2
		newArr := make([]string, newCap)
		copy(newArr, s.Arr)
		s.Arr = newArr
		s.Capacity = newCap
	}
	s.Top++
	s.Arr[s.Top] = value
	if !s.Silent {
		fmt.Println("Элемент", value, "добавлен в стек")
	}
}

func (s *Stack) Pop() (string, bool) {
	if s.Top < 0 {
		if !s.Silent {
			fmt.Println("Стек пуст!")
		}
		return "", false
	}
	val := s.Arr[s.Top]
	s.Arr[s.Top] = ""
	s.Top--
	if !s.Silent {
		fmt.Println("Элемент", val, "удалён из стека")
	}
	return val, true
}

func (s *Stack) TopValue() (string, bool) {
	if s.Top < 0 {
		if !s.Silent {
			fmt.Println("Стек пуст!")
		}
		return "", false
	}
	return s.Arr[s.Top], true
}

func (s *Stack) IsEmpty() bool {
	return s.Top < 0
}

func (s *Stack) Print() {
	if s.IsEmpty() {
		fmt.Println("(пустой стек)")
		return
	}
	fmt.Print("(нижний -> верхний): ")
	for i := 0; i <= s.Top; i++ {
		fmt.Print(s.Arr[i], " ")
	}
	fmt.Println()
}
