#include "citizen.h"
#include <cassert>


/**
 * Citizen
 */

Citizen::Citizen(HealthPoints health, Age age) :
	_health(health), _age(age) {
	assert(health > 0);
}


HealthPoints Citizen::getHealth() const {
	return _health;
}

Age Citizen::getAge() const {
	return _age;
}

void Citizen::takeDamage(AttackPower damage) {
	assert(damage > 0);
	_health = damage > _health ? 0 : _health - damage;
}

void Citizen::OnDamagedBy(Monster&) {
}

/**
 * Adult
 */
Adult::Adult (HealthPoints health, Age age) :
	Citizen(health, age) {
	assert(18 <= age && age <= 100);
}


/**
 * Teenager
 */
Teenager::Teenager(HealthPoints health, Age age) :
	Citizen(health, age) {
	assert(11 <= age && age <= 17);
}


/**
 * Sheriff
 */
Sheriff::Sheriff(HealthPoints health, Age age, AttackPower attack) :
	Citizen(health, age), _attack(attack) {
	assert(18 <= age && age <= 100);
	assert(attack >= 0);
}

Sheriff::~Sheriff() {
}

AttackPower Sheriff::getAttackPower() const {
	return _attack;
}

void Sheriff::OnDamagedBy(Monster& monster) {
	monster.takeDamage(_attack);
}

/**
 * Funkcje fabrykujace
 */


std::shared_ptr<Adult> createAdult(HealthPoints health, Age age) {
	return std::make_shared<Adult>(health, age);
}

std::shared_ptr<Teenager> createTeenager(HealthPoints health, Age age) {
	return std::make_shared<Teenager>(health, age);
}

std::shared_ptr<Sheriff> createSheriff(HealthPoints health, Age age, AttackPower attack) {
	return std::make_shared<Sheriff>(health, age, attack);
}
