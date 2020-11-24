//The big player component
//Rather than make a component for each part of the player data, we just have 1 big component
//Will also contain some functions that will be frequiently used in gameplay, such as gunplay, taking damage, etc
#pragma once
#include <PhysicsSystem.h>
struct PlayerData
{
	//this contains data such as hp, xp and so on
	int m_HP;
	int m_XP;
	int m_EntityId = 0; //defaulting to 0, because that is the convention we have
	bool m_CanJump;
};

class Player
{
public:
	//this is a raycast test and shoots from camera look at for a distance specified with range
	bool Shoot(float range);
	void Update();
	void CheckJump();

	PlayerData GetPlayerData();
	void SetPlayerData(PlayerData playdata);


private:
	PlayerData m_PlayerData;

};