#include <Novice.h>
#include "KamataEngine.h"

#include "GameManager.h"

using namespace KamataEngine;

const char kWindowTitle[] = "4049_変幻洞窟";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	const int KWindowWidth = 1280;

	const int KWindowHeight = 700;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, KWindowWidth, KWindowHeight);

	GameManager* gameManager = new GameManager();

	gameManager->Run();

	return 0;
}