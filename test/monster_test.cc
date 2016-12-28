#include "../monster.h"
#include <iostream>
#include <cassert>

using namespace std;


int main() {
	Zombie z(10, 50);
	Vampire v(10, 200);
	assert(z.getHealth() == 10);
	assert(v.getAttackPower() == 200);


	auto m = createMummy(90, 1);

	assert(m->getHealth() == 90);
	assert(m->getAttackPower() == 1);

	auto group = GroupOfMonsters({m});
	auto groupOfMonsters = createGroupOfMonsters({
		createMummy(90, 1),
		createZombie(20, 1),
		createVampire(30, 1)
	});

	assert(groupOfMonsters->getHealth() == 140);
	assert(groupOfMonsters->getAttackPower() == 3);

}