package main

import (
	"fmt"
	"hash/fnv"
)

const SIZE = 100

type HNode struct {
	key   string
	value string
	next  *HNode
}

type HashTable struct {
	table     [SIZE]*HNode
	sizetable int
}

func NewHashTable() *HashTable {
	return &HashTable{}
}

func (ht *HashTable) hashFunction(key string) int {
	h := fnv.New32a()
	h.Write([]byte(key))
	return int(h.Sum32() % uint32(SIZE))
}

func (ht *HashTable) Insert(key, value string) {
	hashValue := ht.hashFunction(key)
	newPair := &HNode{key: key, value: value}

	if ht.table[hashValue] == nil {
		ht.table[hashValue] = newPair
		ht.sizetable++
	} else {
		current := ht.table[hashValue]
		for current != nil {
			if current.key == key {
				current.value = value // Обновляем значение
				return
			}
			if current.next == nil {
				break
			}
			current = current.next
		}
		current.next = newPair
		ht.sizetable++
	}
}

func (ht *HashTable) Get(key string) (string, bool) {
	hashValue := ht.hashFunction(key)
	current := ht.table[hashValue]
	for current != nil {
		if current.key == key {
			return current.value, true // Ключ найден
		}
		current = current.next
	}
	return "", false // Ключ не найден
}

func (ht *HashTable) Remove(key string) bool {
	hashValue := ht.hashFunction(key)
	current := ht.table[hashValue]
	var prev *HNode

	for current != nil {
		if current.key == key {
			if prev != nil {
				prev.next = current.next
			} else {
				ht.table[hashValue] = current.next
			}
			ht.sizetable-- // Уменьшаем размер
			return true
		}
		prev = current
		current = current.next
	}
	return false
}

func (ht *HashTable) Size() int {
	return ht.sizetable // Возвращаем текущее количество элементов
}

func main() {
	ht := NewHashTable()
	ht.Insert("key1", "value1")
	ht.Insert("key2", "value2")

	if value, found := ht.Get("key1"); found {
		fmt.Println("Found:", value)
	} else {
		fmt.Println("Not found")
	}

	fmt.Println("Size of hash table:", ht.Size())

	if ht.Remove("key1") {
		fmt.Println("Key1 removed")
	}

	fmt.Println("Size of hash table after removal:", ht.Size())
}
