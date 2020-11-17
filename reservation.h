#pragma once
#include <iostream>
#include <vector>

class Reservation {

public:
	const std::string room_name;
	const std::string course_code;
	const int start_time;
	const int end_time;
	Reservation(const std::string& r, const std::string& c, int start, int end)
	    : room_name(r)
	    , course_code(c)
	    , start_time(start)
	    , end_time(end){};

	void print() const {
		std::cout << "Reservation for Course " << course_code << " in Room " << room_name << " [" << start_time << "-" << end_time << "]\n";
	}
};