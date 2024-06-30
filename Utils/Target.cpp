#include "Target.h"

#include <regex>
#include "../BadMan/FriendList/FriendsManager.h"

#include "../BadMan/Module/ModuleManager.h"

LocalPlayer** localPlayer;

void Target::init(LocalPlayer** cl) {
	localPlayer = cl;
}

bool Target::isValidTarget(Entity* ent) {

	auto localPlayer = Game.getLocalPlayer();

	if (ent == localPlayer)
		return false;

	static auto antibot = moduleMgr->getModule<AntiBot>();
	static auto hitboxMod = moduleMgr->getModule<Hitbox>();
	static auto teams = moduleMgr->getModule<Teams>();
	static auto noFriends = moduleMgr->getModule<NoFriends>();
	std::string name = ent->getNameTag()->getText();
	name = Utils::sanitize(name);
	std::string botname[] = {
		"game selector", 
		"play game"  
	};
	if (!Game.isInGame())
		return false;
	if (!ent->isAlive())
		return false;

	auto entityTypeId = ent->getEntityTypeId();

	if (ent->isPlayer()) {
		if (teams->isColorCheckEnabled()) {
			std::string targetName = ent->getNameTag()->getText();
			std::string localName = localPlayer->getNameTag()->getText();

			if (targetName.size() > 2 && localName.size() > 2) {
				targetName = std::string(targetName, 0, targetName.find('\n'));
				localName = std::string(localName, 0, localName.find('\n'));

				std::string colorTargetName = std::regex_replace(targetName, std::regex(u8"§r"), "");
				std::string colorLocalName = std::regex_replace(localName, std::regex(u8"§r"), "");
				char colorTarget = colorTargetName[colorTargetName.find(u8"§") + 2];
				char colorLocal = colorLocalName[colorLocalName.find(u8"§") + 2];
				std::vector<char*> colorList;
				colorList.push_back(BLACK);
				colorList.push_back(DARK_BLUE);
				colorList.push_back(DARK_GREEN);
				colorList.push_back(DARK_AQUA);
				colorList.push_back(DARK_RED);
				colorList.push_back(DARK_PURPLE);
				colorList.push_back(GOLD);
				colorList.push_back(GRAY);
				colorList.push_back(DARK_GRAY);
				colorList.push_back(BLUE);
				colorList.push_back(GREEN);
				colorList.push_back(AQUA);
				colorList.push_back(RED);
				colorList.push_back(LIGHT_PURPLE);
				colorList.push_back(YELLOW);
				colorList.push_back(WHITE);
				for (auto& i : colorList) {
					if (localName.find(i) != std::string::npos && targetName.find(i) != std::string::npos) return false;
				}
			}
		}
		if (teams->isAlliedCheckEnabled()) {
			if (localPlayer->isAlliedTo(ent)) return false;
		}
	}

	// Temporarily removed from gui, tons of false negatives
	if (antibot->isPlayerCheckEnabled() && !ent->isPlayer())
		return false;

	if (antibot->isPlayerCheckEnabled() && ent->isLocalPlayer())
		return false;

	if (antibot->isPlayerCheckEnabled() && !Game.getLocalPlayer()->canAttack(ent, false))
		return false;
	// if (!Game.getLocalPlayer()->canAttack(currentEntity, false)) return;

	if (antibot->isEntityIdCheckEnabled() && entityTypeId <= 130 || entityTypeId == 316 || entityTypeId == 256)
		return false;

	if (antibot->isASCIICheckEnabled() && !Target::containsOnlyASCII(ent->getNameTag()->getText()))
		return false;

	if (antibot->isNameCheckEnabled() && std::string(ent->getNameTag()->getText()).find(std::string("\n")) != std::string::npos)
		return false;

	if (antibot->isNameCheckEnabled() && name.empty())
		return false;

	if (antibot->isInvisibleCheckEnabled() && ent->isInvisible())
		return false;

	if (antibot->isOtherCheckEnabled() && ent->isImmobile())
		return false;

	if (antibot->isOtherCheckEnabled() && ent->getMovementProxy()->isImmobile())
		return false;

	if (antibot->isOtherCheckEnabled() && ent->getNameTag()->getTextLength() < 2)
		return false;

	if (antibot->isOtherCheckEnabled() && ent->isSilent())
		return false;

	if (!hitboxMod->isEnabled() && antibot->isHitboxCheckEnabled())
		if ((ent->aabb->size.y < 1.5f || ent->aabb->size.x < 0.49f || ent->aabb->size.y > 2.1f || ent->aabb->size.x > 0.9f))
			return false;

	if (antibot->isExtraCheckEnabled() && name.find("shop") != std::string::npos)
		return false;

	if (antibot->isExtraCheckEnabled() && name.find("game selector") != std::string::npos)
		return false;

	if (antibot->isExtraCheckEnabled() && name.find("marketplace") != std::string::npos)
		return false;

	return (ent != nullptr);
	return true;
}

bool Target::containsOnlyASCII(const std::string& string) {
	for (auto c : string) {
		int n = static_cast<unsigned char>(c);
		if (n > 127 && n != -89) {
			return false;
		}
	}
	return true;
}
