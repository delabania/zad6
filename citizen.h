#ifndef __CITIZEN_H__
#define __CITIZEN_H__

#include "helper.h"
#include <cassert>


class Citizen {
protected:
	HealthPoints _health;
	Age _age;

	Citizen(HealthPoints health, Age age) :
		_health(health), _age(age) {}

public :
	HealthPoints getHealth() const {
		return _health;
	}

	Age getAge() const {
		return _age;
	}

	void takeDamage(AttackPower damage) {
		assert(damage > 0);
		_age = damage > _age ? 0 : _age - damage;
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
	Teenager(HealthPoints health, Age age)
	Citizen(health, age) {
		assert(11 <= age && age <= 17);
	}

}

class Sheriff : public Citizen {
private:
	AttackPower _attack;
public:
	AttackPower getAttackPower() const {
		return _attack;
	}

}

Adult createAdult(HealthPoints health, Age age);
Teenanger createTeenager(HealthPoints health, Age age);
Sheriff createSheriff(HealthPoints health, Age age, AttackPower _attack);


#endif /* __CITIZEN_H__ */