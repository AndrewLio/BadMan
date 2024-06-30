#include "NameTags.h"

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

NameTags::NameTags() : IModule(0, Category::VISUAL, "Shows better nametags.") {
	registerBoolSetting("Underline", &underline, underline);
	registerBoolSetting("MyNameTag", &mynametag, mynametag);
	//registerBoolSetting("Armor", &displayArmor, displayArmor);
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
}

NameTags::~NameTags() {
}

const char* NameTags::getModuleName() {
	return ("NameTags");
}

void drawNameTags(Entity* ent, bool) {
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	static auto nameTagsMod = moduleMgr->getModule<NameTags>();

	if (ent != localPlayer) {
		if (ent->getNameTag()->getTextLength() < 1)
			return;
		if (Target::isValidTarget(ent) && nameTagsMod != nullptr) {
			nameTagsMod->nameTags.insert(Utils::sanitize(ent->getNameTag()->getText()));
			float dist = ent->getPosition()->dist(*Game.getLocalPlayer()->getPosition());
			DrawUtils::drawNameTags(ent, fmax(0.6f, 3.f / dist));
			DrawUtils::flush();
		}
	}
}

void NameTags::onPreRender(MinecraftUIRenderContext* renderCtx) {
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer == nullptr || !GameData::canUseMoveKeys()) return;

	if (ingameNametagSetting)
		if (!gotPrevSetting) {
			lastSetting = *ingameNametagSetting;
			gotPrevSetting = true;
			*ingameNametagSetting = false;
		} else
			*ingameNametagSetting = false;  //disable other ppl's nametags
	if (mynametag && localPlayer->getActorRotationComponent()->pitch > -80) {
		Vec3 mypos = localPlayer->getRenderPositionComponent()->renderPos;
		mypos.y += 0.7;
		Vec2 textPos = DrawUtils::worldToScreen(mypos);
		std::string name = localPlayer->getNameTag()->getText();
		DrawUtils::drawCenteredString(textPos, &name, 0.8, MC_Color(1.f, 1.f, 1.f), true, 1);
	}
	Game.forEachEntity(drawNameTags);
}

void NameTags::onDisable() {
	if (ingameNametagSetting && gotPrevSetting) {
		*ingameNametagSetting = lastSetting;
		gotPrevSetting = false;
	}
}