#include "../citizen.h"
#include <cassert>

int main()
{
	// Age powinno byc <= 100, a nie 101
	auto sheriff = createSheriff(100, 101, 60);
}
