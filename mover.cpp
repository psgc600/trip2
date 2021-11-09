//
// mover.cpp
//	Implementation of mover
//

#include "mover.hpp"
#include "game.hpp"
#include "input.hpp"
#include "scene.hpp"

bool Mover::IsHit(const Mover& other)
{
	const int dx = other.x - x;
	const int dy = other.y - y;
	const int hit = other.r + r;
	return dx * dx + dy * dy < hit * hit;
}

bool Player::Init()
{
	const int width = Game::Instance()->WindowWidth();
	const int height = Game::Instance()->WindowHeight();

	// 自機の初期座標
	SetPos(static_cast<int>(width * 0.8), static_cast<int>(height * 0.4));

	// 自機の初期速度
	SetVector(0, 0);

	SetHitRadius(16);

	return true;
}

int Player::Update()
{
	const int width = Game::Instance()->WindowWidth();
	const auto& sound_map = Game::Instance()->SoundMap();

	// カーソルキーで左右に移動
	if (Input::Instance()->IsJoyPressed(Input::BUTTON_LEFT) ||
		(Input::Instance()->IsMousePressed(Input::MOUSE_LEFT) && Input::Instance()->GetMouseX() < width * 0.3)) SetVX(GetVX() - 0.2);
	if (Input::Instance()->IsJoyPressed(Input::BUTTON_RIGHT) ||
		(Input::Instance()->IsMousePressed(Input::MOUSE_LEFT) && Input::Instance()->GetMouseX() >= width * 0.7)) SetVX(GetVX() + 0.2);

	// 加速しすぎ防止
	if (GetVX() < -6) SetVX(-6);
	if (GetVX() > 6) SetVX(6);

	// 最後に速度を足して移動完了
	SetX(GetX() + static_cast<int>(GetVX()));

	// Zキーで上昇
	if (Input::Instance()->IsJoyPressed(Input::BUTTON_TRIG1) || Input::Instance()->IsMousePressed(Input::MOUSE_LEFT)) {
		SetVY(GetVY() - 0.2);

		// 音が鳴っていなかったら音を鳴らす
		if (!(CheckSoundPtr(sound_map.at("floatingSE")))) {
			PlaySoundPtr(sound_map.at("floatingSE"), DX_PLAYTYPE_BACK);
		}
	}
	else {
		SetVY(GetVY() + 0.2);
	}

	// 縦方向に加速しすぎ防止
	if (GetVY() < -6) SetVY(-6);
	if (GetVY() > 6) SetVY(6);

	// 最後に速度を足して移動完了
	SetY(GetY() + static_cast<int>(GetVY()));

	// 画面外に出ないように
	if (GetX() < 16) SetX(16);
	if (GetX() > width - 32) SetX(width - 32);
	if (GetY() < 16) SetY(16);

	return 0;
}

void Player::Draw(graph_ptr graph) const
{
	DrawGraphPtr(
		static_cast<float>(GetX()), static_cast<float>(GetY()), 1.0, 0.0, graph, TRUE);
#ifdef _DEBUG
	// 自機の当たり判定の描画
	DrawCircle(GetX(), GetY(), GetHitRadius(), GetColor(255, 255, 255));
#endif
}

bool Enemy::Init()
{
	SetPos(GetRand(9999) - 10000, GetRand(999));
	SetVector(1, 0);
	SetHitRadius(1);
	return true;
}

int Enemy::Update()
{
	const int width = Game::Instance()->WindowWidth();
	const int uptime = Game::Instance()->RunningScene()->Uptime();

	// 敵を動かす
	SetX(GetX() + static_cast<int>(GetVX()));
	// 敵が過ぎ去ったら位置を元に戻す。お手軽エンドレス
	if (GetX() > width) {
		SetX(-9000);
	}

	// 2000カウントを超えると敵の動きが速くなる
	if (uptime == 2000 || uptime == 4000 || uptime == 6000 || uptime == 8000 || uptime == 10000) {
		SetVX(GetVX() + 1);
	}

	return 0;
}

void Enemy::Draw(graph_ptr graph) const
{
	const int width = Game::Instance()->WindowWidth();

	// 画面内にいるものだけ描画
	if (GetX() > -100 && GetX() < width) {
		DrawGraphPtr(
			static_cast<float>(GetX()), static_cast<float>(GetY()), 1.0, 0.0, graph, TRUE);
	}
}

Thunder::Thunder(const Player& player) : player_(player)
{

}

bool Thunder::Init()
{
	return true;
}

int Thunder::Update()
{
	return 0;
}

void Thunder::Draw(graph_ptr graph) const
{
	DrawGraphPtr(player_.GetX() + 12, 0, graph, TRUE);
}

bool Sea::Init()
{
	const int width = Game::Instance()->WindowWidth();
	const int height = Game::Instance()->WindowHeight();

	// 海の初期座標
	SetX(width - 16);
	SetY(height - 32);

	return true;
}

int Sea::Update()
{
	const int uptime = Game::Instance()->RunningScene()->Uptime();

	// 海の画像を少しずつ右へ
	if (uptime % 5 == 0) SetX(GetX() + 1);
	return 0;
}

void Sea::Draw(graph_ptr graph) const
{
	for (int i = 0; i < 1000; i++) {
		DrawGraphPtr(GetX() - i * 16, GetY(), graph, TRUE);
	}
}
