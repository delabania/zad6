#include "../citizen.h"
#include <cassert>

int main()
{
	auto sheriff = createSheriff(100, 25, 60);

	assert(sheriff.get() != nullptr);
	assert(sheriff->getHealth() == 100);
	assert(sheriff->getAge() == 25);
	assert(sheriff->getAttackPower() == 60);
}
