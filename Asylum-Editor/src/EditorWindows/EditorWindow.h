#pragma once

class EditorWindow
{
protected:
	bool mIsActive;
public:
	EditorWindow()
		: mIsActive(true)
	{}

	virtual void OnUpdate(float dt) = 0;

	bool IsActive() const { return mIsActive; };
};