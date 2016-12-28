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
	Time(int t0, int t1) : _time(t0), _maxTime(t1) {}
public:
	// virtual czy nie?
	void tick(int t) {
		_time += t;
		_time %= _maxTime;
	}
	virtual bool attackTime() = 0;
};

// Wystarczy stworzyc nowa klase dziedziczaca po Time,
// aby ustalic inna strategie ataku potworow
class OurTime : public Time {
public:
	OurTime(int t0, int t1) : Time(t0, t1) {}
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

	SmallTown() {}

public:
	Status getStatus();
	
	void tick(int timeStep) {
		assert(timeStep >= 0);
		if(_time->attackTime()) {
			//@TODO: zasymuluj atak potworow na mieszkancow
		}
		_time->tick(timeStep);
	}

};



#endif /*__SMALLTOWN_H__*/