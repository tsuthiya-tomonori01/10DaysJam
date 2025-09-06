#include "Stage.h"

using namespace KamataEngine;

void Stage::Initialize() {

	Reset();
}

void Stage::Update() {

	PlayerUpdate();
}

void Stage::Draw() {

	//ブロックの描画
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			if (map[y][x] == 1) {
				Novice::DrawSprite(int(block[y][x].pos.x - scrollX), int(block[y][x].pos.y), gh1, 2, 2, 0.0f, WHITE);
			}
		}
	}

	//プレイヤーの描画
	Novice::DrawBox(int(playerPos.x - scrollX), int(playerPos.y), int(playerRad), int(playerRad), 0.0f, BLUE, kFillModeSolid);
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

	if (Input::GetInstance()->PushKey(DIK_SPACE))
	{
		PlayerJumpInitialize();
	}
}

void Stage::PlayerMove()
{
	if (Input::GetInstance()->PushKey(DIK_A))
	{
		if (map[int(playerPos.y) / blockSize][int(playerPos.x - speed) / blockSize] != BLOCK&&
			map[int(playerPos.y + playerRad - 1) / blockSize][int(playerPos.x - speed) / blockSize] != BLOCK) {
			playerPos.x -= speed;
			isLeft = true;
			isRight = false;
		}
	}
	else if (Input::GetInstance()->PushKey(DIK_D))
	{
		if (map[int(playerPos.y) / blockSize][int(playerPos.x + speed + playerRad) / blockSize] != BLOCK&&
			map[int(playerPos.y + playerRad - 1) / blockSize][int(playerPos.x + speed + playerRad) / blockSize] != BLOCK) {
			playerPos.x += speed;
			isLeft = false;
			isRight = true;
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

void Stage::PlayerJumpInitialize()
{

}

void Stage::PlayerJumpUpdate()
{

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
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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
			else {}
		}
	}
}

void Stage::Reset() {

	CreateMap();
	PlayerInitialize();
}

void Stage::GetAllCollision()
{

}

void Stage::Player2MapCollision()
{

}

void Stage::Player2EnemyCollision()
{

}

