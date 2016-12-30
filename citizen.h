#ifndef __CITIZEN_H__
#define __CITIZEN_H__

#include "helper.h"
#include <memory>


class Citizen {
protected:
	HealthPoints _health;
	Age _age;
	Citizen(HealthPoints, Age);

public :
	HealthPoints getHealth() const;
	Age getAge() const;
	void takeDamage(AttackPower);
	virtual ~Citizen() = default;
};

class Adult : public Citizen {
public:
	Adult(HealthPoints, Age);
};

class Teenager : public Citizen {
public:
	Teenager(HealthPoints, Age);
};

class Sheriff : public Citizen {
private:
	AttackPower _attack;
public:
	Sheriff(HealthPoints, Age, AttackPower);
	AttackPower getAttackPower() const;
};


std::shared_ptr<Adult> createAdult(HealthPoints, Age);
std::shared_ptr<Teenager> createTeenager(HealthPoints, Age);
std::shared_ptr<Sheriff> createSheriff(HealthPoints, Age, AttackPower);

#endif /* __CITIZEN_H__ */