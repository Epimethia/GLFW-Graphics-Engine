#pragma once
class GameObject {
public:
	virtual void Init();
	virtual void Render();
};

class UIObject : public GameObject {

};