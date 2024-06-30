#include "Killaura.h"

using namespace std;
string targetname = "None";
Killaura::Killaura() : IModule(0, Category::COMBAT, "Attacks entities") {
	rotations.addEntry(EnumEntry("None", 0))
		.addEntry(EnumEntry("Silent", 1))
	.addEntry(EnumEntry("Client", 2))
		.addEntry(EnumEntry("Actual", 3));
	registerEnumSetting("rotations", &rotations, 0);
	//
	mode.addEntry(EnumEntry("Single", 0))
		.addEntry(EnumEntry("Multi", 1));
	registerEnumSetting("mode", &mode, 0);
	//
	AutoWeapon.addEntry(EnumEntry("None", 0))
		.addEntry(EnumEntry("Full", 1))
		.addEntry(EnumEntry("Silent", 2));
	registerEnumSetting("AutoWeapon", &AutoWeapon, 0);
	//
	registerBoolSetting("MobAura", &mobs, mobs);
	registerBoolSetting("Visualize", &visualize, visualize);
	registerBoolSetting("Hold", &hold, hold);
	registerFloatSetting("Range", &range, range, 3.f, 20.f);
	registerIntSetting("Attack delay", &delayka, delayka, 0, 20);
	registerBoolSetting("Swing", &swingKA, swingKA);
	registerBoolSetting("hurttime", &hurttimeka, hurttimeka);
}

void Killaura::findWeapon() {
	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	Inventory* inv = supplies->inventory;
	float damage = 0;
	int slot = supplies->selectedHotbarSlot;
	for (int n = 0; n < 9; n++) {
		ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			float currentDamage = stack->getAttackingDamageWithEnchants();
			if (currentDamage > damage) {
				damage = currentDamage;
				slot = n;
			}
		}
	}
	supplies->selectedHotbarSlot = slot;
}

const char* Killaura::getRawModuleName() {
	return "Killaura";
}

const char* Killaura::getModuleName() {
	return "Killaura";
}

struct CompareTargetEnArray {
	bool operator()(Entity* lhs, Entity* rhs) {
		LocalPlayer* localPlayer = Game.getLocalPlayer();
		return (*lhs->getPosition()).dist(*localPlayer->getPosition()) < (*rhs->getPosition()).dist(*localPlayer->getPosition());
	}
};

static vector<Entity*> targetList;
void findEntity(Entity* currentEntity, bool isRegularEntity) {
	static auto killaura = moduleMgr->getModule<Killaura>();

	if (currentEntity == nullptr) return;
	if (currentEntity == Game.getLocalPlayer()) return;
	if (!Game.getLocalPlayer()->canAttack(currentEntity, false)) return;
	if (!Game.getLocalPlayer()->isAlive()) return;
	if (!currentEntity->isAlive()) return;
	if (currentEntity->getEntityTypeId() == 66)  // falling block
		return;
	if (currentEntity->getEntityTypeId() == 69)  // XP
		return;
	if (currentEntity->getEntityTypeId() == 64)  // item
		return;
	if (currentEntity->getEntityTypeId() == 80 || currentEntity->getEntityTypeId() == 69) return;

	if (killaura->mobs) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 319) return;
		// if (currentEntity->getEntityTypeId() == 64) return;
		if (currentEntity->getEntityTypeId() == 0xC00050)  // Arrows - new item id
			return;
		if (currentEntity->getEntityTypeId() == 307)  // NPC
			return;
	} else {
		if (!Target::isValidTarget(currentEntity)) return;
		if (currentEntity->getEntityTypeId() == 51 || currentEntity->getEntityTypeId() == 1677999) return;
	}
	float dist = (*currentEntity->getPosition()).dist(*Game.getLocalPlayer()->getPosition());
	if (dist < killaura->range) {
		targetList.push_back(currentEntity);
		sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	}
}

void Killaura::onEnable() {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	targetListEmpty = true;
	targetList.clear();
}

void Killaura::onTick(GameMode* gm) {
	auto player = Game.getLocalPlayer();
	int dbrr = Game.getLocalPlayer()->getSelectedItemId();
	if (player == nullptr) return;

	Level* level = Game.getLocalPlayer()->level;
	// auto clickGUI = moduleMgr->getModule<ClickGUIMod>();
	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	// if (clickGUI->isEnabled()) targetListEmpty = true;
	targetListEmpty = targetList.empty();

	targetList.clear();

	Game.forEachEntity(findEntity);
	Odelay++;
	slotKA = supplies->selectedHotbarSlot;
	if (!targetList.empty()) {
		targetname = std::string(targetList[0]->getNameTag()->getText());
	} else {
		targetname = "None";
	}
	if (hold && !Game.isLeftClickDown())
		return;
	// if (wtfdb && (dbrr == 259 || dbrr == 426) && Game.isRightClickDown()) return;
	if (AutoWeapon.selected != 0 && !targetList.empty()) findWeapon();
	if (!targetList.empty() && Odelay >= delayka) {
		if (mode.selected == 0) {
			for (auto& i : targetList) {
				if (!(i->damageTime > 1 && hurttimeka)) {
					gm->attack(targetList[0]);
					gm->attack(targetList[0]);
					gm->attack(targetList[0]);
					gm->attack(targetList[0]);
					if (swingKA) {
						player->swing();
					}
				}
			}
		}
		if (mode.selected == 1) {
			for (auto& i2 : targetList) {
				if (!(i2->damageTime > 1 && hurttimeka)) {
					gm->attack(i2);
					gm->attack(i2);
					gm->attack(i2);
					gm->attack(i2);
					gm->attack(i2);
					if (swingKA) {
						player->swing();
					}
				}
			}
		}
		if (AutoWeapon.selected == 2) supplies->selectedHotbarSlot = slotKA;
		if (rotations.selected == 3) {
			tro = Game.getLocalPlayer()->getPosition()->CalcAngle(*targetList[0]->getPosition());
		}
		Odelay = 0;
	} else
		targetListEmpty = true;
	// gm->destroyBlock(&Vec3i(277070, 69, -254355), 1);
}

void Killaura::onPlayerTick(Player* plr) {
	if (plr == nullptr) return;

	if (!targetList.empty()) {
		if (hold && !Game.isLeftClickDown())
			return;

		for (auto& i : targetList) {
			Vec2 angle = Game.getLocalPlayer()->getPosition()->CalcAngle(*targetList[0]->getPosition());
			Vec2 pos = Game.getLocalPlayer()->getPosition()->CalcAngle(*i->getPosition());

			if (rotations.selected == 2) {
			}

			// Strafe
			if (rotations.selected == 3) {
				plr->setRot(tro);
			}
		}
	}
}

void Killaura::onSendPacket(Packet* packet) {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	if (!targetList.empty()) {
		if (hold && !Game.isLeftClickDown())
			return;

		if (packet->isInstanceOf<C_MovePlayerPacket>() && (rotations.selected == 1 || rotations.selected == 2) && !targetList.empty()) {
			Vec2 anglefd = Game.getLocalPlayer()->getPosition()->CalcAngle(*targetList[0]->getPosition());
			auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);

			movePacket->pitch = anglefd.x;
			movePacket->headYaw = anglefd.y;
			movePacket->yaw = anglefd.y;
		}
	}
}

void Killaura::onLevelRender() {
}

void Killaura::onDisable() {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	targetListEmpty = true;
	targetList.clear();
}
