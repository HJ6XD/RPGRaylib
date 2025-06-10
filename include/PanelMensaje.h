#pragma once
#include "raylib.h"
#include <string>
#include <iostream>
#include "Stack.h"

enum PanelState
{
	hidden,
	moveing, 
	showing
};
class PanelMensaje
{
private:
	float timer;
	PanelState state = hidden;
	Stack<std::string> msgStack = Stack<std::string>(10);

public: 
	PanelMensaje(float posx, float width, float height, int _timeOnScreen) {
		position = { posx, -height };
		size = { width, height };
		timeOnScreen = _timeOnScreen;
		timer = 0;
		dessiredPositionY = height;
		state = hidden;
	}
	float dessiredPositionY;

	Vector2 position;
	Vector2 size;

	float timeOnScreen;

	std::string message;

	void update() {
		if (state == hidden) {
			if (!msgStack.isEmpty()) {
				message = msgStack.pop();
				state = moveing;
				timer = 0;
				dessiredPositionY = size.y;
				position.y -= size.y;
			}
			else
				return;
		}

		else if (state == moveing) 
		{
			if (position.y != dessiredPositionY) {
				//lerp position
				position.y += (dessiredPositionY - position.y) * 5.f * GetFrameTime();
			}
			if (dessiredPositionY - position.y < 0.1f && dessiredPositionY - position.y > -0.1f) {
				position.y = dessiredPositionY;
				state = showing;
				timer = 0;
				if (dessiredPositionY < 0)
					state = hidden;
			}
		}
		else if (state == showing) {
			timer += GetFrameTime();
			if (timer > timeOnScreen) {
				//Start moving up
				dessiredPositionY = -size.y ;
				state = moveing;
			}
		}
	}

	void draw() {
		DrawRectangle(position.x, position.y, size.x, size.y, DARKGRAY);
		DrawRectangleLines(position.x, position.y, size.x, size.y, DARKPURPLE);
		DrawText(message.c_str(), position.x + 10, position.y + 10, 20, PURPLE);
	}
	void show(std::string _msg) {


		msgStack.push(_msg);
	}
};

