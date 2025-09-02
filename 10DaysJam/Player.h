#pragma once
#include "KamataEngine.h"

class Player
{
public:
   
	void Start();

	void Update();

	void Draw();

private:

	//プレイヤー生存フラグ
	bool PlayerAlive_ = false;

	//WORLDTRANSFORM
	KamataEngine::WorldTransform worldTransform_;

	//プレイヤー・ジャンプ・変数


	//プレイヤー・画像
	uint32_t PlayerTexture_ = 0u;
};

