#define __MONSTER_H__
#ifndef __MONSTER_H__

#include "helper.h"
#include <vector>
#include <initializer_list>


class Monster {
protected:
	HealthPoints _health;
	AttackPower _attack;

	Monster(HealthPoints health, AttackPower attack) :
		_health(health),
		_attack(attack) {}

public:
	Health getHealth() const {
		return _health;
	}

	AttackPower getAttackPower() const {
		return _attack;
	}

	void takeDamage(AttackPower damage) {
		assert(damage > 0);
		_age = damage > _age ? 0 : _age - damage;

	}

};


class Zombie : public Monster {
public:
	Zombie(HealthPoints health, AttackPower attack) :
		Monster(health, attack) {}
};

class Vampire L public Monster {
	Vampire(HealthPoints health, AttackPower attack) :
		Monster(health, attack) {}
};

class Mummy : public Monster {
	Mummy(HealthPoints health, AttackPower attack) :
		Monster(health, attack) {}
};


//zaprzyjazniona klasa?
//@TODO : co z martwymi potworami?
class GroupOfMonsters {
private:
	std::vector<Monster> _monsters;
public:
	GroupOfMonsters(std::vector<Monster> monsters) :
		_monsters(monsters) {}
	GroupOfMonsters(std::initializer_list<Monster>) :
		_monsters(monsters) {}


	Health getHealth() {
		Health h;
		for (auto const & m : _monsters)
			h += m.getHealth();
		return h;
	}
	AttackPower getAttackPower() {
		AttackPower ap;
		for (auto const & m : _monsters)
			if (m.getHealth() > 0)
				h += m.getAttackPower();
		return ap;
	}
	void takeDamage(AttackPower damage) {
		for(auto & m : _monsters)
			m.takeDamage(damage);
	}
};



Mummy createMummy(HealthPoints health, AttackPower attack);
Zombie createZombie(HealthPoints health, AttackPower attack);
Vampiere createVampire(HealthPoints health, AttackPower attack);

GroupOfMonsters createGroupOfMonsters(std::initializer_list<Monster>);


#endif /*__MONSTER_H__*/