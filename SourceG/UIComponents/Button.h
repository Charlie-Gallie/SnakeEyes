#pragma once

#ifndef UICOMPONENT_BUTTON
#define UICOMPONENT_BUTTON

#include "UIComponent.h"
#include "Label.h"

enum class HAlign {
	LEFT,
	MIDDLE,
	RIGHT
};

enum class VAlign {
	TOP,
	MIDDLE,
	BOTTOM
};

enum class BackgroundType {
	SOLID,
	IMAGE
};

class Button : public UIComponent {
public:
	olc::Pixel
		textColorNormal = Palette::ui.primary,
		textColorHover = Palette::ui.secondary,
		textColorClick = Palette::ui.tertiary,

		backgroundColorNormal = Palette::ui.secondary,
		backgroundColorHover = Palette::ui.tertiary,
		backgroundColorClick = Palette::ui.quaternary,

		borderColorNormal = Palette::ui.tertiary,
		borderColorHover = Palette::ui.tertiary,
		borderColorClick = Palette::ui.quaternary,

		textColor = textColorNormal,
		backgroundColor = backgroundColorNormal,
		borderColor = borderColorNormal;

	Button(olc::PixelGameEngine& _pge) :
		UIComponent(_pge),
		text(pge)
	{
		// Constructor
	}

	~Button() {
		// Destructor
	}

	void update() override {
		handleMouseInput();
		drawBackground();
		drawBorder();
		drawText();
	}

	void setBorderVisible(bool _borderVisible) { borderVisible = _borderVisible; }
	bool getBorderVisible() { return borderVisible; }

	void setBorderThickness(int _borderThickness) { borderThickness = _borderThickness; }
	int getBorderThickness() { return borderThickness; }

	void setText(std::string _text) { text.setText(_text); }
	std::string getText() { return text.getText(); }

	void setTextHAlign(HAlign _hAlign) { hAlign = _hAlign; updateTextPosition(); }
	HAlign getTextHAlign() { return hAlign; }

	void setTextVAlign(VAlign _vAlign) { vAlign = _vAlign; updateTextPosition(); }
	VAlign getTextVAlign() { return vAlign; }

	void setTextPadding(uint8_t _textPadding) { textPadding = _textPadding; }
	uint8_t getTextPadding() { return textPadding; }

	void setPosition(olc::vi2d _position) override {
		position = _position;
		updateTextPosition();
	}
	olc::vi2d getPosition() override { return position; }

	void setBackgroundType(BackgroundType _backgroundType) { backgroundType = _backgroundType; }
	BackgroundType getBackgroundType() { return backgroundType; }

	void setBackgroundImageNormalPath(std::string _backgroundImageNormalPath) {
		backgroundImageNormalPath = _backgroundImageNormalPath;

		std::cout << backgroundImage.Load(backgroundImageNormalPath) << std::endl;
		backgroundImage.Create(size.x, size.y);
		backgroundImage.Decal()->UpdateSprite();
	}
	std::string getBackgroundImageNormalPath() { return backgroundImageNormalPath; }
protected:
	Label text;
	bool borderVisible = true;
	int borderThickness = 3;
	uint8_t textPadding = 5;
	BackgroundType backgroundType = BackgroundType::SOLID;
	HAlign hAlign = HAlign::MIDDLE;
	VAlign vAlign = VAlign::MIDDLE;

	std::string backgroundImageNormalPath = "";
	std::string backgroundImageHoverPath = "";
	std::string backgroundImageClickPath = "";

	olc::Renderable backgroundImage;

	void handleMouseInput() override {
		olc::vi2d mousePos = pge.GetMousePos();

		if (
			mousePos.x > position.x && mousePos.x < position.x + size.x &&
			mousePos.y > position.y && mousePos.y < position.y + size.y
		) {
			

			if (pge.GetMouse(olc::Mouse::LEFT).bHeld) {
				textColor = textColorClick;
				backgroundColor = backgroundColorClick;
				borderColor = borderColorClick;

				dispatchEvent(this, UIEventType::ON_MOUSE_LEFT_HELD);

				if (!mouseDown) {
					dispatchEvent(this, UIEventType::ON_MOUSE_LEFT_DOWN);
					mouseDown = true;
				}
			}
			else {
				textColor = textColorHover;
				backgroundColor = backgroundColorHover;
				borderColor = borderColorHover;

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
				textColor = textColorNormal;
				backgroundColor = backgroundColorNormal;
				borderColor = borderColorNormal;

				dispatchEvent(this, UIEventType::ON_MOUSE_EXIT);
				mouseHovering = false;
			}
		}
	}

	void drawBackground() {
		switch (backgroundType) {
		case BackgroundType::SOLID:
			pge.FillRect(
				position,
				size,
				backgroundColor
			);
			break;
		case BackgroundType::IMAGE:
			pge.DrawDecal(position, backgroundImage.Decal());
			break;
		}
	}

	void drawBorder() {
		if (borderVisible) {
			for (int borderN = 0; borderN < borderThickness; borderN++) {
				pge.DrawRect(
					position + olc::vi2d(borderN, borderN),
					size - olc::vi2d(borderN * 2, borderN * 2),
					borderColor
				);
			}
		}
	}

	void drawText() {
		/* TODO: Move to setPosition */
		updateTextPosition();
		text.setColor(textColor);
		text.update();
	}

	void updateTextPosition() {
		switch (hAlign) {
		case HAlign::LEFT:
			text.setPosition(
				{
					position.x + borderThickness + textPadding,
					text.getPosition().y
				}
			);
			break;
		case HAlign::MIDDLE:
			text.setPosition(
				{
					position.x + (size.x / 2) - (text.getBounds().x / 2),
					text.getPosition().y
				}
			);
			break;
		case HAlign::RIGHT:
			text.setPosition(
				{
					(position.x + size.x) - (text.getBounds().x + textPadding + borderThickness),
					text.getPosition().y
				}
			);
			break;
		}

		switch (vAlign) {
		case VAlign::TOP:
			text.setPosition(
				{
					text.getPosition().x,
					position.y + borderThickness + textPadding
				}
			);
			break;
		case VAlign::MIDDLE:
			text.setPosition(
				{
					text.getPosition().x,
					position.y + (size.y / 2) - (text.getBounds().y / 2)
				}
			);
			break;
		case VAlign::BOTTOM:
			text.setPosition(
				{
					text.getPosition().x,
					(position.y + size.y) - (text.getBounds().y + textPadding + borderThickness)
				}
			);
			break;
		}
	}
};

#endif // UICOMPONENT_BUTTON