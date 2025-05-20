#pragma once
template <typename T>
class Queue
{
private:
	T* data;
	size_t front;
	size_t rear;
	size_t maxsize;

public:
	Queue(size_t _maxsize) {
		rear = 0;
		front = 0;
		maxsize = _maxsize;
	}
	~Queue() {
		delete[] data;
	}
	bool isEmpty() {
		return front == rear;
	}
	size_t size() {
		return rear - front;
	}
	void enqueue(T item) {
		if (size() == maxsize) {
			std::cout << "la cola esta llena, queue overflow!" << std::endl;
			return;
		}
		data[rear++] = item;
	}
	T dequeue() {
		if (isEmpty()) {
			std::cout << "la cola esta vacia" << std::endl;
			return T();
		}

		T temp = data[front];
		for (int i = 0; i < rear; i++) {
			data[i] = data[i + 1];
		}
		rear--;
		return temp;
	}

	T* peek() {
		if (isEmpty()) {
			std::cout << "la cola esta vacia" << std::endl;
			return nullptr;
		}
		return &data[front];
	}

	void DebugPrintContents() {
		std::cout << "Cola: [";
		for (size_t i = 0; i <= maxsize; i++) {
			std::cout << data[i] << " ";
		}
		std::cout << "] Rear: " << rear << " Front: " << front << std::endl;
	}
};

