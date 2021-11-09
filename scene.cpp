//
// scene.cpp
//	Implementation of scene
//

#include <iomanip>
#include <sstream>
#include "scene.hpp"
#include "game.hpp"
#include "input.hpp"

TitleScene::TitleScene()
{
	graph_map.insert(std::make_pair("titleScreen", LoadGraphPtr("image/title.png")));
}

TitleScene::~TitleScene()
{
	graph_map.clear();
}

int TitleScene::Update()
{
	Scene::Update();

	// C�L�[�������ꂽ��n�C�X�R�A������
	if (Input::Instance()->IsJoyPushed(Input::BUTTON_TRIG3) || Input::Instance()->IsMousePushed(Input::MOUSE_CENTER)) {
		Game::Instance()->SetHiscore(0);
		Game::Instance()->Write();
	}

	// Z�L�[�������ꂽ��Q�[�����C����ʂ�
	if (Input::Instance()->IsJoyPushed(Input::BUTTON_TRIG1) || Input::Instance()->IsMousePushed(Input::MOUSE_LEFT)) {
		Game::Instance()->ChangeScene(std::make_shared<MainScene>());
	}
	return 0;
}

void TitleScene::Draw() const
{
	const int width = Game::Instance()->WindowWidth();
	const int height = Game::Instance()->WindowHeight();

	DrawGraphPtr(width / 2.0f, height / 2.0f, 1, 0, graph_map.at("titleScreen"), TRUE);
}

MainScene::MainScene()
{
	graph_map.insert(std::make_pair("playerGraph", LoadGraphPtr("image/player.png")));
	graph_map.insert(std::make_pair("enemyGraph", LoadGraphPtr("image/enemy.png")));
	graph_map.insert(std::make_pair("thunderGraph", LoadGraphPtr("image/thunder.png")));
	graph_map.insert(std::make_pair("seaGraph", LoadGraphPtr("image/sea.png")));

	player.Init();
	for (auto& enemy : enemies) {
		enemy.Init();
	}
	sea.Init();
	thunder = std::make_shared<Thunder>(player);

	// �J�n����̃X�R�A��0�_
	score = 0;
	hiscore = Game::Instance()->Hiscore();

	// �J�n����͏�ɂ����ɂ����Ȃ�
	countUpperSide = 0;
	countLowerSide = 0;
}

MainScene::~MainScene()
{
	graph_map.clear();
}

int MainScene::Update()
{
	Scene::Update();

	const auto& sound_map = Game::Instance()->SoundMap();
	const int height = Game::Instance()->WindowHeight();

	// ���y�����Ă��Ȃ�������炷
	if (!(CheckSoundPtr(sound_map.at("stageMusic")))) {
		PlaySoundPtr(sound_map.at("stageMusic"), DX_PLAYTYPE_LOOP);
	}

	player.Update();
	for (auto& enemy : enemies) {
		enemy.Update();
	}
	sea.Update();

	// ��̂ق��ɂ�����J�E���g����
	if (player.GetY() < 200 - 64) countUpperSide++;
	else countUpperSide = 0;

	// ���̂ق��ɂ�����J�E���g����
	if (player.GetY() > 340) countLowerSide++;
	else countLowerSide = 0;

	// �X�R�A���X�V
	score = uptime / 20 * 10;

	// �n�C�X�R�A���X�V�����Ƃ��Ɍ���A�n�C�X�R�A�̒l���X�V
	if (score > hiscore) hiscore = score;

	// �G�ɓ���������Q�[���I�[�o�[
	for (auto& enemy : enemies) {
		if (player.IsHit(enemy)) {
			// ����炷
			if (!(CheckSoundPtr(sound_map.at("missSE")))) {
				PlaySoundPtr(sound_map.at("missSE"), DX_PLAYTYPE_BACK);
			}
			Game::Instance()->SetHiscore(hiscore);
			Game::Instance()->Write();
			Game::Instance()->ChangeScene(std::make_shared<GameoverScene>());
			break;
		}
	}

	// ���ɗ����Ă��Q�[���I�[�o�[
	if (player.GetY() > height) {
		// ����炷
		if (!(CheckSoundPtr(sound_map.at("missSE")))) {
			PlaySoundPtr(sound_map.at("missSE"), DX_PLAYTYPE_BACK);
		}
		Game::Instance()->SetHiscore(hiscore);
		Game::Instance()->Write();
		Game::Instance()->ChangeScene(std::make_shared<GameoverScene>());
	}

	// �Y�h�[��
	if (countUpperSide > 230 || countLowerSide > 230) {
		// ����炷
		if (!(CheckSoundPtr(sound_map.at("thunderSE")))) {
			PlaySoundPtr(sound_map.at("thunderSE"), DX_PLAYTYPE_BACK);
		}
	}
	// ���ɑł��ꂽ�̂ŃQ�[���I�[�o�[
	if (countUpperSide > 250 || countLowerSide > 250) {
		Game::Instance()->SetHiscore(hiscore);
		Game::Instance()->Write();
		Game::Instance()->ChangeScene(std::make_shared<GameoverScene>());
	}

	return 0;
}

void MainScene::Draw() const
{
	int width = Game::Instance()->WindowWidth();
	int height = Game::Instance()->WindowHeight();

	const auto& font = Game::Instance()->Font();
	static const std::string empty_string;
	std::stringstream ss;

	// ���@�̕`��
	player.Draw(graph_map.at("playerGraph"));

#ifdef _DEBUG
	DrawBox(0, 0, static_cast<int>(width * 0.3), height, GetColor(255, 0, 0), FALSE);
	DrawBox(static_cast<int>(width * 0.7), 0, width, height, GetColor(0, 0, 255), FALSE);
#endif

	// �C�̕`��
	sea.Draw(graph_map.at("seaGraph"));

	// �G�̕`��
	for (const auto& enemy : enemies) {
		enemy.Draw(graph_map.at("enemyGraph"));
	}

	// �㕔�ɒ�������ƌx��
	if (countUpperSide > 150 && countUpperSide < 250) {
		font->Draw(static_cast<float>(width / 2), 60, 1, 0, "CAUTION...");
	}
	// �����ɒ�������ƌx��
	if (countLowerSide > 150 && countLowerSide < 250) {
		font->Draw(static_cast<float>(width / 2), static_cast<float>(height - 60), 1, 0, "CAUTION...");
	}

	// �㕔�E�����ɒ�������Ɨ��U���̑O�G��
	if ((countUpperSide > 200 && countUpperSide < 210) ||
		(countLowerSide > 200 && countLowerSide < 210)) {
		thunder->Draw(graph_map.at("thunderGraph"));
	}
	// �Y�h�[��
	if (countUpperSide > 230 || countLowerSide > 230) {
		// �摜�\��
		thunder->Draw(graph_map.at("thunderGraph"));
	}

#ifdef _DEBUG
	// �o�ߎ��Ԃ̕`��
	ss << uptime;
	font->Draw(10, 50, 1, 0, ss.str().c_str());
	ss.str(empty_string);
	ss.clear();

	// �㕔�J�E���g
	ss << "Upper: " << countUpperSide;
	font->Draw(10, 70, 1, 0, ss.str().c_str());
	ss.str(empty_string);
	ss.clear();

	// �����J�E���g
	ss << "Lower: " << countLowerSide;
	font->Draw(10, 94, 1, 0, ss.str().c_str());
	ss.str(empty_string);
	ss.clear();
#endif

	// �X�R�A�̕`��
	font->Draw(width * 0.25f, 10, 1, 0, "SCORE");
	ss << std::setfill('0') << std::setw(5) << score;
	font->Draw(width * 0.25f, 30, 1, 0, ss.str().c_str());
	ss.str(empty_string);
	ss.clear();

	// �n�C�X�R�A�̕`��
	font->Draw(width * 0.5f, 10, 1, 0, "HISCORE");
	ss << std::setfill('0') << std::setw(5) << hiscore;
	font->Draw(width * 0.5f, 30, 1, 0, ss.str().c_str());
}

GameoverScene::GameoverScene()
{
	graph_map.insert(std::make_pair("missScreen", LoadGraphPtr("image/miss.png")));
}

GameoverScene::~GameoverScene()
{
	graph_map.clear();
}

int GameoverScene::Update()
{
	Scene::Update();

	const auto& sound_map = Game::Instance()->SoundMap();

	// ����Ă��鉹�y���~�߂�
	if (CheckSoundPtr(sound_map.at("stageMusic"))) {
		StopSoundPtr(sound_map.at("stageMusic"));
	}

	// X�L�[�������ꂽ��^�C�g����ʂ�
	if (Input::Instance()->IsJoyPushed(Input::BUTTON_TRIG2) || Input::Instance()->IsMousePushed(Input::MOUSE_RIGHT)) {
		Game::Instance()->ChangeScene(std::make_shared<TitleScene>());
	}
	return 0;
}

void GameoverScene::Draw() const
{
	const int width = Game::Instance()->WindowWidth();
	const int height = Game::Instance()->WindowHeight();

	DrawGraphPtr(width / 2.0f, height / 2.0f, 1, 0, graph_map.at("missScreen"), TRUE);
}