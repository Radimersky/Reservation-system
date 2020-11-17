#pragma once

#include <iostream>

class Course {

public:
	const std::string code;
	const std::string teacher;
	Course(const std::string& c, const std::string& t)
	    : code(c)
	    , teacher(t){};

	void print() const {
		std::cout << "Course: " << code;
		if (!teacher.empty()) {
			std::cout << " [Teacher: " << teacher << "]";
		}
		std::cout << "\n";
	}
};
