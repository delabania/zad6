#ifndef __CITIZEN_H__
#define __CITIZEN_H__

#include "helper.h"
#include <memory>
#include <cassert>


class Citizen {
protected:
	HealthPoints _health;
	Age _age;

	Citizen(HealthPoints health, Age age) :
		_health(health), _age(age) {
		assert(health > 0);
	}

public :
	HealthPoints getHealth() const {
		return _health;
	}

	Age getAge() const {
		return _age;
	}

	void takeDamage(AttackPower damage) {
		assert(damage > 0);
		_health = damage > _health ? 0 : _health - damage;
	}
};

class Adult : public Citizen {
public:
	Adult (HealthPoints health, Age age) :
		Citizen(health, age) {
		assert(18 <= age && age <= 100);
	}
};

class Teenager : public Citizen {
public:
	Teenager(HealthPoints health, Age age) :
		Citizen(health, age) {
		assert(11 <= age && age <= 17);
	}

};

class Sheriff : public Citizen {
private:
	AttackPower _attack;
public:
	Sheriff(HealthPoints health, Age age, AttackPower attack) :
		Citizen(health, age) {
		assert(18 <= age && age <= 100);
		assert(attack >= 0);
	}

	AttackPower getAttackPower() const {
		return _attack;
	}

};


std::shared_ptr<Adult> createAdult(HealthPoints health, Age age);
std::shared_ptr<Teenager> createTeenager(HealthPoints health, Age age);
std::shared_ptr<Sheriff> createSheriff(HealthPoints health, Age age, AttackPower attack);

#endif /* __CITIZEN_H__ */