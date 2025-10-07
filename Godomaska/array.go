package main

import "fmt"

type Array struct {
	Data     []string
	Size     int
	Capacity int
}

func NewArray(initialCapacity int) *Array {
	if initialCapacity <= 0 {
		initialCapacity = 10
	}
	return &Array{
		Data:     make([]string, initialCapacity),
		Size:     0,
		Capacity: initialCapacity,
	}
}

func (a *Array) resize() {
	newCap := a.Capacity * 2
	if newCap == 0 {
		newCap = 1
	}
	newData := make([]string, newCap)
	copy(newData, a.Data[:a.Size])
	a.Data = newData
	a.Capacity = newCap
}

func (a *Array) Add(value string) {
	if a.Size == a.Capacity {
		a.resize()
	}
	a.Data[a.Size] = value
	a.Size++
}

func (a *Array) AddAt(index int, value string) bool {
	if index < 0 || index > a.Size {
		return false
	}
	if a.Size == a.Capacity {
		a.resize()
	}
	// shift elements to the right
	a.Data = append(a.Data[:index+1], a.Data[index:a.Size]...)
	a.Data[index] = value
	a.Size++
	return true
}

func (a *Array) Get(index int) (string, bool) {
	if index < 0 || index >= a.Size {
		return "", false
	}
	return a.Data[index], true
}

func (a *Array) Remove(index int) bool {
	if index < 0 || index >= a.Size {
		return false
	}
	copy(a.Data[index:], a.Data[index+1:a.Size])
	a.Size--
	a.Data[a.Size] = ""
	return true
}

func (a *Array) Set(index int, value string) bool {
	if index < 0 || index >= a.Size {
		return false
	}
	a.Data[index] = value
	return true
}

func (a *Array) Length() int {
	return a.Size
}

func (a *Array) Print() {
	fmt.Print("(массив): ")
	for i := 0; i < a.Size; i++ {
		fmt.Print(a.Data[i], " ")
	}
	fmt.Println()
}

func (a *Array) Find(value string) int {
	for i := 0; i < a.Size; i++ {
		if a.Data[i] == value {
			return i
		}
	}
	return -1
}
