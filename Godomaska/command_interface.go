package main

import (
	"fmt"
	"strconv"
	"strings"
)

// Поиск по имени
func findStackByName(name string) *NamedStack {
	for i := 0; i < namedStacksCount; i++ {
		if namedStacks[i].Used && namedStacks[i].Name == name {
			return &namedStacks[i]
		}
	}
	return nil
}

func findQueueByName(name string) *NamedQueue {
	for i := 0; i < namedQueuesCount; i++ {
		if namedQueues[i].Used && namedQueues[i].Name == name {
			return &namedQueues[i]
		}
	}
	return nil
}

func findArrayByName(name string) *NamedArray {
	for i := 0; i < namedArraysCount; i++ {
		if namedArrays[i].Used && namedArrays[i].Name == name {
			return &namedArrays[i]
		}
	}
	return nil
}

func findListByName(name string) *NamedList {
	for i := 0; i < namedListsCount; i++ {
		if namedLists[i].Used && namedLists[i].Name == name {
			return &namedLists[i]
		}
	}
	return nil
}

func findListTwoByName(name string) *NamedListTwo {
	for i := 0; i < namedListsTwoCount; i++ {
		if namedListsTwo[i].Used && namedListsTwo[i].Name == name {
			return &namedListsTwo[i]
		}
	}
	return nil
}

// Создание новых именованных структур
func createNewStack(name string) *NamedStack {
	existing := findStackByName(name)
	if existing != nil {
		fmt.Println("Стек", name, "уже существует!")
		return existing
	}
	if namedStacksCount >= MAX_NAMED_STRUCTURES {
		fmt.Println("Достигнут лимит именованных стеков!")
		return nil
	}
	namedStacks[namedStacksCount].Name = name
	namedStacks[namedStacksCount].Used = true
	namedStacks[namedStacksCount].Stack = NewStack(100, true)
	namedStacksCount++
	return &namedStacks[namedStacksCount-1]
}

func createNewQueue(name string) *NamedQueue {
	existing := findQueueByName(name)
	if existing != nil {
		fmt.Println("Очередь", name, "уже существует!")
		return existing
	}
	if namedQueuesCount >= MAX_NAMED_STRUCTURES {
		fmt.Println("Достигнут лимит именованных очередей!")
		return nil
	}
	namedQueues[namedQueuesCount].Name = name
	namedQueues[namedQueuesCount].Used = true
	namedQueues[namedQueuesCount].Queue = NewQueue(100, true)
	namedQueuesCount++

	return &namedQueues[namedQueuesCount-1]
}

func createNewArray(name string) *NamedArray {
	existing := findArrayByName(name)
	if existing != nil {
		fmt.Println("Массив", name, "уже существует!")
		return existing
	}
	if namedArraysCount >= MAX_NAMED_STRUCTURES {
		fmt.Println("Достигнут лимит именованных массивов!")
		return nil
	}
	namedArrays[namedArraysCount].Name = name
	namedArrays[namedArraysCount].Used = true
	namedArrays[namedArraysCount].Array = NewArray(10)
	namedArraysCount++

	return &namedArrays[namedArraysCount-1]
}

func createNewList(name string) *NamedList {
	existing := findListByName(name)
	if existing != nil {
		fmt.Println("Односвязный список", name, "уже существует!")
		return existing
	}
	if namedListsCount >= MAX_NAMED_STRUCTURES {
		fmt.Println("Достигнут лимит именованных односвязных списков!")
		return nil
	}
	namedLists[namedListsCount].Name = name
	namedLists[namedListsCount].Used = true
	namedLists[namedListsCount].List = NewForwardList()
	namedListsCount++
	fmt.Println("Создан новый односвязный список:", name)
	return &namedLists[namedListsCount-1]
}

func createNewListTwo(name string) *NamedListTwo {
	existing := findListTwoByName(name)
	if existing != nil {
		fmt.Println("Двусвязный список", name, "уже существует!")
		return existing
	}
	if namedListsTwoCount >= MAX_NAMED_STRUCTURES {
		fmt.Println("Достигнут лимит именованных двусвязных списков!")
		return nil
	}
	namedListsTwo[namedListsTwoCount].Name = name
	namedListsTwo[namedListsTwoCount].Used = true
	namedListsTwo[namedListsTwoCount].List = NewDoublyList()
	namedListsTwoCount++
	fmt.Println("Создан новый двусвязный список:", name)
	return &namedListsTwo[namedListsTwoCount-1]
}

// Набор команд для стека
func NAMED_SPUSH(stackName, value string) {
	stack := findStackByName(stackName)
	if stack == nil {
		stack = createNewStack(stackName)
		if stack == nil {
			return
		}
	}
	stack.Stack.Push(value)
	fmt.Println("Добавлен элемент", value, "в стек", stackName)
}

func NAMED_SPOP(stackName string) {
	stack := findStackByName(stackName)
	if stack != nil && !stack.Stack.IsEmpty() {
		val, _ := stack.Stack.Pop()
		fmt.Println("Извлечен элемент", val, "из стека", stackName)
	} else {
		fmt.Println("Стек", stackName, "не найден или пуст")
	}
}

func NAMED_SGET(stackName string) {
	stack := findStackByName(stackName)
	if stack != nil && !stack.Stack.IsEmpty() {
		val, _ := stack.Stack.TopValue()
		fmt.Println("Верхний элемент стека", stackName+":", val)
	} else {
		fmt.Println("Стек", stackName, "не найден или пуст")
	}
}

func NAMED_PRINT_STACK(stackName string) {
	stack := findStackByName(stackName)
	if stack == nil {
		fmt.Println("Стек", stackName, "не найден")
		return
	}
	if stack.Stack.IsEmpty() {
		fmt.Println("Стек", stackName, ": пуст")
	} else {
		fmt.Print("Стек ", stackName, ": ")
		stack.Stack.Print()
	}
}

// Очереди
func NAMED_QPUSH(queueName, value string) {
	q := findQueueByName(queueName)
	if q == nil {
		q = createNewQueue(queueName)
		if q == nil {
			return
		}
	}
	q.Queue.Enqueue(value)
	fmt.Println("Добавлен элемент", value, "в очередь", queueName)
}

func NAMED_QPOP(queueName string) {
	q := findQueueByName(queueName)
	if q != nil && !q.Queue.IsEmpty() {
		val, _ := q.Queue.Dequeue()
		fmt.Println("Извлечен элемент", val, "из очереди", queueName)
	} else {
		fmt.Println("Очередь", queueName, "не найдена или пуста")
	}
}

func NAMED_QGET(queueName string) {
	q := findQueueByName(queueName)
	if q != nil && !q.Queue.IsEmpty() {
		val, _ := q.Queue.Front()
		fmt.Println("Первый элемент очереди", queueName+":", val)
	} else {
		fmt.Println("Очередь", queueName, "не найдена или пуста")
	}
}

func NAMED_PRINT_QUEUE(queueName string) {
	q := findQueueByName(queueName)
	if q == nil {
		fmt.Println("Очередь", queueName, "не найдена")
		return
	}
	if q.Queue.IsEmpty() {
		fmt.Println("Очередь", queueName, ": пуста")
	} else {
		fmt.Print("Очередь ", queueName, ": ")
		q.Queue.Print()
	}
}

// Массивы
func NAMED_MPUSH(arrayName, value string) {
	arr := findArrayByName(arrayName)
	if arr == nil {
		arr = createNewArray(arrayName)
		if arr == nil {
			return
		}
	}
	arr.Array.Add(value)
	fmt.Println("Добавлен элемент", value, "в массив", arrayName)
}

func NAMED_MDEL(arrayName string, index int) {
	arr := findArrayByName(arrayName)
	if arr != nil {
		if index >= 0 && index < arr.Array.Size {
			val, _ := arr.Array.Get(index)
			arr.Array.Remove(index)
			fmt.Println("Удален элемент", val, "из массива", arrayName, "по индексу", index)
		} else {
			fmt.Println("Неверный индекс")
		}
	} else {
		fmt.Println("Массив", arrayName, "не найден")
	}
}

func NAMED_MGET(arrayName string, index int) {
	arr := findArrayByName(arrayName)
	if arr != nil {
		if index >= 0 && index < arr.Array.Size {
			val, _ := arr.Array.Get(index)
			fmt.Println("Элемент по индексу", index, "в массиве", arrayName+":", val)
		} else {
			fmt.Println("Неверный индекс")
		}
	} else {
		fmt.Println("Массив", arrayName, "не найден")
	}
}

func NAMED_MADDAT(arrayName string, index int, value string) {
	arr := findArrayByName(arrayName)
	if arr != nil {
		if index >= 0 && index <= arr.Array.Size {
			ok := arr.Array.AddAt(index, value)
			if ok {
				fmt.Println("Добавлен элемент", value, "в массив", arrayName, "по индексу", index)
			} else {
				fmt.Println("Ошибка добавления")
			}
		} else {
			fmt.Println("Неверный индекс")
		}
	} else {
		fmt.Println("Массив", arrayName, "не найден")
	}
}

func NAMED_MSET(arrayName string, index int, value string) {
	arr := findArrayByName(arrayName)
	if arr != nil {
		if index >= 0 && index < arr.Array.Size {
			arr.Array.Set(index, value)
			fmt.Println("Заменен элемент по индексу", index, "на значение", value, "в массиве", arrayName)
		} else {
			fmt.Println("Неверный индекс")
		}
	} else {
		fmt.Println("Массив", arrayName, "не найден")
	}
}

func NAMED_MLENGTH(arrayName string) {
	arr := findArrayByName(arrayName)
	if arr != nil {
		fmt.Println("Длина массива", arrayName+":", arr.Array.Length(), "элементов")
	} else {
		fmt.Println("Массив", arrayName, "не найден")
	}
}

func NAMED_MFIND(arrayName, value string) {
	arr := findArrayByName(arrayName)
	if arr != nil {
		idx := arr.Array.Find(value)
		if idx != -1 {
			fmt.Println("Элемент", value, "найден в массиве", arrayName, "по индексу", idx)
		} else {
			fmt.Println("Элемент", value, "не найден в массиве", arrayName)
		}
	} else {
		fmt.Println("Массив", arrayName, "не найден")
	}
}

func NAMED_MCREATE(arrayName string) {
	arr := findArrayByName(arrayName)
	if arr == nil {
		arr = createNewArray(arrayName)
		if arr != nil {
			fmt.Println("Массив", arrayName, "создан")
		}
	} else {
		fmt.Println("Массив", arrayName, "уже существует")
	}
}

func NAMED_PRINT_ARRAY(arrayName string) {
	arr := findArrayByName(arrayName)
	if arr == nil {
		fmt.Println("Массив", arrayName, "не найден")
		return
	}
	fmt.Print("Массив ", arrayName, ": ")
	arr.Array.Print()
}

// Односвязный список - отдельные команды для начала/конца
func NAMED_FPUSH_HEAD(listName, value string) {
	list := findListByName(listName)
	if list == nil {
		list = createNewList(listName)
		if list == nil {
			return
		}
	}
	addNodeHead(list.List, value)
	fmt.Println("Добавлен элемент", value, "в начало односвязного списка", listName)
}

func NAMED_FPUSH_TAIL(listName, value string) {
	list := findListByName(listName)
	if list == nil {
		list = createNewList(listName)
		if list == nil {
			return
		}
	}
	addNodeTail(list.List, value)
	fmt.Println("Добавлен элемент", value, "в конец односвязного списка", listName)
}

func NAMED_FPOP_HEAD(listName string) {
	list := findListByName(listName)
	if list != nil && list.List.head != nil {
		val := list.List.head.node
		deleteNodeHead(list.List)
		fmt.Println("Удален элемент", val, "из начала односвязного списка", listName)
	} else {
		fmt.Println("Список", listName, "не найден или пуст")
	}
}

func NAMED_FPOP_TAIL(listName string) {
	list := findListByName(listName)
	if list != nil && list.List.head != nil {
		// Находим последний элемент
		cur := list.List.head
		for cur.next != nil {
			cur = cur.next
		}
		val := cur.node
		// Удаляем последний элемент
		if list.List.head.next == nil {
			// Только один элемент
			list.List.head = nil
		} else {
			// Ищем предпоследний элемент
			prev := list.List.head
			for prev.next != nil && prev.next.next != nil {
				prev = prev.next
			}
			prev.next = nil
		}
		fmt.Println("Удален элемент", val, "из конца односвязного списка", listName)
	} else {
		fmt.Println("Список", listName, "не найден или пуст")
	}
}

func NAMED_FPUSH_AFTER(listName, value string, position int) {
	list := findListByName(listName)
	if list == nil {
		list = createNewList(listName)
		if list == nil {
			return
		}
	}
	target := getNodeByIndex(*list.List, position)
	if target != nil {
		addNodeAfter(list.List, target, value)
		fmt.Println("Добавлен элемент", value, "после позиции", position, "в односвязном списке", listName)
	} else {
		fmt.Println("Неверная позиция")
	}
}

func NAMED_FPUSH_BEFORE(listName, value string, position int) {
	list := findListByName(listName)
	if list == nil {
		list = createNewList(listName)
		if list == nil {
			return
		}
	}
	target := getNodeByIndex(*list.List, position)
	if target != nil {
		addNodeBefore(list.List, target, value)
		fmt.Println("Добавлен элемент", value, "перед позицией", position, "в односвязном списке", listName)
	} else {
		fmt.Println("Неверная позиция")
	}
}

func NAMED_FDEL(listName, value string) {
	list := findListByName(listName)
	if list != nil {
		if deleteNodeIndex(list.List, value) {
			fmt.Println("Удален элемент", value, "из односвязного списка", listName)
		} else {
			fmt.Println("Элемент не найден или список не существует")
		}
	} else {
		fmt.Println("Список", listName, "не найден")
	}
}

func NAMED_FGET(listName string, index int) {
	list := findListByName(listName)
	if list != nil {
		node := getNodeByIndex(*list.List, index)
		if node != nil {
			fmt.Println("Элемент по индексу", index, "в списке", listName+":", node.node)
		} else {
			fmt.Println("Неверный индекс")
		}
	} else {
		fmt.Println("Список", listName, "не найден")
	}
}

func NAMED_PRINT_LIST(listName string) {
	list := findListByName(listName)
	if list == nil {
		fmt.Println("Односвязный список", listName, "не найден")
		return
	}
	fmt.Print("Односвязный список ", listName, ": ")
	printList(*list.List)
}

func NAMED_FFIND(listName, value string) {
	list := findListByName(listName)
	if list != nil {
		if findNodeIndex(list.List, value) {
			fmt.Println("Элемент", value, "найден в списке", listName)
		} else {
			fmt.Println("Элемент", value, "не найден в списке", listName)
		}
	} else {
		fmt.Println("Список", listName, "не найден")
	}
}

func NAMED_FCOUNT(listName string) {
	list := findListByName(listName)
	if list != nil {
		fmt.Println("Количество элементов в списке", listName+":", countNodes(*list.List))
	} else {
		fmt.Println("Список", listName, "не найден")
	}
}

// Двусвязный список - отдельные команды для начала/конца
func NAMED_LPUSH_HEAD(listName, value string) {
	list := findListTwoByName(listName)
	if list == nil {
		list = createNewListTwo(listName)
		if list == nil {
			return
		}
	}
	addNodeHeadTwo(list.List, value)
	fmt.Println("Добавлен элемент", value, "в начало двусвязного списка", listName)
}

func NAMED_LPUSH_TAIL(listName, value string) {
	list := findListTwoByName(listName)
	if list == nil {
		list = createNewListTwo(listName)
		if list == nil {
			return
		}
	}
	addNodeTailTwo(list.List, value)
	fmt.Println("Добавлен элемент", value, "в конец двусвязного списка", listName)
}

func NAMED_LPOP_HEAD(listName string) {
	list := findListTwoByName(listName)
	if list != nil && list.List.head != nil {
		val := list.List.head.node
		deleteNodeHeadTwo(list.List)
		fmt.Println("Удален элемент", val, "из начала двусвязного списка", listName)
	} else {
		fmt.Println("Список", listName, "не найден или пуст")
	}
}

func NAMED_LPOP_TAIL(listName string) {
	list := findListTwoByName(listName)
	if list != nil && list.List.tail != nil {
		val := list.List.tail.node
		deleteNodeTailTwo(list.List)
		fmt.Println("Удален элемент", val, "из конца двусвязного списка", listName)
	} else {
		fmt.Println("Список", listName, "не найден или пуст")
	}
}

func NAMED_LPUSH_AFTER(listName, value string, position int) {
	list := findListTwoByName(listName)
	if list == nil {
		list = createNewListTwo(listName)
		if list == nil {
			return
		}
	}
	target := getNodeByIndexTwo(*list.List, position)
	if target != nil {
		addNodeAfterTwo(list.List, target, value)
		fmt.Println("Добавлен элемент", value, "после позиции", position, "в двусвязном списке", listName)
	} else {
		fmt.Println("Неверная позиция")
	}
}

func NAMED_LPUSH_BEFORE(listName, value string, position int) {
	list := findListTwoByName(listName)
	if list == nil {
		list = createNewListTwo(listName)
		if list == nil {
			return
		}
	}
	target := getNodeByIndexTwo(*list.List, position)
	if target != nil {
		addNodeBeforeTwo(list.List, target, value)
		fmt.Println("Добавлен элемент", value, "перед позицией", position, "в двусвязном списке", listName)
	} else {
		fmt.Println("Неверная позиция")
	}
}

func NAMED_LDEL(listName, value string) {
	list := findListTwoByName(listName)
	if list != nil {
		if deleteNodeIndexTwo(list.List, value) {
			fmt.Println("Удален элемент", value, "из двусвязного списка", listName)
		} else {
			fmt.Println("Элемент не найден или список не существует")
		}
	} else {
		fmt.Println("Список", listName, "не найден")
	}
}

func NAMED_LGET(listName string, index int) {
	list := findListTwoByName(listName)
	if list != nil {
		node := getNodeByIndexTwo(*list.List, index)
		if node != nil {
			fmt.Println("Элемент по индексу", index, "в списке", listName+":", node.node)
		} else {
			fmt.Println("Неверный индекс")
		}
	} else {
		fmt.Println("Список", listName, "не найден")
	}
}

func NAMED_PRINT_LIST_TWO(listName string) {
	list := findListTwoByName(listName)
	if list == nil {
		fmt.Println("Двусвязный список", listName, "не найден")
		return
	}
	fmt.Print("Двусвязный список ", listName, ": ")
	printListTwo(*list.List)
}

func NAMED_LFIND(listName, value string) {
	list := findListTwoByName(listName)
	if list != nil {
		if findNodeIndexTwo(list.List, value) {
			fmt.Println("Элемент", value, "найден в списке", listName)
		} else {
			fmt.Println("Элемент", value, "не найден в списке", listName)
		}
	} else {
		fmt.Println("Список", listName, "не найден")
	}
}

func NAMED_LCOUNT(listName string) {
	list := findListTwoByName(listName)
	if list != nil {
		fmt.Println("Количество элементов в списке", listName+":", countNodesTwo(*list.List))
	} else {
		fmt.Println("Список", listName, "не найден")
	}
}

func NAMED_PRINT_LIST_TWO_REVERSE(listName string) {
	list := findListTwoByName(listName)
	if list == nil {
		fmt.Println("Двусвязный список", listName, "не найден")
		return
	}
	fmt.Print("Двусвязный список ", listName, " (обратный порядок): ")
	cur := list.List.tail
	for cur != nil {
		fmt.Print(cur.node, " ")
		cur = cur.prev
	}
	fmt.Println()
}

// Системные функции
func LIST_STRUCTURES() {
	fmt.Println("=== ИМЕНОВАННЫЕ СТРУКТУРЫ ===")
	fmt.Print("Стеки (", namedStacksCount, "): ")
	for i := 0; i < namedStacksCount; i++ {
		if namedStacks[i].Used {
			fmt.Print(namedStacks[i].Name, " ")
		}
	}
	fmt.Println()

	fmt.Print("Очереди (", namedQueuesCount, "): ")
	for i := 0; i < namedQueuesCount; i++ {
		if namedQueues[i].Used {
			fmt.Print(namedQueues[i].Name, " ")
		}
	}
	fmt.Println()

	fmt.Print("Массивы (", namedArraysCount, "): ")
	for i := 0; i < namedArraysCount; i++ {
		if namedArrays[i].Used {
			fmt.Print(namedArrays[i].Name, " ")
		}
	}
	fmt.Println()

	fmt.Print("Односвязные списки (", namedListsCount, "): ")
	for i := 0; i < namedListsCount; i++ {
		if namedLists[i].Used {
			fmt.Print(namedLists[i].Name, " ")
		}
	}
	fmt.Println()

	fmt.Print("Двусвязные списки (", namedListsTwoCount, "): ")
	for i := 0; i < namedListsTwoCount; i++ {
		if namedListsTwo[i].Used {
			fmt.Print(namedListsTwo[i].Name, " ")
		}
	}
	fmt.Println()
}

func SAVE_ALL() {
	saveAllTo("named_data")
}

func LOAD_ALL() {
	loadAllFrom("named_data")
}

func CLEAR_ALL() {
	for i := 0; i < namedStacksCount; i++ {
		namedStacks[i].Used = false
		namedStacks[i].Stack = nil
	}
	for i := 0; i < namedQueuesCount; i++ {
		namedQueues[i].Used = false
		namedQueues[i].Queue = nil
	}
	for i := 0; i < namedArraysCount; i++ {
		namedArrays[i].Used = false
		namedArrays[i].Array = nil
	}
	for i := 0; i < namedListsCount; i++ {
		namedLists[i].Used = false
		namedLists[i].List = nil
	}
	for i := 0; i < namedListsTwoCount; i++ {
		namedListsTwo[i].Used = false
		namedListsTwo[i].List = nil
	}
	namedStacksCount = 0
	namedQueuesCount = 0
	namedArraysCount = 0
	namedListsCount = 0
	namedListsTwoCount = 0
}

func SAVE_ALL_TO(filename string) {
	saveAllTo(filename)
}

func LOAD_ALL_FROM(filename string) {
	CLEAR_ALL()
	loadAllFrom(filename)
}

// read-only checker
func isReadOnlyCommand(command string) bool {
	s := strings.TrimSpace(command)
	if s == "" {
		return true
	}
	parts := strings.Fields(s)
	cmd := parts[0]
	ro := []string{"SGET", "QGET", "MGET", "FGET", "LGET", "PRINT", "HELP", "LIST"}
	for _, r := range ro {
		if cmd == r {
			return true
		}
	}
	return false
}

// processCommand (поддерживает все команды, как в C++-файле)
func processCommand(command string) {
	command = strings.TrimSpace(command)
	if command == "" {
		return
	}
	// определяем команду по первому слову
	parts := strings.Fields(command)
	cmd := parts[0]

	switch cmd {
	case "SPUSH":
		t := strings.SplitN(command, " ", 3)
		if len(t) < 3 {
			fmt.Println("Неверный формат команды: SPUSH <stack_name> <value>")
			return
		}
		NAMED_SPUSH(t[1], t[2])
	case "SPOP":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: SPOP <stack_name>")
			return
		}
		NAMED_SPOP(parts[1])
	case "SGET":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: SGET <stack_name>")
			return
		}
		NAMED_SGET(parts[1])
	case "QPUSH":
		t := strings.SplitN(command, " ", 3)
		if len(t) < 3 {
			fmt.Println("Неверный формат команды: QPUSH <queue_name> <value>")
			return
		}
		NAMED_QPUSH(t[1], t[2])
	case "QPOP":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: QPOP <queue_name>")
			return
		}
		NAMED_QPOP(parts[1])
	case "QGET":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: QGET <queue_name>")
			return
		}
		NAMED_QGET(parts[1])
	case "MPUSH":
		t := strings.SplitN(command, " ", 3)
		if len(t) < 3 {
			fmt.Println("Неверный формат команды: MPUSH <array_name> <value>")
			return
		}
		NAMED_MPUSH(t[1], t[2])
	case "MDEL":
		if len(parts) < 3 {
			fmt.Println("Неверный формат команды: MDEL <array_name> <index>")
			return
		}
		idx, err := strconv.Atoi(parts[2])
		if err != nil {
			fmt.Println("Неверный индекс")
			return
		}
		NAMED_MDEL(parts[1], idx)
	case "MGET":
		if len(parts) < 3 {
			fmt.Println("Неверный формат команды: MGET <array_name> <index>")
			return
		}
		idx, err := strconv.Atoi(parts[2])
		if err != nil {
			fmt.Println("Неверный индекс")
			return
		}
		NAMED_MGET(parts[1], idx)
	case "MADDAT":
		t := strings.SplitN(command, " ", 4)
		if len(t) < 4 {
			fmt.Println("Неверный формат команды: MADDAT <array_name> <index> <value>")
			return
		}
		idx, err := strconv.Atoi(t[2])
		if err != nil {
			fmt.Println("Неверный индекс")
			return
		}
		NAMED_MADDAT(t[1], idx, t[3])
	case "MSET":
		t := strings.SplitN(command, " ", 4)
		if len(t) < 4 {
			fmt.Println("Неверный формат команды: MSET <array_name> <index> <value>")
			return
		}
		idx, err := strconv.Atoi(t[2])
		if err != nil {
			fmt.Println("Неверный индекс")
			return
		}
		NAMED_MSET(t[1], idx, t[3])
	case "MLENGTH":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: MLENGTH <array_name>")
			return
		}
		NAMED_MLENGTH(parts[1])
	case "MFIND":
		if len(parts) < 3 {
			fmt.Println("Неверный формат команды: MFIND <array_name> <value>")
			return
		}
		NAMED_MFIND(parts[1], parts[2])
	case "MCREATE":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: MCREATE <array_name>")
			return
		}
		NAMED_MCREATE(parts[1])
	// Односвязные списки - отдельные команды
	case "FPUSH_HEAD":
		t := strings.SplitN(command, " ", 3)
		if len(t) < 3 {
			fmt.Println("Неверный формат команды: FPUSH_HEAD <list_name> <value>")
			return
		}
		NAMED_FPUSH_HEAD(t[1], t[2])
	case "FPUSH_TAIL":
		t := strings.SplitN(command, " ", 3)
		if len(t) < 3 {
			fmt.Println("Неверный формат команды: FPUSH_TAIL <list_name> <value>")
			return
		}
		NAMED_FPUSH_TAIL(t[1], t[2])
	case "FPOP_HEAD":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: FPOP_HEAD <list_name>")
			return
		}
		NAMED_FPOP_HEAD(parts[1])
	case "FPOP_TAIL":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: FPOP_TAIL <list_name>")
			return
		}
		NAMED_FPOP_TAIL(parts[1])
	case "FPUSH_AFTER":
		t := strings.SplitN(command, " ", 4)
		if len(t) < 4 {
			fmt.Println("Неверный формат команды: FPUSH_AFTER <list_name> <value> <position>")
			return
		}
		pos, err := strconv.Atoi(t[3])
		if err != nil {
			fmt.Println("Неверная позиция")
			return
		}
		NAMED_FPUSH_AFTER(t[1], t[2], pos)
	case "FPUSH_BEFORE":
		t := strings.SplitN(command, " ", 4)
		if len(t) < 4 {
			fmt.Println("Неверный формат команды: FPUSH_BEFORE <list_name> <value> <position>")
			return
		}
		pos, err := strconv.Atoi(t[3])
		if err != nil {
			fmt.Println("Неверная позиция")
			return
		}
		NAMED_FPUSH_BEFORE(t[1], t[2], pos)
	case "FDEL":
		if len(parts) < 3 {
			fmt.Println("Неверный формат команды: FDEL <list_name> <value>")
			return
		}
		NAMED_FDEL(parts[1], parts[2])
	case "FGET":
		if len(parts) < 3 {
			fmt.Println("Неверный формат команды: FGET <list_name> <index>")
			return
		}
		idx, err := strconv.Atoi(parts[2])
		if err != nil {
			fmt.Println("Неверный индекс")
			return
		}
		NAMED_FGET(parts[1], idx)
	case "FFIND":
		if len(parts) < 3 {
			fmt.Println("Неверный формат команды: FFIND <list_name> <value>")
			return
		}
		NAMED_FFIND(parts[1], parts[2])
	case "FCOUNT":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: FCOUNT <list_name>")
			return
		}
		NAMED_FCOUNT(parts[1])
	// Двусвязные списки - отдельные команды
	case "LPUSH_HEAD":
		t := strings.SplitN(command, " ", 3)
		if len(t) < 3 {
			fmt.Println("Неверный формат команды: LPUSH_HEAD <list_name> <value>")
			return
		}
		NAMED_LPUSH_HEAD(t[1], t[2])
	case "LPUSH_TAIL":
		t := strings.SplitN(command, " ", 3)
		if len(t) < 3 {
			fmt.Println("Неверный формат команды: LPUSH_TAIL <list_name> <value>")
			return
		}
		NAMED_LPUSH_TAIL(t[1], t[2])
	case "LPOP_HEAD":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: LPOP_HEAD <list_name>")
			return
		}
		NAMED_LPOP_HEAD(parts[1])
	case "LPOP_TAIL":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: LPOP_TAIL <list_name>")
			return
		}
		NAMED_LPOP_TAIL(parts[1])
	case "LPUSH_AFTER":
		t := strings.SplitN(command, " ", 4)
		if len(t) < 4 {
			fmt.Println("Неверный формат команды: LPUSH_AFTER <list_name> <value> <position>")
			return
		}
		pos, err := strconv.Atoi(t[3])
		if err != nil {
			fmt.Println("Неверная позиция")
			return
		}
		NAMED_LPUSH_AFTER(t[1], t[2], pos)
	case "LPUSH_BEFORE":
		t := strings.SplitN(command, " ", 4)
		if len(t) < 4 {
			fmt.Println("Неверный формат команды: LPUSH_BEFORE <list_name> <value> <position>")
			return
		}
		pos, err := strconv.Atoi(t[3])
		if err != nil {
			fmt.Println("Неверная позиция")
			return
		}
		NAMED_LPUSH_BEFORE(t[1], t[2], pos)
	case "LDEL":
		if len(parts) < 3 {
			fmt.Println("Неверный формат команды: LDEL <list_name> <value>")
			return
		}
		NAMED_LDEL(parts[1], parts[2])
	case "LGET":
		if len(parts) < 3 {
			fmt.Println("Неверный формат команды: LGET <list_name> <index>")
			return
		}
		idx, err := strconv.Atoi(parts[2])
		if err != nil {
			fmt.Println("Неверный индекс")
			return
		}
		NAMED_LGET(parts[1], idx)
	case "LFIND":
		if len(parts) < 3 {
			fmt.Println("Неверный формат команды: LFIND <list_name> <value>")
			return
		}
		NAMED_LFIND(parts[1], parts[2])
	case "LCOUNT":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: LCOUNT <list_name>")
			return
		}
		NAMED_LCOUNT(parts[1])
	case "LPRINT_REVERSE":
		if len(parts) < 2 {
			fmt.Println("Неверный формат команды: LPRINT_REVERSE <list_name>")
			return
		}
		NAMED_PRINT_LIST_TWO_REVERSE(parts[1])
	case "LIST":
		LIST_STRUCTURES()
	case "PRINT":
		// PRINT <type> <name>
		if len(parts) < 3 {
			PRINT("")
			return
		}
		typ := parts[1]
		name := parts[2]
		switch typ {
		case "S":
			NAMED_PRINT_STACK(name)
		case "Q":
			NAMED_PRINT_QUEUE(name)
		case "M":
			NAMED_PRINT_ARRAY(name)
		case "F":
			NAMED_PRINT_LIST(name)
		case "L":
			NAMED_PRINT_LIST_TWO(name)
		default:
			fmt.Println("Неизвестный тип структуры:", typ)
		}
	case "SAVE_ALL":
		SAVE_ALL()
	case "LOAD_ALL":
		LOAD_ALL()
	case "CLEAR_ALL":
		CLEAR_ALL()
	case "EXIT", "QUIT":
		SAVE_ALL()
		// program exit should be handled by caller; here we just save
	case "HELP":
		printHelp()
	default:
		fmt.Println("Неизвестная команда. Введите HELP для списка команд.")
	}
}

func PRINT(arg string) {
	if arg == "" {
		fmt.Println("Используйте PRINT <тип> <имя> для именованных структур")
		fmt.Println("Типы: S (стек), Q (очередь), M (массив), F (односвязный список), L (двусвязный список)")
		fmt.Println("Пример: PRINT S mystack")
	}
}

func printHelp() {
	fmt.Println("Доступные команды (только именованные структуры):")
	fmt.Println("  SPUSH <stack_name> <value> - добавить в именованный стек")
	fmt.Println("  SPOP <stack_name> - извлечь из именованного стека")
	fmt.Println("  SGET <stack_name> - посмотреть верхний элемент именованного стека")
	fmt.Println("  QPUSH <queue_name> <value> - добавить в именованную очередь")
	fmt.Println("  QPOP <queue_name> - извлечь из именованной очереди")
	fmt.Println("  QGET <queue_name> - посмотреть первый элемент именованной очереди")
	fmt.Println("  MPUSH <array_name> <value> - добавить в именованный массив")
	fmt.Println("  MDEL <array_name> <index> - удалить из именованного массива по индексу")
	fmt.Println("  MGET <array_name> <index> - получить элемент именованного массива по индексу")
	fmt.Println("  MADDAT <array_name> <index> <value> - добавить в массив по индексу")
	fmt.Println("  MSET <array_name> <index> <value> - заменить элемент в массиве по индексу")
	fmt.Println("  MLENGTH <array_name> - получить длину массива")
	fmt.Println("  MFIND <array_name> <value> - найти элемент в массиве по значению")
	fmt.Println("  MCREATE <array_name> - создать новый массив")
	// Односвязные списки
	fmt.Println("  FPUSH_HEAD <list_name> <value> - добавить в начало односвязного списка")
	fmt.Println("  FPUSH_TAIL <list_name> <value> - добавить в конец односвязного списка")
	fmt.Println("  FPOP_HEAD <list_name> - удалить из начала односвязного списка")
	fmt.Println("  FPOP_TAIL <list_name> - удалить из конца односвязного списка")
	fmt.Println("  FPUSH_AFTER <list_name> <value> <position> - добавить после позиции")
	fmt.Println("  FPUSH_BEFORE <list_name> <value> <position> - добавить перед позицией")
	fmt.Println("  FDEL <list_name> <value> - удалить по значению")
	fmt.Println("  FGET <list_name> <index> - получить по индексу")
	fmt.Println("  FFIND <list_name> <value> - найти по значению")
	fmt.Println("  FCOUNT <list_name> - подсчитать элементы")
	// Двусвязные списки
	fmt.Println("  LPUSH_HEAD <list_name> <value> - добавить в начало двусвязного списка")
	fmt.Println("  LPUSH_TAIL <list_name> <value> - добавить в конец двусвязного списка")
	fmt.Println("  LPOP_HEAD <list_name> - удалить из начала двусвязного списка")
	fmt.Println("  LPOP_TAIL <list_name> - удалить из конца двусвязного списка")
	fmt.Println("  LPUSH_AFTER <list_name> <value> <position> - добавить после позиции")
	fmt.Println("  LPUSH_BEFORE <list_name> <value> <position> - добавить перед позицией")
	fmt.Println("  LDEL <list_name> <value> - удалить по значению")
	fmt.Println("  LGET <list_name> <index> - получить по индексу")
	fmt.Println("  LFIND <list_name> <value> - найти по значению")
	fmt.Println("  LCOUNT <list_name> - подсчитать элементы")
	fmt.Println("  LPRINT_REVERSE <list_name> - вывести в обратном порядке")
	// Системные команды
	fmt.Println("  LIST - показать все именованные структуры")
	fmt.Println("  PRINT <type> <name> - вывести именованную структуру (типы: S,Q,M,F,L)")
	fmt.Println("  SAVE_ALL - сохранить все именованные данные")
	fmt.Println("  LOAD_ALL - загрузить все именованные данные")
	fmt.Println("  CLEAR_ALL - очистить все именованные данные")
	fmt.Println("  EXIT/QUIT - выход (с автосохранением)")
	fmt.Println("  HELP - показать эту справку")
}
