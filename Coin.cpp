#include "Coin.h"
#include"Novice.h"

const Vector2 Coin::kSize = { 50.0f,50.0f };
const Vector2 Coin::kHalfSize = kSize * 0.5f;
int Coin::textureHandle = 0;

void Coin::Initalize()
{
	textureHandle = Novice::LoadTexture("./images/coin.png");
}

void Coin::Draw()
{
	Vector2 lefttop = position - kHalfSize;
	Vector2 s = kSize / 256.0f;
	Novice::DrawSpriteRect((int)lefttop.x, (int)lefttop.y, 0, 0, 256, 256, textureHandle, s.x, s.y, 0.0f, WHITE);

}
