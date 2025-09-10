#include "GameOver.h"

using namespace KamataEngine;

void GameOver::Initialize()
{
}

void GameOver::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE))
	{
		sceneNo = TITLE;
	}
}

void GameOver::Draw()
{
}

GameOver::~GameOver()
{
}
