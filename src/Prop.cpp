#include "Prop.h"

void Prop::Draw()
{
	DrawRectangle(position.x - player->cameraOffset.x, position.y - player->cameraOffset.y, size, size, BROWN);
	DrawText(name.c_str(), position.x - player->cameraOffset.x, position.y - player->cameraOffset.y - 40, 16, DARKPURPLE);
	DrawText(getUID().c_str(), position.x - player->cameraOffset.x, position.y - player->cameraOffset.y + 40, 16, DARKPURPLE);
}
