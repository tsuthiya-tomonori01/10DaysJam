#include "Player.h"

using namespace KamataEngine;

void Player::Initialize()
{
	playerPosition_ = { 100.0f,550.0f };
}

void Player::Update()
{
	if (Input::GetInstance()->PushKey(DIK_D))
	{
		playerPosition_.x += PlayerSpeed_;
	}
	else if (Input::GetInstance()->PushKey(DIK_A))
	{
		playerPosition_.x -= PlayerSpeed_;
	}
}

void Player::Draw()
{
	Novice::DrawBox(int(playerPosition_.x), int(playerPosition_.y), playerwide, playerHigh, 0.0f, WHITE, kFillModeSolid);
}
