#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "helper.h"
#include <cassert>
#include <memory>
#include <vector>
#include <initializer_list>


class Monster {
protected:
	HealthPoints _health;
	AttackPower _attack;
	Monster(HealthPoints, AttackPower);
public:
	HealthPoints getHealth() const;
	AttackPower getAttackPower() const;
	void takeDamage(AttackPower damage);
	virtual ~Monster() = default;
};


class Zombie : public Monster {
public:
	Zombie(HealthPoints health, AttackPower attack);
};

class Vampire : public Monster {
public:
	Vampire(HealthPoints health, AttackPower attack);
};

class Mummy : public Monster {
public:
	Mummy(HealthPoints health, AttackPower attack);
};


//@TODO : co z martwymi potworami?
class GroupOfMonsters {
private:
	std::vector<std::shared_ptr<Monster>> _monsters;
public:
	// 1. shared_ptr czy unique_ptr?
	// 2. kopiowanie initializer_list / vector czy jakies manipulacje na rvalue ref.?
	GroupOfMonsters(std::vector<std::shared_ptr<Monster>> monsters) :
		_monsters(monsters) {}
	GroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> monsters) :
		_monsters(monsters) {}

	HealthPoints getHealth() const;
	AttackPower getAttackPower() const;
	void takeDamage(AttackPower damage);
};



std::shared_ptr<Mummy> createMummy(HealthPoints health, AttackPower attack);
std::shared_ptr<Zombie> createZombie(HealthPoints health, AttackPower attack);
std::shared_ptr<Vampire> createVampire(HealthPoints health, AttackPower attack);
std::shared_ptr<GroupOfMonsters> createGroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> monsters);



#endif /*__MONSTER_H__*/