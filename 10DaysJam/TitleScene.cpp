#include "TitleScene.h"

using namespace KamataEngine;

void TitleScene::Initialize() {

	
}

void TitleScene::Update() {

	if (Input::GetInstance()->TriggerKey(DIK_SPACE))
	{
		sceneNo = STAGE;
	}
}

void TitleScene::Draw() {

	
}

TitleScene::~TitleScene()
{
}
