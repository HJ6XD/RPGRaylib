#pragma once
#include "GameObject.h"
#include "PlayerCharacter.h"
class Prop :
    public GameObject
{
public:
    int size;
    PlayerCharacter* player;

    Prop(char* _name, float _x, float _y, int _size, PlayerCharacter* _player) : GameObject(_name) {
        position = { _x,_y };
        size = _size;
        player = _player;
    }

    void Start() override {}
    void Update() override {}
    void Draw() override;
};

