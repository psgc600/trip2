#pragma once

#include <DxLib.h>
#include <memory>

class graph_handle
{
public:
	explicit graph_handle(const TCHAR* path)
		: handle_(DxLib::LoadGraph(path))
	{
	}

	~graph_handle()
	{
		DeleteGraph(handle_);
	}

	int handle() const
	{
		return handle_;
	}

private:
	int handle_;
};

typedef std::shared_ptr<graph_handle> graph_ptr;

inline graph_ptr LoadGraphPtr(const TCHAR* path)
{
	return std::make_shared< graph_handle >(path);
}

inline int DrawGraphPtr(int x, int y, graph_ptr graph, int trans_flag = TRUE)
{
	return DxLib::DrawGraph(x, y, graph->handle(), trans_flag);
}

inline int DrawGraphPtr(float x, float y, double scale, double angle, graph_ptr graph, int trans_flag = TRUE, int turn_flag = FALSE)
{
	return DxLib::DrawRotaGraphF(x, y, scale, angle, graph->handle(), trans_flag, turn_flag);
}
