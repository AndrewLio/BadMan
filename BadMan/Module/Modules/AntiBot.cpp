#include "AntiBot.h"

AntiBot::AntiBot() : IModule(0, Category::COMBAT, "Enable this module to filter out bots!") {
	registerBoolSetting("Hitbox Check", &hitboxCheck, hitboxCheck);
	registerBoolSetting("ASCII Check", &nameCheck, nameCheck);
	registerBoolSetting("Name Check", &nameCheckA, nameCheckA);
	registerBoolSetting("Invisible Check", &invisibleCheck, invisibleCheck);
	registerBoolSetting("EntityID Check", &entityIdCheck, entityIdCheck);
	registerBoolSetting("Other Check", &otherCheck, otherCheck);
	registerBoolSetting("Extra Check", &extraCheck, extraCheck);
	registerBoolSetting("Player Check", &playerCheck, playerCheck);
}

AntiBot::~AntiBot() {
}

const char* AntiBot::getModuleName() {
	return ("AntiBot");
}
