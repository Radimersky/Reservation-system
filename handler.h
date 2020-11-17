#pragma once
#include "rsystem.h"

class Handler {
private:
	void printOptions() const;
	ReservationSystem reservationSystem;
	void inputOne();
	void inputTwo();
	void inputThree();
	void inputFour() const;
	void inputFive() const;
	void inputSix() const;
	void inputSeven() const;
	void inputWrong() const;
	void getInputString(std::string &input, const char *errorMsg, const char *coutMsg) const;
	void getInputNumber(std::string &input) const;

public:
	void handle();
};
