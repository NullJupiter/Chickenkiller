#pragma once

#include <Asylum.h>

class App : public Asylum::Application
{
private:
	Asylum::Layer* mEditorLayer;
public:
	App() { OnStartup(); };
	~App() { OnShutdown(); };

	virtual void OnStartup() override;
	virtual void OnShutdown() override;
	virtual void OnUpdate(float dt) override;
private:
	void OnKeyPressed(int keycode);
};
