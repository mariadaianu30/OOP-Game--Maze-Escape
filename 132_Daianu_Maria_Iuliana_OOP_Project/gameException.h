#pragma once
#include<iostream>
#include <exception>
#include <string>


class GameException : public std::exception {
protected:
	std::string msg;
public:
	explicit GameException(const std::string& message) : msg(message) {}
	virtual const char* what() const noexcept override {
		return msg.c_str();
	}
};