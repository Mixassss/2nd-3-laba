package hash

import (
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

	// Тест: Вставка дубликатов
	ht.Insert("key2", "newValue2")
	if value, found := ht.Get("key2"); !found || value != "newValue2" {
		t.Errorf("Expected newValue2, got %s (found: %v)", value, found)
	}

	// Тест: Вставка коллизий
	ht.Insert("key3", "value3")
	ht.Insert("key13", "value3") // Столкновение предполагаемое (зависит от хеш-функции)
	if value, found := ht.Get("key3"); !found || value != "value3" {
		t.Errorf("Expected value3 for key3, got %s (found: %v)", value, found)
	}
	if value, found := ht.Get("key13"); !found || value != "value3" {
		t.Errorf("Expected value3 for key13, got %s (found: %v)", value, found)
	}

	// Тест: Получение значения для несуществующего ключа
	if value, found := ht.Get("nonExistent"); found || value != "" {
		t.Error("Expected nonExistent to be not found")
	}

	// Тест: Удаление несуществующего ключа
	if removed := ht.Remove("key3"); !removed {
		t.Error("Expected key3 to be removed")
	}

	// Тест: Проверка на вставку значений в пустой хэш-таблицу
	ht = NewHashTable()
	ht.Insert("key1", "value1")
	if value, found := ht.Get("key1"); !found || value != "value1" {
		t.Errorf("Expected value1 after inserting into an empty hashtable, got %s", value)
	}

	// Тест: Пустая хэш-таблица
	ht.Remove("key2") // Убираем ключ перед завершением
	if size := ht.Size(); size != 1 {
		t.Errorf("Expected size 1 after removing key2, got %d", size)
	}
}
