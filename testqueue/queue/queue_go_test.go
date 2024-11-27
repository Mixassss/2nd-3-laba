package queue

import (
	"strconv"
	"testing"
	"time"
)

func TestNewQueue(t *testing.T) {
	start := time.Now() // Запуск таймера
	defer func() {
		duration := time.Since(start)
		t.Logf("TestNewQueue execution time: %v seconds", duration.Seconds())
	}()

	q := NewQueue(5)
	if q.capacity != 5 {
		t.Errorf("Expected capacity 5, got %d", q.capacity)
	}
	if q.size != 0 {
		t.Errorf("Expected size 0, got %d", q.size)
	}
}

func TestPush(t *testing.T) {
	start := time.Now()
	defer func() {
		duration := time.Since(start)
		t.Logf("TestPush execution time: %v seconds", duration.Seconds())
	}()

	q := NewDefaultQueue()
	err := q.Push("1")
	if err != nil {
		t.Errorf("Expected no error, got %v", err)
	}
	if q.Size() != 1 {
		t.Errorf("Expected size 1, got %d", q.Size())
	}

	for i := 2; i <= 30; i++ {
		err := q.Push(strconv.Itoa(i))
		if err != nil {
			t.Errorf("Expected no error on push, got %v", err)
		}
	}
	err = q.Push("overflow")
	if err == nil {
		t.Error("Expected overflow error, got nil")
	}
}

func TestPop(t *testing.T) {
	start := time.Now()
	defer func() {
		duration := time.Since(start)
		t.Logf("TestPop execution time: %v seconds", duration.Seconds())
	}()

	q := NewDefaultQueue()
	q.Push("1")
	q.Push("2")

	val, err := q.Pop()
	if err != nil {
		t.Errorf("Expected no error, got %v", err)
	}
	if val != "1" {
		t.Errorf("Expected '1', got %s", val)
	}
	if q.Size() != 1 {
		t.Errorf("Expected size 1 after pop, got %d", q.Size())
	}

	val, err = q.Pop()
	if err != nil {
		t.Errorf("Expected no error, got %v", err)
	}
	if val != "2" {
		t.Errorf("Expected '2', got %s", val)
	}
	if !q.IsEmpty() {
		t.Error("Expected queue to be empty")
	}

	_, err = q.Pop()
	if err == nil {
		t.Error("Expected error on popping from empty queue, got nil")
	}
}

func TestPeek(t *testing.T) {
	start := time.Now()
	defer func() {
		duration := time.Since(start)
		t.Logf("TestPeek execution time: %v seconds", duration.Seconds())
	}()

	q := NewDefaultQueue()
	_, err := q.Peek()
	if err == nil {
		t.Error("Expected error on peek from empty queue, got nil")
	}

	q.Push("1")
	val, err := q.Peek()
	if err != nil {
		t.Errorf("Expected no error, got %v", err)
	}
	if val != "1" {
		t.Errorf("Expected '1', got %s", val)
	}
}

func TestIsEmpty(t *testing.T) {
	start := time.Now()
	defer func() {
		duration := time.Since(start)
		t.Logf("TestIsEmpty execution time: %v seconds", duration.Seconds())
	}()

	q := NewDefaultQueue()
	if !q.IsEmpty() {
		t.Error("Expected queue to be empty")
	}
	q.Push("test")
	if q.IsEmpty() {
		t.Error("Expected queue not to be empty")
	}
}
