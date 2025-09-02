#include "Player.h"

using namespace KamataEngine;

void Player::Start()
{
	worldTransform_.Initialize();

	PlayerAlive_ = false;
}

void Player::Update()
{
	if (PlayerAlive_ == true)
	{
		//プレイヤー・移動
		if (Input::GetInstance()->PushKey(DIK_D))
		{
			worldTransform_.translation_.x += 10;
		}
		else if (Input::GetInstance()->PushKey(DIK_A))
		{
			worldTransform_.translation_.x -= 10;
		}

		//プレイヤー・ジャンプ
	}
}

void Player::Draw()
{
	
}
