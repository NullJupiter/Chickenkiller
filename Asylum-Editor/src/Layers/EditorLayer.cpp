#include "EditorLayer.h"

#include "ImGui/ImGuiManager.h"
#include "EditorWindows/WindowStateManager.h"

class TestEntity : public Asylum::Entity
{
public:
    TestEntity(const glm::vec2& position, const glm::vec2& size)
        : Entity(position, size)
    {}

    virtual void OnUpdate(float dt)
    {

    }
    virtual void OnRender()
    {
        Asylum::Renderer::DrawRectangle(mPosition, mSize, {255, 255, 255, 255}, 0.0f);
    }
};

EditorLayer::EditorLayer()
{
	// create windows
    mMainMenuWindow = Asylum::CreateScope<MainMenu>();
	mViewportWindow = Asylum::CreateScope<Viewport>();
    mResourceTreeWindow = Asylum::CreateScope<ResourceTree>();
}

void EditorLayer::OnAttach()
{
	ImGuiManager::Init();
    WindowStateManager::Init();

    Asylum::EntitySystem::RegisterEntity(Asylum::EntityData("TestEntity", Asylum::CreateRef<TestEntity>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), "default"));
    Asylum::EntitySystem::RegisterEntity(Asylum::EntityData("TestEntity2", Asylum::CreateRef<TestEntity>(glm::vec2(1.1f, 0.0f), glm::vec2(1.0f, 1.0f)), "default"));
    Asylum::EntitySystem::RegisterEntity(Asylum::EntityData("TestEntity3", Asylum::CreateRef<TestEntity>(glm::vec2(2.2f, 0.0f), glm::vec2(1.0f, 1.0f)), "default"));
    Asylum::EntitySystem::RegisterEntity(Asylum::EntityData("TestEntity4", Asylum::CreateRef<TestEntity>(glm::vec2(3.3f, 0.0f), glm::vec2(1.0f, 1.0f)), "default"));
}

void EditorLayer::OnDetach()
{
	ImGuiManager::Shutdown();

    Asylum::EntitySystem::RemoveAllEntities();
}

void EditorLayer::OnUpdate(float dt)
{
    // begin new imgui frame
    ImGuiManager::Begin();

    // create the dockspace
    CreateDockSpace();

	// update all imgui windows
    mMainMenuWindow->OnUpdate(dt);
	mViewportWindow->OnUpdate(dt);
    mResourceTreeWindow->OnUpdate(dt);

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