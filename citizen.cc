#include "citizen.h"


std::shared_ptr<Adult> createAdult(HealthPoints health, Age age){
	return std::make_shared<Adult>(health, age);
}

std::shared_ptr<Teenager> createTeenager(HealthPoints health, Age age) {
	return std::make_shared<Teenager>(health, age);
}

std::shared_ptr<Sheriff> createSheriff(HealthPoints health, Age age, AttackPower attack) {
	return std::make_shared<Sheriff>(health, age, attack);
}
