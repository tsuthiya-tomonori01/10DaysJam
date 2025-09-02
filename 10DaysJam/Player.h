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

	uint32_t PlayerTexture_ = 0u;
};

