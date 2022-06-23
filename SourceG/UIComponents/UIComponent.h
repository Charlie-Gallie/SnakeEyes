#pragma once

#ifndef UICOMPONENT_UICOMPONENT
#define UICOMPONENT_UICOMPONENT

#include <olcPixelGameEngine.h>

#include "Palette.h"

class UIComponent;

enum class UIEventType {
	ON_MOUSE_ENTER,
	ON_MOUSE_HOVER,
	ON_MOUSE_EXIT,

	ON_MOUSE_LEFT_UP,
	ON_MOUSE_LEFT_DOWN,
	ON_MOUSE_LEFT_HELD
};

struct UIEvent {
	UIComponent* component;
	UIEventType eventType;
};

class UIComponent {
public:
	uint32_t buttonID = 0; // Used within the event so you can get a specific button obj

	virtual void update() {
		handleMouseInput();
	}

	virtual void setPosition(olc::vi2d _position) { position = _position; }
	virtual olc::vi2d getPosition() { return position; }

	virtual void setSize(olc::vi2d _size) { size = _size; }
	virtual olc::vi2d getSize() { return size; }

	virtual void setScale(int _scale) { scale = _scale; }
	virtual int getScale() { return scale; }

	virtual void setColor(olc::Pixel _color) { color = _color; }
	virtual olc::Pixel getColor() { return color; }

	void bindEventFunction(void (*_eventHandler)(UIEvent)) { if (_eventHandler) eventHandler = _eventHandler; }
protected:
	olc::PixelGameEngine& pge;

	olc::vi2d
		position = { 100, 100 },
		size = { 300, 100 };
	olc::Pixel color = Palette::ui.primary;
	int scale = 30;

	bool
		mouseHovering = false,
		mouseDown = false;

	void (*eventHandler)(UIEvent) = nullptr;

	UIComponent(olc::PixelGameEngine& _pge) : pge(_pge) {};

	void dispatchEvent(UIComponent* _component, UIEventType _eventType) {
		if (eventHandler)
			eventHandler({ _component, _eventType });
	}

	virtual void handleMouseInput() {
		olc::vi2d mousePos = pge.GetMousePos();

		if (
			mousePos.x > position.x && mousePos.x < position.x + size.x &&
			mousePos.y > position.y && mousePos.y < position.y + size.y
		) {
			if (pge.GetMouse(olc::Mouse::LEFT).bHeld) {
				dispatchEvent(this, UIEventType::ON_MOUSE_LEFT_HELD);

				if (!mouseDown) {
					dispatchEvent(this, UIEventType::ON_MOUSE_LEFT_DOWN);
					mouseDown = true;
				}
			}
			else {
				if (mouseDown) {
					dispatchEvent(this, UIEventType::ON_MOUSE_LEFT_UP);
					mouseDown = false;
				}
			}

			if (!mouseHovering) {
				dispatchEvent(this, UIEventType::ON_MOUSE_ENTER);
				mouseHovering = true;
			}

			dispatchEvent(this, UIEventType::ON_MOUSE_HOVER);
		}
		else {
			if (mouseHovering) {
				dispatchEvent(this, UIEventType::ON_MOUSE_EXIT);
				mouseHovering = false;
			}
		}
	}
};

#endif // UICOMPONENT_UICOMPONENT