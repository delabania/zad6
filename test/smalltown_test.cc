#include "../smalltown.h"
#include <iostream>
#include <cassert>

using namespace std;


int main() {
	auto smallTown = SmallTown::Builder()
	                 .startTime(3)
	                 .maxTime(27)
	                 .citizen(createSheriff(100, 35, 20))
	                 .citizen(createAdult(100, 21))
	                 .citizen(createTeenager(50, 14))
	                 .build();

	cout << smallTown.function() << endl;             
}