#pragma once
#include <string>
#include "raylib.h"

extern "C" {
	#include "md5.h"
}

class GameObject
{
public:
	GameObject(char* _name) {
		name = _name;
		md5String(_name, uid);
		position = { 0,0 };
		texture = { 0 };
		enable = true;
	}

	Vector2 position;
	Texture2D texture;

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void printUID();

	std::string getUID() {
		std::string uidString;
		for (int i = 0; i < 16; i++) {
			char buffer[3];
			sprintf(buffer, "%02X", uid[i]);
			uidString += buffer;
		}
		return uidString;
	}

	void setEnable(bool _enable);

	bool getEnable();

protected:
	std::string name;		
	//unique id en MD5
	uint8_t uid[16];
	bool enable;
};

