package hash

import (
	"hash/fnv"
)

// Размер хэш-таблицы
const SIZE = 100

// Узел хэш-таблицы
type HNode struct {
	key   string
	value string
	next  *HNode
}

// Хэш-таблица
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

// Публичный метод для добавления элемента
func (ht *HashTable) Insert(key, value string) {
	ht.insert(key, value)
}

// Публичный метод для получения значения по ключу
func (ht *HashTable) Get(key string) (string, bool) {
	return ht.get(key)
}

// Публичный метод для удаления элемента
func (ht *HashTable) Remove(key string) bool {
	return ht.remove(key)
}

// Публичный метод для получения текущего количества элементов
func (ht *HashTable) Size() int {
	return ht.tableSize
}

// Приватный метод добавления элемента
func (ht *HashTable) insert(key, value string) {
	hashValue := ht.hashFunction(key)
	newPair := &HNode{key: key, value: value}

	if ht.table[hashValue] == nil {
		ht.table[hashValue] = newPair
		ht.tableSize++
		return
	}

	current := ht.table[hashValue]
	for current != nil {
		if current.key == key {
			current.value = value // Обновление значения
			return
		}
		if current.next == nil {
			break
		}
		current = current.next
	}
	current.next = newPair // Добавление нового элемента
	ht.tableSize++
}

// Приватный метод получения значения по ключу
func (ht *HashTable) get(key string) (string, bool) {
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

// Приватный метод удаления элемента
func (ht *HashTable) remove(key string) bool {
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
			ht.tableSize-- // Уменьшение размера
			return true
		}
		prev = current
		current = current.next
	}
	return false
}
