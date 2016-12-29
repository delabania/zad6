#include "monster.h"

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

