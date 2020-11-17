#pragma once
#include <iostream>
#include <vector>

class Room {
public:
	const std::string name;
	Room(const std::string& n)
	    : name(n)
	    , reservation(24, false){};

	bool isFree(int from, int to) const {
		if ((!isInRange(from) || !isInRange(to)) || to <= from) {
			return false;
		}

		for (int i = from; i < to; ++i) {
			if (reservation[i]) {
				return false;
			}
		}
		return true;
	}

	int isFreeFor(int duration) const {
		if (!isInRange(duration)) {
			return -1;
		}

		for (int i = 0; i < 25 - duration; ++i) {
			for (int j = 0; j < duration; ++j) {
				if (reservation[i + j]) { // If is reserved
					i += j;
					break;
				} else if (j == duration - 1) { // If every hour in duration is not reserved
					return i;
				}
			}
		}
		return -1;
	}

	bool occupy(int from, int to) {
		//Correct from-to range is tested in "isFree" function
		if (!isFree(from, to)) {
			return false;
		}

		for (int i = from; i < to; ++i) {
			reservation[i] = true;
		}
		return true;
	}

	void print() const {
		std::cout << "Room: " << name << "\n";
	}

	void schedule() const {
		for (int i = 0; i < 24; ++i) {
			if (reservation[i]) {
				std::cout << "X";
			} else {
				std::cout << "_";
			}
		}
		std::cout << "\n";
	}

private:
	std::vector<bool> reservation;

	bool isInRange(int i) const {
		return i >= 0 && i <= 24;
	}
};
