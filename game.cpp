//
// game.cpp
//	Implementation of game
//

#include "game.hpp"
#include "DxLib.h"
#include <stdio.h>
#include "input.hpp"
#include "scene.hpp"

int Game::Run()
{
	if (!Init()) return -1;

	// 各種ファイルの読み込み
	LoadFiles();

	// ハイスコアを読み込む
	hiScore = Read();

	// メインループ
	while (ProcessMessage() == 0) {
		// 移動処理・変数の更新処理
		if (Update() == -1) break;

		// 描画処理
		ClearDrawScreen();
		Draw();
		ScreenFlip();
	}

	// アプリケーションの終了処理
	return DxLib_End();
}

void Game::ChangeScene(const std::shared_ptr<Scene>& newScene)
{
	currentScene = newScene;
}

void Game::Write()
{
	FILE* fp;
	errno_t err;

	if ((err = fopen_s(&fp, "score.dat", "wb")) != 0) {
		fprintf(stderr, "File open failed\n");
		return;
	}
	fwrite(&hiScore, sizeof(hiScore), 1, fp);
	fclose(fp);
}

bool Game::Init()
{
	// ウィンドウのタイトルを設定
#ifdef _DEBUG
	SetMainWindowText("DANGEROUS TRIP - DEBUG MODE");
#else
	SetMainWindowText("DANGEROUS TRIP");
#endif

	// ログ出力の有無(TRUE: する, FALSE: しない)
	SetOutApplicationLogValidFlag(FALSE);

	// アーカイブ機能を使う
	SetUseDXArchiveFlag(TRUE);

	// アーカイブの拡張子
	SetDXArchiveExtension("arc");

	// フルスクリーン or ウィンドウ
	int isFullScreen = MessageBox(NULL, TEXT("フルスクリーンで起動しますか"),
		TEXT("Dangerous Trip"), MB_YESNO | MB_ICONQUESTION);

	if (isFullScreen == IDYES) {
		ChangeWindowMode(FALSE);
	}
	else {
		ChangeWindowMode(TRUE);
	}

	// 画面サイズなどを設定
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_BIT);

	// DXライブラリ初期化処理
	if (DxLib_Init() == -1) return false;

	// 透過色の変更
	SetTransColor(255, 0, 255);

	// 裏画面処理
	SetDrawScreen(DX_SCREEN_BACK);

	font = std::make_shared<AsciiFont>();
	if (font->Load("image/FontAscii.png") == -1) return false;

	// 起動直後はタイトル画面へ
	ChangeScene(std::make_shared<TitleScene>());

	return true;
}

void Game::LoadFiles()
{
	// BGMのロード
	sound_map.insert(std::make_pair("stageMusic", LoadSoundPtr("sound/stage.ogg")));

	// SEのロード
	sound_map.insert(std::make_pair("floatingSE", LoadSoundPtr("sound/floating.wav")));
	sound_map.insert(std::make_pair("thunderSE", LoadSoundPtr("sound/thunder.wav")));
	sound_map.insert(std::make_pair("missSE", LoadSoundPtr("sound/miss.wav")));
}

int Game::Update()
{
	Input::Instance()->Update();

	currentScene->Update();

	//
	// Common update process
	//
	if (Input::Instance()->IsJoyPushed(Input::BUTTON_TRIG9)) {
		// quit
		return -1;
	}

	return 0;
}

void Game::Draw() const
{
	currentScene->Draw();
}

int Game::Read()
{
	FILE* fp;
	errno_t err;
	int input = 0;

	if ((err = fopen_s(&fp, "score.dat", "rb")) == 0) {
		fread(&input, sizeof(input), 1, fp);
		fclose(fp);
	}

	return input;
}
