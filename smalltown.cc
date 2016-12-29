#include "smalltown.h"
#include <memory>


/**
 * Time
 */

// virtual czy nie?
void Time::tick(int t) {
	_time += t;
	_time %= _maxTime;
}

void Time::setStartTime(int t0) {
	assert(t0 >= 0);
	_time = t0;
}

void Time::setMaxTime(int t1) {
	assert(t1 >= 0);
	_maxTime = t1;
}

/**
 * TownTime
 */

bool TownTime::isAttackTime() {
	return ((_time % 3 == 0) || (_time % 13 == 0)) && (_time % 7 != 0);
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
//@TODO : cos tu jest syfiascie jesli chodiz o wzorzec strategia
SmallTown::SmallTown() : _time(std::make_shared<TownTime>()) {}


void SmallTown::tick(int timeStep) {
	assert(timeStep >= 0);
	if (_time->isAttackTime()) {
		//@TODO: zasymuluj atak potworow na mieszkancow
	}
	_time->tick(timeStep);

}




SmallTown::Builder::Builder() : _town(std::make_shared<SmallTown>()) {}

SmallTown::Builder & SmallTown::Builder::startTime(int t0) {
	assert(_town->_time);
	_town->_time->setStartTime(t0);
	return *this;
}

SmallTown::Builder & SmallTown::Builder::maxTime(int t1) {
	_town->_time->setMaxTime(t1);
	return *this;
}

SmallTown::Builder & SmallTown::Builder::citizen(std::shared_ptr<Citizen> c) {
	_town->_citizens.push_back(c);
	return *this;
}


SmallTown SmallTown::Builder::build() {
	return *_town;
}






