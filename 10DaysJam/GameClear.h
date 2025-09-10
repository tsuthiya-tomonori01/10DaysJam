#pragma once
#include "KamataEngine.h"
#include "Novice.h"

#include "Iscene.h"

#include "audio/Audio.h"

class GameClear : public Iscene
{
public:

	void Initialize() override;

	void Update() override;

	void Draw() override;

	~GameClear();

private:

	//ゲームクリア
	int GCbg = Novice::LoadTexture("gameclear.png");
};

