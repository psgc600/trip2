#pragma once

#include <array>
#include <map>
#include "graph.hpp"
#include "mover.hpp"

class Scene
{
public:
	Scene() : uptime(0) {}
	virtual ~Scene() {}
	virtual int Update() { ++uptime; return 0; }
	virtual void Draw() const = 0;

	const int Uptime() const { return uptime; }

protected:
	int uptime;
};

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();
	int Update() override;
	void Draw() const override;

private:
	std::map<const TCHAR*, graph_ptr> graph_map;
};

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();
	int Update() override;
	void Draw() const override;

private:
	static const int ENEMY_MAX = 600;		// �G�̍ő吔

	std::map<const TCHAR*, graph_ptr> graph_map;
	Player player;
	std::array<Enemy, ENEMY_MAX> enemies;
	std::shared_ptr<Thunder> thunder;
	Sea sea;

	int countUpperSide;			// ��ʏ㕔�ɂ�������
	int countLowerSide;			// ��ʉ����ɂ�������

	int score;					// ����̃X�R�A
	int hiscore;
};

class GameoverScene : public Scene
{
public:
	GameoverScene();
	~GameoverScene();
	int Update() override;
	void Draw() const override;

private:
	std::map<const TCHAR*, graph_ptr> graph_map;
};
