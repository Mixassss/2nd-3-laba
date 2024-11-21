package hash

import (
	"testing"
)

func TestHashTable(t *testing.T) {
	ht := NewHashTable()

	// Test insertion
	ht.Insert("key1", "value1")
	if size := ht.Size(); size != 1 {
		t.Errorf("Expected size 1, got %d", size)
	}

	// Test getting value
	if value, found := ht.Get("key1"); !found || value != "value1" {
		t.Errorf("Expected value1, got %s (found: %v)", value, found)
	}

	// Test updating value
	ht.Insert("key1", "newValue1")
	if value, found := ht.Get("key1"); !found || value != "newValue1" {
		t.Errorf("Expected newValue1, got %s (found: %v)", value, found)
	}

	// Test inserting another key
	ht.Insert("key2", "value2")
	if size := ht.Size(); size != 2 {
		t.Errorf("Expected size 2, got %d", size)
	}

	// Test removal
	if removed := ht.Remove("key1"); !removed {
		t.Error("Expected key1 to be removed")
	}

	if size := ht.Size(); size != 1 {
		t.Errorf("Expected size 1 after removing key1, got %d", size)
	}

	// Test getting removed key
	if _, found := ht.Get("key1"); found {
		t.Error("Expected key1 to be not found after removal")
	}

	// Test getting existing key
	if value, found := ht.Get("key2"); !found || value != "value2" {
		t.Errorf("Expected value2, got %s (found: %v)", value, found)
	}
}
