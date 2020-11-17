#include "handler.h"
#include <cstring>

void Handler::handle() {
	std::string input;
	printOptions();

	while (getline(std::cin, input)) {
		if (std::stoi(input) == 0) {
			std::cout << "Termination request registered!" << std::endl;
			std::cout << "OK\n";
			break;
		}

		switch (std::stoi(input)) {
		case 1:
			inputOne();
			break;
		case 2:
			inputTwo();
			break;
		case 3:
			inputThree();
			break;
		case 4:
			inputFour();
			break;
		case 5:
			inputFive();
			break;
		case 6:
			inputSix();
			break;
		case 7:
			inputSeven();
			break;
		default:
			inputWrong();
			break;
		}
		printOptions();
	}
}

void Handler::printOptions() const {
	std::cout << "--------------------------\n"
	          << "0. End program\n"
	          << "1. Add room\n"
	          << "2. Add course\n"
	          << "3. Add reservation\n"
	          << "4. Print all rooms\n"
	          << "5. Print all courses\n"
	          << "6. Print all reservations\n"
	          << "7. Print rooms' occupation" << std::endl;
}

void Handler::inputOne() {
	std::string roomName;
	std::cout << "Room name:" << std::endl;
	getInputString(roomName, "Room name cannot be empty.", "Room name:");

	if (reservationSystem.addRoom(roomName)) {
		std::cout << "OK\n";
	} else {
		std::cerr << "Room of that name already exists." << std::endl;
	}
}

void Handler::inputTwo() {
	std::string courseCode;
	std::string teacherName;
	std::cout << "Course code:" << std::endl;
	getInputString(courseCode, "Course code cannot be empty.", "Course code:");

	std::cout << "Teacher:" << std::endl;
	getline(std::cin, teacherName);

	if (reservationSystem.addCourse(courseCode, teacherName)) {
		std::cout << "OK\n";
	} else {
		std::cerr << "Course with that code already exists." << std::endl;
	}
}

void Handler::inputThree() {
	std::string courseCode;
	std::string roomName;
	std::string yesNo;
	std::string duration;
	std::string start;
	std::string end;

	std::cout << "Course code:" << std::endl;
	getInputString(courseCode, "Course code cannot be empty.", "Course code:");

	std::cout << "Duration only? (yes/no): " << std::endl;
	getline(std::cin, yesNo);

	while ((yesNo != "yes" && yesNo != "no")) { // Empty input
		std::cerr << "Bad yes/no input" << std::endl;
		std::cout << "Duration only? (yes/no): " << std::endl;
		getline(std::cin, yesNo);
	}

	if (yesNo == "yes") {
		std::cout << "Duration:" << std::endl;
		getInputNumber(duration);

		if (isdigit(duration[0])) {
			if (reservationSystem.makeAnyReservation(courseCode, stoi(duration))) {
				std::cout << "OK\n";
			} else {
				std::cerr << "Reservation failed" << std::endl;
			}
		} else {
			std::cerr << "Bad digit input" << std::endl;
		}
	} else { // if answer is NO
		std::cout << "Room name:" << std::endl;
		getInputString(roomName, "Room name cannot be empty.", "Room name:");

		std::cout << "Starting time:" << std::endl;
		getInputNumber(start);

		std::cout << "Finishing time:" << std::endl;
		getInputNumber(end);

		if (isdigit(start[0]) && isdigit(end[0])) {
			int from = stoi(start);
			int to = stoi(end);
			if (reservationSystem.makeReservation(courseCode, roomName, from, to)) {
				std::cout << "OK\n";
			} else {
				std::cerr << "Reservation failed" << std::endl;
			}
		} else {
			std::cerr << "Bad digit input";
		}
	}
}

void Handler::inputFour() const {
	std::cout << "Rooms:" << std::endl;
	for (const auto &r : reservationSystem.getRooms()) {
		r.print();
	}
	std::cout << "OK\n";
}

void Handler::inputFive() const {
	std::cout << "Courses:" << std::endl;
	for (const auto &c : reservationSystem.getCourses()) {
		c.print();
	}
	std::cout << "OK\n";
}

void Handler::inputSix() const {
	std::cout << "Reservations:" << std::endl;
	for (const auto &r : reservationSystem.getReservations()) {
		r.print();
	}
	std::cout << "OK\n";
}

void Handler::inputSeven() const {
	std::string roomName;

	std::cout << "Room name:" << std::endl;
	getInputString(roomName, "Room name cannot be empty.", "Room name:");

	if (reservationSystem.hasRoom(roomName)) {
		reservationSystem.getRoom(roomName).schedule();
		std::cout << "OK\n";
	} else {
		std::cerr << "Room does not exists!" << std::endl;
	}
}

void Handler::inputWrong() const {
	std::cerr << "Wrong action; try again." << std::endl;
}

void Handler::getInputString(std::string &input, const char *errorMsg,
    const char *coutMsg) const {
	getline(std::cin, input);

	while (input.empty()) {
		std::cerr << errorMsg << std::endl;
		std::cout << coutMsg << std::endl;
		getline(std::cin, input);
	}
}

void Handler::getInputNumber(std::string &input) const {
	getline(std::cin, input);

	while (input.empty()) { // Empty input
		getline(std::cin, input);
	}
}