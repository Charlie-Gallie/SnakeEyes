#pragma once

#include <olcPixelGameEngine.h>

#include "../UIComponents/Button.h"
#include "../UIComponents/Label.h"

class SnakeEyes : public olc::PixelGameEngine {
public:
	SnakeEyes();
	void begin();
	bool OnUserCreate() override;
	bool OnUserUpdate(float dt) override;
private:
};