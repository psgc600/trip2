#pragma once

#include <map>
#include "font.hpp"
#include "singleton.hpp"
#include "sound.hpp"

class Scene;

class Game : public Singleton<Game>
{
public:
	int Run();

	const int WindowWidth() const { return WINDOW_WIDTH; }
	const int WindowHeight() const { return WINDOW_HEIGHT; }

	const std::map<const TCHAR*, sound_ptr> SoundMap() const { return sound_map; }

	void ChangeScene(const std::shared_ptr<Scene>& newScene);
	const std::shared_ptr<Scene> RunningScene() const { return currentScene; }

	void SetHiscore(int hiscore) { hiScore = hiscore; }
	const int Hiscore() const { return hiScore; }

	const std::shared_ptr<AsciiFont> Font() const { return font; }

	/// �t�@�C���ۑ�����
	void Write();

private:
	static const int WINDOW_WIDTH = 854;
	static const int WINDOW_HEIGHT = 480;
	static const int COLOR_BIT = 32;		// ��ʂ̐F�[�x

	// SE�n���h��
	std::map<const TCHAR*, sound_ptr> sound_map;

	std::shared_ptr<AsciiFont> font;

	std::shared_ptr<Scene> currentScene;
	int hiScore;				// �ō��L�^

	bool Init();

	// �e��t�@�C���̓ǂݍ���
	void LoadFiles();

	// �ړ������E�ϐ��̍X�V����
	int Update();

	// �`�揈��
	void Draw() const;

	// �t�@�C���ǂݍ��ݏ���
	int Read();
};