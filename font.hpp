//
// font.hpp
//	Interface of font
//

#pragma once

#include <DxLib.h>

class AsciiFont
{
public:
	~AsciiFont();

	int Load(const TCHAR* path);

	void Draw(float x, float y, double scale, double angle, const TCHAR* text) const;

private:
	int handle[16 * 16];
};
