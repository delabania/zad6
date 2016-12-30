#include "monster.h"

/**
 * Monster
 */
Monster::Monster(HealthPoints health, AttackPower attack) :
	_health(health),
	_attack(attack) {
	assert(attack >= 0);
	assert(health > 0);
}

HealthPoints Monster::getHealth() const {
	return _health;
}

AttackPower Monster::getAttackPower() const {
	return _attack;
}

void Monster::takeDamage(AttackPower damage) {
	assert(damage > 0);
	_health = damage > _health ? 0 : _health - damage;
}



/**
 * Zombie
 */
Zombie::Zombie(HealthPoints health, AttackPower attack) :
	Monster(health, attack) {}


/**
 * Vampire
 */
Vampire::Vampire(HealthPoints health, AttackPower attack) :
	Monster(health, attack) {}


/**
 * Mummy
 */
Mummy::Mummy(HealthPoints health, AttackPower attack) :
	Monster(health, attack) {}

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

