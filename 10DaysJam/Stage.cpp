#include "Stage.h"

using namespace KamataEngine;

void Stage::Initialize() {

	Reset();
}

void Stage::Update() {

	PlayerUpdate();
	BulletUpdate();

	//境界線
	CheckBoundary1();

	//落下
	IsFallCheck();

	//当たり判定
	GetAllCollision();
}

void Stage::Draw() {

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

	//プレイヤーの描画
	Novice::DrawBox(int(playerPos.x - scrollX), int(playerPos.y), int(playerRad), int(playerRad), 0.0f, BLUE, kFillModeSolid);

	if (isBullet)
	{
		Novice::DrawEllipse(int(BulletPos.x - scrollX), int(BulletPos.y), int(BulletRadius), int(BulletRadius), 0.0f, RED, kFillModeSolid);
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
		if (playerPos.x + scrollX >= mapEndPos.x + 32) {
			scrollX = scrollX;
		}
		else {
			scrollX = int(playerPos.x - scrollStartX);
		}
	}
}

void Stage::PlayerJumppInitialize()
{
	isJump = true;
	jumpSpeed = -36.0f;
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
	
	else if (Boundary1 == true)
	{
		BulletSpeed = 5.0f;
	}
	else
	{
		BulletSpeed = 10.0f;   // → 右向き（デフォルト）
	}

	BulletRadius = 16.0f;

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

	if (map[mapY][mapX] == BLOCK)
	{
		// ブロックに当たったら弾を消す
		isBullet = false;
	}
}

void Stage::CreateMap() {

	int mapTmp1[100][100] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1},
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
			else {}
		}
	}
}

void Stage::Reset() {

	CreateMap();
	PlayerInitialize();

	scrollX = 0;

	isLeft = false;
	isRight = true;
	isJump = false;
}

void Stage::CheckBoundary1()
{
	float boundaryX1 = 1280.0f;

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
	float boundaryX2 = 1280.0f;

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

void Stage::IsFallCheck()
{
	if (playerPos.y >= 700)
	{
		FallCheck = true;
		if (FallCheck == true)
		{
			playerPos = { 129.0f,576.0f };
			scrollX = 0;
		}
	}
}

void Stage::GetAllCollision()
{
	CheckTrapCollision();
}

void Stage::Player2EnemyCollision()
{
	
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
				OnPlayerHitTrap();
				return;
			}
		}
	}
}

void Stage::OnPlayerHitTrap()
{
	PlayerHP -= 1;
}

