#include "Player.h"

using namespace KamataEngine;

void Player::Initialize()
{
	playerPosition_ = { 65.0f,577.0f };
	PlayerVelocity = { 0.0f,0.0f };
	PlayerAccelarationn = { 0.0f,-0.8f };
}

void Player::Update()
{
	//プレイヤー・移動
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
