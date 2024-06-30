#include "Freecam.h"
#include "../../../Utils/Utils.h"
#include "../../DrawUtils.h"

Freecam::Freecam() : IModule(0, Category::MISC, "Move your camera without moving the player.") {
	registerFloatSetting("Speed", &speed, speed, 0.50f, 1.25f);
}

Freecam::~Freecam() {
}

const char* Freecam::getModuleName() {
	return ("Freecam");
}



void Freecam::onEnable() {
	auto Player = Game.getLocalPlayer();
	pos = Player->getRenderPositionComponent()->renderPos;
	Player->setGameModeType(6);
}

void Freecam::onDisable() {
	auto Player = Game.getLocalPlayer();
	Player->getMovementProxy()->setPos(pos);
	Player->setGameModeType(0);
	Player->location->velocity.x = 0;
	Player->location->velocity.z = 0;
}

void Freecam::onPreRender(MinecraftUIRenderContext* rcx) {
	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();
	auto Player = Game.getLocalPlayer();

	if (input == nullptr)
		return;

	if (Player == nullptr)
		return;
	DrawUtils::drawBox(pos.sub(0.3f, 1.62f, 0.3f), pos.add(0.3f, 0.18f, 0.3f), 0.3f, true);
}