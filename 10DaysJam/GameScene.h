#pragma once
#include "KamataEngine.h"
#include "Novice.h"

#include "Player.h"
#include "MapChip.h"

class GameScene
{
public:

	GameScene();

	~GameScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; }

private:

	bool finished_ = false;

	Player* player_ = nullptr;
	MapChip* mapChip_ = nullptr;
};

