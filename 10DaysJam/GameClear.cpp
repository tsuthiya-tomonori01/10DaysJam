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
}

GameClear::~GameClear()
{
}
