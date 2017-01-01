#include "../smalltown.h"
#include <iostream>
#include <cassert>

using namespace std;


int main() {
	auto groupOfMonsters = createGroupOfMonsters({
			createMummy(90, 1),
			createZombie(20, 1)
	});

	auto smallTown = SmallTown::Builder()
		.monster(groupOfMonsters)
		.startTime(3)
		.maxTime(27)
		.citizen(createSheriff(100, 35, 20))
		.citizen(createAdult(100, 21))
		.citizen(createTeenager(50, 14))
		.build();

	auto singleMonster = createVampire(30, 1);

	auto spookyTown = SmallTown::Builder()
		.monster(singleMonster)
		.startTime(3)
		.maxTime(27)
		.citizen(createSheriff(100, 35, 20))
		.build();
}
