package queue

import (
	"errors"
)

// Queue класс для структуры очереди.
type Queue struct {
	data     []string
	size     int
	front    int // Индекс первого элемента
	rear     int // Индекс последнего элемента
	capacity int // Вместимость очереди
}

// NewQueue создает новый экземпляр класса Queue с заданной вместимостью.
func NewQueue(cap int) *Queue {
	return &Queue{
		data:     make([]string, cap),
		capacity: cap,
		front:    0,
		rear:     -1,
		size:     0,
	}
}

// NewDefaultQueue создает новый экземпляр класса Queue с вместимостью по умолчанию.
func NewDefaultQueue() *Queue {
	return NewQueue(30)
}

// IsEmpty проверяет, пуста ли очередь.
func (q *Queue) IsEmpty() bool {
	return q.size == 0
}

// Push добавляет элемент в конец очереди.
func (q *Queue) Push(value string) error {
	if q.size == q.capacity {
		return errors.New("очередь переполнена")
	}
	q.rear = (q.rear + 1) % q.capacity
	q.data[q.rear] = value
	q.size++
	return nil
}

// Pop удаляет элемент из начала очереди и возвращает его.
func (q *Queue) Pop() (string, error) {
	if q.IsEmpty() {
		return "", errors.New("очередь пуста")
	}
	value := q.data[q.front]
	q.front = (q.front + 1) % q.capacity
	q.size--
	return value, nil
}

// Peek возвращает элемент на начале очереди, не удаляя его.
func (q *Queue) Peek() (string, error) {
	if q.IsEmpty() {
		return "", errors.New("очередь пуста")
	}
	return q.data[q.front], nil
}

// Size возвращает текущее количество элементов в очереди.
func (q *Queue) Size() int {
	return q.size
}
