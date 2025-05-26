#pragma once
#include <vector>
#include <algorithm>

/// defining the Observer and Subject classes for the Observer design pattern

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
		observers.push_back(obs);		///add an observer to the list
	}

	void notify(int score)
	{
		for (auto obs : observers)		/// iterate through all observers and call their update method
			obs->update(score);
	}
};
