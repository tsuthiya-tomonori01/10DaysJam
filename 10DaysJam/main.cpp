#include <Novice.h>
#include "KamataEngine.h"

#include "GameScene.h"
#include "TitleScene.h"

using namespace KamataEngine;

const char kWindowTitle[] = "4049_変幻洞窟";

void ChangeScene();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	const int KWindowWidth = 1280;

	const int KWindowHeight = 700;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, KWindowWidth, KWindowHeight);

	GameScene* gameScene = new GameScene;
	TitleScene* titleScene = new TitleScene;

	//最初のシーンの初期化

	titleScene->Initialize();

	gameScene->Initialize();


	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		titleScene->Update();

		gameScene->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		titleScene->Draw();

		gameScene->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	//delete gameScene;
	//gameScene = nullptr;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}