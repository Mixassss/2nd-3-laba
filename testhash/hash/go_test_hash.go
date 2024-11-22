package hash

import (
	"fmt"
	"testing"
)

func TestHashTable(t *testing.T) {
	ht := NewHashTable()

	// Тест: Вставка элемента
	ht.Insert("key1", "value1")
	if size := ht.Size(); size != 1 {
		t.Errorf("Expected size 1, got %d", size)
	}

	// Тест: Получение значения
	if value, found := ht.Get("key1"); !found || value != "value1" {
		t.Errorf("Expected value1, got %s (found: %v)", value, found)
	}

	// Тест: Обновление значения
	ht.Insert("key1", "newValue1")
	if value, found := ht.Get("key1"); !found || value != "newValue1" {
		t.Errorf("Expected newValue1, got %s (found: %v)", value, found)
	}

	// Тест: Вставка другого ключа
	ht.Insert("key2", "value2")
	if size := ht.Size(); size != 2 {
		t.Errorf("Expected size 2, got %d", size)
	}

	// Тест: Удаление ключа
	if removed := ht.Remove("key1"); !removed {
		t.Error("Expected key1 to be removed")
	}

	if size := ht.Size(); size != 1 {
		t.Errorf("Expected size 1 after removing key1, got %d", size)
	}

	// Тест: Получение удаленного ключа
	if _, found := ht.Get("key1"); found {
		t.Error("Expected key1 to be not found after removal")
	}

	// Тест: Получение существующего ключа
	if value, found := ht.Get("key2"); !found || value != "value2" {
		t.Errorf("Expected value2, got %s (found: %v)", value, found)
	}

	// Тест: Удаление несуществующего ключа
	if removed := ht.Remove("key3"); removed {
		t.Error("Expected key3 to be not removed")
	}

	// Тест: Вставка дубликатов
	ht.Insert("key2", "newValue2")
	if value, found := ht.Get("key2"); !found || value != "newValue2" {
		t.Errorf("Expected newValue2, got %s (found: %v)", value, found)
	}

	// Тест: Проверка на пустую хеш-таблицу
	ht.Remove("key2") // Удалим ключ перед завершением
	if size := ht.Size(); size != 0 {
		t.Errorf("Expected size 0 after removing key2, got %d", size)
	}
}

func BenchmarkHashTable(b *testing.B) {
	ht := NewHashTable()
	for i := 0; i < b.N; i++ {
		ht.Insert(fmt.Sprintf("key%d", i), fmt.Sprintf("value%d", i))
	}
}
