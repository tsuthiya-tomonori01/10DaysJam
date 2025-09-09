#include "Stage.h"

using namespace KamataEngine;

void Stage::Initialize() {

	soundDataHandle_ = Audio::GetInstance()->LoadWave("gameBGM.wav");

	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);

	Reset();
}

void Stage::Update() {

	PlayerUpdate();
	BulletUpdate();

	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		enemy->Update();
	}

	//境界線
	CheckBoundary1();
	CheckBoundary2();

	//ステージ終了判定
	StageFinish();

	//当たり判定
	GetAllCollision();
}

void Stage::Draw() {

	Novice::DrawSprite(850 - scrollX, 0, gh3, 1.0, 1.5, 0.0f, WHITE);

	//ブロックの描画
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			if (map[y][x] == 1) {
				Novice::DrawSprite(int(block[y][x].pos.x - scrollX), int(block[y][x].pos.y), gh1, 2, 2, 0.0f, WHITE);
			}
			if (map[y][x] == 2) {
				Novice::DrawSprite(int(block[y][x].pos.x - scrollX), int(block[y][x].pos.y), gh2, 2, 2, 0.0f, WHITE);
			}
		}
	}

	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		enemy->Draw(scrollX);
	}

	Novice::DrawBox(850 - scrollX, 0, 20, 700, 0.0f, RED, kFillModeSolid);

	Novice::DrawBox(1920 - scrollX, 0, 20, 700, 0.0f, RED, kFillModeSolid);

	//プレイヤーの描画
	Novice::DrawBox(int(playerPos.x - scrollX), int(playerPos.y), int(playerRad), int(playerRad), 0.0f, BLUE, kFillModeSolid);

	if (isBullet)
	{
		Novice::DrawEllipse(int(BulletPos.x - scrollX), int(BulletPos.y), int(BulletRadius), int(BulletRadius), 0.0f, RED, kFillModeSolid);
	}

	if (GolaActive) {
		// ゴールを描画（ここでは簡単に四角形で表現）
		Novice::DrawBox(int(GoalPos.x - scrollX), int(GoalPos.y), 64, 64, 0.0f, GREEN, kFillModeSolid);
	}
}

void Stage::PlayerInitialize()
{
	//プレイヤー
	playerPos = { 129.0f,576.0f };
	playerRad = 64.0f;

	speed = 5.0f;
	playerAcceleration = 0.8f;
}

void Stage::PlayerUpdate()
{
	PlayerMove();

	if (Boundary1) 
	{
		speed = 8.0f; 
	}
	else 
	{
		speed = 5.0f;
	}

	PlayerJumpUpdate();
}

void Stage::PlayerMove()
{
	if (Input::GetInstance()->PushKey(DIK_A))
	{
		if (map[int(playerPos.y) / blockSize][int(playerPos.x - speed) / blockSize] != BLOCK &&
			map[int(playerPos.y + playerRad - 1) / blockSize][int(playerPos.x - speed) / blockSize] != BLOCK) {
			playerPos.x -= speed;
			isLeft = true;
			isRight = false;
		}
	}
	else if (Input::GetInstance()->PushKey(DIK_D))
	{
		if (map[int(playerPos.y) / blockSize][int(playerPos.x + speed + playerRad) / blockSize] != BLOCK &&
			map[int(playerPos.y + playerRad - 1) / blockSize][int(playerPos.x + speed + playerRad) / blockSize] != BLOCK) {
			playerPos.x += speed;
			isLeft = false;
			isRight = true;
		}
	}

	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && !isJump)
	{
		PlayerJumppInitialize();
		if (isJump)
		{
			PlayerJumpUpdate();
		}
	}

	if (Input::GetInstance()->IsPressMouse(1) && !isBullet)
	{
		BulletInitialize();
		if (isBullet)
		{
			BulletUpdate();
		}
	}

	if (playerPos.x >= scrollStartX) {
		if (playerPos.x - scrollStartX > 1720) {
			scrollX = 1720;
		}
		else {
			scrollX = int(playerPos.x - scrollStartX);
		}
	}
}

void Stage::PlayerJumppInitialize()
{
	isJump = true;

	if (Boundary2)
	{
		jumpSpeed = -16.0f;
	}
	else
	{
		jumpSpeed = -36.0f;
	}
}

void Stage::PlayerGravity() {

	//重力処理
	if (map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x) / blockSize)] != BLOCK &&
		map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x + playerRad - 1) / blockSize)] != BLOCK) {
	}
	else {
		isGravity = false;
	}
	if (isGravity && !isJump) {
		if (map[int(playerPos.y + playerRad + 10) / blockSize][int(playerPos.x) / blockSize] != BLOCK &&
			map[int(playerPos.y + playerRad + 10) / blockSize][int(playerPos.x + playerRad - 1) / blockSize] != BLOCK) {
		}
	}
}

void Stage::PlayerJumpUpdate()
{
	// ジャンプ処理
	if (isJump) {
		// 上昇
		if (jumpSpeed <= 0) {
			if (map[int((playerPos.y + jumpSpeed) / blockSize)][int(playerPos.x) / blockSize] != BLOCK &&
				map[int((playerPos.y + jumpSpeed) / blockSize)][int(playerPos.x + playerRad - 1) / blockSize] != BLOCK) {
				playerPos.y += jumpSpeed;
				jumpSpeed += 4.0f;
			}
			else {
				// ぶつかった
				jumpSpeed = 0;
			}
		}
		// 下降
		else {
			if (map[int((playerPos.y + playerRad + jumpSpeed)) / blockSize][int(playerPos.x) / blockSize] != BLOCK &&
				map[int((playerPos.y + playerRad + jumpSpeed)) / blockSize][int(playerPos.x + playerRad - 1) / blockSize] != BLOCK) {
				playerPos.y += jumpSpeed;
			}
			else {
				// 着地
				isJump = false;
				jumpSpeed = 0;
				playerPos.y = 576.0f;
			}
		}

	}
	// 落下開始
	else if (!isJump) {
		if (map[int((playerPos.y + playerRad + 0) / blockSize)][int(playerPos.x) / blockSize] != BLOCK &&
			map[int((playerPos.y + playerRad + 0) / blockSize)][int(playerPos.x + playerRad - 1) / blockSize] != BLOCK) {
			jumpSpeed = 0;
			isGravity = true;
		}
		else {}
	}
}

void Stage::BulletInitialize()
{

	isBullet = true;

	if (isLeft)
	{
		BulletSpeed = -10.0f;  // ← 左向き発射
	}
	else
	{
		BulletSpeed = 10.0f;   // → 右向き（デフォルト）
	}

	BulletRadius = 16.0f;
	BulletPos = { 0.0f,0.0f };

	// 弾をプレイヤーの位置に生成（中央 or 右手など）
	BulletPos.x = playerPos.x;
	BulletPos.y = playerPos.y + playerRad / 2 - BulletRadius / 2;
}

void Stage::BulletUpdate()
{
	if (!isBullet) return;

	// 弾を進める
	BulletPos.x += BulletSpeed;

	// マップのブロックと衝突しているか確認
	int mapX = int((BulletPos.x + BulletRadius / 2) / blockSize);
	int mapY = int((BulletPos.y + BulletRadius / 2) / blockSize);

	if (map[mapY][mapX] == BLOCK || map[mapX][mapY] == ENEMY)
	{
		// ブロックに当たったら弾を消す
		isBullet = false;
	}
}

void Stage::CreateMap() {

	int mapTmp1[100][100] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,4,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,2,0,0,2,0,4,0,0,0,0,0,0,0,0,0,4,0,0,0,4,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	
	//マップ生成
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			
			map[y][x] = mapTmp1[y][x];
	
			//ブロックの座標、サイズ設定
			block[y][x].pos.x = float(x * blockSize);
			block[y][x].pos.y = float(y * blockSize);
			block[y][x].size.x = 128.0f;
			block[y][x].size.y = 128.0f;
	
			//ブロックがある場合
		    if (map[y][x] == 1) {
				block[y][x].state = BLOCK;
				block[y][x].imagePos.x = 0.0f;
				block[y][x].imagePos.y = 128.0f;
				block[y][x].color = blockColor;
				mapEndPos.x = (float)x * blockSize;
				mapEndPos.y = (float)y * blockSize;
			}
	
			//ブロックがない場合
			else if (map[y][x] == 0) {
				block[y][x].state = NONE;
				block[y][x].imagePos.x = 128.0f;
				block[y][x].imagePos.y = 0.0f;
			}

			else if (map[y][x] == 2) {
				block[y][x].state = TRAP;
				block[y][x].imagePos.x = 128.0f;
				block[y][x].imagePos.y = 0.0f;
			}

			//敵がいる場合
			else if (map[y][x] == 4) {
				block[y][x].state = ENEMY;

				//敵の生成
				std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();

				//初期化
				newEnemy->Initialize(Vector2{ float(x * blockSize), float(float(y * blockSize)) });
				//リストに敵を登録する, std::moveでユニークポインタの所有権移動
				enemies_.push_back(std::move(newEnemy));

				//イテレータ
				for (std::unique_ptr<Enemy>& enemy : enemies_) {
					//更新
					enemy->Update();
				}
				enemyMax++;
			}
			else {}
		}
	}
}

void Stage::Reset() {

	CreateMap();
	PlayerInitialize();

	scrollX = 0;

	isHitP2E = false;

	isLeft = false;
	isRight = true;
	isJump = false;

	Boundary1 = false;
	Boundary2 = false;
}

void Stage::CheckBoundary1()
{
	float boundaryX1 = 850.0f;

	if (playerPos.x >= boundaryX1) 
	{
		Boundary1 = true;
	}
	else 
	{
		Boundary1 = false;
	}
}

void Stage::CheckBoundary2()
{
	float boundaryX2 = 1920.0f;

	if (playerPos.x >= boundaryX2 && Boundary1 == true)
	{
		Boundary2 = true;
	}
	else
	{
		Boundary2 = false;
		Boundary1 = true;
	}
}

void Stage::StageFinish()
{
	if (!GolaActive) return;

	// プレイヤーとゴールの衝突判定
	float goalRadius = 32.0f;  // ゴールの半径（例として32に設定）
	if (playerPos.x < GoalPos.x + goalRadius &&
		playerPos.x + playerRad > GoalPos.x &&
		playerPos.y < GoalPos.y + goalRadius &&
		playerPos.y + playerRad > GoalPos.y) {
		
		sceneNo = CLEAR;
		Audio::GetInstance()->StopWave(voiceHandle_);
	}
}

void Stage::CreateGoal()
{
	GoalPos = { 2880.0f, 576.0f };  // ゴールの位置を設定（例：右側に設置）

	// ゴールをアクティブにする
	GolaActive = true;
}

void Stage::GetAllCollision()
{
	CheckTrapCollision();
	PlayerEnemyCollision();
	BulletEnemyCollision();
}

void Stage::PlayerEnemyCollision()
{
	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		if (playerPos.y <= enemy->GetPosition().y + enemy->GetRad() &&
			playerPos.y + playerRad >= enemy->GetPosition().y) {
			if (playerPos.x <= enemy->GetPosition().x + enemy->GetRad() &&
				playerPos.x + playerRad >= enemy->GetPosition().x) {
				if (enemy->GetisEnemyAlive()) {
					isHitP2E = true;
					OnPlayerDamege();
				}
			}
		}
	}
}

void Stage::BulletEnemyCollision()
{
	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		if (BulletPos.y <= enemy->GetPosition().y + enemy->GetRad() &&
			BulletPos.y + BulletRadius >= enemy->GetPosition().y) {
			if (BulletPos.x <= enemy->GetPosition().x + enemy->GetRad() &&
				BulletPos.x + BulletRadius >= enemy->GetPosition().x) {
				if (enemy->GetisEnemyAlive()) {

					enemy->SetisEnemyAlive(false);
					isBullet = false;

					enemyKillCount++;
					if (enemyMax <= enemyKillCount) {
						//ステージ転換エフェクトフラグ
						CreateGoal();
					}
				}
			}
		}
	}
}

void Stage::CheckTrapCollision()
{
	int playerLeft = int(playerPos.x) / blockSize;
	int playerRight = int(playerPos.x + playerRad - 1) / blockSize;
	int playerTop = int(playerPos.y) / blockSize;
	int playerBottom = int(playerPos.y + playerRad - 1) / blockSize;

	// プレイヤーが重なっているマスの中にトラップがあるかチェック
	for (int y = playerTop; y <= playerBottom; y++) {
		for (int x = playerLeft; x <= playerRight; x++) {
			if (map[y][x] == TRAP) {
				// トラップに触れた！
				OnPlayerDamege();
				return;
			}
		}
	}
}

void Stage::OnPlayerDamege()
{
	PlayerHP -= 1;
}

