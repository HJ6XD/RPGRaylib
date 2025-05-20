#include "PlayerCharacter.h"

void PlayerCharacter::Start() 
{
	texture = LoadTexture("wabbit_alpha.png");

	inventory = new Inventory();

	//posicion inicial
	position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	speedPlayer = 100;

	scrollBorder = GetScreenHeight() * 0.3f;
}

void PlayerCharacter::Update()
{
	if (IsKeyDown(KeyboardKey::KEY_W)) {
		speedPlayer = -300;
		position.y += speedPlayer * GetFrameTime();
		if (position.y < scrollBorder) {
			position.y = scrollBorder;
			cameraOffset.y += speedPlayer * GetFrameTime();
		}
	}

	if (IsKeyDown(KeyboardKey::KEY_S)) {
		speedPlayer = 300;
		position.y += speedPlayer * GetFrameTime();
		if (position.y > GetScreenHeight() - scrollBorder) {
			position.y = GetScreenHeight() - scrollBorder;
			cameraOffset.y += speedPlayer * GetFrameTime();
		}
	}

	if (IsKeyDown(KeyboardKey::KEY_A)) {
		speedPlayer = -300;
		position.x += speedPlayer * GetFrameTime();
		if (position.x < scrollBorder) {
			position.x = scrollBorder;
			cameraOffset.x += speedPlayer * GetFrameTime();
		}
	}

	if (IsKeyDown(KeyboardKey::KEY_D)) {
		speedPlayer= 300;
		position.x += speedPlayer * GetFrameTime();
		if (position.x > GetScreenWidth() - scrollBorder) {
			position.x = GetScreenWidth() - scrollBorder;
			cameraOffset.x += speedPlayer * GetFrameTime();
		}
	}

	if(IsKeyPressed(KeyboardKey::KEY_E)) {
		//asume que siempre tiene inventory
		inventory->NextItem();
	}
	
	if(IsKeyPressed(KeyboardKey::KEY_Q)) {
		//asume que siempre tiene inventory
		inventory->LastItem();
	}
}

void PlayerCharacter::Draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
	DrawText(name.c_str(), position.x, position.y - 40, 16, WHITE);
	DrawText(getUID().c_str(), position.x, position.y + 40, 16, WHITE);

	//Hud

	DrawRectangle(10, 10, 100, 50, BLACK);

	if (inventory != nullptr && inventory->currentItem != nullptr)
		DrawText(inventory->GetCurrentItemName().c_str(), 20, 20, 16, YELLOW);

	else
		DrawText("EMPTY", 20, 20, 10, YELLOW);
	
}