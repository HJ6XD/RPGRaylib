#include "Inventory.h"
#include <iostream>

void Inventory::AddItem(Item* _item)
{
	currentItem = AddNode(_item);
	_item->SetInventory(this);
}

void Inventory::debugPrintContents()
{
	LLNode<Item>* iter = head;
	std::cout << "Items en inventario: " << std::endl;
	while (iter != nullptr) {
		std::cout << "\t" << iter->data->name << std::endl;
		iter = iter->next;
	}
}

void Inventory::NextItem()
{
	if (currentItem == nullptr) {
		currentItem = head;
		return;
	}

	if (currentItem->next != nullptr) {
		currentItem = currentItem->next;
	}

	else {
		currentItem = head;
	}
}

void Inventory::LastItem()
{
	if (currentItem == nullptr) {
		currentItem = head;
		return;
	}
	if (currentItem->last != nullptr) {
		currentItem = currentItem->last;
	}
	else {
		currentItem = head;
	}
}
