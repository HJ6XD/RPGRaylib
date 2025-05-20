#include "GameObject.h"

void GameObject::printUID()
{
	printf("%s : ", name.c_str() );
	for (int i = 0; i < 16; i++) {
		printf("%02X", uid[i]);
	}
	printf("\n");
}

void GameObject::setEnable(bool _enable)
{
	enable = _enable;
}

bool GameObject::getEnable()
{
	return enable;
}
