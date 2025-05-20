#include "Prop.h"

void Prop::Draw()
{
	DrawRectangle(position.x - player->cameraOffset.x, position.y - player->cameraOffset.y, size, size, BROWN);
}
