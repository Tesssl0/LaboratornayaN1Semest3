package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// Сохраняем/загружаем именованные структуры в отдельные файлы с суффиксами.

func saveNamedStacksToFile(base string) {
	fname := base + ".named_stacks"
	f, err := os.Create(fname)
	if err != nil {
		fmt.Println("Ошибка при создании", fname, ":", err)
		return
	}
	defer f.Close()

	for i := 0; i < namedStacksCount; i++ {
		if namedStacks[i].Used && namedStacks[i].Stack != nil {
			fmt.Fprint(f, "STACK ", namedStacks[i].Name, " ")
			// выводим элементы снизу вверх
			for j := 0; j <= namedStacks[i].Stack.Top; j++ {
				fmt.Fprint(f, namedStacks[i].Stack.Arr[j], " ")
			}
			fmt.Fprintln(f)
		}
	}
}

func loadNamedStacksFromFile(base string) {
	fname := base + ".named_stacks"
	f, err := os.Open(fname)
	if err != nil {
		// файл может не существовать — игнорируем
		return
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line := scanner.Text()
		tokens := strings.Fields(line)
		if len(tokens) >= 2 && tokens[0] == "STACK" {
			name := tokens[1]
			st := findStackByName(name)
			if st == nil {
				st = createNewStack(name)
				if st == nil {
					continue
				}
			}
			// push values in order
			for i := 2; i < len(tokens); i++ {
				st.Stack.Push(tokens[i])
			}
		}
	}
}

func saveNamedQueuesToFile(base string) {
	fname := base + ".named_queues"
	f, err := os.Create(fname)
	if err != nil {
		fmt.Println("Ошибка при создании", fname, ":", err)
		return
	}
	defer f.Close()

	for i := 0; i < namedQueuesCount; i++ {
		if namedQueues[i].Used && namedQueues[i].Queue != nil {
			fmt.Fprint(f, "QUEUE ", namedQueues[i].Name, " ")
			q := namedQueues[i].Queue
			for j := 0; j < q.size; j++ {
				fmt.Fprint(f, q.arr[(q.front+j)%q.capacity], " ")
			}
			fmt.Fprintln(f)
		}
	}
}

func loadNamedQueuesFromFile(base string) {
	fname := base + ".named_queues"
	f, err := os.Open(fname)
	if err != nil {
		return
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line := scanner.Text()
		tokens := strings.Fields(line)
		if len(tokens) >= 2 && tokens[0] == "QUEUE" {
			name := tokens[1]
			q := findQueueByName(name)
			if q == nil {
				q = createNewQueue(name)
				if q == nil {
					continue
				}
			}
			for i := 2; i < len(tokens); i++ {
				q.Queue.Enqueue(tokens[i])
			}
		}
	}
}

func saveNamedArraysToFile(base string) {
	fname := base + ".named_arrays"
	f, err := os.Create(fname)
	if err != nil {
		fmt.Println("Ошибка при создании", fname, ":", err)
		return
	}
	defer f.Close()

	for i := 0; i < namedArraysCount; i++ {
		if namedArrays[i].Used && namedArrays[i].Array != nil {
			fmt.Fprint(f, "ARRAY ", namedArrays[i].Name, " ")
			arr := namedArrays[i].Array
			for j := 0; j < arr.Size; j++ {
				fmt.Fprint(f, arr.Data[j], " ")
			}
			fmt.Fprintln(f)
		}
	}
}

func loadNamedArraysFromFile(base string) {
	fname := base + ".named_arrays"
	f, err := os.Open(fname)
	if err != nil {
		return
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line := scanner.Text()
		tokens := strings.Fields(line)
		if len(tokens) >= 2 && tokens[0] == "ARRAY" {
			name := tokens[1]
			arrN := findArrayByName(name)
			if arrN == nil {
				arrN = createNewArray(name)
				if arrN == nil {
					continue
				}
			}
			// clear array and fill
			arrN.Array = NewArray(10)
			for i := 2; i < len(tokens); i++ {
				arrN.Array.Add(tokens[i])
			}
		}
	}
}

func saveNamedListsToFile(base string) {
	fname := base + ".named_lists"
	f, err := os.Create(fname)
	if err != nil {
		fmt.Println("Ошибка при создании", fname, ":", err)
		return
	}
	defer f.Close()

	for i := 0; i < namedListsCount; i++ {
		if namedLists[i].Used && namedLists[i].List != nil {
			fmt.Fprint(f, "LIST ", namedLists[i].Name, " ")
			cur := namedLists[i].List.head
			for cur != nil {
				fmt.Fprint(f, cur.node, " ")
				cur = cur.next
			}
			fmt.Fprintln(f)
		}
	}
}

func loadNamedListsFromFile(base string) {
	fname := base + ".named_lists"
	f, err := os.Open(fname)
	if err != nil {
		return
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line := scanner.Text()
		tokens := strings.Fields(line)
		if len(tokens) >= 2 && tokens[0] == "LIST" {
			name := tokens[1]
			if namedListsCount >= MAX_NAMED_STRUCTURES {
				continue
			}
			namedLists[namedListsCount].Name = name
			namedLists[namedListsCount].Used = true
			namedLists[namedListsCount].List = NewForwardList()
			for i := 2; i < len(tokens); i++ {
				// Используем отдельную функцию вместо addNode с TAIL
				addNodeTail(namedLists[namedListsCount].List, tokens[i])
			}
			namedListsCount++
		}
	}
}

func saveNamedListsTwoToFile(base string) {
	fname := base + ".named_lists_two"
	f, err := os.Create(fname)
	if err != nil {
		fmt.Println("Ошибка при создании", fname, ":", err)
		return
	}
	defer f.Close()

	for i := 0; i < namedListsTwoCount; i++ {
		if namedListsTwo[i].Used && namedListsTwo[i].List != nil {
			fmt.Fprint(f, "LIST_TWO ", namedListsTwo[i].Name, " ")
			cur := namedListsTwo[i].List.head
			for cur != nil {
				fmt.Fprint(f, cur.node, " ")
				cur = cur.next
			}
			fmt.Fprintln(f)
		}
	}
}

func loadNamedListsTwoFromFile(base string) {
	fname := base + ".named_lists_two"
	f, err := os.Open(fname)
	if err != nil {
		return
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line := scanner.Text()
		tokens := strings.Fields(line)
		if len(tokens) >= 2 && tokens[0] == "LIST_TWO" {
			name := tokens[1]
			if namedListsTwoCount >= MAX_NAMED_STRUCTURES {
				continue
			}
			namedListsTwo[namedListsTwoCount].Name = name
			namedListsTwo[namedListsTwoCount].Used = true
			namedListsTwo[namedListsTwoCount].List = NewDoublyList()
			for i := 2; i < len(tokens); i++ {
				// Используем отдельную функцию вместо addNodeTwo с TAILTwo
				addNodeTailTwo(namedListsTwo[namedListsTwoCount].List, tokens[i])
			}
			namedListsTwoCount++
		}
	}
}

func saveAllTo(base string) {
	saveNamedStacksToFile(base)
	saveNamedQueuesToFile(base)
	saveNamedArraysToFile(base)
	saveNamedListsToFile(base)
	saveNamedListsTwoToFile(base)
}

func loadAllFrom(base string) {
	// Note: clear current content
	CLEAR_ALL()
	loadNamedStacksFromFile(base)
	loadNamedQueuesFromFile(base)
	loadNamedArraysFromFile(base)
	loadNamedListsFromFile(base)
	loadNamedListsTwoFromFile(base)
}
