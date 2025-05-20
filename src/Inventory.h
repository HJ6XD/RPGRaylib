#pragma once
#include "LinkedList.h"
#include "Item.h"

class Inventory : public LinkedList<Item>
{
public:
	//constructor
	Inventory() : LinkedList<Item>() {};

	void AddItem(Item* item);

	void debugPrintContents();

	void NextItem();

	void LastItem();

	LLNode<Item>* currentItem;

	std::string GetCurrentItemName() {
		if (currentItem != nullptr) {
			std::string ret;
			if (currentItem->data != nullptr)
				ret = currentItem->data->name;
			else 
				return "error";
			
			return ret;
		}
		else
			return "no item";
	}
};

