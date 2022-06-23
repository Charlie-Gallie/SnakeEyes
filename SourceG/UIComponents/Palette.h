#pragma once

#ifndef	PALETTE_PALETTE
#define PALETTE_PALETTE

#include <olcPixelGameEngine.h>

struct ColorSet {
	olc::Pixel
		primary,
		secondary,
		tertiary,
		quaternary;
};

struct Palette {
	const static inline ColorSet ui = {
		{ 220, 200, 200 },
		{ 60, 35, 35 },
		{ 0, 0, 0 },
		{ 255, 255, 255 }
	};
};

#endif // PALETTE_PALETTE