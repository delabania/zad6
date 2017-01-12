#include "../smalltown.h"
#include "../citizen.h"
#include "../monster.h"

int main()
{
	// hp, age, atak

	// hp, atak
	auto mummy = createMummy(1, 1);
	auto zombie = createZombie(1000, 5);
	auto monster = createGroupOfMonsters({
			mummy,
			zombie});

	std::vector<std::shared_ptr<Citizen>> vec {
		createAdult(10, 23),
		createSheriff(100, 33, 10),
		createAdult(100, 25),
		createAdult(100, 24),
		createAdult(10, 23)};

	auto town = SmallTown::Builder()
		.monster(monster)
		.startTime(3) // Attack time initially
		.maxTime(10)
		.citizen(vec[0])
		.citizen(vec[1])
		.citizen(vec[2])
		.citizen(vec[3])
		.build();

	assert(monster->getAttackPower() == 6);

	town.tick(1);

	assert(monster->getAttackPower() == 5);

	assert(vec[0]->getHealth() == 10 - 6); // Attacked by 2 monsters
	assert(vec[1]->getHealth() == 100 - 6); // Attacked by 2 monsters
	assert(mummy->getHealth() <= 0); // Mummy killed by Sheriff, shouldn't damage citizens anymore
	assert(zombie->getHealth() > 0);
	assert(vec[2]->getHealth() == 100 - 5);

	return 0;
}
