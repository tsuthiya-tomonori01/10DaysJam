//#include "stage1.h"
//#include "Time.h"
//
//Stage1::Stage1() {}
//
//Stage1::~Stage1() {}
//
//void Stage1::Initialize() {
//	//ステージ転換エフェクト
//	fade_ = std::make_unique<Fade>();
//
//	//スコア
//	score_ = std::make_unique<TimeCount>();
//
//	isChangeScoreScene = false;
//
//	stage = 0;
//
//	//オールリセット
//	Reset();
//}
//
//void Stage1::Update() {
//	//デバイス関連
//	GetDevice();
//
//	//チュートリアル
//	if (stage == 1 && talk == 4) {
//		if (enemyMax - 1 <= enemyKillCount) {
//			isTutorial = true;
//			score_->SetPlayerRangeAttack(true);
//		}
//	}
//
//	//チュートリアル
//	if (isTutorial) {
//		if (IsTriggerJump()) {
//			talk++;
//		}
//		if (enemyMax - 1 <= enemyKillCount) {
//			if (talk >= 5) {
//				isTutorial = false;
//			}
//		}
//		else {
//			if (talk >= 4) {
//				isTutorial = false;
//			}
//		}
//	}
//	else {
//		PlayerGravity();
//
//		//ステージクリアはんてい
//		if (isChangeScoreScene) {
//			//紙吹雪
//			for (int i = 0; i < confettiMax; i++) {
//				confettiPos[i].x += confettiSpeed[i].x;
//				confettiPos[i].y += confettiSpeed[i].y;
//
//				if (colorNum[i] == 1) {
//					color[i] = WHITE;
//				}
//				else if (colorNum[i] == 2) {
//					color[i] = 0xFFFF66FF;
//				}
//				else if (colorNum[i] == 3) {
//					color[i] = 0xFF6666FF;
//				}
//				else if (colorNum[i] == 4) {
//					color[i] = 0x66FF66FF;
//				}
//				else if (colorNum[i] == 5) {
//					color[i] = 0x6666FFFF;
//				}
//
//				if (confettiPos[i].y >= 1100 ||
//					confettiPos[i].x >= 1950 || confettiPos[i].x <= -20) {
//					if (!isAppear[i]) {
//						isAppear[i] = true;
//					}
//					confettiPos[i].x = 1920.0f / 2.0f - 1.0f;
//					confettiPos[i].y = -100.0f;
//					confettiSpeed[i].x = float(rand() % 30 - 15);
//					confettiSpeed[i].y = float(rand() % 5 + 5);
//					confettiTheta[i] = float(rand() % 100 + 1) / 100.0f;
//					colorNum[i] = rand() % 5 + 1;
//				}
//			}
//
//			//文字イージング
//			if (clearPos.y <= 100) {
//				clearPos.y += 20;
//			}
//			else {
//				if (scorePos.x <= 200) {
//					scorePos.x += 40;
//				}
//				else {
//					if (rankPos.x >= 250) {
//						rankPos.x -= 40;
//					}
//					else {
//						isPushSpaceKey = true;
//					}
//				}
//			}
//
//			//文字カラー
//			if (isNextColor) {
//				nextColor += 0x00000011;
//				if (nextColor >= 0xFFFFFFFF) {
//					isNextColor = false;
//				}
//			}
//			else {
//				nextColor -= 0x00000005;
//				if (nextColor <= 0xFFFFFF00) {
//					isNextColor = true;
//				}
//			}
//
//			//スペースキーを押したら次のステージへ
//			if (IsTriggerJump()) {
//				isChangeScoreScene = false;
//				isplayScoreAudio = false;
//				Novice::StopAudio(scorebgm.errorESC);
//				Reset();
//			}
//		}
//		else {
//			if (!isRangeAttackNow) {
//				//プレイヤーの更新
//				PlayerUpdate();
//
//				//敵の更新関数
//				for (std::unique_ptr<Enemy>& enemy : enemies_) {
//					enemy->Update();
//				}
//
//				//タルの更新処理
//				for (int i = 0; i < taruNo; ++i) {
//					taru_[i]->Update();
//				}
//
//				//樽に刺さっているかつ飛んでいないとき
//				if (!isFly && isHitP2W) {
//					if (IsTriggerJump()) {
//						isflySounds = 1;
//						//飛ぶ処理初期化
//						FlyInitialize();
//					}
//				}
//				//飛ぶ処理フラグがtrueのとき
//				if (isFly) {
//					//飛ぶ処理更新
//					FlyUpdate();
//				}
//			}
//
//			//プレイヤー範囲攻撃
//			if (score_->GetPlayerRangeAttack()) {
//				isSoulDraw = 0;
//				isSoulRDraw = 1;
//				if (IsTriggerEnter()) {
//					isRangeAttackNow = true;
//					//ステージ転換エフェクトフラグ
//					fade_->SetFadeFlag(true);
//				}
//			}
//			else {
//				isSoulDraw = 1;
//				isSoulRDraw = 0;
//			}
//
//			//当たり判定
//			GetAllCollision();
//
//			//スコア取得処理の更新
//			score_->Update();
//			if (score_->GetSRank()) {
//				rankGH = matuGH;
//			}
//			else if (score_->GetARank()) {
//				rankGH = takeGH;
//			}
//			else if (score_->GetBRank()) {
//				rankGH = umeGH;
//			}
//			else {
//				rankGH = matuGH;
//			}
//
//			//クリア判定
//			//全ての敵を倒したら
//			if (enemyMax <= enemyKillCount) {
//				if (isRangeAttackNow) {
//					if (rangeAttackColor <= 0xFFFFFF00) {
//						//ステージ転換エフェクト更新
//						fade_->Update();
//
//						if (fade_->GetFadeEnd()) {
//							Novice::StopAudio(stagebgm.errorESC);
//							isRangeAttackNow = false;
//							score_->SetPlayerRangeAttack(false);
//							isChangeScoreScene = true;
//							isplayScoreAudio = true;
//							isgameToScore = 1;
//						}
//					}
//					else {
//						rangeAttackColor -= 0x00000011;
//					}
//				}
//				else {
//					//ステージ転換エフェクト更新
//					fade_->Update();
//
//					if (fade_->GetFadeEnd()) {
//						Novice::StopAudio(stagebgm.errorESC);
//						isRangeAttackNow = false;
//						score_->SetPlayerRangeAttack(false);
//						isChangeScoreScene = true;
//						isplayScoreAudio = true;
//						isgameToScore = 1;
//					}
//				}
//			}
//		}
//	}
//
//	playerSoulFrame++;
//	playerSoulRFrame++;
//
//	if (playerSoulFrame >= 0) {
//		playerSoulAnim = 0;
//	}
//	if (playerSoulFrame >= 5) {
//		playerSoulAnim = 1;
//	}
//	if (playerSoulFrame >= 10) {
//		playerSoulFrame = 0;
//	}
//
//	if (playerSoulRFrame >= 0) {
//		playerSoulRAnim = 0;
//	}
//	if (playerSoulRFrame >= 5) {
//		playerSoulRAnim = 1;
//	}
//	if (playerSoulRFrame >= 10) {
//		playerSoulRFrame = 0;
//	}
//}
//
//
//void Stage1::Draw() {
//
//	Novice::SetBlendMode(BlendMode::kBlendModeNormal);
//
//#ifdef _DEBUG
//	Novice::ScreenPrintf(0, 20, "rotatePlayerLeftTop : %f, %f", rotatePlayerLeftTop.x, rotatePlayerLeftTop.y);
//	Novice::ScreenPrintf(0, 40, "ArrowLeftTop : %f, %f", ArrowLeftTop.x, ArrowLeftTop.y);
//	Novice::ScreenPrintf(0, 60, "rotateArrowLeftTop : %f, %f", rotateArrowLeftTop.x, rotateArrowLeftTop.y);
//#endif
//
//	//背景
//	Novice::DrawSprite(int(viewPosX), int(viewPosY), gh2, 1, 1, 0.0f, 0xFFFFFFFF);
//
//	//ブロックの描画
//	for (int y = 0; y < 100; y++) {
//		for (int x = 0; x < 100; x++) {
//			if (map[y][x] == 1) {
//				Novice::DrawSprite(int(block[y][x].pos.x - scrollX), int(block[y][x].pos.y), gh1, 1, 1, 0.0f, block[y][x].color);
//			}
//		}
//	}
//
//	//敵の描画関数
//	for (std::unique_ptr<Enemy>& enemy : enemies_) {
//		enemy->Draw(scrollX);
//	}
//
//	//プレイヤーの描画(樽に刺さっている姿)
//	if (isHitP2W) {
//		isSoulDraw = 0;
//		isSoulRDraw = 0;
//		Novice::DrawQuad(
//			int(rotatePlayerLeftTop.x - scrollX), int(rotatePlayerLeftTop.y),
//			int(rotatePlayerRightTop.x - scrollX), int(rotatePlayerRightTop.y),
//			int(rotatePlayerLeftBottom.x - scrollX), int(rotatePlayerLeftBottom.y),
//			int(rotatePlayerRightBottom.x - scrollX), int(rotatePlayerRightBottom.y),
//			0, 0,
//			256, 256,
//			gh4, playerColor
//		);
//	}
//	else {
//		isSoulDraw = 1;
//	}
//	//樽の描画
//	if (!isTutorial) {
//		for (int i = 0; i < taruNo; ++i) {
//			taru_[i]->Draw(scrollX);
//		}
//	}
//
//	// Arrow
//	if (isArrowDraw) {
//		Novice::DrawQuad(
//			int(rotateArrowLeftTop.x - scrollX), int(rotateArrowLeftTop.y),
//			int(rotateArrowRightTop.x - scrollX), int(rotateArrowRightTop.y),
//			int(rotateArrowLeftBottom.x - scrollX), int(rotateArrowLeftBottom.y),
//			int(rotateArrowRightBottom.x - scrollX), int(rotateArrowRightBottom.y),
//			0, 0,
//			128, 128,
//			gh3, playerColor
//		);
//	}
//
//	//範囲攻撃パーティクルの描画
//	if (isRangeAttackNow) {
//		Novice::DrawQuad(
//			int(rotatePlayerLeftTop.x - scrollX - rangeAttackPos.x), int(rotatePlayerLeftTop.y - rangeAttackPos.y),
//			int(rotatePlayerRightTop.x - scrollX + rangeAttackPos.x), int(rotatePlayerRightTop.y - rangeAttackPos.y),
//			int(rotatePlayerLeftBottom.x - scrollX - rangeAttackPos.x), int(rotatePlayerLeftBottom.y + rangeAttackPos.y),
//			int(rotatePlayerRightBottom.x - scrollX + rangeAttackPos.x), int(rotatePlayerRightBottom.y + rangeAttackPos.y),
//			0, 0,
//			705, 706,
//			rangeAttackGazo, rangeAttackColor
//		);
//	}
//
//	if (isSoulDraw == 1) {
//		if (playerSoulAnim == 0) {
//			Novice::DrawSpriteRect(int(rotatePlayerLeftTop.x - scrollX), int(rotatePlayerLeftTop.y), 0, 0, 128, 128, gh5, 0.55f, 1.0f, 0.0f, 0xFFFFFFFF);
//		}
//		else if (playerSoulAnim == 1) {
//			Novice::DrawSpriteRect(int(rotatePlayerLeftTop.x - scrollX), int(rotatePlayerLeftTop.y), 128, 0, 128, 128, gh5, 0.55f, 1.0f, 0.0f, 0xFFFFFFFF);
//		}
//	}
//
//	if (isSoulRDraw == 1) {
//		if (playerSoulRAnim == 0) {
//			Novice::DrawSpriteRect(int(rotatePlayerLeftTop.x - scrollX), int(rotatePlayerLeftTop.y), 0, 0, 128, 128, gh6, 0.55f, 1.0f, 0.0f, 0xFFFFFFFF);
//		}
//		else if (playerSoulRAnim == 1) {
//			Novice::DrawSpriteRect(int(rotatePlayerLeftTop.x - scrollX), int(rotatePlayerLeftTop.y), 128, 0, 128, 128, gh6, 0.55f, 1.0f, 0.0f, 0xFFFFFFFF);
//		}
//	}
//
//	//プレイヤーの描画(通常の津堅)
//	if (!isHitP2W) {
//		if (isRight) {
//			if (playerAnimCount == 0) {
//				Novice::DrawQuad(
//					int(rotatePlayerLeftTop.x - scrollX), int(rotatePlayerLeftTop.y),
//					int(rotatePlayerRightTop.x - scrollX), int(rotatePlayerRightTop.y),
//					int(rotatePlayerLeftBottom.x - scrollX), int(rotatePlayerLeftBottom.y),
//					int(rotatePlayerRightBottom.x - scrollX), int(rotatePlayerRightBottom.y),
//					0, 0,
//					128, 128,
//					playerGazo, playerColor
//				);
//			}
//
//			else if (playerAnimCount == 1) {
//				Novice::DrawQuad(
//					int(rotatePlayerLeftTop.x - scrollX), int(rotatePlayerLeftTop.y),
//					int(rotatePlayerRightTop.x - scrollX), int(rotatePlayerRightTop.y),
//					int(rotatePlayerLeftBottom.x - scrollX), int(rotatePlayerLeftBottom.y),
//					int(rotatePlayerRightBottom.x - scrollX), int(rotatePlayerRightBottom.y),
//					128, 0,
//					128, 128,
//					playerGazo, playerColor
//				);
//			}
//
//		}
//		else if (isLeft) {
//			if (playerAnimCount == 0) {
//				Novice::DrawQuad(
//					int(rotatePlayerRightTop.x - scrollX), int(rotatePlayerRightTop.y),
//					int(rotatePlayerLeftTop.x - scrollX), int(rotatePlayerLeftTop.y),
//					int(rotatePlayerRightBottom.x - scrollX), int(rotatePlayerRightBottom.y),
//					int(rotatePlayerLeftBottom.x - scrollX), int(rotatePlayerLeftBottom.y),
//					0, 0,
//					128, 128,
//					playerGazo, playerColor
//				);
//			}
//
//			else if (playerAnimCount == 1) {
//				Novice::DrawQuad(
//					int(rotatePlayerRightTop.x - scrollX), int(rotatePlayerRightTop.y),
//					int(rotatePlayerLeftTop.x - scrollX), int(rotatePlayerLeftTop.y),
//					int(rotatePlayerRightBottom.x - scrollX), int(rotatePlayerRightBottom.y),
//					int(rotatePlayerLeftBottom.x - scrollX), int(rotatePlayerLeftBottom.y),
//					128, 0,
//					128, 128,
//					playerGazo, playerColor
//				);
//			}
//		}
//	}
//
//	//チュートリアル会話
//	if (isTutorial) {
//		if (talk <= 3) {
//			Novice::DrawSprite(int(rotatePlayerRightTop.x - scrollX), int(rotatePlayerRightTop.y - 100.0f), talkGH[talk], 1, 1, 0.0f, WHITE);
//		}
//		else if (talk >= 4) {
//			Novice::DrawSprite(int(rotatePlayerRightTop.x - scrollX - 400.0f), int(rotatePlayerRightTop.y - 130.0f), talkGH[talk], 1, 1, 0.0f, WHITE);
//		}
//	}
//
//	if (isChangeScoreScene) {
//		Novice::SetBlendMode(BlendMode::kBlendModeAdd);
//
//		//紙吹雪
//		for (int i = 0; i < confettiMax; i++) {
//			if (isAppear[i]) {
//				Novice::DrawBox(int(confettiPos[i].x), int(confettiPos[i].y), 12, 9, confettiTheta[i], color[i], kFillModeSolid);
//			}
//		}
//
//		Novice::SetBlendMode(BlendMode::kBlendModeNormal);
//
//		//スコア描画
//		Novice::DrawSprite((int)clearPos.x, (int)clearPos.y, clearGH, 1, 1, 0.0f, 0xFFFFFFFF);
//		if (score_->GetRank()) {
//			Novice::DrawSprite((int)rankPos.x, (int)rankPos.y, rankGH, 1, 1, 0.0f, 0xFFFFFFFF);
//		}
//		Novice::DrawSprite((int)scorePos.x, (int)scorePos.y, scoreGH, 1, 1, 0.0f, 0xFFFFFFFF);
//		//Novice::DrawSprite((int)nextPos.x, (int)nextPos.y, nextGH, 1, 1, 0.0f, nextColor);
//
//		if (isPushSpaceKey) {
//			Novice::DrawSprite((int)0, (int)100, spaceGH, 1, 1, 0.0f, nextColor);
//		}
//
//		score_->Draw();
//	}
//
//	//ステージ転換エフェクト描画
//	fade_->Draw();
//
//	//BGM
//	if (!isplayScoreAudio) {
//		if (Novice::IsPlayingAudio(stagebgm.errorESC) == 0 || stagebgm.errorESC == -1) {
//			stagebgm.errorESC = Novice::PlayAudio(stagebgm.soundsHG, true, 0.5f);
//		}
//	}
//	else if (isplayScoreAudio) {
//		if (Novice::IsPlayingAudio(scorebgm.errorESC) == 0 || scorebgm.errorESC == -1) {
//			scorebgm.errorESC = Novice::PlayAudio(scorebgm.soundsHG, true, 0.5f);
//		}
//	}
//	else {}
//
//	if (isgameToScore == 1) {
//		if (Novice::IsPlayingAudio(nextSounds.errorESC) == 0 || nextSounds.errorESC == -1) {
//			nextSounds.errorESC = Novice::PlayAudio(nextSounds.soundsHG, false, 0.8f);
//			isgameToScore = 0;
//		}
//		else {
//			Novice::StopAudio(nextSounds.errorESC);
//		}
//	}
//
//	if (isEnemyDeath == 1) {
//		if (Novice::IsPlayingAudio(enemyDeathSounds.errorESC) == 0 || enemyDeathSounds.errorESC == -1) {
//			enemyDeathSounds.errorESC = Novice::PlayAudio(enemyDeathSounds.soundsHG, false, 0.8f);
//			isEnemyDeath = 0;
//		}
//		else {
//			Novice::StopAudio(enemyDeathSounds.errorESC);
//		}
//	}
//
//	if (isStingSounds == 1) {
//		if (Novice::IsPlayingAudio(stingSounds.errorESC) == 0 || stingSounds.errorESC == -1) {
//			stingSounds.errorESC = Novice::PlayAudio(stingSounds.soundsHG, false, 1.0);
//			isStingSounds = 0;
//		}
//		else {
//			Novice::StopAudio(stingSounds.errorESC);
//		}
//	}
//
//	if (isflySounds == 1) {
//		if (Novice::IsPlayingAudio(flySounds.errorESC) == 0 || flySounds.errorESC == -1) {
//			flySounds.errorESC = Novice::PlayAudio(flySounds.soundsHG, false, 1.0);
//			isflySounds = 0;
//		}
//		else {
//			Novice::StopAudio(flySounds.errorESC);
//		}
//	}
//}
//
//void Stage1::PlayerUpdate()
//{
//	//移動処理
//	PlayerMove();
//
//	//ジャンプ処理
//	if (!isJump) {
//		if (!isHitP2W) {
//			if (IsTriggerJump()) {
//				//ジャンプ開始
//				PlayerJumpInitialize();
//			}
//		}
//	}
//	else {
//		if (!isHitP2W) {
//			//ジャンプ更新処理
//			PlayerJumpUpdate();
//		}
//		else {
//			jumpSpeed = 0;
//		}
//	}
//
//	// スクロール
//	if (playerPos.x >= scrollStartX) {
//		if (playerPos.x + scrollX >= mapEndPos.x + 32) {
//			scrollX = scrollX;
//		}
//		else {
//			scrollX = int(playerPos.x - scrollStartX);
//		}
//	}
//
//	//アニメーション
//	playerAnimFrame++;
//
//	if (playerAnimFrame >= 0) {
//		playerAnimCount = 0;
//	}
//	if (playerAnimFrame >= 5) {
//		playerAnimCount = 1;
//	}
//	if (playerAnimFrame >= 10) {
//		playerAnimFrame = 0;
//	}
//
//}
//
//void Stage1::PlayerMove()
//{
//	if (!isHitP2W) {
//		//移動
//		//左ボタンを押しているとき
//		if (IsPushLeft()) {
//			if (map[int(playerPos.y) / blockSize][int(playerPos.x - speed) / blockSize] != BLOCK &&
//				map[int(playerPos.y + playerRad - 1) / blockSize][int(playerPos.x - speed) / blockSize] != BLOCK) {
//				playerPos.x -= speed;
//				isLeft = true;
//				isRight = false;
//			}
//		}
//		//右ボタンを押しているとき
//		else if (IsPushRight()) {
//			if (map[int(playerPos.y) / blockSize][int(playerPos.x + speed + playerRad) / blockSize] != BLOCK &&
//				map[int(playerPos.y + playerRad - 1) / blockSize][int(playerPos.x + speed + playerRad) / blockSize] != BLOCK) {
//				playerPos.x += speed;
//				isLeft = false;
//				isRight = true;
//			}
//		}
//	}
//}
//void Stage1::PlayerGravity() {
//
//	//重力処理
//	if (map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x) / blockSize)] != BLOCK &&
//		map[int((playerPos.y + playerRad) / blockSize)][int((playerPos.x + playerRad - 1) / blockSize)] != BLOCK) {
//		if (!isHitP2W && !isFly) {
//			isGravity = true;
//		}
//	}
//	else {
//		isGravity = false;
//		flySpeed.x = 0.0f;
//		flySpeed.y = 0.0f;
//	}
//	if (isGravity && !isJump) {
//		if (map[int(playerPos.y + playerRad + 10) / blockSize][int(playerPos.x) / blockSize] != BLOCK &&
//			map[int(playerPos.y + playerRad + 10) / blockSize][int(playerPos.x + playerRad - 1) / blockSize] != BLOCK) {
//			if (!isHitP2W && !isFly) {
//				playerPos.y += 10.0f;
//			}
//		}
//		BottomPushingBack();
//	}
//}
//
//void Stage1::PlayerJumpInitialize()
//{
//	isJump = true;
//
//	jumpSpeed = -18.0f;
//	playerAcceleration = 0.8f;
//}
//
//void Stage1::PlayerJumpUpdate()
//{
//	// ジャンプ処理
//	if (isJump) {
//		// 上昇
//		if (jumpSpeed <= 0) {
//			if (map[int((playerPos.y + jumpSpeed) / blockSize)][int(playerPos.x) / blockSize] != BLOCK &&
//				map[int((playerPos.y + jumpSpeed) / blockSize)][int(playerPos.x + playerRad - 1) / blockSize] != BLOCK) {
//				playerPos.y += jumpSpeed;
//			}
//			else {
//				// ぶつかった
//				jumpSpeed = 0;
//			}
//		}
//		// 下降
//		else {
//			if (map[int((playerPos.y + playerRad + jumpSpeed)) / blockSize][int(playerPos.x) / blockSize] != BLOCK &&
//				map[int((playerPos.y + playerRad + jumpSpeed)) / blockSize][int(playerPos.x + playerRad - 1) / blockSize] != BLOCK) {
//				playerPos.y += jumpSpeed;
//			}
//			else {
//				// 着地
//				isJump = false;
//				jumpSpeed = 0;
//			}
//		}
//
//		// 樽に対して衝突していない場合のみ重力の影響を受ける(=下降する)
//		if (!isHitP2W && !isFly) {
//			// スピードに重力
//			jumpSpeed += 0.8f;
//		}
//
//	}
//	// 落下開始
//	else if (!isJump) {
//		if (map[int((playerPos.y + playerRad + 0) / blockSize)][int(playerPos.x) / blockSize] != BLOCK &&
//			map[int((playerPos.y + playerRad + 0) / blockSize)][int(playerPos.x + playerRad - 1) / blockSize] != BLOCK) {
//			isGravity = true;
//			jumpSpeed = 0;
//		}
//		else {}
//	}
//}
//
//void Stage1::GetAllCollision()
//{
//	//敵が生きている時
//	for (std::unique_ptr<Enemy>& enemy : enemies_) {
//		if (enemy->GetisEnemyAlive()) {
//			//プレイヤーと敵の当たり判定
//			Player2EnemyCollision();
//		}
//	}
//	if (isHitP2E) {
//		isHitP2E = false;
//		isEnemyDeath = 1;
//	}
//
//	//プレイヤーと樽の当たり判定
//	PlayerWalaCollision();
//
//	//範囲攻撃当たり判定
//	if (isRangeAttackNow) {
//		rangeAttackPos.x += 10.0f;
//		rangeAttackPos.y += 10.0f;
//		RangeAttack2EnemyCollision();
//	}
//}
//
//void Stage1::PlayerRotateInitialize()
//{
//	playerPos.x = taru_[isTaruHitNo]->GetPosition().x + taru_[isTaruHitNo]->GetRad() / 4;
//	playerPos.y = taru_[isTaruHitNo]->GetPosition().y + taru_[isTaruHitNo]->GetRad() / 4;
//
//	playerLeftTop = {
//	.x = -playerRad / 1.35f,
//	.y = -playerRad / 1.35f,
//	};
//	playerRightTop = {
//	.x = playerRad / 1.35f,
//	.y = -playerRad / 1.35f,
//	};
//	playerLeftBottom = {
//	.x = -playerRad / 1.35f,
//	.y = playerRad / 1.35f,
//	};
//	playerRightBottom = {
//	.x = playerRad / 1.35f,
//	.y = playerRad / 1.35f,
//	};
//
//	rotatePlayerLeftTop = taru_[isTaruHitNo]->Multiply(playerLeftTop, taru_[isTaruHitNo]->GetRotateMatrix());
//	rotatePlayerRightTop = taru_[isTaruHitNo]->Multiply(playerRightTop, taru_[isTaruHitNo]->GetRotateMatrix());
//	rotatePlayerLeftBottom = taru_[isTaruHitNo]->Multiply(playerLeftBottom, taru_[isTaruHitNo]->GetRotateMatrix());
//	rotatePlayerRightBottom = taru_[isTaruHitNo]->Multiply(playerRightBottom, taru_[isTaruHitNo]->GetRotateMatrix());
//
//	ArrowCenter.x = playerPos.x;
//	ArrowCenter.y = playerPos.y;
//
//	ArrowLeftTop.x = playerLeftTop.x + playerRad / 2.2f;
//	ArrowLeftTop.y = playerLeftTop.y - playerRad / 1.35f;
//	ArrowRightTop.x = playerRightTop.x + playerRad / 2.2f;
//	ArrowRightTop.y = playerRightTop.y - playerRad / 1.35f;
//	ArrowLeftBottom.x = playerLeftBottom.x + playerRad / 2.2f;
//	ArrowLeftBottom.y = playerLeftBottom.y - playerRad / 1.35f;
//	ArrowRightBottom.x = playerRightBottom.x + playerRad / 2.2f;
//	ArrowRightBottom.y = playerRightBottom.y - playerRad / 1.35f;
//
//	rotateArrowLeftTop = rotatePlayerLeftTop;
//	rotateArrowRightTop = rotatePlayerRightTop;
//	rotateArrowLeftBottom = rotatePlayerLeftBottom;
//	rotateArrowRightBottom = rotatePlayerRightBottom;
//
//	isHitFlagTrue = false;
//}
//
//void Stage1::PlayerRotateUpdate()
//{
//	// プレイヤーの回転更新処理
//	rotatePlayerLeftTop = taru_[isTaruHitNo]->Multiply(playerLeftTop, taru_[isTaruHitNo]->GetRotateMatrix());
//	rotatePlayerRightTop = taru_[isTaruHitNo]->Multiply(playerRightTop, taru_[isTaruHitNo]->GetRotateMatrix());
//	rotatePlayerLeftBottom = taru_[isTaruHitNo]->Multiply(playerLeftBottom, taru_[isTaruHitNo]->GetRotateMatrix());
//	rotatePlayerRightBottom = taru_[isTaruHitNo]->Multiply(playerRightBottom, taru_[isTaruHitNo]->GetRotateMatrix());
//
//	rotatePlayerLeftTop.x += playerPos.x + playerRad / 2;
//	rotatePlayerLeftTop.y += playerPos.y + playerRad / 2;
//
//	rotatePlayerRightTop.x += playerPos.x + playerRad / 2;
//	rotatePlayerRightTop.y += playerPos.y + playerRad / 2;
//
//	rotatePlayerLeftBottom.x += playerPos.x + playerRad / 2;
//	rotatePlayerLeftBottom.y += playerPos.y + playerRad / 2;
//
//	rotatePlayerRightBottom.x += playerPos.x + playerRad / 2;
//	rotatePlayerRightBottom.y += playerPos.y + playerRad / 2;
//
//	// 矢印の回転更新処理
//	rotateArrowLeftTop = taru_[isTaruHitNo]->Multiply(ArrowLeftTop, taru_[isTaruHitNo]->GetRotateMatrix());
//	rotateArrowRightTop = taru_[isTaruHitNo]->Multiply(ArrowRightTop, taru_[isTaruHitNo]->GetRotateMatrix());
//	rotateArrowLeftBottom = taru_[isTaruHitNo]->Multiply(ArrowLeftBottom, taru_[isTaruHitNo]->GetRotateMatrix());
//	rotateArrowRightBottom = taru_[isTaruHitNo]->Multiply(ArrowRightBottom, taru_[isTaruHitNo]->GetRotateMatrix());
//
//	rotateArrowLeftTop.x += ArrowCenter.x + playerRad / 2;
//	rotateArrowLeftTop.y += ArrowCenter.y + playerRad / 2;
//
//	rotateArrowRightTop.x += ArrowCenter.x + playerRad / 2;
//	rotateArrowRightTop.y += ArrowCenter.y + playerRad / 2;
//
//	rotateArrowLeftBottom.x += ArrowCenter.x + playerRad / 2;
//	rotateArrowLeftBottom.y += ArrowCenter.y + playerRad / 2;
//
//	rotateArrowRightBottom.x += ArrowCenter.x + playerRad / 2;
//	rotateArrowRightBottom.y += ArrowCenter.y + playerRad / 2;
//}
//
//void Stage1::BottomPushingBack()
//{
//	if (map[int(playerPos.y + speed) / blockSize][int(playerPos.x) / blockSize] != BLOCK) {}
//}
//
//bool Stage1::IsHitLeft()
//{
//	int startY = int((playerPos.y) / blockSize);
//	int endY = int((playerPos.y + playerRad - 1) / blockSize);
//	int startX = int((playerPos.x) / blockSize);
//	int endX = int((playerPos.x) / blockSize);
//
//	return map[startY][startX] == BLOCK || map[startY][endX] == BLOCK ||
//		map[endY][startX] == BLOCK || map[endY][endX] == BLOCK ? true : false;
//}
//
//bool Stage1::IsHitRight()
//{
//	int startY = int((playerPos.y) / blockSize);
//	int endY = int((playerPos.y + playerRad - 1) / blockSize);
//	int startX = int((playerPos.x + playerRad - 1) / blockSize);
//	int endX = int((playerPos.x + playerRad - 1) / blockSize);
//
//	return map[startY][startX] == BLOCK || map[startY][endX] == BLOCK ||
//		map[endY][startX] == BLOCK || map[endY][endX] == BLOCK ? true : false;
//}
//
//bool Stage1::IsHitTop()
//{
//	int startY = int((playerPos.y) / blockSize);
//	int endY = int((playerPos.y) / blockSize);
//	int startX = int((playerPos.x) / blockSize);
//	int endX = int((playerPos.x + playerRad - 1) / blockSize);
//
//	return map[startY][startX] == BLOCK || map[startY][endX] == BLOCK ||
//		map[endY][startX] == BLOCK || map[endY][endX] == BLOCK ? true : false;
//}
//
//bool Stage1::IsHitBottom()
//{
//	int startY = int((playerPos.y + playerRad - 1) / blockSize);
//	int endY = int((playerPos.y + playerRad - 1) / blockSize);
//	int startX = int((playerPos.x) / blockSize);
//	int endX = int((playerPos.x + playerRad - 1) / blockSize);
//
//	return map[startY][startX] == BLOCK || map[startY][endX] == BLOCK ||
//		map[endY][startX] == BLOCK || map[endY][endX] == BLOCK ? true : false;
//}
//
//void Stage1::Player2EnemyCollision()
//{
//	for (std::unique_ptr<Enemy>& enemy : enemies_) {
//		if (playerPos.y <= enemy->GetPosition().y + enemy->GetRad() &&
//			playerPos.y + playerRad >= enemy->GetPosition().y) {
//			if (playerPos.x <= enemy->GetPosition().x + enemy->GetRad() &&
//				playerPos.x + playerRad >= enemy->GetPosition().x) {
//				if (enemy->GetisEnemyAlive()) {
//					isHitP2E = true;
//					enemy->SetisEnemyAlive(false);
//					enemyKillCount++;
//					if (enemyMax <= enemyKillCount) {
//						//ステージ転換エフェクトフラグ
//						fade_->SetFadeFlag(true);
//					}
//				}
//			}
//		}
//	}
//}
//
//void Stage1::RangeAttack2EnemyCollision()
//{
//	for (std::unique_ptr<Enemy>& enemy : enemies_) {
//		if (rotatePlayerLeftTop.y - rangeAttackPos.y <= enemy->GetPosition().y + enemy->GetRad() &&
//			rotatePlayerLeftBottom.y + rangeAttackPos.y >= enemy->GetPosition().y) {
//			if (rotatePlayerLeftTop.x - rangeAttackPos.x <= enemy->GetPosition().x + enemy->GetRad() &&
//				rotatePlayerRightTop.x + rangeAttackPos.x >= enemy->GetPosition().x) {
//				if (enemy->GetisEnemyAlive()) {
//					isHitP2E = true;
//					enemyKillCount++;
//					enemy->SetisEnemyAlive(false);
//				}
//			}
//		}
//	}
//}
//
//void Stage1::PlayerWalaCollision()
//{
//	for (int i = 0; i < taruNo; ++i) {
//		if (playerPos.y <= taru_[i]->GetPosition().y + taru_[i]->GetRad() &&
//			playerPos.y + playerRad >= taru_[i]->GetPosition().y) {
//			if (playerPos.x <= taru_[i]->GetPosition().x + taru_[i]->GetRad() &&
//				playerPos.x + playerRad >= taru_[i]->GetPosition().x) {
//				if (isHitFlagTrue) {
//					isHitP2W = true;
//					isArrowDraw = true;
//					isTaruHitNo = i;
//					isStingSounds = 1;
//					//プレイヤー回転処理初期化
//					PlayerRotateInitialize();
//				}
//			}
//		}
//	}
//
//	if (isHitP2W) {
//		//回転処理
//		PlayerRotateUpdate();
//	}
//	else {
//		rotatePlayerLeftTop = {
//			.x = playerPos.x,
//			.y = playerPos.y
//		};
//		rotatePlayerRightTop = {
//			.x = playerPos.x + playerRad,
//			.y = playerPos.y
//		};
//		rotatePlayerLeftBottom = {
//			.x = playerPos.x,
//			.y = playerPos.y + playerRad
//		};
//		rotatePlayerRightBottom = {
//			.x = playerPos.x + playerRad,
//			.y = playerPos.y + playerRad
//		};
//	}
//	if (!isHitFlagTrue && isHitWall) {
//		if (++CoolTime >= 20) {
//			isHitFlagTrue = true;
//			isHitWall = false;
//			CoolTime = 0;
//		}
//	}
//}
//
//void Stage1::Reset()
//{
//	//rand初期化
//	unsigned int currentTime = reinterpret_cast<time_t>(nullptr);
//	srand(currentTime);
//
//	//チュートリアル
//	talk = 0;
//
//	//プレイヤー
//	playerPos = { 129.0f,768.0f };
//	playerRad = 128.0f;
//
//	rotatePlayerLeftTop = {
//		.x = playerPos.x,
//		.y = playerPos.y
//	};
//	rotatePlayerRightTop = {
//		.x = playerPos.x + playerRad,
//		.y = playerPos.y
//	};
//	rotatePlayerLeftBottom = {
//		.x = playerPos.x,
//		.y = playerPos.y + playerRad
//	};
//	rotatePlayerRightBottom = {
//		.x = playerPos.x + playerRad,
//		.y = playerPos.y + playerRad
//	};
//
//	speed = 5.0f;
//	playerAcceleration = 0.8f;
//	playerColor = 0xFFFFFFFF;
//
//	isJump = false;
//	isGravity = false;
//
//	//範囲攻撃
//	isRangeAttackNow = false;
//	rangeAttackPos = { 0.0f,0.0f };
//	rangeAttackColor = 0xFFFFFFFF;
//
//	//樽
//	taruNo = 0;
//
//	//敵
//	enemyMax = 0;
//	enemyKillCount = 0;
//
//	//当たり判定
//	isHitP2E = false;
//	isHitP2W = false;
//	isHitFlagTrue = true;
//	isHitWall = false;
//	CoolTime = 0;
//	isArrowDraw = false;
//
//	//スコア
//	score_->Initialize();
//	for (int i = 0; i < confettiMax; ++i) {
//		confettiPos[i].x = 1920.0f / 2.0f - 1.0f;
//		confettiPos[i].y = -100.0f;
//		confettiSpeed[i].x = 0.0f;
//		confettiSpeed[i].y = 1000.0f;
//		confettiTheta[i] = float(rand() % 100 + 1) / 100.0f;
//		color[i] = WHITE;
//		colorNum[i] = 0;
//		isAppear[i] = false;
//	}
//	clearPos = { 300.0f,-1080.0f };
//	rankPos = { 1920.0f,150.0f };
//	scorePos = { -1920.0f,150.0f };
//	nextPos = { 250.0f,1080.0f };
//
//	//ステージ転換エフェクト
//	fade_->Initialize();
//
//	//BGM・SE
//	isplayScoreAudio = false;
//	isflySounds = false;
//	isStingSounds = false;
//	isEnemyDeath = false;
//	isgameToScore = 0;
//
//	scrollX = 0;
//
//	isNextColor = false;
//	nextColor = 0xFFFFFFFF;
//	isPushSpaceKey = false;
//
//	//ステージを次に移動してマップを作り直す
//	stage++;
//	if (stage == 1) {
//		isTutorial = true;
//	}
//
//	if (stage > 16) {
//		Novice::StopAudio(stagebgm.errorESC);
//		sceneNo_ = TITLE;
//	}
//	else {
//		CreateMap();
//	}
//}
//
//void Stage1::CreateMap()
//{
//	int mapTmp1[100][100] = {
//		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
//		{1,2,0,0,0,0,1,0,0,0,0,0,2,2,0,0,0,0,0,0,0,1,0,0,2,1},
//		{1,1,1,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0,0,1,1},
//		{1,0,0,0,3,0,1,0,3,0,0,0,0,0,0,0,0,3,0,0,0,1,0,0,2,1},
//		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//		{1,0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,1},
//		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, };
//
//	
//
//	//マップ生成
//	for (int y = 0; y < 100; y++) {
//		for (int x = 0; x < 100; x++) {
//			if (stage == 1) {
//				map[y][x] = mapTmp1[y][x];
//			}
//			
//
//			//ブロックの座標、サイズ設定
//			block[y][x].pos.x = float(x * blockSize);
//			block[y][x].pos.y = float(y * blockSize);
//			block[y][x].size.x = 128.0f;
//			block[y][x].size.y = 128.0f;
//
//			//ブロックがある場合
//		    if (map[y][x] == 1) {
//				block[y][x].state = BLOCK;
//				block[y][x].imagePos.x = 0.0f;
//				block[y][x].imagePos.y = 128.0f;
//				block[y][x].color = blockColor;
//				mapEndPos.x = (float)x * blockSize;
//				mapEndPos.y = (float)y * blockSize;
//			}
//
//			//ブロックがない場合
//			else if (map[y][x] == 0) {
//				block[y][x].state = NONE;
//				block[y][x].imagePos.x = 128.0f;
//				block[y][x].imagePos.y = 0.0f;
//			}
//			else {}
//		}
//	}
//}
//
//void Stage1::GetDevice()
//{
//	memcpy(preKeys, keys, 256);
//	Novice::GetHitKeyStateAll(keys);
//	Novice::GetAnalogInputLeft(0, &stickPosX, &stickPosY);
//}
//
//bool Stage1::IsTriggerJump() {
//	return keys[DIK_SPACE] && !preKeys[DIK_SPACE] ||
//		Novice::IsTriggerButton(0, PadButton::kPadButton10) ? true : false;
//}
//
//bool Stage1::IsTriggerEnter()
//{
//	return keys[DIK_RETURN] && !preKeys[DIK_RETURN] ||
//		Novice::IsTriggerButton(0, PadButton::kPadButton11) ? true : false;
//}
//
//bool Stage1::IsPushLeft()
//{
//	return keys[DIK_A] || stickPosX <= -20000 ? true : false;
//}
//
//bool Stage1::IsPushRight()
//{
//	return keys[DIK_D] || stickPosX >= 20000 ? true : false;
//}
//
//void Stage1::FlyInitialize() {
//	//飛ぶスピードを初期化
//	flySpeed.x = rotatePlayerLeftTop.x - rotatePlayerLeftBottom.x;
//	flySpeed.y = rotatePlayerLeftTop.y - rotatePlayerLeftBottom.y;
//	//飛ぶスピードを正規化してスピード倍する
//	flySpeed = Scalar(Normalize(flySpeed), 35.0f);
//
//	//フラグをtrueに
//	isFly = true;
//
//	isHitWall = false;
//
//	isArrowDraw = false;
//}
//
////更新処理
//void Stage1::FlyUpdate() {
//	//左の壁にぶつかったとき
//	if (map[int(playerPos.y - flySpeed.y) / blockSize][int(playerPos.x - flySpeed.x - 64) / blockSize] == BLOCK ||
//		map[int(playerPos.y + playerRad + flySpeed.y + 1) / blockSize][int(playerPos.x - flySpeed.x - 64) / blockSize] == BLOCK) {
//		//飛ばす処理終了
//		FlyFinish();
//		isHitP2W = false;
//		isHitWall = true;
//	}
//	//右の壁にぶつかったとき
//	if (map[int(playerPos.y - flySpeed.y) / blockSize][int(playerPos.x + flySpeed.x + playerRad + 1) / blockSize] == BLOCK ||
//		map[int(playerPos.y + playerRad + flySpeed.y + 1) / blockSize][int(playerPos.x + flySpeed.x + playerRad + 1) / blockSize] == BLOCK) {
//		//飛ばす処理終了
//		FlyFinish();
//		isHitP2W = false;
//		isHitWall = true;
//	}
//	//上の壁にぶつかったとき
//	if (map[int(playerPos.y - flySpeed.y) / blockSize][int(playerPos.x - flySpeed.x - 1) / blockSize] == BLOCK ||
//		map[int(playerPos.y - flySpeed.y) / blockSize][int(playerPos.x + playerRad + flySpeed.x + 1) / blockSize] == BLOCK) {
//		//飛ばす処理終了
//		FlyFinish();
//		isHitP2W = false;
//		isHitWall = true;
//	}
//	//下の壁にぶつかったとき
//	if (map[int(playerPos.y + playerRad + flySpeed.y) / blockSize][int(playerPos.x - flySpeed.x - 1) / blockSize] == BLOCK ||
//		map[int(playerPos.y + playerRad + flySpeed.y) / blockSize][int(playerPos.x + playerRad + flySpeed.x + 1) / blockSize] == BLOCK) {
//		//飛ばす処理終了
//		FlyFinish();
//		isHitP2W = false;
//		isHitWall = true;
//	}
//	//どこの壁にもぶつかっていないとき
//	else {
//		//飛ぶ移動処理
//		FlyMove();
//	}
//}
//
//void Stage1::FlyMove() {
//	playerPos.x += flySpeed.x;
//	playerPos.y += flySpeed.y;
//}
//
//void Stage1::FlyFinish()
//{
//	flySpeed.x = 0.0f;
//	flySpeed.y = 0.0f;
//	isFly = false;
//	isJump = false;
//}
//
//// 正規化
//Vector2 Stage1::Normalize(const Vector2& v)
//{
//	Vector2 result = { 0 };
//	float length = sqrtf(v.x * v.x + v.y * v.y);
//	if (length != 0) {
//		result.x = v.x / length;
//		result.y = v.y / length;
//	}
//	return result;
//}
//
//Vector2 Stage1::Scalar(const Vector2& v, const float scalar)
//{
//	Vector2 result;
//	result.x = scalar * v.x;
//	result.y = scalar * v.y;
//	return result;
//}
//
////内積
//float Stage1::Dot(const Vector2& v1, const Vector2& v2) {
//	float result = { 0 };
//	result = v1.x * v2.x + v1.y * v2.y;
//	return result;
//}
//
////線と平面の衝突
//bool Stage1::IsCollision(const Plane plane, const Segment segment) {
//	//法線と線の内積
//	float dot = Dot(segment.diff, plane.normal);
//
//	//垂直=平行なので、衝突していないため早期リターン
//	if (dot == 0.0f) {
//		return false;
//	}
//
//	//tを求める
//	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;
//
//	//tの値と種類によって衝突しているかを判断する
//	if (t <= 1.0f && t >= 0.0f) {
//		//衝突処理
//		return true;
//	}
//
//	return false;
//}
