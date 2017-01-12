#include "../smalltown.h"
#include "../citizen.h"

int main()
{
	auto sheriff = createSheriff(50, 50, 100);

	auto town = SmallTown::Builder()
		.monster(createZombie(15, 30))
		.startTime(3)
		.maxTime(27)
		// Make sure we don't duplicate the same citizen
		.citizen(sheriff)
		.citizen(sheriff)
		.citizen(sheriff)
		.build();

	auto status = town.getStatus();

	assert(status.getAliveCitizens() == 1);

	return 0;
}
