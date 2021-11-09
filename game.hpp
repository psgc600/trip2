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

	/// ファイル保存処理
	void Write();

private:
	static const int WINDOW_WIDTH = 854;
	static const int WINDOW_HEIGHT = 480;
	static const int COLOR_BIT = 32;		// 画面の色深度

	// SEハンドル
	std::map<const TCHAR*, sound_ptr> sound_map;

	std::shared_ptr<AsciiFont> font;

	std::shared_ptr<Scene> currentScene;
	int hiScore;				// 最高記録

	bool Init();

	// 各種ファイルの読み込み
	void LoadFiles();

	// 移動処理・変数の更新処理
	int Update();

	// 描画処理
	void Draw() const;

	// ファイル読み込み処理
	int Read();
};