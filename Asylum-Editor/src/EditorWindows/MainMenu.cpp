#include "MainMenu.h"

#include <imgui.h>

MainMenu::MainMenu()
{

}

void MainMenu::OnUpdate(float dt)
{
    mIsActive = ImGui::IsWindowFocused();

    // main menu bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Asylum"))
        {
            if (ImGui::MenuItem("About"));
            if (ImGui::MenuItem("Quit")) Asylum::Window::Get()->Close();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("New"))
        {
            if (ImGui::MenuItem("Create Entity"));
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

}
