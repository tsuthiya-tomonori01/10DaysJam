#include "GameScene.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	//プレイヤー
	player_ = new Player();
	player_->Initialize();

	mapChip_ = new MapChip();
	mapChip_->Initialize();
}

void GameScene::Update() {

	//プレイヤー
	player_->Update();

	mapChip_->Update();
}

void GameScene::Draw() {
	
	mapChip_->Draw();

	//プレイヤー
	player_->Draw();
}
