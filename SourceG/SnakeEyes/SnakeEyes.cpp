#define OLC_PGE_APPLICATION
#define OLC_PGEX_TTF
#include "SnakeEyes.h"

#include <iostream>

using namespace olc;

SnakeEyes::SnakeEyes() {
	sAppName = "Snake Eyes";
}

void SnakeEyes::begin() {
	Construct(
		1920,	// Window resolution X
		1080,	// Window resolution Y
		1,		// Pixel scaler X
		1,		// Pixel scaler Y
		true,	// Fullscreen
		true,	// VSync - TODO: Cap to 30fps
		true	// Maintain aspect ratio (I think)
	);
	Start();	// Open the window
}

bool SnakeEyes::OnUserCreate() {

	return true;
}

bool SnakeEyes::OnUserUpdate(float dt) {
	Clear(DARK_CYAN);

	Button btn{ *this };
	btn.setPosition({ 10, 10 });
	btn.setSize({ 400, 400 });
	btn.setText("protect me");
	btn.setBackgroundImageNormalPath("Source/Assets/Button.png");
	btn.setBackgroundType(BackgroundType::IMAGE);
	btn.update();

	return true;
}