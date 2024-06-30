#pragma once

#include "Module.h"

class ClickGuiMod : public IModule {
public:
	ClickGuiMod();
	~ClickGuiMod();
	bool keystrokes = false;
	float saturation = 1.f;
	float brightness = 1.f;
	bool tabGUI = false;
	int opacity = 150;
	float coloropacity = 150.f;
	int glowlayers = 12;
	float glowopacity = 0.75;
	int spacing = 70;

	float scale = 1.f;

	// Colors
	SettingEnum color = this;
	SettingEnum Fonts = this;
	float r = 255.f, g = 255.f, b = 255.f;
	float r2 = 0.f, g2 = 220.f, b2 = 255.f;

	bool showTooltips = true;
	// Inherited via IModule
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual bool allowAutoStart() override;
	virtual void onLoadConfig(void* conf) override;
	virtual void onSaveConfig(void* conf) override;
};
