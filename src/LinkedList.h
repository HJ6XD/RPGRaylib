#pragma once
#include "LLNode.h"
template<class T>
class LinkedList
{
protected:
	LLNode<T>* head;

public:
	//Lista vacia
	LinkedList() : head(nullptr) {}
	LinkedList(LLNode<T>* _hd) : head(_hd) {};

	LLNode<T>* AddNode(T* _data) {
		if (head == nullptr) {
			head = new LLNode<T>(_data);
			return head;
		}

		LLNode<T>* iter = head;
		while (iter->next != nullptr)
			iter = iter->next;
		iter->next = new LLNode<T>(_data, iter);

		head->last = iter->next;

		return iter->next;
	}

	void RemoveLastNode() {
		if (head == nullptr)
			return;

		if (head->next == nullptr) {
			delete head;
			head = nullptr;
			return;
		}

		LLNode<T>* iter = head;
		while (iter->next->next != nullptr)
			iter = iter->next;

		delete iter->next;
		iter->next = nullptr;
	}
};