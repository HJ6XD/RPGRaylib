#pragma once
#include <string>

class Inventory;

class Item
{
private:
	Inventory* inventory;
	
public:
	std::string name;
	int id;

	Item(std::string _name, int _id) : name(_name), id(_id) {}

	void SetInventory(Inventory* _inventory) {
		inventory = _inventory;
	}
	void Consume();
};

