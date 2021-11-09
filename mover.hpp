//
// mover.hpp
//	Interface of mover
//

#pragma once

#include "graph.hpp"

// 移動物体のクラス
class Mover {
public:
	void SetX(int x) { this->x = x; }
	void SetY(int y) { this->y = y; }
	void SetPos(int x, int y) { this->x = x; this->y = y; }
	int GetX() const { return x; }
	int GetY() const { return y; }
	void SetVX(double vx) { this->vx = vx; }
	void SetVY(double vy) { this->vy = vy; }
	void SetVector(double vx, double vy) { this->vx = vx; this->vy = vy; }
	double GetVX() const { return vx; }
	double GetVY() const { return vy; }
	void SetHitRadius(int r) { this->r = r; }
	int GetHitRadius() const { return r; }

	bool IsHit(const Mover& other);

	virtual bool Init() = 0;
	virtual int Update() = 0;
	virtual void Draw(graph_ptr graph) const = 0;

private:
	int x, y;		// 座標
	double vx, vy;	// 速度
	int r;
};

class Player : public Mover {
public:
	bool Init() override;
	int Update() override;
	void Draw(graph_ptr graph) const override;
};

class Enemy : public Mover {
public:
	bool Init() override;
	int Update() override;
	void Draw(graph_ptr graph) const override;
};

class Thunder : public Mover {
public:
	explicit Thunder(const Player& player);
	bool Init() override;
	int Update() override;
	void Draw(graph_ptr graph) const override;

private:
	const Player& player_;
};

class Sea : public Mover {
public:
	bool Init() override;
	int Update() override;
	void Draw(graph_ptr graph) const override;
};
