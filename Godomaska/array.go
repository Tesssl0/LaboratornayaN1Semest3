package main

import "fmt"

type Array struct {
    data     []int
    size     int
    capacity int
}

func NewArray(initialCapacity int) *Array {
    if initialCapacity <= 0 {
        initialCapacity = 10
    }
    return &Array{
        data:     make([]int, initialCapacity),
        size:     0,
        capacity: initialCapacity,
    }
}

func (arr *Array) Add(value int) {
    if arr.size == arr.capacity {
        arr.resize()
    }
    arr.data[arr.size] = value
    arr.size++
}

func (arr *Array) resize() {
    arr.capacity *= 2
    newData := make([]int, arr.capacity)
    copy(newData, arr.data[:arr.size])
    arr.data = newData
}

func (arr *Array) Print() {
    for i := 0; i < arr.size; i++ {
        fmt.Printf("%d ", arr.data[i])
    }
    fmt.Println()
}

func (arr *Array) Length() int {
    return arr.size
}

func (arr *Array) Capacity() int {
    return arr.capacity
}
func (arr *Array) AddAt(index int, value int) error {
    if index < 0 || index > arr.size {
        return fmt.Errorf("индекс %d вне границ", index)
    }
    
    if arr.size == arr.capacity {
        arr.resize()
    }
    
    // Сдвигаем элементы вправо
    for i := arr.size; i > index; i-- {
        arr.data[i] = arr.data[i-1]
    }
    
    arr.data[index] = value
    arr.size++
    return nil
}

// Remove удаляет элемент по индексу
func (arr *Array) Remove(index int) error {
    if index < 0 || index >= arr.size {
        return fmt.Errorf("индекс %d вне границ", index)
    }
    
    // Сдвигаем элементы влево
    for i := index; i < arr.size-1; i++ {
        arr.data[i] = arr.data[i+1]
    }
    
    arr.size--
    return nil
}

// Get возвращает элемент по индексу
func (arr *Array) Get(index int) (int, error) {
    if index < 0 || index >= arr.size {
        return 0, fmt.Errorf("индекс %d вне границ", index)
    }
    return arr.data[index], nil
}

// Set устанавливает значение элемента по индексу
func (arr *Array) Set(index int, value int) error {
    if index < 0 || index >= arr.size {
        return fmt.Errorf("индекс %d вне границ", index)
    }
    arr.data[index] = value
    return nil
}

// Contains проверяет наличие элемента
func (arr *Array) Contains(value int) bool {
    for i := 0; i < arr.size; i++ {
        if arr.data[i] == value {
            return true
        }
    }
    return false
}