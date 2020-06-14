#include "EditorLayer.h"

#include "ImGui/ImGuiManager.h"

EditorLayer::EditorLayer()
{
	// create windows
	mViewportWindow = Asylum::CreateScope<Viewport>();
}

void EditorLayer::OnAttach()
{
	ImGuiManager::Init();
}

void EditorLayer::OnDetach()
{
	ImGuiManager::Shutdown();
}

void EditorLayer::OnUpdate(float dt)
{
    // begin new imgui frame
	ImGuiManager::Begin();

    // create the dockspace
    CreateDockSpace();

    // main menu bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Asylum"))
        {
            if (ImGui::MenuItem("About"));
            if (ImGui::MenuItem("Quit")) Asylum::Window::Get()->Close();
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

	// update all imgui windows
	mViewportWindow->OnUpdate(dt);

    // end dockspace
    ImGui::End();
	ImGuiManager::End();
}

void EditorLayer::AddEventCallbacks()
{
    Asylum::Input::AddKeyPressedCallback([](int keycode) {

        if (keycode == AM_KEY_F5)
            Asylum::Window::Get()->SetFullscreenMode();

        });
}

void EditorLayer::CreateDockSpace()
{
    // set parameters
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // handle fullscreen
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // begin dockspace window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    static bool p_open = true;
    ImGui::Begin("Editor", &p_open, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // create dockspace
    ImGuiID dockspace_id = ImGui::GetID("EditorDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
}