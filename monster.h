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


//zaprzyjazniona klasa?
//@TODO : co z martwymi potworami?
class GroupOfMonsters {
private:
	std::vector<std::unique_ptr<Monster> > _monsters;
public:
	GroupOfMonsters(std::vector<std::unique_ptr<Monster> > monsters) :
		_monsters(std::move(monsters)) {}
		/*
		Tu jeszcze cos nie dziala - moze nie robic na unique_ptr, tylko shared?
		http://stackoverflow.com/questions/8468774/can-i-list-initialize-a-vector-of-move-only-type/8469002#8469002
		http://stackoverflow.com/questions/9618268/initializing-container-of-unique-ptrs-from-initializer-list-fails-with-gcc-4-7
	
	GroupOfMonsters(std::initializer_list<std::unique_ptr<Monster> > monsters) :
		_monsters(std::move(monsters)) {}*/


	HealthPoints getHealth() {
		HealthPoints h;
		for (auto const & m : _monsters)
			h += m->getHealth();
		return h;
	}
	AttackPower getAttackPower() {
		AttackPower ap;
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
	return std::make_unique<Mummy>(health, attack);
}
auto createZombie(HealthPoints health, AttackPower attack) {
	return std::make_unique<Zombie>(health, attack);
}
auto createVampire(HealthPoints health, AttackPower attack) {
	return std::make_unique<Vampire>(health, attack);
}

GroupOfMonsters createGroupOfMonsters(std::initializer_list<Monster>);


#endif /*__MONSTER_H__*/