#pragma once
#include "KamataEngine.h"
#include "Novice.h"

class Stage
{
public:

	void Initialize();

	void Update();

	void Draw();

private:

	//関数
	void CreateMap();

	void PlayerInitialize();

	void PlayerUpdate();

	void PlayerMove();

	void PlayerJumpInitialize();

	void PlayerJumpUpdate();

	void Reset();

	//関数・当たり判定
	void GetAllCollision();
	void Player2MapCollision();
	void Player2EnemyCollision();

	//変数・その他

	//マップチップ
	int map[100][100]{};
	KamataEngine::Vector2 mapEndPos = {};

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
	int blockSize = 64;
	int blockColor = 0xFFFFFFFF;

	//プレイヤー
	KamataEngine::Vector2 playerPos = {};//実ポジション
	
	KamataEngine::Vector2 playerLeftTop = {};//左上のXY座標
	KamataEngine::Vector2 playerRightTop = {};//右上のXY座標
	KamataEngine::Vector2 playerLeftBottom = {};//左下のXY座標
	KamataEngine::Vector2 playerRightBottom = {};//右下のXY座標

	bool isLeft = false;
	bool isRight = true;
	
	float kRectCenterX = 400;
	float kRectCenterY = 100;
	
	float playerRad;
	float speed;
	float speed1;
	float playerAcceleration = 0.8f;

	//その他・変数
	float scrollStartX = 640;
	int scrollX = 0;

	//画像・読み込み

};

