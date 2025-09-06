//#pragma once
//#include <Novice.h>
//#include "Vector2.h"
//
//#include "Enemy.h"
//
//#include "Taru.h"
//
//#include <memory>
//#include <list>
//
//#include <time.h>
//
//
////線分(0~1)
//struct Segment {
//	Vector2 origin;//始点
//	Vector2 diff;//終点への差分ベクトル
//};
//
//struct Plane {
//	Vector2 normal;//法線
//	float distance;//距離
//};
//
//class Stage1 : public Scene
//{
//public:
//
//	Stage1();
//	~Stage1();
//	void Initialize() override;
//	void Update() override;
//	void Draw() override;
//
//private:
//	void GetDevice();
//
//	void CreateMap();
//
//	void PlayerUpdate();
//	void PlayerMove();
//	void PlayerJumpInitialize();
//	void PlayerJumpUpdate();
//
//	void GravityInitialize();
//	void GravityUpdate();
//
//	void Reset();
//
//	void GetAllCollision();
//	//void Player2MapCollision();
//	void Player2EnemyCollision();
//	void RangeAttack2EnemyCollision();
//
//	//プレイヤーと藁の当たり判定
//	void PlayerWalaCollision();
//
//	//プレイヤーを藁から飛ばす処理
//	//回転初期化関数
//	void PlayerRotateInitialize();
//
//	//回転更新関数
//	void PlayerRotateUpdate();
//
//	void AllPushingBack();
//	void LeftPushingBack();
//	void RightPushingBack();
//	void TopPushingBack();
//	void BottomPushingBack();
//
//	bool IsHitLeft();
//	bool IsHitRight();
//	bool IsHitTop();
//	bool IsHitBottom();
//
//	bool IsTriggerJump();
//	bool IsTriggerEnter();
//	bool IsPushLeft();
//	bool IsPushRight();
//
//	//飛ぶ処理初期化
//	void FlyInitialize();
//	//飛ぶ処理更新
//	void FlyUpdate();
//	//飛ぶ移動処理
//	void FlyMove();
//	//飛ぶ処理終了
//	void FlyFinish();
//
//	//重力
//	void PlayerGravity();
//
//	// 正規化
//	Vector2 Normalize(const Vector2& v);
//	// スカラー倍
//	Vector2 Scalar(const Vector2& v, const float scalar);
//
//	//内積
//	float Dot(const Vector2& v1, const Vector2& v2);
//
//	bool IsCollision(const Plane plane, const Segment segment);
//
//private:
//	enum MapInfo {
//		NONE,
//		BLOCK,
//		ENEMY,
//		WALA,
//	};
//
//	struct Block {
//		MapInfo state; //ブロックの状態
//		Vector2 pos; //座標
//		Vector2 size; //画像の大きさ
//		Vector2 imagePos; //読み込む画像の座標
//		int color;//色
//	};
//
//private:
//
//	char keys[256] = { 0 };
//	char preKeys[256] = { 0 };
//
//	int stickPosX = 0;
//	int stickPosY = 0;
//
//	int gh1 = Novice::LoadTexture("./Resources/Mblock.png");
//	int gh2 = Novice::LoadTexture("./Resources/stage00.png");
//	int gh3 = Novice::LoadTexture("./Resources/Arrow.png");
//	int gh4 = Novice::LoadTexture("./Resources/player3.png");
//	int gh5 = Novice::LoadTexture("./Resources/SoulBlue.png");
//	int gh6 = Novice::LoadTexture("./Resources/SoulRed.png");
//
//	bool isLeft = false;
//	bool isRight = true;
//
//	Vector2 playerPos = {};//実ポジション
//
//	Vector2 playerLeftTop = {};//左上のXY座標
//	Vector2 playerRightTop = {};//右上のXY座標
//	Vector2 playerLeftBottom = {};//左下のXY座標
//	Vector2 playerRightBottom = {};//右下のXY座標
//
//	Vector2 rotatePlayerLeftTop = {};
//	Vector2 rotatePlayerRightTop = {};
//	Vector2 rotatePlayerLeftBottom = {};
//	Vector2 rotatePlayerRightBottom = {};
//
//	float kRectCenterX = 400;
//	float kRectCenterY = 100;
//
//	float playerRad;
//	float speed;
//	float speed1;
//	float playerAcceleration = 0.8f;
//	int playerGazo = Novice::LoadTexture("./Resources/player.png");
//	unsigned int playerColor = 0xFFFFFFFF;
//	unsigned int playerColor1 = 0xFFFFFFFF;
//	unsigned int playerColor2 = 0xFFFFFFFF;
//	unsigned int playerColor3 = 0xFFFFFFFF;
//	unsigned int playerColor4 = 0xFFFFFFFF;
//
//	float scenePosX;
//	float scenePosY;
//
//	bool isJump = false;
//	float jumpSpeed = 0.0f;
//
//	bool isSpeed = false;
//
//	bool isLanding = false;
//
//	bool isGravity = false;
//
//	//敵の生成
//	std::list<std::unique_ptr<Enemy>> enemies_;
//
//	bool isHitP2E = false;
//
//	//タルの生成
//	std::list<std::unique_ptr<Taru>> tarus_;
//	std::unique_ptr<Taru> taru_[20] = {};
//	int taruNo = 0;
//
//	bool isHitP2W = false;
//	int isTaruHitNo = 0;
//
//	Block block[100][100]{};
//	int blockSize = 128;
//	int blockColor = 0xFFFFFFFF;
//
//	int map[100][100]{};
//	Vector2 mapEndPos = {};
//
//	int stage = 0;
//
//	// 背景
//	int viewPosX = 0;
//	int viewPosY = 0;
//
//	// 矢印
//	Vector2 ArrowLeftTop = {};//左上のXY座標
//	Vector2 ArrowRightTop = {};//右上のXY座標
//	Vector2 ArrowLeftBottom = {};//左下のXY座標
//	Vector2 ArrowRightBottom = {};//右下のXY座標
//
//	Vector2 rotateArrowLeftTop = {};
//	Vector2 rotateArrowRightTop = {};
//	Vector2 rotateArrowLeftBottom = {};
//	Vector2 rotateArrowRightBottom = {};
//
//	Vector2 ArrowCenter = {};
//
//	int leftTopX;//左上のX座標
//	int leftTopY;//左上のY座標
//	int rightTopX;//右上のX座標
//	int rightTopY;//右上のY座標
//	int leftBottomX;//左下のX座標
//	int leftBottomY;//左下のY座標
//	int rightBottomX;//右下のX座標
//	int rightBottomY;//右下のY座標
//
//	//飛ぶスピード
//	Vector2 flySpeed = {};
//	//飛ぶ処理フラグ
//	bool isFly = false;
//
//	int CoolTime = 0;
//
//	bool isHitFlagTrue = true;
//
//	bool isHitWall = false;
//
//	// アニメーション
//	int playerAnimCount = 0;
//	int playerAnimFrame = 0;
//
//	int playerSoulAnim = 0;
//	int playerSoulFrame = 0;
//
//	int playerSoulRAnim = 0;
//	int playerSoulRFrame = 0;
//
//	// スクロール
//	float scrollStartX = 400;
//	float lineY = 0;
//	int scrollX = 0;
//	float monitorX = 0;
//
//	const int kWindowWidth = 1920;
//	const int kWindowHeight = 1024;
//
//	int enemyMax = 0;
//	int enemyKillCount = 0;
//
//	struct Sounds {
//		int soundsHG;
//		int errorESC;
//	};
//
//	Sounds stagebgm = {
//		Novice::LoadAudio("./Resources/stage.mp3"),
//		-1
//	};
//
//	bool isplayAudio = 1;
//
//	bool isChangeScoreScene = false;
//
//	Sounds scorebgm = {
//		Novice::LoadAudio("./Resources/score.wav"),
//		-1
//	};
//
//	bool isplayScoreAudio = 1;
//
//	Sounds nextSounds = {
//		Novice::LoadAudio("./Resources/next.wav"),
//		-1
//	};
//
//	bool isgameToScore = 0;
//
//	Sounds enemyDeathSounds = {
//		Novice::LoadAudio("./Resources/enemyDeath.wav"),
//		-1
//	};
//
//	bool isEnemyDeath = 0;
//
//	Sounds stingSounds = {
//		Novice::LoadAudio("./Resources/sting.mp3"),
//		-1
//	};
//
//	bool isStingSounds = 0;
//
//	Sounds flySounds = {
//		Novice::LoadAudio("./Resources/fly.mp3"),
//		-1
//	};
//
//	bool isflySounds = 0;
//
//	//スコア
//	std::unique_ptr<TimeCount> score_ = {};
//	int clearGH = Novice::LoadTexture("./Resources/cleartime.png");
//	Vector2 clearPos = {};
//	int rankGH = 0;
//	int matuGH = Novice::LoadTexture("./Resources/matu.png");
//	int takeGH = Novice::LoadTexture("./Resources/take.png");
//	int umeGH = Novice::LoadTexture("./Resources/ume.png");
//	Vector2 rankPos = {};
//	int scoreGH = Novice::LoadTexture("./Resources/Score.png");
//	Vector2 scorePos = {};
//	int nextGH = Novice::LoadTexture("./Resources/Next.png");
//	Vector2 nextPos = {};
//	int nextColor = 0xFFFFFFFF;
//	bool isNextColor = false;
//	int spaceGH = Novice::LoadTexture("./Resources/TM.png");
//	bool isPushSpaceKey = false;
//
//	static const int confettiMax = 500;
//	Vector2 confettiPos[confettiMax] = {};
//	Vector2 confettiSpeed[confettiMax] = {};
//	bool isAppear[confettiMax] = {};
//	int color[confettiMax] = {};
//	int colorNum[confettiMax] = {};
//	float confettiTheta[confettiMax] = {};
//
//	//範囲攻撃パーティクル
//	int rangeAttackGazo = Novice::LoadTexture("./Resources/rangeAttack.png");
//	Vector2 rangeAttackPos = {};
//	int rangeAttackColor = 0xFFFFFFFF;
//	bool isRangeAttackNow = false;
//
//	//フェード
//	std::unique_ptr<Fade> fade_ = {};
//
//	bool isArrowDraw = false;
//
//	bool isSoulDraw = 1;
//	bool isSoulRDraw = 0;
//
//	//チュートリアル
//	bool isTutorial = true;
//	int talk = 0;
//	int talkGH[5] = { Novice::LoadTexture("./Resources/Lines1.png"),
//	Novice::LoadTexture("./Resources/Lines2.png") ,
//	Novice::LoadTexture("./Resources/Lines3.png") ,
//	Novice::LoadTexture("./Resources/Lines4.png") ,
//	Novice::LoadTexture("./Resources/Lines5.png") };
//};
//
