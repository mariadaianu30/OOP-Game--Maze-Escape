#pragma once
#include <vector>
#include <algorithm>

class Observer {
public:
	virtual void update(int score) = 0;
	virtual ~Observer() = default;
};

class Subject {
protected:
	std::vector<Observer*> observers;

public:
	void attach(Observer* obs)
	{
		observers.push_back(obs);
	}

	void notify(int score)
	{
		for (auto obs : observers)
			obs->update(score);
	}
};
