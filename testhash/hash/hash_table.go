package hash

import (
	"hash/fnv"
)

const SIZE = 100 // Размер хэш-таблицы

type HNode struct {
	key   string
	value string
	next  *HNode
}

type HashTable struct {
	table     [SIZE]*HNode
	tableSize int
}

// Создание нового экземпляра HashTable
func NewHashTable() *HashTable {
	return &HashTable{}
}

// Хеш-функция
func (ht *HashTable) hashFunction(key string) int {
	h := fnv.New32a()
	h.Write([]byte(key))
	return int(h.Sum32()) % SIZE
}

// Функция добавления элемента
func (ht *HashTable) Insert(key, value string) {
	hashValue := ht.hashFunction(key)
	newPair := &HNode{key: key, value: value}

	if ht.table[hashValue] == nil {
		ht.table[hashValue] = newPair
		ht.tableSize++
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
		current.next = newPair // Добавляем новый элемент
		ht.tableSize++
	}
}

// Функция получения значения по ключу
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

// Функция удаления элемента
func (ht *HashTable) Remove(key string) bool {
	hashValue := ht.hashFunction(key)
	current := ht.table[hashValue]
	var prev *HNode = nil

	for current != nil {
		if current.key == key {
			if prev != nil {
				prev.next = current.next
			} else {
				ht.table[hashValue] = current.next
			}
			ht.tableSize-- // Уменьшаем размер
			return true
		}
		prev = current
		current = current.next
	}
	return false
}

// Возвращает текущее количество элементов
func (ht *HashTable) Size() int {
	return ht.tableSize
}
