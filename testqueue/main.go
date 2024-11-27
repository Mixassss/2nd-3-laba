package main

import (
	"fmt"
	"log"
	"queue/queue"
)

func main() {
	// Создаем очередь и добавляем элементы
	que := queue.NewDefaultQueue()
	que.Push("1")
	que.Push("2")
	que.Push("3")

	// Сериализация в текстовом формате
	textFilename := "queue.txt"
	if err := que.SerializeQueueText(textFilename); err != nil {
		log.Fatalf("Ошибка сериализации в текстовом формате: %v", err)
	}
	fmt.Println("Очередь успешно сериализована в текстовом формате")

	// Десериализация из текстового формата
	deserializedTextQueue, err := queue.DeserializeQueueText(textFilename)
	if err != nil {
		log.Fatalf("Ошибка десериализации из текстового формата: %v", err)
	}
	fmt.Println("Очередь успешно десериализована из текстового формата:")
	for deserializedTextQueue.Size() > 0 { // Проверяем, есть ли элементы для вывода
		fmt.Println(deserializedTextQueue.Pop())
	}

	// Сериализация в бинарном формате
	binaryFilename := "queue.bin"
	if err := que.SerializeQueueBinary(binaryFilename); err != nil {
		log.Fatalf("Ошибка сериализации в бинарном формате: %v", err)
	}
	fmt.Println("Очередь успешно сериализована в бинарном формате")

	// Десериализация из бинарного формата
	deserializedBinaryQueue, err := queue.DeserializeQueueBinary(binaryFilename)
	if err != nil {
		log.Fatalf("Ошибка десериализации из бинарного формата: %v", err)
	}
	fmt.Println("Очередь успешно десериализована из бинарного формата:")
	for deserializedBinaryQueue.Size() > 0 { // Проверяем, есть ли элементы для вывода
		fmt.Println(deserializedBinaryQueue.Pop())
	}
}
