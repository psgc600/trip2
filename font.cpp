//
// font.cpp
//	Implementation of font
//

#include "font.hpp"

AsciiFont::~AsciiFont()
{
	for (int i = 0; i < 16 * 16; ++i) DeleteGraph(handle[i]);
}

int AsciiFont::Load(const TCHAR* path)
{
	return LoadDivGraph(path, 16 * 16, 16, 16, 16, 16, handle);
}

void AsciiFont::Draw(float x, float y, double scale, double angle, const TCHAR* text) const
{
	for (size_t i = 0; i < strlen(text); ++i) {
		DrawRotaGraphF(
			static_cast<float>(x + (i * 16 * scale)), y,
			scale, angle, handle[text[i]], TRUE);
	}
}
