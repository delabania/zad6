#include "../citizen.h"
#include <iostream>
#include <cassert>

using namespace std;


int main() {
	Adult a(50, 20);
	Teenager t(30, 15);

	assert(a.getAge() == 20);
	assert(t.getHealth() == 30);
}
