#ifndef __SMALLTOWN_H__
#define __SMALLTOWN_H__

#include "helper.h"
#include "monster.h"
#include "citizen.h"
#include <string>
#include <memory>


// Wzorzec strategia
class Clock {
protected:
	std::unique_ptr<Time> _time;
	std::unique_ptr<Time> _maxTime;
public:
	virtual ~Clock() = default;

	void tick(const Time&);
	void setStartTime(const Time&);
	const Time* getStartTime() const;
	void setMaxTime(const Time&);
	const Time* getMaxTime() const;
	virtual bool isAttackTime() const = 0;
};

// Wystarczy stworzyc nowa klase dziedziczaca po Clock,
// aby ustalic inna strategie ataku potworow
class TownClock : public Clock {
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
	const std::string & getMonsterName() const;
	HealthPoints getMonsterHealth() const;
	unsigned int getAliveCitizens() const;
};



class SmallTown {
private:
	std::shared_ptr<Clock> _clock;
	std::vector<std::shared_ptr<Citizen>> _citizens;
	std::shared_ptr<Monster> _monster;
public:
	SmallTown();
	Status getStatus() const;
	void tick(Time timeStep);

	const char* getOutcome() const;

	class Builder;
};

class SmallTown::Builder {
private:
	SmallTown _town;
public:
	Builder();
	Builder & monster(std::shared_ptr<Monster>);
	Builder & startTime(Time);
	Builder & maxTime(Time);
	Builder & citizen(std::shared_ptr<Citizen>);
	SmallTown build();
};

#endif /*__SMALLTOWN_H__*/
