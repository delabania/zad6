#include "smalltown.h"
#include <memory>
#include <cassert>
#include <algorithm>

/**
 * Clock
 */

// TODO: Trzymanie klasy zarzadzajacej czasem ma sens i poprawnie rozdziela
// obowiazki, natomiast nie wiem czy nie prosciej trzymac 2 pointery na biez./maks.
// czas (inaczej duzo funkcjonalnosci sie duplikuje + de facto nie pozwalamy na razie
// uzytkownikom na zewnetrzna zmiane strategii, mozemy tylko zmienic startTime i maxTime
void Clock::tick(const Time& t) {
	const Time& maxTime = *_maxTime.get();
	Time& time = *_time.get();

	time = (time + t) % maxTime;
}

void Clock::setStartTime(const Time& t0) {
	assert(t0 >= 0);

	_time = std::make_unique<Time>(t0);
}

const Time* Clock::getStartTime() const {
	return _time.get();

}

void Clock::setMaxTime(const Time& t1) {
	assert(t1 >= 0);

	_maxTime = std::make_unique<Time>(t1);
}

const Time* Clock::getMaxTime() const {
	return _maxTime.get();
}

/**
 * TownClock
 */

bool TownClock::isAttackTime() const {
	const Time& time = *_time.get();

	return ((time % 3 == 0) || (time % 13 == 0)) && (time % 7 != 0);
}


/**
 * Status
 */

Status::Status(const std::string & monsterName, HealthPoints monsterHealth,
               unsigned int aliveCitizens) :
	_monsterName(monsterName),
	_monsterHealth(monsterHealth),
	_aliveCitizens(aliveCitizens) {}

const std::string & Status::getMonsterName() {
	return _monsterName;
}
HealthPoints Status::getMonsterHealth() {
	return _monsterHealth;
}
unsigned int Status::getAliveCitizens() {
	return _aliveCitizens;
}


/**
 * SmallTown
 */
//@TODO : czy to na pewno jest "ladnie"?
SmallTown::SmallTown() : _clock(std::make_unique<TownClock>()) {}

void SmallTown::tick(Time timeStep) {
	assert(timeStep >= 0);

	if (_clock->isAttackTime()) {
		//@TODO: zasymuluj atak potworow na mieszkancow
	}
	_clock->tick(timeStep);

}

Status SmallTown::getStatus() {
	unsigned int aliveCitizens = std::count_if(_citizens.begin(), _citizens.end(),
			[](const std::shared_ptr<Citizen>& c) { return c->getHealth() > 0; });

	return Status(_monster->getName(), _monster->getHealth(), aliveCitizens);
}


SmallTown::Builder::Builder() : _town() {}

SmallTown::Builder & SmallTown::Builder::startTime(Time t0) {
	assert(_town._clock);
	_town._clock->setStartTime(t0);
	return *this;
}

SmallTown::Builder & SmallTown::Builder::maxTime(Time t1) {
	_town._clock->setMaxTime(t1);
	return *this;
}

SmallTown::Builder & SmallTown::Builder::citizen(std::shared_ptr<Citizen> c) {
	_town._citizens.push_back(c);
	return *this;
}

SmallTown::Builder & SmallTown::Builder::monster(std::shared_ptr<Monster> m) {
	_town._monster = m;
	return *this;
}


SmallTown SmallTown::Builder::build() {
	assert(_town._monster.get());
	assert(_town._clock->getStartTime() && _town._clock->getMaxTime());
	assert(_town._citizens.empty() == false);

	return std::move(_town);
}

