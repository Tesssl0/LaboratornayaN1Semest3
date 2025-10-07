package main

// Определения именованных контейнеров и глобальных массивов/счетчиков

type NamedStack struct {
	Name  string
	Used  bool
	Stack *Stack
}

type NamedQueue struct {
	Name  string
	Used  bool
	Queue *Queue
}

type NamedArray struct {
	Name  string
	Used  bool
	Array *Array
}

type NamedList struct {
	Name string
	Used bool
	List *ForwardList
}

type NamedListTwo struct {
	Name string
	Used bool
	List *ForwardListTwo
}

var namedStacks [MAX_NAMED_STRUCTURES]NamedStack
var namedQueues [MAX_NAMED_STRUCTURES]NamedQueue
var namedArrays [MAX_NAMED_STRUCTURES]NamedArray
var namedLists [MAX_NAMED_STRUCTURES]NamedList
var namedListsTwo [MAX_NAMED_STRUCTURES]NamedListTwo

var namedStacksCount int
var namedQueuesCount int
var namedArraysCount int
var namedListsCount int
var namedListsTwoCount int

var firstLoad bool = true

func initGlobalStructures() {
	namedStacksCount = 0
	namedQueuesCount = 0
	namedArraysCount = 0
	namedListsCount = 0
	namedListsTwoCount = 0
	firstLoad = true
}
