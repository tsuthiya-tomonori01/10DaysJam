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
	int playerHigh = 64;
	int playerwide = 64;

	float PlayerRadius = 32;

	//プレイヤー生存フラグ
	bool PlayerAlive_ = false;

	//プレイヤー・移動速度
	int PlayerSpeed_ = 5;

	//プレイヤー・HP
	int PlayerHP_ = 3;

	KamataEngine::Vector2 PlayerVelocity;
	KamataEngine::Vector2 PlayerAccelarationn;

	//スクロール	
	KamataEngine::Vector2 scroll = { 0,0 };

	//プレイヤー・ジャンプ/フラグ
	bool OnGround_ = true;

	//プレイヤー・画像
	uint32_t PlayerTexture_ = 0u;
};

