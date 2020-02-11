#pragma once
#include <vector>
#include <random>


class Scene {
public:
	Scene();
	~Scene();

	virtual void Render();
	virtual void Tick();
	virtual void FixedTick();
	virtual void Init();

	std::vector<class GameObject*>& GetEntityVect() { return m_EntityVect; };

private:

	//Render vectors
	std::vector<class UIObject*> m_BackgroundUI;
	std::vector<class GameObject*> m_EntityVect;
	std::vector<class UIObject*> m_ForegroundUI;

	class Tetronimo* m_ActivePiece = nullptr;
	class Tetronimo* m_HoldPiece = nullptr;

	std::vector<Tetronimo*> m_RandomBag;
	std::random_device m_RandomGenerator;

};

