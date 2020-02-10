#pragma once
#include <vector>
class Scene {
public:
	Scene();
	~Scene();

private:

	void Tick();
	void FixedTick();
	void Render();
	void ProcessInput();

	//Block grid
	std::vector<class Base_Block*> PlayGrid;

	//Render vectors
	std::vector<class UIObject*> BackgroundUI;
	std::vector<class GameObject> EntityVect;
	std::vector<class UIObject*> ForegroundUI;

	class Tetronimo* m_ActivePiece = nullptr;
	class Tetronimo* m_HoldPiece = nullptr;

	class Tetronimo* GenerateTetronimo();
};

