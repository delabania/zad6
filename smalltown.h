#ifndef __SMALLTOWN_H__
#define __SMALLTOWN_H__

#include "helper.h"
#include "monster.h"
#include "citizen.h"
#include <string>
#include <memory>
#include <cassert>


// Wzorzec strategia
class Time {
protected:
	unsigned int _time;
	unsigned int _maxTime;
	Time(int t0 = 0, int t1 = 0) : _time(t0), _maxTime(t1) {}
public:
	// virtual czy nie?
	void tick(int t) {
		_time += t;
		_time %= _maxTime;
	}

	void setStartTime(int t0) {
		assert(t0 >= 0);
		_time = t0;
	}

	void setMaxTime(int t1) {
		assert(t1 >= 0);
		_maxTime = t1;
	}

	virtual bool attackTime() = 0;
};

// Wystarczy stworzyc nowa klase dziedziczaca po Time,
// aby ustalic inna strategie ataku potworow
class TownTime : public Time {
public:
	TownTime(int t0 = 0, int t1 = 0) : Time(t0, t1) {}
	bool attackTime() {
		return ((_time % 3 == 0) || (_time % 13 == 0)) && (_time % 7 != 0);
	}
};


// Pomocnicza klasa do metody getStatus
class Status {
private:
	std::string _monsterName;
	HealthPoints _monsterHealth;
	unsigned int _aliveCitizens;
public:
	Status(std::string monsterName, HealthPoints monsterHealth,
	       unsigned int aliveCitizens) :
		_monsterName(monsterName),
		_monsterHealth(monsterHealth),
		_aliveCitizens(aliveCitizens) {}


	std::string getMonsterName() {
		return _monsterName;
	}
	HealthPoints getMonsterHealth() {
		return _monsterHealth;
	}
	unsigned int getAliveCitizens() {
		return _aliveCitizens;
	}
};



class SmallTown {
private:
	std::shared_ptr<Time> _time;
	std::vector<std::shared_ptr<Citizen>> _citizens;


public:
	Status getStatus();

	void tick(int timeStep) {
		assert(timeStep >= 0);
		if (_time->attackTime()) {
			//@TODO: zasymuluj atak potworow na mieszkancow
		}
		_time->tick(timeStep);
	}

	class Builder {
	private:
		std::shared_ptr<SmallTown> _town;
	public:
		Builder() : _town(std::make_shared<SmallTown>()) {}
		Builder & monster(std::shared_ptr<GroupOfMonsters>);
		Builder & monster(std::shared_ptr<Monster>);
		Builder & startTime(int t0) {
			_town->_time->setStartTime(t0);
			return *this;
		}
		Builder & maxTime(int t1) {
			_town->_time->setMaxTime(t1);
			return *this;
		}
		Builder & citizen(std::shared_ptr<Citizen> c) {
			_town->_citizens.push_back(c);
			return *this;
		}
		SmallTown build() {
			return *_town;
		}
	};


};


#endif /*__SMALLTOWN_H__*/