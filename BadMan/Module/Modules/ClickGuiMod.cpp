#include "ClickGuiMod.h"
#include "../../Menu/ClickGui.h"

ClickGuiMod::ClickGuiMod() : IModule(VK_INSERT, Category::CLIENT, "The clickgui - toggle everything just by clicking on it!") {
	color.addEntry(EnumEntry("Wave", 0))
	.addEntry(EnumEntry("RGB", 1))
	.addEntry(EnumEntry("Astolfo", 2))
	.addEntry(EnumEntry("BadMan", 4))
	.addEntry(EnumEntry("RGBWave", 3));
	registerEnumSetting("Color", &color, 0);
	registerFloatSetting("Brightness", &brightness, brightness, 0.f, 1.f);
	registerFloatSetting("Saturation", &saturation, saturation, 0.f, 1.f);
	registerIntSetting("Spacing", &spacing, spacing, 1, 200);
	registerBoolSetting("Show Tooltips", &showTooltips, showTooltips);
	registerFloatSetting("Opacity", &coloropacity, coloropacity, 0.f, 255.f);
	registerIntSetting("Opacity2", &opacity, opacity, 0, 255);
	registerFloatSetting("R", &r, r, 0.f, 255.f);
	registerFloatSetting("G", &g, g, 0.f, 255.f);
	registerFloatSetting("B", &b, b, 0.f, 255.f);
	registerFloatSetting("R2", &r2, r2, 0.f, 255.f);
	registerFloatSetting("G2", &g2, g2, 0.f, 255.f);
	registerFloatSetting("B2", &b2, b2, 0.f, 255.f);
}

ClickGuiMod::~ClickGuiMod() {
}

const char* ClickGuiMod::getModuleName() {
	return ("ClickGui");
}

void ClickGuiMod::onEnable() {
	Game.getClientInstance()->releaseMouse();
}

bool ClickGuiMod::allowAutoStart() {
	return false;
}

void ClickGuiMod::onDisable() {
	Game.getClientInstance()->grabMouse();
}

void ClickGuiMod::onPostRender(MinecraftUIRenderContext* renderCtx) {
	if (GameData::canUseMoveKeys())
		Game.getClientInstance()->releaseMouse();
}
void ClickGuiMod::onLoadConfig(void* conf) {
	IModule::onLoadConfig(conf);
	ClickGui::onLoadConfig(conf);
}
void ClickGuiMod::onSaveConfig(void* conf) {
	IModule::onSaveConfig(conf);
	ClickGui::onSaveConfig(conf);
}
