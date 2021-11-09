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

	// �e��t�@�C���̓ǂݍ���
	LoadFiles();

	// �n�C�X�R�A��ǂݍ���
	hiScore = Read();

	// ���C�����[�v
	while (ProcessMessage() == 0) {
		// �ړ������E�ϐ��̍X�V����
		if (Update() == -1) break;

		// �`�揈��
		ClearDrawScreen();
		Draw();
		ScreenFlip();
	}

	// �A�v���P�[�V�����̏I������
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
	// �E�B���h�E�̃^�C�g����ݒ�
#ifdef _DEBUG
	SetMainWindowText("DANGEROUS TRIP - DEBUG MODE");
#else
	SetMainWindowText("DANGEROUS TRIP");
#endif

	// ���O�o�̗͂L��(TRUE: ����, FALSE: ���Ȃ�)
	SetOutApplicationLogValidFlag(FALSE);

	// �A�[�J�C�u�@�\���g��
	SetUseDXArchiveFlag(TRUE);

	// �A�[�J�C�u�̊g���q
	SetDXArchiveExtension("arc");

	// �t���X�N���[�� or �E�B���h�E
	int isFullScreen = MessageBox(NULL, TEXT("�t���X�N���[���ŋN�����܂���"),
		TEXT("Dangerous Trip"), MB_YESNO | MB_ICONQUESTION);

	if (isFullScreen == IDYES) {
		ChangeWindowMode(FALSE);
	}
	else {
		ChangeWindowMode(TRUE);
	}

	// ��ʃT�C�Y�Ȃǂ�ݒ�
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_BIT);

	// DX���C�u��������������
	if (DxLib_Init() == -1) return false;

	// ���ߐF�̕ύX
	SetTransColor(255, 0, 255);

	// ����ʏ���
	SetDrawScreen(DX_SCREEN_BACK);

	font = std::make_shared<AsciiFont>();
	if (font->Load("image/FontAscii.png") == -1) return false;

	// �N������̓^�C�g����ʂ�
	ChangeScene(std::make_shared<TitleScene>());

	return true;
}

void Game::LoadFiles()
{
	// BGM�̃��[�h
	sound_map.insert(std::make_pair("stageMusic", LoadSoundPtr("sound/stage.ogg")));

	// SE�̃��[�h
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
