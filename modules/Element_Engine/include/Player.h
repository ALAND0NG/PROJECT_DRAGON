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

class Weapon
{
public:
	bool Shoot(float range);
	void Update();//basically just updates a timer
	float m_FireDelay = 1.5f; //after shooting, gun needs 0.2 seconds before you can fire again;
	int m_Damage = 1;
	float m_Timer;
	bool m_CanShoot = true;
};





class Player
{
public:
	//this is a raycast test and shoots from camera look at for a distance specified with range
	Player()
	{
		Weapon weapon;
		m_Weapons.push_back(weapon);
	}
	void Update();
	void CheckJump();

	PlayerData GetPlayerData();
	void SetPlayerData(PlayerData playdata);

	bool FireWeapon(int index)
	{
		return m_Weapons[index].Shoot(15.f);
	}

	Weapon GetWeapon(int index);
	std::vector<Weapon> GetWeaponVector();
	void SetActiveWeapon(int activeweapon);
	int GetActiveWeapon();


private:
	PlayerData m_PlayerData;
	std::vector<Weapon> m_Weapons;
	int m_ActiveWeapon = 0;

};