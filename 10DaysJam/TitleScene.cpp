#include "TitleScene.h"

using namespace KamataEngine;

void TitleScene::Initialize() {

	soundDataHandle_ = Audio::GetInstance()->LoadWave("titleBGM.wav");

	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);
}

void TitleScene::Update() {

	if (Input::GetInstance()->TriggerKey(DIK_SPACE))
	{
		sceneNo = STAGE;

		Audio::GetInstance()->StopWave(voiceHandle_);
	}
}

void TitleScene::Draw() {

	
}

TitleScene::~TitleScene()
{

	
}
