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

	Monster(HealthPoints health, AttackPower attack) :
		_health(health),
		_attack(attack) {
		assert(attack >= 0);
		assert(health > 0);
	}

public:
	HealthPoints getHealth() const {
		return _health;
	}

	AttackPower getAttackPower() const {
		return _attack;
	}

	void takeDamage(AttackPower damage) {
		assert(damage > 0);
		_health = damage > _health ? 0 : _health - damage;
	}

};


class Zombie : public Monster {
public:
	Zombie(HealthPoints health, AttackPower attack) :
		Monster(health, attack) {}
};

class Vampire : public Monster {
public:
	Vampire(HealthPoints health, AttackPower attack) :
		Monster(health, attack) {}
};

class Mummy : public Monster {
public:
	Mummy(HealthPoints health, AttackPower attack) :
		Monster(health, attack) {}
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



	HealthPoints getHealth() const {
		HealthPoints h = 0;
		for (auto const & m : _monsters)
			h += m->getHealth();
		return h;
	}
	AttackPower getAttackPower() const {
		AttackPower ap = 0;
		for (auto const & m : _monsters)
			if (m->getHealth() > 0)
				ap += m->getAttackPower();
		return ap;
	}
	void takeDamage(AttackPower damage) {
		for (auto & m : _monsters)
			m->takeDamage(damage);
	}
};



auto createMummy(HealthPoints health, AttackPower attack) {
	return std::make_shared<Mummy>(health, attack);
}
auto createZombie(HealthPoints health, AttackPower attack) {
	return std::make_shared<Zombie>(health, attack);
}
auto createVampire(HealthPoints health, AttackPower attack) {
	return std::make_shared<Vampire>(health, attack);
}


auto createGroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> monsters) {
	return std::make_shared<GroupOfMonsters>(monsters);
}

/*
GroupOfMonsters createGroupOfMonsters(const std::initializer_list<std::shared_ptr<Monster>> & monsters) {
	return GroupOfMonsters(monsters);
}*/



#endif /*__MONSTER_H__*/