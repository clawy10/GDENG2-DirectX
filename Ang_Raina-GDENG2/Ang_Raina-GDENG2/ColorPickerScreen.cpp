#include "ColorPickerScreen.h"

ColorPickerScreen::ColorPickerScreen(std::string name) : AUIScreen(name)
{
}

ColorPickerScreen::~ColorPickerScreen()
{
}

void ColorPickerScreen::DrawUI()
{
	ImGui::Begin("Color Picker");
	ImGui::ColorEdit4("Color", this->color);
	ImGui::End();
}
