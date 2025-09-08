#include "GameClear.h"

using namespace KamataEngine;

void GameClear::Initialize()
{
}

void GameClear::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE))
	{
		sceneNo = CLEAR;
	}
}

void GameClear::Draw()
{
}

GameClear::~GameClear()
{
}
