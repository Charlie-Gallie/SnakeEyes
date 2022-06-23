#pragma once

#ifndef UICOMPONENT_LABEL
#define UICOMPONENT_LABEL

#include <olcPGEX_TTF.h>

#include "UIComponent.h"

class Label : public UIComponent {
public:
	// TODO: Position may not align with text because of the anchor fix

	Label(olc::PixelGameEngine& _pge) : UIComponent(_pge) {
		olc::Font::init();
		setFontPath(fontPath); // Assign font to a value
	};

	void update() override {
		std::u32string u32Text = std::u32string().assign(text.begin(), text.end());
		olc::vi2d textBounds = font.GetStringBounds(u32Text).size;
		font.DrawString(
			u32Text,
			position + olc::vi2d(0, textBounds.y), // Move the pivot to top left rather than bottom left
			color
		);
	}

	void setText(std::string _text) { text = _text; }
	std::string getText() { return text; }

	void setFontPath(std::string _fontPath) {
		fontPath = _fontPath;
		font = olc::Font(fontPath, scale);
	}
	std::string getFontPath() { return fontPath; }

	void setScale(int _scale) override {
		scale = _scale;
		setFontPath(fontPath); // Make new font with the new scale
	}
	// int getScale() { return scale; } // Not changed from base class

	olc::vi2d getBounds() { return font.GetStringBounds(std::u32string().assign(text.begin(), text.end())).size; }
protected:
	/*	Protect set/get size - Can't be used for labels.	*/
	void setSize(olc::vi2d) override {}
	olc::vi2d getSize() override { return size; }

	std::string text = "";
	olc::Font font;
	std::string fontPath = "Source/Assets/CinzelBlack.otf";
};

#endif // UICOMPONENT_LABEL