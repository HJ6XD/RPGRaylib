#pragma once
template <class T>
class LLNode
{
public:
	//referencia al siguiente nodo
	LLNode<T > *next;

	//referencia al nodo anterior
	LLNode<T > *last;

	//dato contenido
	T* data;

	//constructor polymorfo
	LLNode(T* _data) : data(_data), next(nullptr), last(nullptr) {}
	LLNode(T* d, LLNode* nxt, LLNode* lst): data(d), next(nxt), last(lst) {}
	LLNode(T* d, LLNode* lst): data(d), next(nullptr), last(lst) {}
};

