#pragma once

#include "course.h"
#include "reservation.h"
#include "room.h"

class ReservationSystem {

private:
	std::vector<Room> room;
	std::vector<Course> course;
	std::vector<Reservation> reservation;

	Room& getRoomNonConst(const std::string& name) {
		for (auto& r : room) {
			if (r.name == name) {
				return r;
			}
		}
		throw std::runtime_error("Room not found.");
	}

public:
	bool hasRoom(const std::string& name) const {
		for (const auto& r : room) {
			if (r.name == name) {
				return true;
			}
		}
		return false;
	}

	bool addRoom(const std::string& name) {
		if (!hasRoom(name)) {
			room.emplace_back(name);
			return true;
		}
		return false;
	}

	const Room& getRoom(const std::string& name) const {
		for (const auto& r : room) {
			if (r.name == name) {
				return r;
			}
		}
		throw std::runtime_error("Room not found.");
	}

	bool hasCourse(const std::string& code) const {
		for (const auto& c : course) {
			if (c.code == code) {
				return true;
			}
		}
		return false;
	}

	bool addCourse(const std::string& code, const std::string& teacher) {
		if (!hasCourse(code)) {
			course.emplace_back(code, teacher);
			return true;
		}
		return false;
	}

	const Course& getCourse(const std::string& code) const {
		for (const auto& c : course) {
			if (c.code == code) {
				return c;
			}
		}
		throw std::runtime_error("Course not found.");
	}

	const std::vector<Room>& getRooms() const {
		return room;
	}

	const std::vector<Course>& getCourses() const {
		return course;
	}

	const std::vector<Reservation>& getReservations() const {
		return reservation;
	}

	bool makeAnyReservation(const std::string& course_code, int duration) {
		if (hasCourse(course_code)) {
			int startTime;
			for (auto& r : room) {
				if ((startTime = r.isFreeFor(duration)) != -1 && r.occupy(startTime, startTime + duration)) {
					reservation.emplace_back(r.name, course_code, startTime, startTime + duration);
					return true;
				}
			}
		}

		return false;
	}

	bool makeReservation(const std::string& course_code, const std::string& room_name, int from, int to) {
		if (hasCourse(course_code) && hasRoom(room_name)) {
			Room& refRoom = getRoomNonConst(room_name);
			if (refRoom.occupy(from, to)) {
				reservation.emplace_back(room_name, course_code, from, to);
				return true;
			}
		}

		return false;
	}
};
