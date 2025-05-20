#pragma once
#include "Inventory.h"
#include "raylib.h"
#include "GameObject.h"
class PlayerCharacter : public GameObject
{
public:

	PlayerCharacter(char* _name) : GameObject(_name) {

	}

	float speedPlayer = 100;
	float scrollBorder = 100;
	Vector2 cameraOffset = { 0,0 };
	Inventory* inventory;

	void Start() override;
	void Update() override;
	void Draw() override;

private:

};

