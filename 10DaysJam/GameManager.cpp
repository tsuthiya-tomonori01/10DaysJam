#include "GameManager.h"
#include "Novice.h"

GameManager::GameManager()
{
	sceneArr_[TITLE] = std::make_unique<TitleScene>();
	sceneArr_[STAGE] = std::make_unique<Stage>();
	sceneArr_[CLEAR] = std::make_unique<GameClear>();

	currentSceneNo_ = iScene->GetSceneNo();

	sceneArr_[TITLE]->Initialize();
}

GameManager::~GameManager()
{
}

int GameManager::Run()
{
	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();

		memcpy(prekeys_, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		preSceneno_ = currentSceneNo_;
		currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();

		if (preSceneno_ != currentSceneNo_) {
			sceneArr_[currentSceneNo_]->Initialize();
		}

		sceneArr_[currentSceneNo_]->Update();

		sceneArr_[currentSceneNo_]->Draw();

		Novice::EndFrame();

		if (keys[DIK_ESCAPE] == 0 && prekeys_[DIK_ESCAPE] != 0)
		{
			break;
		}
	}
	return 0;
}
