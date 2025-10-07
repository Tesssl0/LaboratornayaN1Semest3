package main

import (
	"fmt"
	"os"
)

func usageAndExit() {
	fmt.Fprintf(os.Stderr, "Usage: %s --file <filename> --query <QUERY>\n", os.Args[0])
	os.Exit(1)
}

func main() {
	if len(os.Args) < 5 {
		usageAndExit()
	}

	var fileName, query string
	for i := 1; i < len(os.Args); i++ {
		if os.Args[i] == "--file" && i+1 < len(os.Args) {
			fileName = os.Args[i+1]
			i++
		} else if os.Args[i] == "--query" && i+1 < len(os.Args) {
			query = os.Args[i+1]
			i++
		}
	}

	if fileName == "" || query == "" {
		usageAndExit()
	}

	// Загружаем все данные из файла
	LOAD_ALL_FROM(fileName)

	// Выполняем команду
	processCommand(query)

	// Если команда меняет данные, сохраняем их обратно
	if !isReadOnlyCommand(query) {
		SAVE_ALL_TO(fileName)
	}
}
