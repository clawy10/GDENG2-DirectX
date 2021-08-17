#include "CreditsScreen.h"


CreditsScreen::CreditsScreen(std::string name) : AUIScreen(name)
{
	this->logo = new ImGuiTexture("../Assets/Textures/yuujiball.jpg");	
}

CreditsScreen::~CreditsScreen()
{
	
}

void CreditsScreen::DrawUI()
{
	ImGui::Begin("Credits");

	ImGui::Image(this->logo->GetTexture() , ImVec2(this->logo->GetTextureWidth(), this->logo->GetTextureHeight()));
	
	ImGui::Text("About");
	ImGui::Text("Scene Editor v1.0");

	ImGui::Text("");

	ImGui::Text("Developed by: Raina Cally Ang");

	ImGui::Text("");

	ImGui::Text("Acknowledgements: ");
	ImGui::Text("Pardcode's 3D Game Engine Tutorial Series");
	ImGui::Text("Sir Neil's GDENG-2 Course");

	ImGui::End();
}
