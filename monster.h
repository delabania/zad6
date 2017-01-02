#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "helper.h"
#include "citizen.h"
#include <cassert>
#include <memory>
#include <vector>
#include <initializer_list>
#include <string>

class Citizen;

// Podstawowy abstrakcyjny interfejs potwora
class Monster {
public:
	virtual ~Monster() = default;

	virtual HealthPoints getHealth() const = 0;
	virtual AttackPower getAttackPower() const = 0;
	virtual void takeDamage(AttackPower damage) = 0;

	virtual void attack(Citizen&) = 0; // TODO: wymaga lepszego miejsca/designu

	virtual std::string getName() const = 0;
};

// Bazowa, konkretna implementacja pojedynczego potwora
class SingleMonster : public Monster {
protected:
	HealthPoints _health;
	AttackPower _attack;

	SingleMonster(HealthPoints, AttackPower);
public:
	virtual ~SingleMonster() = default;

	virtual HealthPoints getHealth() const override;
	virtual AttackPower getAttackPower() const override;
	virtual void takeDamage(AttackPower damage) override;

	virtual void attack(Citizen& citizen) override;
};

class Zombie : public SingleMonster {
public:
	Zombie(HealthPoints, AttackPower);

	virtual std::string getName() const override;
};

class Vampire : public SingleMonster {
public:
	Vampire(HealthPoints, AttackPower);

	virtual std::string getName() const override;
};

class Mummy : public SingleMonster {
public:
	Mummy(HealthPoints, AttackPower);

	virtual std::string getName() const override;
};


//@TODO : co z martwymi potworami?
// Konkretna implementacja grupy potworow
class GroupOfMonsters : public Monster {
private:
	std::vector<std::shared_ptr<Monster>> _monsters;
public:
	virtual ~GroupOfMonsters() = default;

	// 1. shared_ptr czy unique_ptr?
	GroupOfMonsters(const std::vector<std::shared_ptr<Monster>>& monsters) :
		_monsters(monsters) {}
	// Kopiowanie initializer_list jest tanie (to tylko wrapper) i ogolnie przyjete (np. robi to STL)
	GroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> monsters) :
		_monsters(monsters) {}

	virtual HealthPoints getHealth() const override;
	virtual AttackPower getAttackPower() const override;
	virtual void takeDamage(AttackPower damage) override;

	virtual void attack(Citizen& citizen) override;

	virtual std::string getName() const override;
};

std::shared_ptr<Mummy> createMummy(HealthPoints health, AttackPower attack);
std::shared_ptr<Zombie> createZombie(HealthPoints health, AttackPower attack);
std::shared_ptr<Vampire> createVampire(HealthPoints health, AttackPower attack);
std::shared_ptr<GroupOfMonsters> createGroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> monsters);

#endif /*__MONSTER_H__*/

