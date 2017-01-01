#ifndef __SMALLTOWN_H__
#define __SMALLTOWN_H__

#include "helper.h"
#include "monster.h"
#include "citizen.h"
#include <string>
#include <memory>


// Wzorzec strategia
class Time {
protected:
	unsigned int _time;
	unsigned int _maxTime;
public:
	void tick(int);
	void setStartTime(int);
	void setMaxTime(int);
	virtual bool isAttackTime() const = 0;
	virtual ~Time() = default;
};

// Wystarczy stworzyc nowa klase dziedziczaca po Time,
// aby ustalic inna strategie ataku potworow
class TownTime : public Time {
public:
	virtual bool isAttackTime() const override;
};


// Pomocnicza klasa do metody getStatus
class Status {
private:
	std::string _monsterName;
	HealthPoints _monsterHealth;
	unsigned int _aliveCitizens;
public:
	Status(const std::string &, HealthPoints, unsigned int);
	const std::string & getMonsterName();
	HealthPoints getMonsterHealth();
	unsigned int getAliveCitizens();
};



class SmallTown {
private:
	std::shared_ptr<Time> _time;
	std::vector<std::shared_ptr<Citizen>> _citizens;
public:
	SmallTown();
	Status getStatus();
	void tick(int timeStep);

	class Builder {
	private:
		std::shared_ptr<SmallTown> _town;
	public:
		Builder();
		Builder & monster(std::shared_ptr<GroupOfMonsters>);
		Builder & monster(std::shared_ptr<Monster>);
		Builder & startTime(int);
		Builder & maxTime(int);
		Builder & citizen(std::shared_ptr<Citizen>);
		SmallTown build();
	};

};


#endif /*__SMALLTOWN_H__*/
