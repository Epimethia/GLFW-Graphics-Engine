#pragma once
#include <vector>
#include <random>

enum class ERotationDirection {
	CLOCKWISE,
	ANTI_CLOCKWISE
};

enum class ETranslationDirection {
	LEFT,
	RIGHT,
	DOWN,
	HARD_DROP
};

class GameManager {
public:

	void FixedTick();
	void Tick();

	void RotateActiveTet(ERotationDirection _Direction);
	void TranslateActiveTet(int _X, int _Y);
	void HardDropTet();
	void ProcessInput(int _Key, int _Action, int _Mods);

	void SetActiveScene(class Scene* _Scene) { m_ActiveScene = _Scene; };

private:

	class Scene* m_ActiveScene = nullptr;

	class Tetronimo* m_ActivePiece = nullptr;
	class Tetronimo* m_HoldPiece = nullptr;
	std::vector<class Base_Block*> PlayGrid;
	std::vector<class GameObject*> m_EntityVect;

	class Tetronimo* GenerateTetronimo();

	std::vector<Tetronimo*> m_RandomBag;
	std::random_device m_RandomGenerator;

	bool CheckColliding(int _X, int _Y);
	bool CheckColliding(int _X, int _Y, std::vector<Base_Block*> _BlockVect);
	bool CheckRotation(ERotationDirection _Direction);
};

