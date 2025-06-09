#include "EnemyCharacter.h"
#include <cmath>

void EnemyCharacter::Start()
{
	texture = LoadTexture("Enemigo.png");
}

void EnemyCharacter::Update()
{
	direction = SetDirection(player->position);
	position = { position.x + (direction.x * enemySpeed * GetFrameTime()),
				 position.y + (direction.y * enemySpeed * GetFrameTime())};
}

void EnemyCharacter::Draw()
{
	DrawTexture(texture, position.x , position.y,  WHITE);
	DrawText(name.c_str(), position.x, position.y - 20, 16, RED);
}

Vector2 EnemyCharacter::SetDirection(Vector2 _target)
{
	Vector2 dir = { _target.x - position.x + player->cameraOffset.x , _target.y - position.y + player->cameraOffset.y };
	float _dx = pow(dir.x, 2);
	float _dy = pow(dir.y, 2);
	float _dmag = sqrt(_dx + _dy);
	Vector2 _dnormal = { dir.x / _dmag, dir.y / _dmag };
	return _dnormal;
}
