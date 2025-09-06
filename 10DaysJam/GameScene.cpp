#include "GameScene.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete stage_;
}

void GameScene::Initialize() {

	stage_ = new Stage;
	stage_->Initialize();
}

void GameScene::Update() {

	stage_->Update();
}

void GameScene::Draw() {
	
	stage_->Draw();
}
