#include <Novice.h>
#include "MyMath.h"
#include "ParticleManager.h"
#include "ParticleBase.h"
#include "Random.h"

const char kWindowTitle[] = "学籍番号";

class Part : public ParticleBase {

public:
	Vector2 pos;
	Vector2 vel;
	float radius = 10;
	unsigned int color = WHITE;

public:
	Part() : ParticleBase() {}
	~Part() {}

	void Update() {
		pos += vel;
	}
	void Draw() {
		Novice::DrawEllipse(pos.x, pos.y, radius, radius, 0.0f, color, kFillModeSolid);
	}
	bool IsDelete() {
		// 画面外
		return 
			pos.x - radius < 0 || 1280 < pos.x + radius ||
			pos.y - radius < 0 || 720 < pos.y + radius;
	}
};

void CreateParticle();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Srand();
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	ParticleManager* particleMana = ParticleManager::GetInstance();
		CreateParticle();

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


		particleMana->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		particleMana->Draw();

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

void CreateParticle()
{
	int particleCount = 10;
	Vector2 center = { 640,360 };
	ParticleManager* partMana = ParticleManager::GetInstance();

	for (int i = 0; i < particleCount; i++) {
		Part* particle = new Part;
		particle->pos = Vector2{ (float)Random(-100, 100),(float)Random(-100, 100) } + center;
		particle->vel = Rotated(VECTOR2::UnitX, Math::Lerp(Random(), 0.0f, Math::TwoPi)) * 5.0f;
		particle->radius = Math::Lerp(Random(), 5.0f, 20.0f);
		partMana->AddParticle(particle);
	}
}
