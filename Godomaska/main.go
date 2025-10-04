package main

import "fmt"

func main() {
    fmt.Println("=== Базовый тест ===")
    arr := NewArray(3)
    
    arr.Add(10)
    arr.Add(20)
    arr.Add(30)
    
    fmt.Print("Массив: ")
    arr.Print()
    fmt.Printf("Размер: %d, Емкость: %d\n\n", arr.Length(), arr.Capacity())
    
    fmt.Println("=== Тест вставки по индексу ===")
    arr.AddAt(1, 15) // Вставляем 15 на позицию 1
    fmt.Print("После вставки 15 на позицию 1: ")
    arr.Print()
    
    fmt.Println("=== Тест удаления ===")
    arr.Remove(2) // Удаляем элемент на позиции 2
    fmt.Print("После удаления элемента на позиции 2: ")
    arr.Print()
    
    fmt.Println("=== Тест получения элемента ===")
    if value, err := arr.Get(1); err == nil {
        fmt.Printf("Элемент на позиции 1: %d\n", value)
    }
    
    fmt.Println("=== Тест поиска ===")
    fmt.Printf("Содержит 15: %v\n", arr.Contains(15))
    fmt.Printf("Содержит 100: %v\n", arr.Contains(100))
    
    fmt.Println("=== Тест изменения элемента ===")
    arr.Set(0, 999)
    fmt.Print("После изменения первого элемента на 999: ")
    arr.Print()
    
    fmt.Printf("Итоговый размер: %d, емкость: %d\n", arr.Length(), arr.Capacity())
}