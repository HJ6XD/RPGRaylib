#pragma once
#include "GameObject.h"
#include "PlayerCharacter.h"
class EnemyCharacter :
    public GameObject
{
public:

    float enemySpeed = 100.f;
    Vector2 direction = { 0,0 };
    PlayerCharacter* player;

    EnemyCharacter(char* _name, PlayerCharacter* _player, float _x, float _y) : GameObject(_name){
        position = { _x,_y };
        player = _player;
    }

    void Start() override;
    void Update() override;
    void Draw() override;
    Vector2 SetDirection(Vector2 _target);
};

