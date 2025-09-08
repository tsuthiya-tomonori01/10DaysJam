#pragma once
#include <memory>
#include "Iscene.h"

#include "TitleScene.h"
#include "Stage.h"
#include "GameClear.h"

class GameManager
{
private:

	std::unique_ptr<Iscene> sceneArr_[3];

	int currentSceneNo_;
	int preSceneno_;

	char keys[256] = { 0 };
	char prekeys_[256] = { 0 };

public:
	GameManager();
	~GameManager();

	int Run();

private:
	Iscene* iScene;
};

