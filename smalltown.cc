#include "smalltown.h"
#include <memory>
#include <cassert>
#include <algorithm>

/**
 * Clock
 */
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

const std::string & Status::getMonsterName() const {
	return _monsterName;
}
HealthPoints Status::getMonsterHealth() const {
	return _monsterHealth;
}
unsigned int Status::getAliveCitizens() const {
	return _aliveCitizens;
}


/**
 * SmallTown
 */
SmallTown::SmallTown() : _clock(std::make_shared<TownClock>()) {}

void SmallTown::tick(Time timeStep) {
	assert(timeStep >= 0);

	if (const char* outcome = getOutcome())
		printf("%s\n", outcome);
	else {
		if (_clock->isAttackTime()) {
			for (auto& citizen : _citizens)
				_monster->attack(*citizen);
		}
	}

	_clock->tick(timeStep);
}

Status SmallTown::getStatus() const {
	unsigned int aliveCitizens = std::count_if(_citizens.begin(), _citizens.end(),
			[](const std::shared_ptr<Citizen>& c) { return c->getHealth() > 0; });

	return Status(_monster->getName(), _monster->getHealth(), aliveCitizens);
}

const char* SmallTown::getOutcome() const {
	const auto& status = getStatus();

	if (status.getMonsterHealth() > 0 && status.getAliveCitizens() > 0)
		return nullptr;
	else if (status.getMonsterHealth() > 0)
		return "MONSTER WON";
	else if (status.getAliveCitizens() > 0)
		return "CITIZENS WON";
	else
		return "DRAW";
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
	const auto it = std::find_if(_town._citizens.begin(), _town._citizens.end(),
			[&c](const decltype(_town._citizens)::value_type& elem) { return elem.get() == c.get(); });

	if (it == _town._citizens.end()) // Make sure we don't duplicate citizens
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

	return _town;
}

