#include "GameScene.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	//プレイヤー
	player_ = new Player();
	player_->Initialize();
}

void GameScene::Update() {

	//プレイヤー
	player_->Update();


}

void GameScene::Draw() {
	
	//プレイヤー
	player_->Draw();


}
