#include "monster.h"

/**
 * Monster
 */
SingleMonster::SingleMonster(HealthPoints health, AttackPower attack) :
	_health(health),
	_attack(attack) {
	assert(attack >= 0);
	assert(health > 0);
}

HealthPoints SingleMonster::getHealth() const {
	return _health;
}

AttackPower SingleMonster::getAttackPower() const {
	return _attack;
}

void SingleMonster::takeDamage(AttackPower damage) {
	assert(damage >= 0);
	_health = damage > _health ? 0 : _health - damage;
}

void SingleMonster::attack(Citizen& citizen) {
	citizen.takeDamage(_attack);
	citizen.OnDamagedBy(*this);
}

/**
 * Zombie
 */
Zombie::Zombie(HealthPoints health, AttackPower attack) :
	SingleMonster(health, attack) {}

std::string Zombie::getName() const {
	return "Zombie";
}

/**
 * Vampire
 */
Vampire::Vampire(HealthPoints health, AttackPower attack) :
	SingleMonster(health, attack) {}

std::string Vampire::getName() const {
	return "Vampire";
}

/**
 * Mummy
 */
Mummy::Mummy(HealthPoints health, AttackPower attack) :
	SingleMonster(health, attack) {}

std::string Mummy::getName() const {
	return "Mummy";
}

/**
 * GroupOfMonsters
 */

HealthPoints GroupOfMonsters::getHealth() const {
	HealthPoints h = 0;
	for (auto const & m : _monsters)
		h += m->getHealth();
	return h;
}
AttackPower GroupOfMonsters::getAttackPower() const {
	AttackPower ap = 0;
	for (auto const & m : _monsters)
		if (m->getHealth() > 0)
			ap += m->getAttackPower();
	return ap;
}
void GroupOfMonsters::takeDamage(AttackPower damage) {
	for (auto & m : _monsters)
		m->takeDamage(damage);
}

void GroupOfMonsters::attack(Citizen& citizen) {
	citizen.takeDamage(getAttackPower());
	citizen.OnDamagedBy(*this);
}


std::string GroupOfMonsters::getName() const {
	return "GroupOfMonsters";
}


/**
 * Funkcje fabrykujace
 */
std::shared_ptr<Mummy> createMummy(HealthPoints health, AttackPower attack) {
	return std::make_shared<Mummy>(health, attack);
}
std::shared_ptr<Zombie> createZombie(HealthPoints health, AttackPower attack) {
	return std::make_shared<Zombie>(health, attack);
}
std::shared_ptr<Vampire> createVampire(HealthPoints health, AttackPower attack) {
	return std::make_shared<Vampire>(health, attack);
}
std::shared_ptr<GroupOfMonsters> createGroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> monsters) {
	return std::make_shared<GroupOfMonsters>(monsters);
}

