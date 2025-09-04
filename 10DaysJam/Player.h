#pragma once
#include "KamataEngine.h"
#include "Novice.h"

#include <cassert>

class Player
{
public:
   
	void Initialize();

	void Update();

	void Draw();

private:

	//プレイヤー・座標
	KamataEngine::Vector2 playerPosition_ = {};
	int playerHigh = 50;
	int playerwide = 50;

	//プレイヤー生存フラグ
	bool PlayerAlive_ = false;

	//プレイヤー・移動速度
	int PlayerSpeed_ = 5;

	//プレイヤー・ジャンプ/フラグ
	bool OnGround_ = true;

	//プレイヤー・画像
	uint32_t PlayerTexture_ = 0u;
};

