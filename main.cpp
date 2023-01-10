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
	float hsize = 10;
	unsigned int handle = 0;
	unsigned int color = WHITE;

public:
	Part() : ParticleBase() {}
	~Part() {}

	void Update() {
		pos += vel;
	}
	void Draw() {
		Novice::SetBlendMode(kBlendModeAdd);
		int left = pos.x - hsize;
		int top = pos.y - hsize;
		Novice::DrawSpriteRect(left, top, hsize * 2.0f, hsize * 2.0f, 0, 0, 256, 256, handle, 0.0f, color);
		Novice::SetBlendMode(kBlendModeNormal);
	}
	bool IsDelete() {
		// 画面外
		return 
			pos.x < -hsize || 1280 + hsize < pos.x ||
			pos.y < -hsize || 720 + hsize < pos.y;
	}
};

void CreateParticle(unsigned int handle);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Srand();
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	ParticleManager* particleMana = ParticleManager::GetInstance();
		
	unsigned int particleHandle = Novice::LoadTexture("./images/Particle.png");

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

		if (Novice::IsTriggerMouse(0)) {
			CreateParticle(particleHandle);
		}

		particleMana->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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

void CreateParticle(unsigned int handle)
{
	int particleCount = 10;
	Vector2 center = { 640,360 };
	ParticleManager* partMana = ParticleManager::GetInstance();

	for (int i = 0; i < particleCount; i++) {
		Part* particle = new Part;
		particle->pos = Vector2{ (float)Random(-100, 100),(float)Random(-100, 100) } + center;
		particle->vel = Rotated(VECTOR2::UnitX, Math::Lerp(Random(), 0.0f, Math::TwoPi)) * 5.0f;
		particle->hsize = Math::Lerp(Random(), 20.0f, 50.0f);
		particle->handle = handle;
		particle->color = Color::HsvaToRgba(Math::Lerp(Random(), 0.0f, 360.0f), Random(), Random(), 0xFF);
		partMana->AddParticle(particle);
	}
}
