#pragma once
#include "KamataEngine.h"
#include "Novice.h"

#include "Player.h"

class GameScene
{
public:

	GameScene();

	~GameScene();

	void Initialize();

	void Update();

	void Draw();

private:

	Player* player_ = nullptr;
};

