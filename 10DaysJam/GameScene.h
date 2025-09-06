#pragma once
#include "KamataEngine.h"
#include "Novice.h"

#include "Stage.h"

class GameScene
{
public:

	GameScene();

	~GameScene();

	void Initialize();

	void Update();

	void Draw();

private:

	bool finished_ = false;

	Stage* stage_ = nullptr;
};

