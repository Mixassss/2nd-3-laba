package queue

import (
	"encoding/binary"
	"errors"
	"io"
	"os"
	"strings"
)

// SerializeQueueText сохраняет очередь в текстовом формате.
func (q *Queue) SerializeQueueText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return errors.New("не удалось открыть файл для записи")
	}
	defer file.Close()

	for i := 0; i < q.size; i++ {
		index := (q.front + i) % q.capacity
		if _, err := file.WriteString(q.data[index] + "\n"); err != nil {
			return err
		}
	}
	return nil
}

// DeserializeQueueText восстанавливает очередь из текстового файла.
func DeserializeQueueText(filename string) (*Queue, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, errors.New("не удалось открыть файл для чтения")
	}
	defer file.Close()

	data, err := io.ReadAll(file) // Обновленная строка
	if err != nil {
		return nil, err
	}

	que := NewDefaultQueue()
	lines := strings.Split(string(data), "\n")
	for _, line := range lines {
		if line != "" {
			if err := que.Push(line); err != nil {
				return nil, err
			}
		}
	}
	return que, nil
}

// SerializeQueueBinary сохраняет очередь в бинарном формате.
func (q *Queue) SerializeQueueBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return errors.New("не удалось открыть файл для записи")
	}
	defer file.Close()

	for i := 0; i < q.size; i++ {
		index := (q.front + i) % q.capacity
		value := q.data[index]
		length := int32(len(value))
		if err := binary.Write(file, binary.LittleEndian, length); err != nil {
			return err
		}
		if _, err := file.WriteString(value); err != nil {
			return err
		}
	}
	return nil
}

// DeserializeQueueBinary восстанавливает очередь из бинарного файла.
func DeserializeQueueBinary(filename string) (*Queue, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, errors.New("не удалось открыть файл для чтения")
	}
	defer file.Close()

	que := NewDefaultQueue()

	for {
		var length int32
		if err := binary.Read(file, binary.LittleEndian, &length); err != nil {
			break // Достигнут конец файла
		}
		value := make([]byte, length)
		if _, err := file.Read(value); err != nil {
			return nil, err
		}
		if err := que.Push(string(value)); err != nil {
			return nil, err
		}
	}
	return que, nil
}
