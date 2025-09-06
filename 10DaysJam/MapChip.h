#pragma once
#include "KamataEngine.h"
#include "Novice.h"

class MapChip
{
public:
	void Initialize();

	void Update();

	void Draw();

	void CreateMap();

private:

	int map[100][100]{};

	int gh1 = Novice::LoadTexture("block.png");

	int gh2 = Novice::LoadTexture("sample.png");

	float mapCountX = 0.0f;
	float mapCountY = 0.0f;

	const int kBlockSize = 64;

	enum MapInfo {
		NONE,
		BLOCK,
		ENEMY,
	};

	struct Block {
		MapInfo state; //ブロックの状態
		KamataEngine::Vector2 pos; //座標
		KamataEngine::Vector2 size; //画像の大きさ
		KamataEngine::Vector2 imagePos; //読み込む画像の座標
		int color;//色
	};

	Block block[100][100]{};
	int blockSize = 128;
	int blockColor = 0xFFFFFFFF;

};

