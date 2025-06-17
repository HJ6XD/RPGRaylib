#pragma once
template <class T>
class HeapNode
{
private:
	int value;
	T data;
public:
	HeapNode(T _data, int val) : data(_data), value(val) {}

	const T* GetData() const { return &data; }
	int GetValue() const { return value; }
};

