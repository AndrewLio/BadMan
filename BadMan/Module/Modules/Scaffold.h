#pragma once
#include "Module.h"
class Scaffold : public IModule {
private:
	bool autoSelect = false;
	bool down = false;
	bool highlight = true;
	bool hive = false;
	bool rotations = true;
	int extend = 0;
	bool Ylock = false;
	bool tryScaffold(Vec3 blockBelow);
	bool tryClutchScaffold(Vec3 blockBelow);
	bool findBlock();
	//float YCoord;
	Vec3 blockBelowY;
	bool foundCandidate = false;
	bool tower = false;
	float towerspeed = 1;
	bool nowtower = false;
	int slot = 0;

public:
	Scaffold();
	~Scaffold(){};
	float bodyyaw = 0;
	void handleScaffoldDown(Player* player, float speed, const Vec3& velocity);
	void handleScaffoldUp(Player* player, float speed, const Vec3& velocity);
	Vec3 getBlockBelow(Player* player, float yOffset);
	void adjustYCoordinate(Vec3& blockBelow, const Vec3& blockBelowReal);
	void extendBlock(Player* player, const Vec3& velocity, Vec3& blockBelow);
	void attemptScaffoldWhileMoving(Player* player, float speed, const Vec3& velocity, Vec3& blockBelow, Vec3& blockBelowBelow);
	void handleReplaceableBlock(Player* player, float speed, const Vec3& velocity, Vec3& blockBelow);
	void handleNonReplaceableBlock(Player* player, float speed, const Vec3& velocity, Vec3& blockBelow);
	Vec3 getNextBlock(Player* player, const Vec3& velocity, const Vec3& blockBelow);

	virtual const char* getModuleName() {
		return "Scaffold";
	};
	virtual void onEnable() {
		auto player = Game.getLocalPlayer();
		if (player == nullptr) return;
		PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
		slot = supplies->selectedHotbarSlot;
		foundCandidate = false;
		blockBelowY = player->getRenderPositionComponent()->renderPos;  // Block 1 block below the player
		blockBelowY.y -= player->aabb->size.y;
		blockBelowY.y -= 0.5f;
		blockBelowY = blockBelowY.floor();
	};
	virtual void onDisable(){
		auto player = Game.getLocalPlayer();
		if (player == nullptr) return;
		PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
		if (autoSelect) supplies->selectedHotbarSlot = slot;
	};
	virtual void onMove(MoveInputHandler* input) override;
	virtual void onPostRender(MinecraftUIRenderContext* ctx) override;
	virtual void onSendPacket(Packet* packet) override;
	virtual void onPlayerTick(Player* player) override;
};
