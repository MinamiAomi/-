#include <Novice.h>
#include "MyMath.h"
#include "ParticleManager.h"
#include "ParticleNormal.h"
#include "Random.h"
#include "Fire.h"
#include "Player.h"
#include "Coin.h"
const char kWindowTitle[] = "学籍番号";

#include <memory>

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SrandFromTime();
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	ParticleManager* particleMana = ParticleManager::GetInstance();
	Fire::Initalize();

	Novice::SetClearColor(BLACK);

	unsigned int particleHandle = Novice::LoadTexture("./images/Particle.png");
	Fire fire;

	fire.Position({ 640,560 });
	fire.Radius(10);
	fire.IsActive(true);

	Player player;
	player.Initalize();

	Coin coins[30];
	Coin::Initalize();

	Vector2 mouse;


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		int x = 0, y = 0;
		Novice::GetMousePosition(&x, &y);
		mouse = { (float)x,(float)y };

		///
		/// ↓更新処理ここから
		///

		if (Novice::IsTriggerMouse(1)) {

			for (auto& it : coins) {
				if (it.state == Coin::kInactive) {
					it.position = mouse;
					it.state = Coin::kActive;
					break;
				}
			}

		}
		if (Novice::IsPressMouse(0)) {
			fire.Position(mouse);
			fire.Update();
		}

		player.Update(keys, preKeys);


		particleMana->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawLine(0, 600, 1280, 600, WHITE);
		
		for (auto& it : coins) {
			it.Draw();
		}

		player.Draw();

		particleMana->Draw();

		Novice::ScreenPrintf(0, 0, "%d個", particleMana->ParticleCount());

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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}


