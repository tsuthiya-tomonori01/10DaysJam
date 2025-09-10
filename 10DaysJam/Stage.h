#pragma once
#include "KamataEngine.h"
#include "Novice.h"

#include "Iscene.h"
#include "Enemy.h"

#include "audio/Audio.h"

class Stage : public Iscene
{
public:

	void Initialize() override;

	void Update() override;

	void Draw() override;

private:

	//関数
	void CreateMap();

	void PlayerInitialize();

	void PlayerUpdate();

	void PlayerMove();

	void PlayerJumppInitialize();

	void PlayerJumpUpdate();

	//弾
	void BulletInitialize();

	void BulletUpdate();

	void Reset();

	//関数・当たり判定
	void GetAllCollision();
	void PlayerEnemyCollision();
	void BulletEnemyCollision();

	//トラップ
	void CheckTrapCollision();

	void OnPlayerDamege();

	//重力
	void PlayerGravity();

	//境界線
	void CheckBoundary1();

	void CheckBoundary2();

	//終了判定
	void StageFinish();

	void CreateGoal();

	//変数・その他

	//マップチップ
	int map[100][100]{};
	KamataEngine::Vector2 mapEndPos = {};

	float mapCountX = 0.0f;
	float mapCountY = 0.0f;

	const int kBlockSize = 64;

	enum MapInfo {
		NONE,
		BLOCK,
		TRAP,
		FALL,
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
	
	int PlayerHP;

	float playerRad;
	float speed;
	float playerAcceleration = 0.8f;

	bool isJump = false;
	float jumpSpeed = 0.0f;

	bool isGravity = false;

	//敵の生成
	std::list<std::unique_ptr<Enemy>> enemies_;

	int enemyMax = 0;

	int enemyKillCount = 0;

	//弾
	KamataEngine::Vector2 BulletPos = {};
	 
	bool isBullet = false;

	float BulletSpeed;
	float BulletRadius;

	//その他・変数
	float scrollStartX = 640;
	int scrollX = 0;

	static int IsTriggerMouse(int buttonNumber);

	//境界線
	bool Boundary1 = false;
	bool Boundary2 = false;

	//ゴール
	KamataEngine::Vector2 GoalPos = {};
	bool GolaActive = false;

	//画像・読み込み

	//マップチップ
	int gh1 = Novice::LoadTexture("block.png");
	int gh2 = Novice::LoadTexture("stoneedge.png");

	//背景
	int gh3 = Novice::LoadTexture("background.png");
	int gh4 = Novice::LoadTexture("background_2.png");
	int gh5 = Novice::LoadTexture("background_3.png");

	//説明
	int TuBg = Novice::LoadTexture("text.png");

	int GCbgS = Novice::LoadTexture("text2.png");
	int GcbgE = Novice::LoadTexture("text3.png");

	//音楽
	uint32_t soundDataHandle_ = 0;

	uint32_t voiceHandle_ = 0;

	//プレイヤー
	int PBg1 = Novice::LoadTexture("Player1.png");
	int PBg2 = Novice::LoadTexture("Player2.png");

	//境界線
	int Bog = Novice::LoadTexture("border.png");
};

