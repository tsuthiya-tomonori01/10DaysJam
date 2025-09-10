#include "GameClear.h"

using namespace KamataEngine;

void GameClear::Initialize()
{
}

void GameClear::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE))
	{
		sceneNo = TITLE;
	}
}

void GameClear::Draw()
{

	Novice::DrawSprite(0, 0, GCbg, 1.0,1.0, 0.0f, WHITE);
}

GameClear::~GameClear()
{
}
